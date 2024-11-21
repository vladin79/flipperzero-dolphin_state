#ifndef PASSPORT
#define PASSPORT

#include <stdint.h>

char* timestamp_to_datetime_string(void);
uint8_t passport_level(void);
char* passport_mood(void);
float passport_complete(void);

#endif
