/*
   File  : R3.c
   Author: Afonso Santos, Portugal

   Last revision: 13h05 August 05 2016
*/

#include "Config.h"
#include "FastMath.h"
#include "R3.h"


// v := { x, y, z }

R3*
R3_set
( R3           *v
, const float   x
, const float   y
, const float   z
)
{
  v->x = x ;
  v->y = y ;
  v->z = z ;
 
  return v ;
}


// b := a

R3*
R3_assign
( R3       *b
, const R3 *a
)
{
  b->x = a->x ;
  b->y = a->y ;
  b->z = a->z ;
 
  return b ;
}


// a == b

bool
R3_isEqual
( const R3 *a
, const R3 *b
)
{ return (a == b) || ((a->x == b->x) && (a->y == b->y) && (a->z == b->z)) ; }


// |v|

float
R3_modulus
( const R3 *v )
{
  const float x = v->x ;
  const float y = v->y ;
  const float z = v->z ;

  return FastMath_sqrt( x*x + y*y + z*z ) ;
}


// c := a + b

R3*
R3_add
( R3       *c
, const R3 *a
, const R3 *b
)
{
  c->x = a->x + b->x ;
  c->y = a->y + b->y ;
  c->z = a->z + b->z ;

  return c ;
}


// c := a - b

R3*
R3_subtract
( R3       *c
, const R3 *a
, const R3 *b
)
{ c->x = a->x - b->x ;
  c->y = a->y - b->y ;
  c->z = a->z - b->z ;

  return c ;
}


// b := k * a

R3*
R3_scalarProduct
( R3         *b
, const float	k
, const R3   *a
)
{
  b->x = k * a->x ;
  b->y = k * a->y ;
  b->z = k * a->z ;

  return b ;
}


//  v := k / |v| * v

R3*
R3_scale
( const float  k
, R3          *v
)
{ const float scale = k / R3_modulus( v ) ;

  return R3_scalarProduct( v, scale, v ) ;
}


//  v := v / |v|

R3*
R3_versor
( R3 *v )
{ return R3_scale( 1.0, v ) ; }


// a . b

float
R3_dotProduct
( const R3 *a
, const R3 *b
)
{
  return a->x * b->x
       + a->y * b->y
       + a->z * b->z
  ;
}


// c := a x b

R3*
R3_crossProduct
( R3       *c
, const R3 *a
, const R3 *b
)
{
  c->x = a->y * b->z - a->z * b->y ;
  c->y = a->z * b->x - a->x * b->z ;
  c->z = a->x * b->y - a->y * b->x ;

  return c ;
}