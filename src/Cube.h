/*
   File  : Cube.h
   Author: Afonso Santos, Portugal

   Last revision: 13h40 August 14 2016
*/

#include "Mesh3D.h"


Mesh3D* Cube_new( ) ;

void
Cube_config
( Mesh3D      *this          // Cube mesh being configured.
, const float  size
, Blinker     *inkBlinker
) ;