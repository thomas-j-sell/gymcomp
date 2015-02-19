#include <pebble.h>
#include "weights.h"
#include <stdio.h>

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
};

struct Weights weights;
int current_exercise = 0;


// @TODO set defaults to 0
void set_default_weights()  
{
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
}


//function to save data to watch
void store_weights()
{
  uint32_t key = 0;
  persist_write_string(key, weights.name);
  key = 1;
  persist_write_int(key, weights.bench);
  key = 2;
  persist_write_int(key, weights.back);
  key = 3;
  persist_write_int(key, weights.biceps);
  key = 4;
  persist_write_int(key, weights.triceps);
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
}


//funtion to load data from watch
void load_weights()
{
  //check for valid storage keys
  uint32_t key = 0;
  if(persist_exists(key)) {
    int buffsize = 10;
    char buffer[buffsize];
    persist_read_string(key,buffer,buffsize);
    strcpy(weights.name, buffer);

    key = 1;
    weights.bench = persist_read_int(key);
    key = 2;
    weights.back = persist_read_int(key);
    key = 3;
    weights.biceps = persist_read_int(key);
    key = 4;
    weights.triceps = persist_read_int(key);
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

  } else {
    set_default_weights();
    store_weights();
  }
}

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

char* get_weights_name()
{
  return weights.name;
}