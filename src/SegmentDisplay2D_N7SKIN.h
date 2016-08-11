/*
   File  : SegmentDisplay2D_N7SKIN.h
   Author: Afonso Santos, Portugal

   Last revision: 13h25 July 31 2016
*/

#pragma once

#include "I2_8.h"
#include "Edge.h"


extern const I2_8_PathInfo  SEG_N7SKIN_VERTEXINFO ;
extern const EdgeInfo       SEG_N7SKIN_EDGEINFO ;
extern const unsigned char *SEG_N7SKIN_DIGIT_EDGEMAP_L2R[10] ;   // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.