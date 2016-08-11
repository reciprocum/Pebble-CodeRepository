/*
   File  : SegmentDisplay2D_NCURVYBONE.h
   Author: Afonso Santos, Portugal

   Last revision: 02h45 July 31 2016
*/

#pragma once

#include "I2_8.h"
#include "Edge.h"


extern const I2_8_PathInfo  SEG_NCURVYBONE_VERTEXINFO ;
extern const EdgeInfo       SEG_NCURVYBONE_EDGEINFO ;
extern const unsigned char *SEG_NCURVYBONE_DIGIT_EDGEMAP_L2R[10] ;   // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.