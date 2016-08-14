/*
   File  : Clock3D.h
   Author: Afonso Santos, Portugal

   Last revision: 13h45 August 14 2016
*/

#pragma once

#include "SegmentDisplay3D.h"
#include "RadialDial3D.h"


// World objects & parameters

// DISPLAY_TYPE OPTIONS: SEG_N7BONE SEG_N7SKIN SEG_N7SKINBONE SEG_NCURVYBONE SEG_NCURVYSKIN
// WARNING!: SEG_NCURVYSKIN consumes a LOT of RAM !!!
#define  CLOCK3D_DISPLAY_TYPE_MAJOR    SEG_NCURVYBONESKIN
#define  CLOCK3D_DISPLAY_TYPE_DEFAULT  SEG_NCURVYBONESKIN

// Comment next line if you need/want to omit the radial dial on the second100ths face (~3KB RAM savings).
#define  CLOCK3D_SECOND100THS_RADIAL
#define  CLOCK3D_SECOND100THS_DISPLAYTYPE_MAJOR  SEG_N7SKINBONE
#define  CLOCK3D_SECOND100THS_DISPLAYTYPE        SEG_N7SKINBONE

#define  CUBE_SIZE            1.0
#define  CUBE_HALF            (0.50 * CUBE_SIZE)
#define  RADIAL_INNER_RADIUS  (0.80 * CUBE_HALF)
#define  RADIAL_OUTER_RADIUS  (0.97 * CUBE_HALF)


extern SegmentDisplayType   clock_displayType ;

// Need to expose digit meshes because of access to blinker.
extern SegmentDisplay3D    *clock_days_leftDigitA ;
extern SegmentDisplay3D    *clock_days_leftDigitB ;
extern SegmentDisplay3D    *clock_days_rightDigitA ;
extern SegmentDisplay3D    *clock_days_rightDigitB ;

extern SegmentDisplay3D    *clock_hours_leftDigitA ;
extern SegmentDisplay3D    *clock_hours_leftDigitB ;
extern SegmentDisplay3D    *clock_hours_rightDigitA ;
extern SegmentDisplay3D    *clock_hours_rightDigitB ;

extern SegmentDisplay3D    *clock_minutes_leftDigitA ;
extern SegmentDisplay3D    *clock_minutes_leftDigitB ;
extern SegmentDisplay3D    *clock_minutes_rightDigitA ;
extern SegmentDisplay3D    *clock_minutes_rightDigitB ;

extern SegmentDisplay3D    *clock_seconds_leftDigit ;
extern SegmentDisplay3D    *clock_seconds_rightDigit ;

extern SegmentDisplay3D    *clock_second100ths_leftDigit ;
extern SegmentDisplay3D    *clock_second100ths_rightDigit ;


void Clock3D_initialize                    ( ) ;
bool Clock3D_isAnimated                    ( ) ;
void Clock3D_animateAllDigits              ( ) ;
void Clock3D_animateAllRadials             ( ) ;
void Clock3D_animateAll                    ( ) ;
void Clock3D_second100ths_update           ( ) ;
void Clock3D_updateDDHHMMSS                ( ) ;
void Clock3D_config                        ( SegmentDisplayType pDisplayType ) ;
void Clock3D_updateAnimation               ( const int pMaxAnimSteps ) ;
void Clock3D_setDisplayType                ( SegmentDisplayType pDisplayType ) ;
void Clock3D_cycleDisplayType              ( ) ;
void Clock3D_finalize                      ( ) ;

void
Clock3D_setTime_DDHHMMSS
( const uint8_t  pDays
, const uint8_t  pHours
, const uint8_t  pMinutes
, const uint8_t  pSeconds
) ;

void
Clock3D_draw
( GContext                      *gCtx
//, Clock3D                     *this    // TODO
, const Cam3D                   *cam
, const int                      w
, const int                      h
, const Mesh3D_TransparencyMode  transparency
) ;