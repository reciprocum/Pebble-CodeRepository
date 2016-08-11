/*
   File  : I2_16.h   - Small (16 bit2 byte coords, max 65K points)
   Author: Afonso Santos, Portugal

   Last revision: 09h25 July 27 2016
*/

#pragma once


#include <pebble.h>

#define I2_16_MAXABS  32000


typedef struct
{ int16_t x ;
  int16_t y ;
} I2_16 ;


typedef struct
{ uint16_t pointsNum ;
  I2_16   *points ;
} I2_16_PathInfo ;