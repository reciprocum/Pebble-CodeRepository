/*
   File  : SegmentDisplay3D.c
   Author: Afonso Santos, Portugal

   Last revision: 13h45 August 14 2016
*/

#include "Config.h"
#include "Binary.h"
#include "SegmentDisplay3D.h"
#include "Mesh3D.h"
#include "TransformR3.h"


SegmentDisplay3D*
SegmentDisplay3D_free
( SegmentDisplay3D *this )
{
  if (this != NULL)
  {
    free( Mesh3D_free( this->mesh ) ) ;
    this->mesh = NULL ;
  }

  return this ;
}


void
SegmentDisplay3D_setNull
( SegmentDisplay3D  *this )
{
  if ((this == NULL) || (this->mesh->edgeInfo == NULL))
    return ;    // NOP on NULLs.

  this->value = -1 ;

  const unsigned int  edgesNum    = this->mesh->edgeInfo->edgesNum ;
  ViewFlags          *edgesState  = this->mesh->edgesState ;
  
  for ( unsigned int me = 0 ; me < edgesNum ; ++me )
    edgesState[me].isDisabled = true ;
}


SegmentDisplay3D*
SegmentDisplay3D_new
( SegmentDisplayType typeMax )
{
  SegmentDisplay3D *this = malloc(sizeof(SegmentDisplay3D)) ;
  
  if (this == NULL)
    return NULL ;

  switch (this->type = this->typeMax = typeMax)
  {
    case SEG_N7BONE:
      this->mesh = Mesh3D_new( SEG_N7BONE_VERTEXINFO.pointsNum, SEG_N7BONE_EDGEINFO.edgesNum, 0 ) ;
      break ;

    case SEG_N7SKIN:
      this->mesh = Mesh3D_new( SEG_N7SKIN_VERTEXINFO.pointsNum, SEG_N7SKIN_EDGEINFO.edgesNum, 0 ) ;
      break ;
    
    case SEG_N7BONESKIN:
    case SEG_N7SKINBONE:
      this->mesh = Mesh3D_new( SEG_N7SKINBONE_VERTEXINFO.pointsNum, SEG_N7SKINBONE_EDGEINFO.edgesNum, 0 ) ;
      break ;

    case SEG_NCURVYBONE:
      this->mesh = Mesh3D_new( SEG_NCURVYBONE_VERTEXINFO.pointsNum, SEG_NCURVYBONE_EDGEINFO.edgesNum, 0 ) ;
      break ;

    case SEG_NCURVYSKIN:
      this->mesh = Mesh3D_new( SEG_NCURVYSKIN_VERTEXINFO.pointsNum, SEG_NCURVYSKIN_EDGEINFO.edgesNum, 0 ) ;
      break ;

    case SEG_NCURVYBONESKIN:
    case SEG_NCURVYSKINBONE:
      this->mesh = Mesh3D_new( SEG_NCURVYSKINBONE_VERTEXINFO.pointsNum, SEG_NCURVYSKINBONE_EDGEINFO.edgesNum, 0 ) ;
      break ;
  }

  if (this->mesh == NULL)
    return SegmentDisplay3D_free( this ) ;

  SegmentDisplay3D_setNull( this ) ;

  return this ;
}


void
__refresh_SegmentDisplay3D
( SegmentDisplay3D  *this )
{
  const unsigned char *valueEdgeMapL2R  ;

  switch (this->type)
  {
    case SEG_N7BONE:
      valueEdgeMapL2R = SEG_N7BONE_DIGIT_EDGEMAP_L2R[this->value] ;
      break ;

    case SEG_N7SKIN:
      valueEdgeMapL2R = SEG_N7SKIN_DIGIT_EDGEMAP_L2R[this->value] ;
      break ;

    case SEG_N7BONESKIN:
    case SEG_N7SKINBONE:
      valueEdgeMapL2R = SEG_N7SKINBONE_DIGIT_EDGEMAP_L2R[this->value] ;
      break ;

    case SEG_NCURVYBONE:
      valueEdgeMapL2R = SEG_NCURVYBONE_DIGIT_EDGEMAP_L2R[this->value] ;
      break ;

    case SEG_NCURVYSKIN:
      valueEdgeMapL2R = SEG_NCURVYSKIN_DIGIT_EDGEMAP_L2R[this->value] ;
      break ;

    case SEG_NCURVYBONESKIN:
    case SEG_NCURVYSKINBONE:
      valueEdgeMapL2R = SEG_NCURVYSKINBONE_DIGIT_EDGEMAP_L2R[this->value] ;
      break ;

    default:
      valueEdgeMapL2R = NULL ;
      break ;
  }

  if (valueEdgeMapL2R != NULL)
  {
    const unsigned int  edgesNum   = this->mesh->edgeInfo->edgesNum ;
    ViewFlags          *edgesState = this->mesh->edgesState ;
  
    for ( unsigned int edgeIdx = 0  ;  edgeIdx < edgesNum  ;  ++edgeIdx )
      edgesState[edgeIdx].isDisabled = ! Binary_isSetL2R( valueEdgeMapL2R, edgeIdx ) ;
  }
}


