#include <pebble.h>
#define BUTTON_UP 1
#define BUTTON_SELECT 2
#define BUTTON_DOWN 3
#define KEY_BUTTON_EVENT 0

static Window *window;
static GBitmap *image;
static Layer *layer;

static void in_received_handler(DictionaryIterator *iter, void *context) 
{
    
}

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


static void layer_update_callback(Layer *me, GContext* ctx) {
  // We make sure the dimensions of the GRect to draw into
  // are equal to the size of the bitmap--otherwise the image

  GRect bounds = image->bounds;

  graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 0, 0 }, .size = bounds.size });

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

void send_int(uint8_t key, uint8_t cmd)
{
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
      
    Tuplet value = TupletInteger(key, cmd);
    dict_write_tuplet(iter, &value);
      
    app_message_outbox_send();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	send_int(KEY_BUTTON_EVENT, BUTTON_SELECT);
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
	send_int(KEY_BUTTON_EVENT, BUTTON_UP);
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
	send_int(KEY_BUTTON_EVENT, BUTTON_DOWN);
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

static void init(void) {
	
	//Register AppMessage events
	app_message_register_inbox_received(in_received_handler);           
	app_message_open(512, 512);    //Large input and output buffer sizes
	
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