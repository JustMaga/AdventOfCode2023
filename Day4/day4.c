#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FILE_LENGTH 212
#define MAX_LINE_LENGTH 120

int find_winning_numbers(char *arr, bool is_part_1){
  bool is_first_n = true, string_divider = false, winning_numbers[99] = {false};
  int number = 0, card_points = 0;

  for (int j = 0; j <= strlen(arr) ; j++){
    switch (string_divider) {
      case false:
        if (isdigit(arr[j])) {
          number *= 10;
          number += (arr[j] - '0');
        }
        else if (arr[j] == '|'){
          string_divider = true;
        }
        else {
          if (number != 0) winning_numbers[number-1] = true;
          number = 0;
        }
        break;
      case true:
        if (isdigit(arr[j])) {
          number *= 10;
          number += (arr[j] - '0');
        }
        else {
          if (winning_numbers[number-1] == true && is_part_1){
            if (is_first_n) {
              card_points++;
              is_first_n = false;
            }
            else card_points *= 2;
          }
          if (winning_numbers[number-1] == true && !is_part_1) card_points++;
          number = 0;
        }
        break;
      }
    }
  return card_points;
}


void part_1(char *arr[]){
  int sum = 0;
  for (int i = 0; i < FILE_LENGTH; i++){
    sum += find_winning_numbers(arr[i], true);
  }
  printf("Sum of winnig cards: %d\n", sum);
}


void part_2(char *arr[]){
  int sum = 0, card_repetition[FILE_LENGTH] = {0};

  for (int i = 0; i < FILE_LENGTH; i++){
    int new_copies;
    for (int j = 0; j <= card_repetition[i]; j++){
      new_copies = find_winning_numbers(arr[i], false);
      for (; new_copies > 0; new_copies--) card_repetition[i+new_copies]++;
    }
  }
  for (int i = 0; i < FILE_LENGTH; i++) {sum += (card_repetition[i]+1);}
  printf("Sum of all scratchcards: %d\n", sum);
}


int main(){
  FILE *file = fopen("input.txt", "r");
  if (file == 0){
    printf("Error opening the file\n");
    return 1;
  }

  char line[MAX_LINE_LENGTH];
  char *values[FILE_LENGTH];
  for (int i = 0; i < FILE_LENGTH; i++){
    values[i]= malloc(MAX_LINE_LENGTH);
  }

  int index = 0;
  while (fgets(line, sizeof(line), file)) {
    int end_line = 0;
    for (end_line; line[end_line] != '\n'; end_line++){}
    strncpy(values[index], &line[10], end_line-10);
    index++;
  }
  fclose(file);
  part_1(values);
  part_2(values);
  return 0;
}