void
SegmentDisplay3D_setValueInt
( SegmentDisplay3D *this
, const uint8_t     value
)
{
  if (this == NULL)
    return ;              // NOP on NULLs.

  if (value > 9)
    return ;              // Invalid argument.

  if (value == this->value)
    return ;      // No change.

  this->value = value ;

  __refresh_SegmentDisplay3D( this ) ;
}


void
SegmentDisplay3D_config
( SegmentDisplay3D  *this          // The SegmentDisplay3D being configured.
, SegmentDisplayType type          // Display type can be changed on-the-fly.
, const float        width
, const float        height
, const float        shiftX
, const float        rotationX
, const float        rotationY
, const float        rotationZ
, const R3          *anchor3D      // 3D anchor of the segment display.
)
{
  if ( this == NULL          // NOP on NULLs.
    || type > this->typeMax  // Instance was allocated with less memory than what the required DisplayType needs.
     )
    return ;

  switch (this->type = type)
  {
    case SEG_N7BONE:
      Mesh3D_setFromI2XSTemplate( this->mesh, &SEG_N7BONE_VERTEXINFO, &SEG_N7BONE_EDGEINFO
                                , width, height, shiftX, rotationX, rotationY, rotationZ, anchor3D
                                ) ;
      this->mesh->strokeWidth = 3 ;
      this->mesh->edgeAlternateMask_L2R = NULL ;
      break ;

    case SEG_N7SKIN:
      Mesh3D_setFromI2XSTemplate( this->mesh, &SEG_N7SKIN_VERTEXINFO, &SEG_N7SKIN_EDGEINFO
                                , width, height, shiftX, rotationX, rotationY, rotationZ, anchor3D
                                ) ;
      this->mesh->strokeWidth = 2 ;
      this->mesh->edgeAlternateMask_L2R = NULL ;
      break ;

    case SEG_N7BONESKIN:
      Mesh3D_setFromI2XSTemplate( this->mesh, &SEG_N7SKINBONE_VERTEXINFO, &SEG_N7SKINBONE_EDGEINFO
                                , width, height, shiftX, rotationX, rotationY, rotationZ, anchor3D
                                ) ;
      this->mesh->strokeWidth          = 1 ;   // Bone
      this->mesh->strokeWidthAlternate = 1 ;   // Skin
      this->mesh->edgeAlternateMask_L2R = SEG_N7BONESKIN_BONEMASK_L2R ;
      break ;

    case SEG_N7SKINBONE:
      Mesh3D_setFromI2XSTemplate( this->mesh, &SEG_N7SKINBONE_VERTEXINFO, &SEG_N7SKINBONE_EDGEINFO
                                , width, height, shiftX, rotationX, rotationY, rotationZ, anchor3D
                                ) ;
      this->mesh->strokeWidth          = 1 ;   // Skin
      this->mesh->strokeWidthAlternate = 1 ;   // Bone
      this->mesh->edgeAlternateMask_L2R = SEG_N7SKINBONE_BONEMASK_L2R ;
      break ;

    case SEG_NCURVYBONE:
      Mesh3D_setFromI2XSTemplate( this->mesh, &SEG_NCURVYBONE_VERTEXINFO, &SEG_NCURVYBONE_EDGEINFO
                                , width, height, shiftX, rotationX, rotationY, rotationZ, anchor3D
                                ) ;
      this->mesh->strokeWidth = 3 ;
      this->mesh->edgeAlternateMask_L2R = NULL ;
      break ;

    case SEG_NCURVYSKIN:
      Mesh3D_setFromI2XSTemplate( this->mesh, &SEG_NCURVYSKIN_VERTEXINFO, &SEG_NCURVYSKIN_EDGEINFO
                                , width, height, shiftX, rotationX, rotationY, rotationZ, anchor3D
                                ) ;
      this->mesh->strokeWidth = 2 ;
      this->mesh->edgeAlternateMask_L2R = NULL ;
      break ;

    case SEG_NCURVYBONESKIN:
      Mesh3D_setFromI2XSTemplate( this->mesh, &SEG_NCURVYSKINBONE_VERTEXINFO, &SEG_NCURVYSKINBONE_EDGEINFO
                                , width, height, shiftX, rotationX, rotationY, rotationZ, anchor3D
                                ) ;
      this->mesh->strokeWidth           = 3 ;   // Bone
      this->mesh->edgeAlternateMask_L2R = SEG_NCURVYBONESKIN_BONEMASK_L2R ;
      break ;

    case SEG_NCURVYSKINBONE:
      Mesh3D_setFromI2XSTemplate( this->mesh, &SEG_NCURVYSKINBONE_VERTEXINFO, &SEG_NCURVYSKINBONE_EDGEINFO
                                , width, height, shiftX, rotationX, rotationY, rotationZ, anchor3D
                                ) ;
      this->mesh->strokeWidth           = 2 ;   // Skin
      this->mesh->edgeAlternateMask_L2R = SEG_NCURVYSKINBONE_BONEMASK_L2R ;
      break ;

    default:
      this->mesh->edgeAlternateMask_L2R = NULL ;
      break ;
  }

  __refresh_SegmentDisplay3D( this ) ;    // Refreshes mesh edges visibility based on current value.
}