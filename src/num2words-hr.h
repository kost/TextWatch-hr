#pragma once

#include "string.h"

void fuzzy_time_to_words(int hours, int minutes, char* words, size_t length);
void time_to_words(int hours, int minutes, char* words, size_t length);
void time_to_2words(int hours, int minutes, char* words, size_t length, char* words2, size_t length2);

