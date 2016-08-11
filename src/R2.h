/*
   File  : R2.h
   Author: Afonso Santos, Portugal

   Last revision: 11h50 July 31 2016
*/

#pragma once

#include <pebble.h>


typedef struct
{
  float x ;
  float y ;
} R2 ;


#define R2_origin        ((R2){ .x = 0.0, .y = 0.0 })
#define R2_versorPlusX   ((R2){ .x =+1.0, .y = 0.0 })
#define R2_versorMinusX  ((R2){ .x =-1.0, .y = 0.0 })
#define R2_versorPlusY   ((R2){ .x = 0.0, .y =+1.0 })
#define R2_versorMinusY  ((R2){ .x = 0.0, .y =-1.0 })


// v := { x, y }
R2*   R2_set( R2 *v, const float x, const float y ) ;

// b := a
R2*   R2_assign( R2 *b, const R2 *a ) ;

// a == b
bool  R2_isEqual( const R2 *a, const R2 *b ) ;

float R2_modulus( const R2 *v ) ;

// c := a + b
R2*   R2_add( R2 *c, const R2 *a, const R2 *b ) ;

// c := a - b
R2*   R2_substract( R2 *c, const R2 *a, const R2 *b ) ;

// b := k * a
R2*   R2_scalarProduct( R2 *b, const float k, const R2 *a ) ;

//  v := k / |v| * v
R2*   R2_scale( const float k, R2 *v ) ;

//  v := v / |v|
R2*   R2_versor( R2 *v ) ;

// a . b
float R2_dotProduct( const R2 *a, const R2 *b ) ;