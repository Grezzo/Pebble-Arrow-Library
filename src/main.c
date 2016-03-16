#include <pebble.h>
#include "arrow_layer.h"

static Window *s_window;
static ArrowLayer *s_compass_arrow_layer;
static ArrowLayer *s_static_arrow_layer;

static void compass_heading_handler(CompassHeadingData heading_data) {
  // Set angle to match compass heading
  int angle = heading_data.true_heading;
  arrow_layer_set_angle(s_compass_arrow_layer, angle);
  
  // Set color and fill mode depending on angle
  bool filled;
  if (angle < TRIG_MAX_ANGLE / 2) {
    #ifdef PBL_COLOR
      arrow_layer_set_color(s_compass_arrow_layer, GColorRed);
    #endif
    filled = true;
  } else {
    #ifdef PBL_COLOR
      arrow_layer_set_color(s_compass_arrow_layer, GColorGreen);
    #endif
    filled = false;
  }
  arrow_layer_set_filled(s_compass_arrow_layer, filled);
}

void main_window_load(Window *window) {
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Set initial color and direction
  GColor compass_arrow_color;
  #ifdef PBL_COLOR
    compass_arrow_color = GColorRed;
  #else
    compass_arrow_color = GColorBlack;
  #endif

  // Create arrow layers
  GRect frame = GRect(28,
                      28,
                      50,
                      50);
  s_static_arrow_layer = arrow_layer_create(frame, DEG_TO_TRIGANGLE(338), GColorBlack, false, 1);
  s_compass_arrow_layer = arrow_layer_create(bounds, DEG_TO_TRIGANGLE(45), compass_arrow_color, true, 5);
  // Add arrow layers to window
  layer_add_child(window_layer, s_static_arrow_layer);
  layer_add_child(window_layer, s_compass_arrow_layer);
  // Subscribe to compass service so we can make arrow point to North
  compass_service_subscribe(compass_heading_handler);
}

void main_window_unload(Window *window) {
  // Unsubscribe from compasss service
  compass_service_unsubscribe();
  
  // Destroy arrow layer
  arrow_layer_destroy(s_static_arrow_layer);
  arrow_layer_destroy(s_compass_arrow_layer);
}

void init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_window, true);
}

void deinit(void) {
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
