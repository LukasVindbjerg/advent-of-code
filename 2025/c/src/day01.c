#include "../include/day01.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 256
#define DIAL_SIZE 100


int sequence_push(Sequence *seq, Turn t) {
    if (seq->size == seq->capacity) {
        size_t new_cap = seq->capacity ? seq->capacity * 2 : 16;
        void *tmp = realloc(seq->turn, new_cap * sizeof *seq->turn);
        if (!tmp) {
            return 0; // allocation failed
        }
        seq->turn = tmp;
        seq->capacity = new_cap;
    }
    seq->turn[seq->size++] = t;
    return 1;
}



void sequence_free(Sequence *seq) {

    free(seq->turn);
    seq->turn = NULL;
    seq->size = 0;
    seq->capacity = 0;
}




Turn loadTurn(const char *line) {
  Turn t;

  t.direction = line[0];       // first character
  t.amount = atoi(line + 1);   // convert the rest to int

  return t;
}


Sequence loadSequence(FILE *f){

  Sequence seq;
  seq.turn = NULL;
  seq.size = 0;
  seq.capacity = 0;

  char line[MAX_LINE]; // Line buffer

  while (f && fgets(line, sizeof(line), f)) // This goes line by line 
  {
    Turn t = loadTurn(line);
    sequence_push(&seq, t);
  }

  return seq;
}


int day01_part1(const char *input_path){

  FILE *fptr;

  fptr = fopen(input_path, "r");
  if (!fptr) {return 0;}

  Sequence seq = loadSequence(fptr);

  fclose(fptr);

  int dial_pos = 50; // Initial dial position is 50
  int zero_ctr = 0;


  for (size_t i = 0; i < seq.size; i++) {
    

    int sign = (seq.turn[i].direction == 'R') ? 1 : -1;

    int change = sign * seq.turn[i].amount;


    // We do modulo as this basically makes a circle.
    dial_pos = (dial_pos + change) % DIAL_SIZE;

    // C doesnt handle negative modulus correctly where -23%100=77,
    // but we can just always add another 100 if it is negative. 
    // Even though it looks ugly it works.
    if (dial_pos < 0) {
      dial_pos += DIAL_SIZE;
    }

    if (dial_pos == 0) {
      zero_ctr++;
    }

  }


  sequence_free(&seq);


  return zero_ctr;
}

int dial_zero_passings(int pos, int sign, int amount) {
    if (amount <= 0) return 0;

    if (sign > 0) {
        // Move to the right: count how many multiples of 100 we cross
        return (pos + amount) / DIAL_SIZE;
    } else if (sign < 0) {
        // Move to the left: mirror to a right-move on a transformed dial
        int q = (DIAL_SIZE - pos) % DIAL_SIZE;
        return (q + amount) / DIAL_SIZE;
    } else {
        // Error basecase
        return 0;
    }
}

int day01_part2(const char *input_path){

  FILE *fptr;

  fptr = fopen(input_path, "r");
  if (!fptr) {return 0;}

  Sequence seq = loadSequence(fptr);

  fclose(fptr);

  int dial_pos = 50; // Initial dial position is 50
  int zero_ctr = 0;


  for (size_t i = 0; i < seq.size; i++) {
    
    int sign = (seq.turn[i].direction == 'R') ? 1 : -1;

    int change = sign * seq.turn[i].amount;

    zero_ctr += dial_zero_passings(dial_pos, sign, seq.turn[i].amount);


    // We do modulo as this basically makes a circle.
    dial_pos = (dial_pos + change) % DIAL_SIZE;

    // C doesnt handle negative modulus correctly where -23%100=77,
    // but we can just always add another 100 if it is negative. 
    // Even though it looks ugly it works.
    if (dial_pos < 0) {
      dial_pos += DIAL_SIZE;
    }

  }


  sequence_free(&seq);

  return zero_ctr;
}
