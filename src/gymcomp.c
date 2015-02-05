#include <pebble.h>
#include <stdio.h>
#include "weights.c"

#define VIEW 0
#define EDIT 1

static Window *window;
static TextLayer *text_layer;
int mode;
int current_exersize;
struct Weights weights;


void next_exersize() {
  if(current_exersize == 9 )
    current_exersize = 0;
  else
    current_exersize = current_exersize + 1;
}

void previous_exersize() {
  if(current_exersize == 0 )
    current_exersize = 9;
  else
    current_exersize = current_exersize - 1;
}

char* weight_string() {
  static char str[65];
  
  switch(current_exersize) {
    case 0 :
      snprintf(str, 10, "%d", weights.bench);
      break;
    case 1 :
      snprintf(str, 10, "%d", weights.back);
      break;
    case 2 :
      snprintf(str, 10, "%d", weights.biceps);
      break;
    case 3 :
      snprintf(str, 10, "%d", weights.triceps);
      break;
    case 4 :
      snprintf(str, 10, "%d", weights.shoulder);
      break;
    case 5 :
      snprintf(str, 10, "%d", weights.ab);
      break;
    case 6 :
      snprintf(str, 10, "%d", weights.quads);
      break;
    case 7 :
      snprintf(str, 10, "%d", weights.hammies);
      break;
    case 8 :
      snprintf(str, 10, "%d", weights.calves);
      break;
    case 9 :
      snprintf(str, 10, "%d", weights.legpress);
      break;
  }
  return str;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Mode: %i", mode);
  if(mode){
    mode = VIEW;
    text_layer_set_text(text_layer, "VIEW");
  }else{
    mode = EDIT;
    text_layer_set_text(text_layer, "EDIT");
  }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  previous_exersize();
  char* str = weight_string(); 
  text_layer_set_text(text_layer, str);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  next_exersize();
  char* str = weight_string();
  text_layer_set_text(text_layer, str);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 30 }, .size = { bounds.size.w, bounds.size.h } });
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text(text_layer, weights.name);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  mode = VIEW;
  current_exersize = 0;
  
  // init weights @TODO change this to read in weights from persisten memory
  weights.name = "Tom";
  weights.bench = 85;
  weights.back = 85;
  weights.biceps = 45;
  weights.triceps = 100;
  weights.shoulder = 25;
  weights.ab = 40;
  weights.quads = 115;
  weights.hammies = 85;
  weights.calves = 165;
  weights.legpress = 180;
  
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

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
