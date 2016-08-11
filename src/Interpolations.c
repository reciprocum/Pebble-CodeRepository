/*
   File  : Interpolations.c
   Author: Afonso Santos, Portugal

   Last revision: 12h55 August 05 2016
*/

#include "Config.h"
#include "FastMath.h"


void
fillInterpolator_AccelerateDecelerate( float     *result
                    							   , const int  nSteps
                    								 )
{
  const float  tStep      = 1.0 / nSteps ;
  const int    nHalfSteps = nSteps / 2 ;

  // First point.
  result[0] = 0.0 ;
  
  // First half.
  for (int iStep = 1  ;  iStep < nHalfSteps  ;  ++iStep)
  {
    const float t = iStep * tStep ;
    result[iStep] = 2.0 * t * t ;
  }

  // Halfway point.
  result[nHalfSteps] = 0.5 ;

  // Second half.
  for (int iStep = nHalfSteps+1  ;  iStep < nSteps  ;  ++iStep)
  {
    const float t = iStep * tStep - 0.5 ;
    result[iStep] = 0.5 + 2.0 * t * (1.0 - t) ;
  }

  // Last point.
  result[nSteps] = 1.0 ;
}


void
fillInterpolator_TrigonometricYoYo( float     *result
                                  , const int  nSteps
                                  )
{
  const float  stepAngle  = DEG_180 / nSteps ;

  // First & last point.
  result[0] = result[nSteps] = 0.0 ;

  for (int iStep = 1  ;  iStep < nSteps  ;  ++iStep)
    result[iStep] = FastMath_sin( iStep * stepAngle ) ;
}