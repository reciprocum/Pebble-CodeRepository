/*
   File  : Cam3D.c
   Author: Afonso Santos, Portugal

   Last revision: 16h35 August 11 2016
*/

#include "Config.h"
#include "R2.h"
#include "Cam3D.h"


Cam3D*
Cam3D_setup
( Cam3D        *cam
, const R3     *viewPoint
, const R3     *lookingAt
, const R3     *upReference
, const float   zoom
, const uint8_t projectionMode
)
{
  R3_assign( &cam->viewPoint, viewPoint ) ;

  R3_versor( R3_subtract( &cam->zAxisVersor, lookingAt, &cam->viewPoint ) ) ;	          // zAxisVersor = versor( lookingAt - viewPoint )
  R3_versor( R3_crossProduct( &cam->xAxisVersor, &cam->zAxisVersor, upReference ) ) ;	  // xAxisVersor = versor( zAxisVersor X upReference  )
  R3_crossProduct( &cam->yAxisVersor, &cam->zAxisVersor, &cam->xAxisVersor ) ;          // yAxisVersor = zAxisVersor X xAxisVersor
  cam->zoom           = zoom ;
  cam->projectionMode = projectionMode ;

  return cam ;
}


Cam3D*
Cam3D_lookAtOriginUpwards
( Cam3D        *cam
, const R3     *viewPoint
, const float   zoom
, const uint8_t projectionMode
)
{
  // setup 3D camera
  return Cam3D_setup( cam
                    , (viewPoint->x != 0.0  ||  viewPoint->y != 0.0)            // Viewpoint not on Z axis ?
                      ? viewPoint                                               // Use original view point.
                      : &(R3){ .x = 0.00001, .y = 0.00001, .z = viewPoint->z}   // Use epsilon displaced alternate view point.
                    , &R3_origin                                                // Looking at.
                    , &R3_versorPlusZ                                           // Use R3_versorPlusZ as vertical reference.
                    , zoom                                                      // Zoom level.
                    , MODE_3D_PROJECTION_PERSPECTIVE                            // Projection mode.
                    ) ;
}


R2*
Cam3D_view
( R2           *v2D      // camera's film plane 2D coordinates of 3D world point
, const Cam3D  *cam      // camera used to view the 3D point
, const R3     *v3D      // world point's 3D coordinates
)
{
  R3 vCam ;

  R3_subtract( &vCam, v3D, &cam->viewPoint ) ;			      // vCamera = norm( v - Eye )

  float x = R3_dotProduct( &cam->xAxisVersor, &vCam ) ;
  float y = R3_dotProduct( &cam->yAxisVersor, &vCam ) ;
  float z = R3_dotProduct( &cam->zAxisVersor, &vCam ) ;

  // TODO: z cliping & projectionMode awareness.
  float k = cam->zoom / z ;

  return R2_set( v2D, k*x, k*y ) ;
}