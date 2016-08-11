/*
   File  : I2.h   - 32 bit integer coords, max 2G points.
   Author: Afonso Santos, Portugal

   Last revision: 10h06 July 27 2016
*/

#pragma once

#define I2_MAXABS  1000000000


typedef struct
{ int x ;
  int y ;
} I2 ;


typedef struct
{ unsigned int pointsNum ;
  I2          *points ;
} I2_PathInfo ;