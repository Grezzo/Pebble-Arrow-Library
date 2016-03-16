#include <pebble.h>
#include "arrow_layer.h"

typedef struct {
    int32_t angle;
    GColor color;
    bool filled;
    uint8_t stroke_width;
} ArrowLayerProperties;

typedef struct GPath ArrowPath;

void arrow_layer_set_angle(ArrowLayer* arrow_layer, int32_t angle) {
  ArrowLayerProperties* properties = layer_get_data(arrow_layer);
  properties->angle = angle;
  layer_mark_dirty(arrow_layer);
}

void arrow_layer_set_color(ArrowLayer* arrow_layer, GColor color) {
  ArrowLayerProperties* properties = layer_get_data(arrow_layer);
  properties->color = color;
  layer_mark_dirty(arrow_layer);
}

void arrow_layer_set_filled(ArrowLayer* arrow_layer, bool filled) {
  ArrowLayerProperties* properties = layer_get_data(arrow_layer);
  properties->filled = filled;
  layer_mark_dirty(arrow_layer);
}

void arrow_layer_set_stroke_width(ArrowLayer* arrow_layer, uint8_t stroke_width) {
  ArrowLayerProperties* properties = layer_get_data(arrow_layer);
  properties->stroke_width = stroke_width;
  layer_mark_dirty(arrow_layer);
}


static ArrowPath *arrow_path_create(GPoint center, uint8_t radius, int32_t angle) {
  GPathInfo arrow_path_info = {
    4,
    (GPoint []) {
      {
        radius * sin_lookup(angle) / TRIG_MAX_RATIO,
        -radius * cos_lookup(angle) / TRIG_MAX_RATIO
      }, {
        radius * sin_lookup(angle + TRIG_MAX_ANGLE * 0.375) / TRIG_MAX_RATIO,
        -radius * cos_lookup(angle + TRIG_MAX_ANGLE * 0.375) / TRIG_MAX_RATIO
      }, {
        0,
        0
      }, {
        radius * sin_lookup(angle + TRIG_MAX_ANGLE * 0.625) / TRIG_MAX_RATIO,
        -radius * cos_lookup(angle + TRIG_MAX_ANGLE * 0.625) / TRIG_MAX_RATIO
      }
    }
  };
  ArrowPath *arrow_path = gpath_create(&arrow_path_info);
  gpath_move_to(arrow_path, center);
  return arrow_path;
}

static void arrow_layer_update_proc(ArrowLayer *arrow_layer, GContext *ctx) {
  
  GRect bounds = layer_get_bounds(arrow_layer);
  GPoint center = {bounds.size.w / 2, bounds.size.h / 2};
  uint8_t radius = bounds.size.w < bounds.size.h ? bounds.size.w / 2 - 1 : bounds.size.h / 2 - 1;
  ArrowLayerProperties* properties = (ArrowLayerProperties*) layer_get_data(arrow_layer);

  ArrowPath *arrow_path = arrow_path_create(center, radius, properties->angle);
  
  // Draw arrow
  graphics_context_set_stroke_width(ctx, properties->stroke_width);
  if (properties->filled) {
    graphics_context_set_fill_color(ctx, properties->color);
    gpath_draw_filled(ctx, arrow_path);
  } else {
    graphics_context_set_stroke_color(ctx, properties->color);
    gpath_draw_outline(ctx, arrow_path);
  }
  
  // Destroy arrow path
  gpath_destroy(arrow_path);
}

ArrowLayer *arrow_layer_create(GRect frame, int32_t angle, GColor color, bool filled, uint8_t stroke_width) {
  // Create layer
  ArrowLayer *arrow_layer = layer_create_with_data(frame, sizeof(ArrowLayerProperties));
  // Set arrow layer properties
  ArrowLayerProperties* properties = (ArrowLayerProperties*) layer_get_data(arrow_layer);
  properties->angle = angle;
  properties->color = color;
  properties->filled = filled;
  properties->stroke_width = stroke_width;
  // Set update procedure
  layer_set_update_proc(arrow_layer, arrow_layer_update_proc);
  return arrow_layer;
}

void arrow_layer_destroy(ArrowLayer *arrow_layer) {
  layer_destroy(arrow_layer);
}