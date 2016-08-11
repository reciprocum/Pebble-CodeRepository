/*
   File  : Interpolations.h
   Author: Afonso Santos, Portugal

   Last revision: 11h45 July 31 2016
*/

#pragma once

void
fillInterpolator_AccelerateDecelerate( float     *result
                    							   , const int  nSteps
                    								 ) ;

void
fillInterpolator_TrigonometricYoYo( float     *result
                                  , const int  nSteps
                                  ) ;