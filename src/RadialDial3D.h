/*
   File  : RadialDial3D.h
   Author: Afonso Santos, Portugal

   Last revision: 15h35 August 06 2016
*/

#pragma once

#include "RadialDial2D.h"
#include "Mesh.h"
#include "R3.h"


typedef struct
{ Mesh          *mesh ;
  RadialDialType type ;
  int8_t         value ;          // Initialized with -1
} RadialDial3D ;


RadialDial3D*  RadialDial3D_new ( RadialDialType type ) ;
RadialDial3D*  RadialDial3D_free( RadialDial3D *this ) ;

void
RadialDial3D_config
( RadialDial3D          *this            // MUST already contain/point a/to pre-allocated mesh.
, const RadialDialShape  shape
, const float            innerRadius
, const float            outerRadius
, const float            rotationX
, const float            rotationY
, const float            rotationZ
, const R3              *anchor3D        // Center of the radial handle
) ;

void  RadialDial3D_setNull ( RadialDial3D  *this ) ;
void  RadialDial3D_setValue( RadialDial3D *this, const uint8_t value ) ;