#include <pebble.h>
#define KEY_DATA 5

static Window *window;
static GBitmap *image;
static Layer *layer;

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

/*static void inbox_recieved_callback() {
	 // Get the first pair
  Tuple *t = dict_read_first(iterator);

  // Process all pairs present
  while(t != NULL) {
    // Process this pair's key
    switch (t->key) {
      case KEY_DATA:
        APP_LOG(APP_LOG_LEVEL_INFO, "KEY_DATA received with value %d", (int)t->value->int32);
        break;
    }

    // Get next pair, if any
    t = dict_read_next(iterator);
  }
};
*/

static void layer_update_callback(Layer *me, GContext* ctx) {
  // We make sure the dimensions of the GRect to draw into
  // are equal to the size of the bitmap--otherwise the image

  GRect bounds = image->bounds;

  graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 0, 0 }, .size = bounds.size });

}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	gbitmap_destroy(image);
	layer_destroy(layer);
	// Init the layer for display the image
  Layer *window_layer = window_get_root_layer(window);
	//window_set_fullscreen(window, true);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_set_update_proc(layer, layer_update_callback);
  layer_add_child(window_layer, layer);

	//Draws the Image
	image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_EMERGENCY);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	gbitmap_destroy(image);
	layer_destroy(layer);
	// Init the layer for display the image
  Layer *window_layer = window_get_root_layer(window);
	//window_set_fullscreen(window, true);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_set_update_proc(layer, layer_update_callback);
  layer_add_child(window_layer, layer);

	//Draws the Image
	image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_AMBULANCE);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	gbitmap_destroy(image);
	layer_destroy(layer);
	// Init the layer for display the image
  Layer *window_layer = window_get_root_layer(window);
	//window_set_fullscreen(window, true);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_set_update_proc(layer, layer_update_callback);
  layer_add_child(window_layer, layer);

	//Draws the Image
	image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_FIRE_POLICE);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
	// Init the layer for display the image
  Layer *window_layer = window_get_root_layer(window);
	//window_set_fullscreen(window, true);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_set_update_proc(layer, layer_update_callback);
  layer_add_child(window_layer, layer);

	//Draws the Image
  image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HOME);
	
}


static void init(void) {
	
	// Register callbacks
	app_message_register_inbox_received(inbox_received_callback);
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_register_outbox_failed(outbox_failed_callback);
	app_message_register_outbox_sent(outbox_sent_callback);
	
	//Open AppMessage
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
  });

	
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
	gbitmap_destroy(image);
	layer_destroy(layer);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}