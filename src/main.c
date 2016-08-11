/*
   Project: ???
   File   : main.c
   Author : Afonso Santos, Portugal

   Last revision: 16h55 August 06 2016
*/

#include "Config.h"
#include <pebble.h>


// UI related
static Window         *window ;
static Layer          *world_layer ;
static ActionBarLayer *action_bar;


void
world_initialize
( )
{ }


void
world_start
( )
{ }


static
void
world_update
( )
{ }


static void
world_draw
( Layer    *me
, GContext *gCtx
)
{ }


void
world_stop
( )
{ }


void
world_finalize
( )
{ }


void
window_load
( Window *window )
{
  Layer *window_root_layer = window_get_root_layer( window ) ;

  action_bar = action_bar_layer_create( ) ;
  action_bar_layer_add_to_window( action_bar, window ) ;

  GRect bounds = layer_get_frame( window_root_layer ) ;
  world_layer = layer_create( bounds ) ;
  layer_set_update_proc( world_layer, world_draw ) ;
  layer_add_child( window_root_layer, world_layer ) ;

  // Position clock handles according to current time, launch blinkers, launch animation, start clock.
  world_start( ) ;
}


void
window_unload
( Window *window )
{
  world_stop( ) ;
  layer_destroy( world_layer ) ;
}


void
app_initialize
( void )
{
  world_initialize( ) ;

  window = window_create( ) ;
  window_set_background_color( window, GColorBlack ) ;
 
  window_set_window_handlers( window
                            , (WindowHandlers)
                              { .load   = window_load
                              , .unload = window_unload
                              }
                            ) ;

  window_stack_push( window, false ) ;
}


void
app_finalize
( void )
{
  window_stack_remove( window, false ) ;
  window_destroy( window ) ;
  world_finalize( ) ;
}


int
main
( void )
{
  app_initialize( ) ;
  app_event_loop( ) ;
  app_finalize( ) ;
}