/*
   File  : R2.c
   Author: Afonso Santos, Portugal

   Last revision: 13h05 August 05 2016
*/

#include "Config.h"
#include <pebble.h>
#include "FastMath.h"
#include "R2.h"


// v := { x, y }

R2*
R2_set
( R2         *v
, const float x
, const float y
)
{
  v->x = x ;
  v->y = y ;
 
  return v ;
}


// b := a

R2*
R2_assign
( R2       *b
, const R2 *a
)
{
  b->x = a->x ;
  b->y = a->y ;
 
  return b ;
}


// a == b

bool
R2_isEqual
( const R2 *a
, const R2 *b
)
{ return (a == b) || ((a->x == b->x) && (a->y == b->y)) ; }


float
R2_modulus
( const R2 *v )
{ const float x = v->x ;
  const float y = v->y ;

  return FastMath_sqrt( x*x + y*y ) ;
}


// c := a + b

R2*
R2_add
( R2       *c
, const R2 *a
, const R2 *b
)
{
  c->x = a->x + b->x ;
  c->y = a->y + b->y ;
 
  return c ;
}


// c := a - b

R2*
R2_substract
( R2       *c
, const R2 *a
, const R2 *b
)
{
  c->x = a->x - b->x ;
  c->y = a->y - b->y ;
 
  return c ;
}


// b := k * a

R2*
R2_scalarProduct
( R2         *b
, const float	k
, const R2   *a
)
{
  b->x = k * a->x ;
  b->y = k * a->y ;
 
  return b ;
}



//  v := k / |v| * v

R2*
R2_scale
( const float  k
, R2          *v
)
{
  const float scale = k / R2_modulus( v ) ;

  return R2_scalarProduct( v, scale, v ) ;
}


//  v = v / |v|

R2*
R2_versor
( R2 *v )
{ return R2_scale( 1.0, v ) ; }



// a . b

float
R2_dotProduct
( const R2 *a
, const R2 *b
)
{
  return a->x * b->x
       + a->y * b->y
  ;
}