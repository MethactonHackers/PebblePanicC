#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static GBitmap *image;
static Layer *layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	//image = gbitmap_create_with_resource(RESOURCE_ID_TEST_IMAGE);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	//image = gbitmap_create_with_resource(RESOURCE_ID_TEST_IMAGE);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	//image = gbitmap_create_with_resource(RESOURCE_ID_TEST_IMAGE);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void layer_update_callback(Layer *me, GContext* ctx) {
  // We make sure the dimensions of the GRect to draw into
  // are equal to the size of the bitmap--otherwise the image

  GRect bounds = image->bounds;

  graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 0, 0 }, .size = bounds.size });

}

static void window_load(Window *window) {
	// Init the layer for display the image
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_set_update_proc(layer, layer_update_callback);
  layer_add_child(window_layer, layer);

	//Draws the Image
  image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HOME);
	
}
static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });

	
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}