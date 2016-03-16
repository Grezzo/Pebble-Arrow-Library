# Pebble-Arrow-Library
An library for Pebble watchapps that draws an arrow on the screen that can be updated with color, angle, etc.

This repo also contains a project that demonstrates the library by drawing two arrows, one that always points to north, and one that is static.

##Use:
Add the `arrow_layer.h` and `arrow_layer.c` files to your project

Include the header in your source (`#include "arrow_layer.c"`)

##Declare:
```
static ArrowLayer *s_arrow_layer;
```

##Create:
```
s_arrow_layer = arrow_layer_create(GRect(0, 0, 50, 50), DEG_TO_TRIGANGLE(90), GColorBlack, false, 1);
```

##Add to window:
```
layer_add_child(window_layer, s_arrow_layer);
```

##Set properties:
```
arrow_layer_set_angle(s_arrow_layer, DEG_TO_TRIGANGLE(45));
arrow_layer_set_color(s_arrow_layer, GColorRed);
arrow_layer_set_filled(s_arrow_layer, true);
arrow_layer_set_stroke_width(s_arrow_layer, 5);
```

##Destroy:
`arrow_layer_destroy(s_arrow_layer);`



...have fun
