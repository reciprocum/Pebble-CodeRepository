/*
   File  : TransformR3.c
   Author: Afonso Santos, Portugal

   Last revision: 13h05 August 05 2016
*/

#include "Config.h"
#include "TransformR3.h"
#include "Matrix34.h"


TransformR3*
TransformR3_setTranslation
( TransformR3 *this
, const R3    *translation
)
{
  if (!R3_isEqual( &this->__translation, translation ))
  {
    R3_assign( &this->__translation, translation ) ;
    this->version++ ;
  }

  return this ;  
}


TransformR3*
TransformR3_setRotationX
( TransformR3 *this
, const float  rotation
)
{
  if (this->__rotationX != rotation)
  {
    this->__rotationX = rotation ;
    this->version++ ;
  }

  return this ;  
}


TransformR3*
TransformR3_setRotationY
( TransformR3 *this
, const float  rotation
)
{
  if (this->__rotationY != rotation)
  {
    this->__rotationY = rotation ;
    this->version++ ;
  }

  return this ;  
}


TransformR3*
TransformR3_setRotationZ
( TransformR3 *this
, const float  rotation
)
{
  if (this->__rotationZ != rotation)
  {
    this->__rotationZ = rotation ;
    this->version++ ;
  }

  return this ;  
}


TransformR3*
TransformR3_setRotation
( TransformR3 *this
, const float  rotationX
, const float  rotationY
, const float  rotationZ
)
{
  TransformR3_setRotationX( this, rotationX ) ;
  TransformR3_setRotationY( this, rotationY ) ;
  TransformR3_setRotationZ( this, rotationZ ) ;

  return this ;  
}


Matrix34*
TransformR3_getTransformation
( TransformR3 *this )
{
  if (this->isDisabled | (this->version == 0))
    return NULL ;

  if (this->__transformation_version != this->version)
  {
    Matrix34_transformation( &this->__transformation, this->__rotationX, this->__rotationY, this->__rotationZ, &this->__translation ) ;
    this->__transformation_version = this->version ;
  }

  return &this->__transformation ;  
}


static TransformR3  __transform ;

R3*
TransformR3_rotateX
( R3          *this
, const float  rotation
)
{
  TransformR3_setRotation( &__transform, rotation, 0.0, 0.0 ) ;

  // Rotate this point around x-axis.
  Matrix34_transform( this, this, TransformR3_getTransformation( &__transform ) ) ;

  return this ;  
}


R3*
TransformR3_rotateY
( R3          *this
, const float  rotation
)
{
  TransformR3_setRotation( &__transform, 0.0, rotation, 0.0 ) ;

  // Rotate this point around y-axis.
  Matrix34_transform( this, this, TransformR3_getTransformation( &__transform ) ) ;

  return this ;  
}


R3*
TransformR3_rotateZ
( R3          *this
, const float  rotation
)
{
  TransformR3_setRotation( &__transform, 0.0, 0.0, rotation ) ;

  // this := this X cam_transform.
  // Rotate this point around z-axis.
  Matrix34_transform( this, this, TransformR3_getTransformation( &__transform ) ) ;

  return this ;  
}