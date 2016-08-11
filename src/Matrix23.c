/*
   File  : Matrix23.c
   Author: Afonso Santos, Portugal

   Last revision: 16h00 August 06 2016
*/

#include "Config.h"
#include "FastMath.h"
#include "R2.h"
#include "Matrix23.h"


Matrix23*
Matrix23_set
( Matrix23 *M
, const float m11, const float m12, const float m13
, const float m21, const float m22, const float m23
)
{
  M->_11 = m11 ; M->_12 = m12 ; M->_13 = m13 ;
  M->_21 = m21 ; M->_22 = m22 ; M->_23 = m23 ;

  return M ;
} ;


// B := A

Matrix23*
Matrix23_assign
( Matrix23       *B
, const Matrix23 *A
)
{
  B->_11 = A->_11 ; B->_12 = A->_12 ; B->_13 = A->_13 ;
  B->_21 = A->_21 ; B->_22 = A->_22 ; B->_23 = A->_23 ;
 
  return B ;
}


Matrix23*
Matrix23_translation
( Matrix23 *T
, const R2 *v
)
{
  T->_11 = 1.0  ; T->_12 = 0.0  ;
  T->_21 = 0.0  ; T->_22 = 1.0  ;
  T->_13 = v->x ; T->_23 = v->y ;

  return T ;
}


// Do not change rotation portion, just translation

Matrix23*
Matrix23_setTranslation
( Matrix23 *T
, const R2 *v
)
{
  T->_13 = v->x ;
  T->_23 = v->y ;

  return T ;
}


Matrix23*
Matrix23_rotation
( Matrix23     *R
, const float   angle    // rotation
)
{
  const float sinAngle  = FastMath_sin( angle ) ;
  const float cosAngle  = FastMath_cos( angle ) ;

  R->_11 = cosAngle ; R->_12 = -sinAngle ;
  R->_21 = sinAngle ; R->_22 =  cosAngle ;

  R->_13 = 0.0 ;  // No translation.
  R->_23 = 0.0 ;  // No translation.

  return R ;
}


//  C := A X B

Matrix23*
Matrix23_compound
( Matrix23       *C
, const Matrix23 *A
, const Matrix23 *B
)
{
  C->_11 = A->_11 * B->_11  +  A->_21 * B->_12 ;
  C->_12 = A->_12 * B->_11  +  A->_22 * B->_12 ;

  C->_21 = A->_11 * B->_21  +  A->_21 * B->_22 ;
  C->_22 = A->_12 * B->_21  +  A->_22 * B->_22 ;

  C->_13 = A->_13 * B->_11  +  A->_23 * B->_12  +  B->_13 ;
  C->_23 = A->_13 * B->_21  +  A->_23 * B->_22  +  B->_23 ;

  return C ;
}


Matrix23*
Matrix23_transformation
( Matrix23     *T
, const float   rotation
, const R2     *translation
)
{
  Matrix23_setTranslation( Matrix23_rotation( T, rotation )
                         , translation
                         ) ;

  return T ;
}


//  t := v X Rot(T)
//  Apply only rotation part of transformation matrix (usefull with face/planar-mesh normals).

R2*
Matrix23_rotate
( R2             *r
, const R2       *v
, const Matrix23 *R
)
{
  if (v == NULL)
    return NULL ;

  if (R == NULL)
    return R2_assign( r, v ) ;    // NOP on NULL transformation.

  const float x = v->x * R->_11  +  v->y * R->_12 ;
  const float y = v->x * R->_21  +  v->y * R->_22 ;

  return R2_set( r, x, y ) ;
}


//  t := v X T

R2*
Matrix23_transform
( R2             *t
, const R2       *v
, const Matrix23 *T
)
{
  if (T == NULL)
    return R2_assign( t, v ) ;    // NOP on NULL transformation.

  const float x = v->x * T->_11  +  v->y * T->_12  +  T->_13 ;
  const float y = v->x * T->_21  +  v->y * T->_22  +  T->_23 ;

  return R2_set( t, x, y ) ;
}