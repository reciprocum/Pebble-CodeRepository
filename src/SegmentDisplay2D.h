/*
   File  : SegmentDisplay2D.h
   Author: Afonso Santos, Portugal

   Last revision: 12h45 August 08 2016
*/

#pragma once

#include "SegmentDisplay2D_N7BONE.h"
#include "SegmentDisplay2D_N7SKIN.h"
#include "SegmentDisplay2D_N7SKINBONE.h"
#include "SegmentDisplay2D_NCURVYBONE.h"
#include "SegmentDisplay2D_NCURVYSKIN.h"
#include "SegmentDisplay2D_NCURVYSKINBONE.h"


typedef enum { SEG_N7BONE           // [0-9] (HEX capable)
             , SEG_N7SKIN           // [0-9]
             , SEG_N7BONESKIN       // [0-9]
             , SEG_N7SKINBONE       // [0-9]
             , SEG_NCURVYBONE       // [0-9]
             , SEG_NCURVYSKIN       // [0-9]
             , SEG_NCURVYSKINBONE   // [0-9]
             , SEG_NCURVYBONESKIN   // [0-9]
             }
SegmentDisplayType ;           // Order is IMPORTANT: do NOT change ! Ordered by ascending memory requirements.