#pragma once

#include <pebble.h>

typedef struct Layer ArrowLayer;

ArrowLayer *arrow_layer_create(GRect frame, int32_t angle, GColor color, bool filled, uint8_t stroke_width);
void arrow_layer_destroy(ArrowLayer *arrow_layer);

// Use DEG_TO_TRIGANGLE(angle) for angle in degrees
void arrow_layer_set_angle(ArrowLayer* arrow_layer, int32_t angle);
void arrow_layer_set_color(ArrowLayer* arrow_layer, GColor color);
void arrow_layer_set_filled(ArrowLayer* arrow_layer, bool filled);
void arrow_layer_set_stroke_width(ArrowLayer* arrow_layer, uint8_t stroke_width);