#include <pebble.h>
#include "weights.h"
#include <stdio.h>

// @TODO add method to save multiple instances of Weights, pass in a number to manipulate storage keys
// @TODO remove Weights.name an all references

struct Weights
{
  char* name;
  int bench;
  int back;
  int biceps;
  int triceps;
  int shoulder;
  int ab;
  int quads;
  int hammies;
  int calves;
  int legpress;
  int lback;
};

struct Weights weights;
int current_exercise = 0;


// @TODO set defaults to 0
void set_default_weights()
{
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "seting default weights");
  weights.name = "Tom";
  weights.bench = 105;
  weights.back = 110;
  weights.triceps = 125;
  weights.biceps = 55;
  weights.shoulder = 45;
  weights.ab = 45;
  weights.quads = 125;
  weights.hammies = 70;
  weights.calves = 160;
  weights.legpress = 180;
  weights.lback = 90;
}


//function to save data to watch
void store_weights()
{
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "preparing to store weights");
  uint32_t key = 0;
  persist_write_string(key, weights.name);
  key = 1;
  persist_write_int(key, weights.bench);
  key = 2;
  persist_write_int(key, weights.back);
  key = 3;
  persist_write_int(key, weights.triceps);
  key = 4;
  persist_write_int(key, weights.biceps);
  key = 5;
  persist_write_int(key, weights.shoulder);
  key = 6;
  persist_write_int(key, weights.ab);
  key = 7;
  persist_write_int(key, weights.quads);
  key = 8;
  persist_write_int(key, weights.hammies);
  key = 9;
  persist_write_int(key, weights.calves);
  key = 10;
  persist_write_int(key, weights.legpress);
  key = 11;
  persist_write_int(key, weights.lback);
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "Stored weights");
}


//funtion to load data from watch
void load_weights()
{
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "checking for persitent records");
  uint32_t key = 0;
  if(persist_exists(key)) {
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "Reading name");
    int buffsize = 10;
    char buffer[buffsize];
    persist_read_string(key,buffer,buffsize);
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "Read name");
    weights.name = buffer;
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "copyied name");

    key = 1;
    weights.bench = persist_read_int(key);
    key = 2;
    weights.back = persist_read_int(key);
    key = 3;
    weights.triceps = persist_read_int(key);
    key = 4;
    weights.biceps = persist_read_int(key);
    key = 5;
    weights.shoulder = persist_read_int(key);
    key = 6;
    weights.ab = persist_read_int(key);
    key = 7;
    weights.quads = persist_read_int(key);
    key = 8;
    weights.hammies = persist_read_int(key);
    key = 9;
    weights.calves = persist_read_int(key);
    key = 10;
    weights.legpress = persist_read_int(key);
    key = 11;
    weights.lback = persist_read_int(key);

  } else {
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "No persistent records, setting defaults");
    set_default_weights();
    store_weights();
  }
}

void next_exercise() {
  if(current_exercise == 10 )
    current_exercise = 0;
  else
    current_exercise = current_exercise + 1;
}

void previous_exercise() {
  if(current_exercise == 0 )
    current_exercise = 10;
  else
    current_exercise = current_exercise - 1;
}

char* cur_exercise_str() {
  static char* str;

  switch(current_exercise) {
    case 0 :
    str = "BENCH";
    break;
    case 1 :
    str = "BACK";
    break;
    case 2 :
    str = "TRICEPS";
    break;
    case 3 :
    str = "BICEPS";
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
    case 10 :
    str = "LOW BACK";
    break;
  }
  return str;
}

char* cur_weight_str() {
  static char str[65];

  switch(current_exercise) {
    case 0 :
    snprintf(str, 10, "%d", weights.bench);
    break;
    case 1 :
    snprintf(str, 10, "%d", weights.back);
    break;
    case 2 :
    snprintf(str, 10, "%d", weights.triceps);
    break;
    case 3 :
    snprintf(str, 10, "%d", weights.biceps);
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
    case 10 :
    snprintf(str, 10, "%d", weights.lback);
    break;
  }
  return str;
}

void increment_cur_weight()
{
  switch(current_exercise) {
    case 0 :
    weights.bench += 5;
    break;
    case 1 :
    weights.back += 5;
    break;
    case 2 :
    weights.triceps += 5;
    break;
    case 3 :
    weights.biceps += 5;
    break;
    case 4 :
    weights.shoulder += 5;
    break;
    case 5 :
    weights.ab += 5;
    break;
    case 6 :
    weights.quads += 5;
    break;
    case 7 :
    weights.hammies += 5;
    break;
    case 8 :
    weights.calves += 5;
    break;
    case 9 :
    weights.legpress += 5;
    break;
    case 10 :
    weights.lback += 5;
    break;
  }
}

void decrement_cur_weight()
{
  switch(current_exercise) {
    case 0 :
    weights.bench -= 5;
    break;
    case 1 :
    weights.back -= 5;
    break;
    case 2 :
    weights.triceps -= 5;
    break;
    case 3 :
    weights.biceps -= 5;
    break;
    case 4 :
    weights.shoulder -= 5;
    break;
    case 5 :
    weights.ab -= 5;
    break;
    case 6 :
    weights.quads -= 5;
    break;
    case 7 :
    weights.hammies -= 5;
    break;
    case 8 :
    weights.calves -= 5;
    break;
    case 9 :
    weights.legpress -= 5;
    break;
    case 10 :
    weights.lback -= 5;
    break;
  }
}

char* get_weights_name()
{
  return weights.name;
}
