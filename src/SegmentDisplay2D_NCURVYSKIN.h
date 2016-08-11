/*
   File  : SegmentDisplay2D_NCURVYSKIN.h
   Author: Afonso Santos, Portugal

   Last revision: 17h30 August 03 2016
*/

#pragma once

#include "I2_8.h"
#include "Edge.h"


extern const I2_8_PathInfo  SEG_NCURVYSKIN_VERTEXINFO ;
extern const EdgeInfo       SEG_NCURVYSKIN_EDGEINFO ;
extern const unsigned char *SEG_NCURVYSKIN_DIGIT_EDGEMAP_L2R[10] ;   // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.