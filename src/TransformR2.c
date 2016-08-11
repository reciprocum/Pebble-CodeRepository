/*
   File  : TransformR2.c
   Author: Afonso Santos, Portugal

   Last revision: 16h05 August 06 2016
*/

#include "Config.h"
#include "TransformR2.h"
#include "Matrix23.h"


TransformR2*
TransformR2_setTranslation
( TransformR2 *this
, const R2    *translation
)
{
  if (!R2_isEqual( &this->__translation, translation ))
  {
    R2_assign( &this->__translation, translation ) ;
    this->version++ ;
  }

  return this ;  
}


TransformR2*
TransformR2_setRotation
( TransformR2 *this
, const float  rotation
)
{
  if (this->__rotation != rotation)
  {
    this->__rotation = rotation ;
    this->version++ ;
  }

  return this ;  
}


Matrix23*
TransformR2_getTranformation
( TransformR2 *this )
{
  if (this->isDisabled | (this->version == 0))
    return NULL ;

  if (this->__transformation_version != this->version)
  {
    Matrix23_transformation( &this->__transformation, this->__rotation, &this->__translation ) ;
    this->__transformation_version = this->version ;
  }

  return &this->__transformation ;  
}