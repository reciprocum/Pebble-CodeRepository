/*
   File  : RadialDial2D.h
   Author: Afonso Santos, Portugal

   Last revision: 11h40 August 06 2016
*/

#pragma once

#include "Edge.h"


typedef enum { RADIAL_DIAL_TYPE_24      // 24 radial lines (analog clock hour handle)
             , RADIAL_DIAL_TYPE_60      // 60 radial lines (analog clock minute/second handle)
             , RADIAL_DIAL_TYPE_100     // 100 radial lines (analog clock 100ths of second handle)
             }
RadialDialType ;           // Order is IMPORTANT: do NOT change ! Ordered by ascending memory requirements.

typedef enum { RADIAL_DIAL_SHAPE_SQUARE
             , RADIAL_DIAL_SHAPE_CIRCLE
             }
RadialDialShape ;           // Order is IMPORTANT: do NOT change ! Ordered by ascending memory requirements.


extern const EdgeInfo       RADIAL_DIAL_24_EDGEINFO ;
extern const unsigned char* RADIAL_DIAL_24_EVERY6ALTERNATEEDGEMASK_L2R ;
extern const EdgeInfo       RADIAL_DIAL_60_EDGEINFO ;
extern const unsigned char* RADIAL_DIAL_60_EVERY5ALTERNATEEDGEMASK_L2R ;
extern const EdgeInfo       RADIAL_DIAL_100_EDGEINFO ;
extern const unsigned char* RADIAL_DIAL_100_EVERY10ALTERNATEEDGEMASK_L2R ;