#include <pebble.h>
#include "weights.h"

#define VIEW 0
#define EDIT 1

static Window *window;
static TextLayer *exercise_layer;
static TextLayer *weight_layer;
int mode;


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  mode = mode ? VIEW : EDIT;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Mode: %i", mode);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  char* str;
  previous_exercise();
  str = cur_exercise_str(); 
  text_layer_set_text(exercise_layer, str);
  str = cur_weight_str(); 
  text_layer_set_text(weight_layer, str);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  char* str;
  next_exercise();
  str = cur_exercise_str(); 
  text_layer_set_text(exercise_layer, str);
  str = cur_weight_str();
  text_layer_set_text(weight_layer, str);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  exercise_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, bounds.size.h/2 } });
//   text_layer_set_background_color(exercise_layer, GColorBlack);
  text_layer_set_font(exercise_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text(exercise_layer, cur_exercise_str());
  text_layer_set_text_alignment(exercise_layer, GTextAlignmentCenter);
  
  weight_layer = text_layer_create((GRect) { .origin = { 0, bounds.size.h/2 }, .size = { bounds.size.w, bounds.size.h/2 } });
  text_layer_set_font(weight_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  text_layer_set_text(weight_layer, cur_weight_str());
  text_layer_set_text_alignment(weight_layer, GTextAlignmentCenter);
  
  layer_add_child(window_layer, text_layer_get_layer(exercise_layer));
  layer_add_child(window_layer, text_layer_get_layer(weight_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(exercise_layer);
  text_layer_destroy(weight_layer);
}

static void init(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Init");
  mode = VIEW;
  
  load_weights();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Loaded weights");
  
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
  store_weights();
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
