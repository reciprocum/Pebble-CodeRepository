/*
   File  : Cam3D.h
   Author: Afonso Santos, Portugal

   Last revision: 12h37 August 11 2016
*/

#pragma once

#include "R2.h"
#include "R3.h"


#define MODE_3D_TRANSPARENCY_SOLID        1
#define MODE_3D_TRANSPARENCY_XRAY         2
#define MODE_3D_TRANSPARENCY_WIREFRAME    3

#define MODE_3D_PROJECTION_ISOMETRIC      1
#define MODE_3D_PROJECTION_PERSPECTIVE    2


typedef struct
{
  R3       viewPoint ;
  R3       xAxisVersor ;
  R3       yAxisVersor ;
  R3       zAxisVersor ;
  float    zoom ;
  uint8_t  projectionMode ;
} Cam3D ;


Cam3D*
Cam3D_setup
( Cam3D        *cam
, const R3     *viewPoint
, const R3     *lookingAt
, const R3     *upReference
, const float   zoom
, const uint8_t projectionMode
) ;


Cam3D*
Cam3D_lookAtOriginUpwards
( Cam3D        *cam
, const R3     *viewPoint
, const float   zoom
, const uint8_t projectionMode
) ;

R2*
Cam3D_view
( R2           *v2D      // out: camera's film plane 2D coordinates of 3D world point
, const Cam3D  *cam      // in: camera used to view the 3D point
, const R3     *v3D      // in: world point's 3D coordinates
) ;