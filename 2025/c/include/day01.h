#ifndef DAY01_H
#define DAY01_H

// #include <stdio.h>
#include <stddef.h>

typedef struct Turn {
  char direction;
  int amount;
} Turn;

typedef struct Sequence {
  Turn *turn;
  size_t size;
  size_t capacity;
} Sequence;

int day01_part1(const char *input_path);

int day01_part2(const char *input_path);


#endif // DAY01_H
