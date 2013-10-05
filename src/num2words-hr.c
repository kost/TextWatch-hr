#include "num2words-hr.h"
#include "string.h"

static const char* const ONES[] = {
  "nula",
  "jedan",
  "dva",
  "tri",
  "cetiri",
  "pet",
  "sest",
  "sedam",
  "osam",
  "devet"
};

static const char* const TEENS[] ={
  "",
  "jedanaest",
  "dvanaest",
  "trinaest",
  "cetrnaest",
  "petnaest",
  "sestnaest",
  "sedamnaest",
  "osamnaest",
  "devetnaest"
};

static const char* const TENS[] = {
  "",
  "deset",
  "dvadeset",
  "trideset",
  "cetrideset",
  "pedeset",
  "sestdeset",
  "sedamdeset",
  "osamdeset",
  "devetdeset"
};

static const char* STR_OH_CLOCK = "sat";
static const char* STR_OH_MCLOCK = "sata";
static const char* STR_OH_PCLOCK = "sati";
static const char* STR_NOON = "podne";
static const char* STR_MIDNIGHT = "ponoc";
static const char* STR_11 = "11";

static size_t append_number(char* words, int num) {
  int tens_val = num / 10 % 10;
  int ones_val = num % 10;

  size_t len = 0;

  if (tens_val > 0) {
    if (tens_val == 1 && num != 10) {
      strcat(words, TEENS[ones_val]);
      return strlen(TEENS[ones_val]);
    }
    strcat(words, TENS[tens_val]);
    len += strlen(TENS[tens_val]);
    if (ones_val > 0) {
      strcat(words, " ");
      len += 1;
    }
  }

  if (ones_val > 0 || num == 0) {
    strcat(words, ONES[ones_val]);
    len += strlen(ONES[ones_val]);
  }
  return len;
}

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}


void time_to_2words(int hours, int minutes, char* words, size_t length, char* words2, size_t length2) {

  size_t remaining = length;
  memset(words, 0, length);

  size_t remaining2 = length2;
  memset(words2, 0, length2);

  if (hours == 0) {
    remaining -= append_string(words, remaining, STR_MIDNIGHT);
  } else if (hours == 11) {
    remaining -= append_string(words, remaining, STR_11);
  } else if (hours == 12) {
    remaining -= append_string(words, remaining, STR_NOON);
  } else {
    remaining -= append_number(words, hours % 12);
  }
  if (minutes == 0 ) {
    hours = hours % 12;
    if (hours==1) {
       remaining2 -= append_string(words2, remaining2, STR_OH_CLOCK);
    } else if (hours<5) {
       remaining2 -= append_string(words2, remaining2, STR_OH_MCLOCK);
    } else {
       remaining2 -= append_string(words2, remaining2, STR_OH_PCLOCK);
    }
  } else {
    remaining2 -= append_number(words2, minutes);
  } 


}

