/*
   File  : FastMath.c
   FAST MATH OPERATIONS ON FLOATS

   Last revision: 16h55 August 06 2016
*/

#include "Config.h"
#include "FastMath.h"


float
FastMath_normalizeAngle
( float a )
{
  while (a < -PI_1)
    a += PI_2 ;

  while (a > PI_1)
    a -= PI_2 ;

  return a ;
}


float
FastMath_reduceAngle
( float a )
{
  a = FastMath_normalizeAngle( a ) ;

  if (a < -PI_HALF)
    a += PI_1 ;

  if (a > PI_HALF)
    a -= PI_1 ;

  return a ;
}


float
FastMath_sin
( float x )
{
  float sin ;

  if (x < -PI_1)
    x += PI_2 ;

  if (x > PI_1)
    x -= PI_2 ;

  if (x < 0)
  {
    sin = 1.2732395 * x + .40528473 * x * x ;

    if (sin < 0)
      sin = .225 * (sin *-sin - sin) + sin ;
    else
      sin = .225 * (sin * sin - sin) + sin ;
  } else
  {
    sin = 1.2732395 * x - .40528473 * x * x ;

    if (sin < 0)
      sin = .225 * (sin *-sin - sin) + sin ;
    else
      sin = .225 * (sin * sin - sin) + sin ;
  }

  return sin ;
}

float
FastMath_cos
( const float x )
{ return FastMath_sin( x + PI_HALF ) ; }

// See http://en.wikipedia.org/wiki/Fast_inverse_square_root for more details;
// In our last step we multiply with 'x' in order to make '1/sqrt(x)' to 'sqrt(x)'.
#define SQRT_MAGIC_F 0x5f3759df 


float
FastMath_sqrt
( const float x )
{
  union
  { float x ;
    int   i ;
  } u ;

  u.x = x ;
  u.i = SQRT_MAGIC_F - (u.i >> 1) ;

  // newton step for increased accuracy
  return x * u.x * (1.5f - 0.5f * x * u.x * u.x) ;
}


int
FastMath_absi
( const int i )
{ return (i < 0) ? -i : i ; }


float
FastMath_absf
( const float f )
{ return (f < 0.0) ? -f : f ; }