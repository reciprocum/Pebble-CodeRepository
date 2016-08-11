/*
   File  : SegmentDisplay2D_16E9V.c
   Author: Afonso Santos, Portugal

   Last revision: 16h05 August 06 2016
*/

#include "Config.h"
#include "Binary.h"
#include "I2_8.h"
#include "Edge.h"


const I2_8_PathInfo SEG_16E9V_VERTEXINFO
= { .pointsNum = 9
  , .points    = (I2_8[])
                 { { 120, 120 }     // v0
                 , { 120,   0 }     // v1
                 , { 120,-120 }     // v2
                 , {   0,-120 }     // v3
                 , {-120,-120 }     // v4
                 , {-120,   0 }     // v5
                 , {-120, 120 }     // v6
                 , {   0, 120 }     // v7
                 , {   0,   0 }     // v8
                 }
  }
;

const EdgeInfo SEG_16E9V_EDGEINFO
= { .edgesNum = 16
  , .edges    = (Edge[])
                { { 0, 1 }      // e0
                , { 1, 2 }      // e1
                , { 2, 3 }      // e2
                , { 3, 4 }      // e3
                , { 4, 5 }      // e4
                , { 5, 6 }      // e5
                , { 6, 7 }      // e6
                , { 7, 0 }      // e7
                , { 0, 8 }      // e8
                , { 1, 8 }      // e9
                , { 2, 8 }      // e10
                , { 3, 8 }      // e11
                , { 4, 8 }      // e12
                , { 5, 8 }      // e13
                , { 6, 8 }      // e14
                , { 7, 8 }      // e15
                }
  }
;


const unsigned char *SEG_16E9V_DIGIT_EDGEMAP_L2R[10]         // IMPORTANT: use left to right (L2R) bit indexing methods when decoding.
// Bit index ruller      [00..07]    [08..15]
//                       00000000    00111111
//                       01234567    89012345
= { (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #0   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #1   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #2   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #3   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #4   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #5   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #6   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #7   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #8   TODO: 
  , (unsigned char[]){ 0b00000000, 0b00000000 }   // edge config for value #9   TODO: 
  }
;


/* DEPRECATED
const uint32_t valueEdgeMap_SEG_16E9V[10]
= { B0 | B1 | B2 | B3 | B4 | B5 | B6 | B7 | B8 | B12      // edge config for value #0
  , B0 | B1 | B8                                          // edge config for value #1
  , B6 | B7 | B0 | B9 | B12| B3 | B2                      // edge config for value #2
  , B6 | B7 | B0 | B9 | B1 | B2 | B3                      // edge config for value #3
  , B5 | B13| B9 | B0 | B1                                // edge config for value #4
  , B7 | B6 | B5 | B13| B10| B2 | B3                      // edge config for value #5
  ,      B6 | B5 | B4 | B3 | B2 | B1 | B9 | B13           // edge config for value #6
  , B6 | B7 | B8 | B11                                    // edge config for value #7
  , B0 | B1 | B2 | B3 | B4 | B5 | B6 | B7 | B9 | B13      // edge config for value #8
  , B9 | B13| B5 | B6 | B7 | B0 | B1 | B2                 // edge config for value #9
  }
;*/
