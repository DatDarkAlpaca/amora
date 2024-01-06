#pragma once
#include "common.h"
#include <stdbool.h>

void clear_screen();

void flush();

void wait_press();

HEAP_ALLOCATED char* get_input();

void clear_input(HEAP_ALLOCATED char* input);

unsigned int get_input_number();