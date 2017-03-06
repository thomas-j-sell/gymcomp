
// functions to write or read to or from persistent memory
void set_default_weights();
void store_weights();
void load_weights();

// rotate current exercise thorugh available exercises
void next_exercise();
void previous_exercise();

// return info about current exercise
char* cur_exercise_str();
char* cur_weight_str();

// alter current exercise weight
void increment_cur_weight();
void decrement_cur_weight();
