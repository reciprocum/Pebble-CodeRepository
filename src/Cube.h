/*
   File  : Cube.h
   Author: Afonso Santos, Portugal

   Last revision: 10h34 July 27 2016
*/

#include "Mesh.h"


Mesh* Cube_new( ) ;

void 
Cube_config
( Mesh        *this          // Cube mesh being configured.
, const float  size
, Blinker     *inkBlinker
) ;