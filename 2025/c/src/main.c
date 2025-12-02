#include "../include/day01.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

  if(argc < 2) {
    printf("Solution day not passed correctly!\n Usage: %s <day>\n", argv[0]);
    return 1;
  }

  if(strcmp(argv[1], "1") == 0) {
    printf("The results from day01 are:\n");
    int result1 = day01_part1("../inputs/day01.txt");
    printf("Part 1: %d\n", result1);

    int result2 = day01_part2("../inputs/day01.txt");
    printf("Part 2: %d\n", result2);
  }




  return 0;
}
