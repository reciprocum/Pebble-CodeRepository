/*
   File  : SegmentDisplay3D.h
   Author: Afonso Santos, Portugal

   Last revision: 10h50 August 08 2016
*/

#pragma once

#include "SegmentDisplay2D.h"
#include "Mesh.h"


typedef struct
{ Mesh               *mesh ;
  SegmentDisplayType  type, typeMax ;
  int8_t              value ;          // Initialized with -1
} SegmentDisplay3D ;


SegmentDisplay3D*  SegmentDisplay3D_free       ( SegmentDisplay3D *this ) ;
void               SegmentDisplay3D_setNull    ( SegmentDisplay3D *this ) ;
SegmentDisplay3D*  SegmentDisplay3D_new        ( SegmentDisplayType typeMax ) ;
void               SegmentDisplay3D_setValueInt( SegmentDisplay3D *this, const uint8_t value ) ;

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
, const R3          *anchor3D      // 3D anchor of the 7 segment display.
) ;