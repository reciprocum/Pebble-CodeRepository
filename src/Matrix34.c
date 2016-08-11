/*
   File  : Matrix34.c
   Author: Afonso Santos, Portugal

   Last revision: 12h55 August 05 2016
*/

#include "Config.h"
#include "FastMath.h"
#include "R3.h"
#include "Matrix34.h"


Matrix34*
Matrix34_set
( Matrix34 *M
, const float m11, const float m12, const float m13, const float m14
, const float m21, const float m22, const float m23, const float m24
, const float m31, const float m32, const float m33, const float m34
)
{
  M->_11 = m11 ; M->_12 = m12 ; M->_13 = m13 ; M->_14 = m14 ;
  M->_21 = m21 ; M->_22 = m22 ; M->_23 = m23 ; M->_24 = m24 ;
  M->_31 = m31 ; M->_32 = m32 ; M->_33 = m33 ; M->_34 = m34 ;

  return M ;
} ;


// B := A

Matrix34*
Matrix34_assign
( Matrix34       *B
, const Matrix34 *A
)
{
  B->_11 = A->_11 ; B->_12 = A->_12 ; B->_13 = A->_13 ; B->_14 = A->_14 ;
  B->_21 = A->_21 ; B->_22 = A->_22 ; B->_23 = A->_23 ; B->_24 = A->_24 ;
  B->_31 = A->_31 ; B->_32 = A->_32 ; B->_33 = A->_33 ; B->_34 = A->_34 ;
 
  return B ;
}


Matrix34*
Matrix34_translation
( Matrix34 *M
, const R3 *t
)
{
  M->_11 = 1.0 ; M->_12 = 0.0 ; M->_13 = 0.0  ;  M->_14 = t->x ;
  M->_21 = 0.0 ; M->_22 = 1.0 ; M->_23 = 0.0  ;  M->_24 = t->y ;
  M->_31 = 0.0 ; M->_32 = 0.0 ; M->_33 = 1.0  ;  M->_34 = t->z ;

  return M ;
}


// Do not change rotation portion, just translation

Matrix34*
Matrix34_setTranslation
( Matrix34 *M
, const R3 *t
)
{
  M->_14 = t->x ;
  M->_24 = t->y ;
  M->_34 = t->z ;

  return M ;
}


Matrix34*
Matrix34_rotation
( Matrix34     *R
, const float   pitch   // rotationX
, const float   yaw     // rotationY
, const float   roll    // rotationZ
)
{
  const float halfPitch = 0.5 * FastMath_normalizeAngle( pitch ) ;
  const float halfYaw   = 0.5 * FastMath_normalizeAngle( yaw ) ;
  const float halfRoll  = 0.5 * FastMath_normalizeAngle( roll ) ;

  const float sinPitch = FastMath_sin( halfPitch ) ;
  const float cosPitch = FastMath_cos( halfPitch ) ;
  const float sinYaw   = FastMath_sin( halfYaw ) ;
  const float cosYaw   = FastMath_cos( halfYaw ) ;
  const float sinRoll  = FastMath_sin( halfRoll ) ;
  const float cosRoll  = FastMath_cos( halfRoll ) ;

  const float x = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll) ;
  const float y = (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll) ;
  const float z = (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll) ;
  const float w = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll) ;

  const float xx = x * x ;
  const float yy = y * y ;
  const float zz = z * z ;
  const float xy = x * y ;
  const float zw = z * w ;
  const float zx = z * x ;
  const float yw = y * w ;
  const float yz = y * z ;
  const float xw = x * w ;

  R->_11 = 1.0 - (2.0 * (yy + zz)) ;
  R->_12 = 2.0 * (xy - zw) ;
  R->_13 = 2.0 * (zx + yw) ;

  R->_21 = 2.0 * (xy + zw) ;
  R->_22 = 1.0 - (2.0 * (zz + xx)) ;
  R->_23 = 2.0 * (yz - xw) ;

  R->_31 = 2.0 * (zx - yw) ;
  R->_32 = 2.0 * (yz + xw) ;
  R->_33 = 1.0 - (2.0 * (yy + xx)) ;

  R->_14 = 0.0 ;  // No translation.
  R->_24 = 0.0 ;  // No translation.
  R->_34 = 0.0 ;  // No translation.

  return R ;
}


//  C := A X B

Matrix34*
Matrix34_compound
( Matrix34       *C
, const Matrix34 *A
, const Matrix34 *B
)
{
  C->_11 = A->_11 * B->_11  +  A->_21 * B->_12  +  A->_31 * B->_13 ;
  C->_12 = A->_12 * B->_11  +  A->_22 * B->_12  +  A->_32 * B->_13 ;
  C->_13 = A->_13 * B->_11  +  A->_23 * B->_12  +  A->_33 * B->_13 ;

  C->_21 = A->_11 * B->_21  +  A->_21 * B->_22  +  A->_31 * B->_23 ;
  C->_22 = A->_12 * B->_21  +  A->_22 * B->_22  +  A->_32 * B->_23 ;
  C->_23 = A->_13 * B->_21  +  A->_23 * B->_22  +  A->_33 * B->_23 ;

  C->_31 = A->_11 * B->_31  +  A->_21 * B->_32  +  A->_31 * B->_33 ;
  C->_32 = A->_12 * B->_31  +  A->_22 * B->_32  +  A->_32 * B->_33 ;
  C->_33 = A->_13 * B->_31  +  A->_23 * B->_32  +  A->_33 * B->_33 ;

  C->_14 = A->_14 * B->_11  +  A->_24 * B->_12  +  A->_34 * B->_13  +  B->_14 ;
  C->_24 = A->_14 * B->_21  +  A->_24 * B->_22  +  A->_34 * B->_23  +  B->_24 ;
  C->_34 = A->_14 * B->_31  +  A->_24 * B->_32  +  A->_34 * B->_33  +  B->_34 ;

  return C ;
}


Matrix34*
Matrix34_transformation
( Matrix34     *T
, const float   rotationX
, const float   rotationY
, const float   rotationZ
, const R3     *translation
)
{
  Matrix34_setTranslation( Matrix34_rotation( T, rotationX, rotationY, rotationZ )
                         , translation
                         ) ;

  return T ;
}


//  t := v X Rot(T)
//  Apply only rotation part of transformation matrix (usefull with face/planar-mesh normals).

R3*
Matrix34_rotate
( R3             *t
, const R3       *v
, const Matrix34 *T
)
{
  if (v == NULL)
    return NULL ;
  
  if (T == NULL)
    return R3_assign( t, v ) ;    // NOP on NULL transformation.

  const float x = v->x * T->_11  +  v->y * T->_12  +  v->z * T->_13 ;
  const float y = v->x * T->_21  +  v->y * T->_22  +  v->z * T->_23 ;
  const float z = v->x * T->_31  +  v->y * T->_32  +  v->z * T->_33 ;

  return R3_set( t, x, y, z ) ;
}


//  t := v X T

R3*
Matrix34_transform
( R3             *t
, const R3       *v
, const Matrix34 *T
)
{
  if (T == NULL)
    return R3_assign( t, v ) ;    // NOP on NULL transformation.

  const float x = v->x * T->_11  +  v->y * T->_12  +  v->z * T->_13  +  T->_14 ;
  const float y = v->x * T->_21  +  v->y * T->_22  +  v->z * T->_23  +  T->_24 ;
  const float z = v->x * T->_31  +  v->y * T->_32  +  v->z * T->_33  +  T->_34 ;

  return R3_set( t, x, y, z ) ;
}