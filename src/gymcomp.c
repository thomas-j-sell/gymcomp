#include <pebble.h>
#include <stdio.h>
#include "weights.c"

#define VIEW 0
#define EDIT 1

static Window *window;
static TextLayer *exercise_layer;
static TextLayer *weight_layer;
int mode;
int current_exercise;
struct Weights weights;


void next_exercise() {
  if(current_exercise == 9 )
    current_exercise = 0;
  else
    current_exercise = current_exercise + 1;
}

void previous_exercise() {
  if(current_exercise == 0 )
    current_exercise = 9;
  else
    current_exercise = current_exercise - 1;
}

char* exercise_string() {
  static char* str;
  
  switch(current_exercise) {
    case 0 :
      str = "BENCH";
      break;
    case 1 :
      str = "BACK";
      break;
    case 2 :
      str = "BICEPS";
      break;
    case 3 :
      str = "TRICEPS";
      break;
    case 4 :
      str = "SHOULDER";
      break;
    case 5 :
      str = "ABS";
      break;
    case 6 :
      str = "QUADS";
      break;
    case 7 :
      str = "HAMMIES";
      break;
    case 8 :
      str = "CALVES";
      break;
    case 9 :
      str = "LEG PRESS";
      break;
  }
  return str;
}

char* weight_string() {
  static char str[65];
  
  switch(current_exercise) {
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
//     text_layer_set_text(text_layer, "VIEW");
  }else{
    mode = EDIT;
//     text_layer_set_text(text_layer, "EDIT");
  }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  char* str;
  previous_exercise();
  str = exercise_string(); 
  text_layer_set_text(exercise_layer, str);
  str = weight_string(); 
  text_layer_set_text(weight_layer, str);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  char* str;
  next_exercise();
  str = exercise_string(); 
  text_layer_set_text(exercise_layer, str);
  str = weight_string();
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
  text_layer_set_text(exercise_layer, weights.name);
  text_layer_set_text_alignment(exercise_layer, GTextAlignmentCenter);
  
  weight_layer = text_layer_create((GRect) { .origin = { 0, bounds.size.h/2 }, .size = { bounds.size.w, bounds.size.h/2 } });
  text_layer_set_font(weight_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  text_layer_set_text(weight_layer, weights.name);
  text_layer_set_text_alignment(weight_layer, GTextAlignmentCenter);
  
  layer_add_child(window_layer, text_layer_get_layer(exercise_layer));
  layer_add_child(window_layer, text_layer_get_layer(weight_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(exercise_layer);
  text_layer_destroy(weight_layer);
}

static void init(void) {
  mode = VIEW;
  current_exercise = 0;
  
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
