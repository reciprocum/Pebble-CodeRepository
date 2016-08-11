/*
   File  : TransformR2.h
   Author: Afonso Santos, Portugal

   Last revision: 12h30 July 31 2016
*/

#pragma once

#include "R2.h"
#include "Matrix23.h"


typedef
struct TransformR2
{ bool                isDisabled ;   // Master public swich to enable toggling tranformation ON/OFF.
  int                 version ;      // Public versioning: to prevent uninitialized use, defer initial (or repeated) calculation of transformation matrix.
  R2                  __translation ;
  float               __rotation ;
  Matrix23            __transformation ;
  int                 __transformation_version ;

  struct TransformR2 *__parent ;
} TransformR2 ;


TransformR2*  TransformR2_setTranslation( TransformR2 *this, const R2 *translation ) ;
TransformR2*  TransformR2_setRotation( TransformR2 *this, const float rotation ) ;
Matrix23*     TransformR2_getTranformation( TransformR2 *this ) ;