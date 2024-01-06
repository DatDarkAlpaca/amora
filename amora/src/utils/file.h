#pragma once
#include "common.h"
#include <stdbool.h>

typedef struct file_results
{
	HEAP_ALLOCATED char* contents;
	bool valid;
} file_results;

file_results read_file(const char* filepath);

void close_file(file_results result);