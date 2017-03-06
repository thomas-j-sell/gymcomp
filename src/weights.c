#include <pebble.h>
#include "weights.h"
#include <stdio.h>

struct Exercise
{
  char name[20];
  int weight;
};

const char * exercises[] = {
  "BENCH",
  "BACK",
  "TRICEPS",
  "BICEPS",
  "SHOULDER",
  "ABS",
  "SIDE ABS",
  "QUADS",
  "HAMMIES",
  "CALVES",
  "LEG PRESS",
  "LOWER BACK",
  "SQUAT"
};

const int defaults[] = {
  135,
  180,
  195,
  80,
  65,
  50,
  45,
  155,
  85,
  270,
  260,
  170,
  135
};

struct Exercise weights[13];
int current_exercise = 0;

// @TODO set defaults to 0
void set_default_weights()
{
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "seting default weights");
  for(int i=0; i<13; i++){
    strcpy(weights[i].name, exercises[i]);
    weights[i].weight = defaults[i];
  }
}

//function to save data to watch
void store_weights()
{
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "preparing to store weights");
  uint32_t key = 0;
  for(key = 0; key<13; key++){
    persist_write_int(key, weights[key].weight);
  }
}

//funtion to load data from watch
void load_weights()
{
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "checking for persitent records");
  uint32_t key = 0;
  if(persist_exists(key)) {
    for(key = 0; key<13; key++){
      strcpy(weights[key].name, exercises[key]);
      weights[key].weight = persist_read_int(key);
    }
  } else {
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "No persistent records, setting defaults");
    set_default_weights();
    store_weights();
  }
}

void next_exercise() {
  if(current_exercise == 12 )
    current_exercise = 0;
  else
    current_exercise = current_exercise + 1;
}

void previous_exercise() {
  if(current_exercise == 0 )
    current_exercise = 12;
  else
    current_exercise = current_exercise - 1;
}

char* cur_exercise_str() {
 return weights[current_exercise].name;
}

char* cur_weight_str() {
  static char str[65];
  snprintf(str, 10, "%d", weights[current_exercise].weight);
  return str;
}

void increment_cur_weight()
{
  weights[current_exercise].weight += 5;
}

void decrement_cur_weight()
{
  weights[current_exercise].weight -= 5;
}
