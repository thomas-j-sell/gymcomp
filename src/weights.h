
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

char* get_weights_name();