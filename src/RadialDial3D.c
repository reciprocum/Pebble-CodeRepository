/*
   File  : RadialDial3D.c
   Author: Afonso Santos, Portugal

   Last revision: 13h45 August 14 2016
*/

#include "Config.h"
#include "RadialDial2D.h"
#include "RadialDial3D.h"
#include "Matrix34.h"
#include "R3.h"


RadialDial3D*
RadialDial3D_free
( RadialDial3D *this )
{
  if (this != NULL)
  {
    free( Mesh3D_free( this->mesh ) ) ;
    this->mesh = NULL ;
  }

  return this ;
}


void
RadialDial3D_setNull
( RadialDial3D  *this )
{
  if ((this == NULL) || (this->mesh->edgeInfo == NULL))
    return ;    // NOP on NULLs.

  this->value = -1 ;

  const unsigned int  edgesNum    = this->mesh->edgeInfo->edgesNum ;
  ViewFlags          *edgesState  = this->mesh->edgesState ;

  for ( unsigned int me = 0 ; me < edgesNum ; ++me )
    edgesState[me].isDisabled = true ;
}


RadialDial3D*
RadialDial3D_new
( RadialDialType type )
{ 
  RadialDial3D *this = malloc(sizeof(RadialDial3D)) ;
  
  if (this == NULL)
    return NULL ;

  switch (this->type = type)
  {
    case RADIAL_DIAL_TYPE_24:
      if ((this->mesh = Mesh3D_new( 48, RADIAL_DIAL_24_EDGEINFO.edgesNum, 0 )) == NULL)
        return RadialDial3D_free( this ) ;

      this->mesh->edgeInfo = &RADIAL_DIAL_24_EDGEINFO ;
      break ;

    case RADIAL_DIAL_TYPE_60:
      if ((this->mesh = Mesh3D_new( 120, RADIAL_DIAL_60_EDGEINFO.edgesNum, 0 )) == NULL)
        return RadialDial3D_free( this ) ;

      this->mesh->edgeInfo = &RADIAL_DIAL_60_EDGEINFO ;
      break ;

    case RADIAL_DIAL_TYPE_100:
      if ((this->mesh = Mesh3D_new( 200, RADIAL_DIAL_100_EDGEINFO.edgesNum, 0 )) == NULL)
        return RadialDial3D_free( this ) ;

      this->mesh->edgeInfo = &RADIAL_DIAL_100_EDGEINFO ;
      break ;
  }

  RadialDial3D_setNull( this ) ;

  return this ;
}


void
RadialDial3D_config
( RadialDial3D          *this            // MUST contain a pre-allocated mesh.
, const RadialDialShape  shape
, const float            innerRadius
, const float            outerRadius
, const float            rotationX
, const float            rotationY
, const float            rotationZ
, const R3              *anchor3D        // Center of the radial handle
)
{
  if ((this == NULL) || (this->mesh == NULL))
    return ;

  Mesh3D *mesh = this->mesh ;

  Matrix34 transformationMtx ;
  Matrix34_transformation( &transformationMtx, rotationX, rotationY, rotationZ, anchor3D ) ;

  // set & rotate the mesh normal.
  Matrix34_rotate( mesh->normal_worldCoord, &R3_versorMinusZ, &transformationMtx ) ;

  // set & transform the mesh vertices.
  int nRadials = 0 ;

  switch (this->type)
  {
    case RADIAL_DIAL_TYPE_24:
      nRadials = 24 ;
      break ;

    case RADIAL_DIAL_TYPE_60:
      nRadials = 60 ;
      break ;

    case RADIAL_DIAL_TYPE_100:
      nRadials = 100 ;
      break ;
  }

  for ( int iRadial = 0  ;  iRadial < nRadials  ;  ++iRadial )
  {
    const int32_t  angle    = TRIG_MAX_ANGLE * iRadial / nRadials ;
    const uint16_t angleDeg = ((uint16_t)(360 * iRadial)) / nRadials ;
    const float    nX       = ((float)sin_lookup( angle )) / TRIG_MAX_RATIO ;
    const float    nY       = ((float)cos_lookup( angle )) / TRIG_MAX_RATIO ;

    R3 vInner, vOutter ;

    switch (shape)
    {
      case RADIAL_DIAL_SHAPE_CIRCLE :
        R3_set( &vInner , innerRadius * nX, innerRadius * nY, 0.0 ) ;
        R3_set( &vOutter, outerRadius * nX, outerRadius * nY, 0.0 ) ;
        break ;

      case RADIAL_DIAL_SHAPE_SQUARE:
        if (angleDeg > 315  ||  angleDeg <= 45)
        {
          R3_set( &vInner , innerRadius * nX / nY, innerRadius, 0.0 ) ;
          R3_set( &vOutter, outerRadius * nX / nY, outerRadius, 0.0 ) ;
        }
        else if (angleDeg > 45  &&  angleDeg <= 135)
        {
          R3_set( &vInner , innerRadius, innerRadius * nY / nX, 0.0 ) ;
          R3_set( &vOutter, outerRadius, outerRadius * nY / nX, 0.0 ) ;
        }
        else if (angleDeg > 135  &&  angleDeg <= 225)
        {
          R3_set( &vInner ,-innerRadius * nX / nY,-innerRadius, 0.0 ) ;
          R3_set( &vOutter,-outerRadius * nX / nY,-outerRadius, 0.0 ) ;
        }
        else if (angleDeg > 225  &&  angleDeg <= 315)
        {
          R3_set( &vInner ,-innerRadius,-innerRadius * nY / nX, 0.0 ) ;
          R3_set( &vOutter,-outerRadius,-outerRadius * nY / nX, 0.0 ) ;
        }
     
        break ;
    }

    Matrix34_transform( &mesh->vertices[iRadial].worldCoord           , &vInner , &transformationMtx ) ;
    Matrix34_transform( &mesh->vertices[iRadial + nRadials].worldCoord, &vOutter, &transformationMtx ) ;
  }
}


void
RadialDial3D_setValue
( RadialDial3D *this
, const uint8_t value
)
{
  if (this == NULL)
    return ;

  if (value == this->value)
    return ;    // No change.

  this->value = value ;

  ViewFlags *edgesState = this->mesh->edgesState ;
  unsigned int nRadials = 0 ;

  switch (this->type)
  {
    case RADIAL_DIAL_TYPE_24:
      nRadials = 24 ;
      break ;

    case RADIAL_DIAL_TYPE_60:
      nRadials = 60 ;
      break ;

    case RADIAL_DIAL_TYPE_100:
      nRadials = 100 ;
      break ;
  }
  
  const unsigned int innerRingOffset = nRadials ;
  const unsigned int outerRingOffset = nRadials << 1 ;   // 2 * nRadials

  for ( unsigned int iRadial = 0  ;  iRadial < nRadials  ;  ++iRadial )
    edgesState[iRadial].isDisabled                       // The radial edges.
    = edgesState[iRadial + innerRingOffset].isDisabled   // The inner ring edges.
    = edgesState[iRadial + outerRingOffset].isDisabled   // The outer ring edges.
    = (iRadial > value)
    ;
}