/*
   File  : SegmentDisplay2D_NCURVYSKINBONE.h
   Author: Afonso Santos, Portugal

   Last revision: 10h35 August 08 2016
*/

#pragma once

#include "I2_8.h"
#include "Edge.h"


extern const I2_8_PathInfo  SEG_NCURVYSKINBONE_VERTEXINFO ;
extern const EdgeInfo       SEG_NCURVYSKINBONE_EDGEINFO ;
extern const unsigned char *SEG_NCURVYSKINBONE_DIGIT_EDGEMAP_L2R[10] ;   // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.
extern const unsigned char *SEG_NCURVYBONESKIN_BONEMASK_L2R ;            // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.
extern const unsigned char *SEG_NCURVYSKINBONE_BONEMASK_L2R ;            // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.