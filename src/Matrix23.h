/*
   File  : Matrix23.h
   Author: Afonso Santos, Portugal

   Last revision: 16h55 July 31 2016
*/

#pragma once

#include "R2.h"


typedef struct
{
  float _11, _12, _13 ;
  float _21, _22, _23 ;
} Matrix23 ;


Matrix23*
Matrix23_set
( Matrix23 *M
, const float m11, const float m12, const float m13
, const float m21, const float m22, const float m23
) ;


// B := A

Matrix23*
Matrix23_assign
( Matrix23       *B
, const Matrix23 *A
) ;


Matrix23*
Matrix23_translation
( Matrix23 *T
, const R2 *v
) ;


// Do not change rotation portion, just translation

Matrix23*
Matrix23_setTranslation
( Matrix23 *T
, const R2 *v
) ;


Matrix23*
Matrix23_rotation
( Matrix23     *R
, const float   angle    // rotation
) ;


//  C := A X B

Matrix23*
Matrix23_compound
( Matrix23       *C
, const Matrix23 *A
, const Matrix23 *B
) ;


Matrix23*
Matrix23_transformation
( Matrix23     *T
, const float   rotation
, const R2     *translation
) ;


//  r := v X Rot(R)
//  Apply only rotation part of transformation matrix (usefull with face/planar-mesh normals).

R2*
Matrix23_rotate
( R2             *r
, const R2       *v
, const Matrix23 *R
) ;


//  t := v X T

R2*
Matrix23_transform
( R2             *t
, const R2       *v
, const Matrix23 *T
) ;