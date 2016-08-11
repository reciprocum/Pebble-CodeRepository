/*
   File  : SegmentDisplay2D_N7SKINBONE.h
   Author: Afonso Santos, Portugal

   Last revision: 12h55 August 08 2016
*/

#pragma once

#include "I2_8.h"
#include "Edge.h"


extern const I2_8_PathInfo  SEG_N7SKINBONE_VERTEXINFO ;
extern const EdgeInfo       SEG_N7SKINBONE_EDGEINFO ;
extern const unsigned char *SEG_N7SKINBONE_DIGIT_EDGEMAP_L2R[10] ;   // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.
extern const unsigned char *SEG_N7BONESKIN_BONEMASK_L2R ;            // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.
extern const unsigned char *SEG_N7SKINBONE_BONEMASK_L2R ;            // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.