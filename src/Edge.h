/*
   File  : Edge.h
   Author: Afonso Santos, Portugal

   Last revision: 16h35 August 06 2016
*/

#pragma once

#include <pebble.h>


typedef struct
{
  uint8_t    v1 ;        // Index of starting vertex.
  uint8_t    v2 ;        // Index of ending vertex.
} Edge ;


typedef struct
{
  uint16_t  edgesNum ;
  Edge     *edges ;
} EdgeInfo ;