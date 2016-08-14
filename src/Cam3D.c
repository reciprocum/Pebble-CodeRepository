/*
   File  : Cam3D.c
   Author: Afonso Santos, Portugal

   Last revision: 17h25 August 11 2016
*/

#include "Config.h"
#include "R2.h"
#include "Cam3D.h"


Cam3D*
Cam3D_setup
( Cam3D                     *cam
, const R3                  *viewPoint
, const R3                  *lookingAt
, const R3                  *upReference
, const float                zoom
, const Cam3D_ProjectionMode projectionMode
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
( Cam3D                     *cam
, const R3                  *viewPoint
, const float                zoom
, const Cam3D_ProjectionMode projectionMode
)
{
  // setup 3D camera
  return Cam3D_setup( cam
                    , (viewPoint->x != 0.0  ||  viewPoint->y != 0.0)            // Viewpoint not on Z axis ?
                      ? viewPoint                                               // Use original view point.
                      : &(R3){ .x = 0.00001, .y = 0.00001, .z = viewPoint->z}   // Use epsilon displaced alternate view point (to avoid math indetermination).
                    , &R3_origin                                                // Looking at.
                    , &R3_versorPlusZ                                           // Use R3_versorPlusZ as vertical reference.
                    , zoom                                                      // Zoom level.
                    , projectionMode                                            // Projection mode.
                    ) ;
}


R2*
Cam3D_view
( R2           *v2D      // camera's film plane 2D coordinates of 3D world point
, const Cam3D  *cam      // camera used to view the 3D point
, const R3     *v3D      // world point's 3D coordinates
)
{ // TODO: z cliping.
  R3 vCam ;

  R3_subtract( &vCam, v3D, &cam->viewPoint ) ;			      // vCamera = norm( v - Eye )

  float k = 1.0 ;  // Assigned value just to mute the compiler warning.

  switch (cam->projectionMode)
  {
    case CAM3D_PROJECTION_PERSPECTIVE:
      k = cam->zoom / R3_dotProduct( &cam->zAxisVersor, &vCam ) ;
      break ;

    case CAM3D_PROJECTION_ISOMETRIC:
      k = cam->zoom ;
      break ;
  }

  return R2_set( v2D
               , k * R3_dotProduct( &cam->xAxisVersor, &vCam )
               , k * R3_dotProduct( &cam->yAxisVersor, &vCam )
               ) ;
}