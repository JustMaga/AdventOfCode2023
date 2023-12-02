#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FILE_LENGTH 100
#define MAX_LINE_LENGTH 170

#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14


void part_1(char *arr[]){
  int number_of_cubes, sum = 0;
  char color_of_n;
  for (int i = 0; i < FILE_LENGTH; i++){
    bool is_game_possible = true;
    for (int j = 0; j < strlen(arr[i]) && is_game_possible == true; j++){
      if (isdigit(arr[i][j])){
        number_of_cubes = arr[i][j] - '0';
        color_of_n = arr[i][j+2];
        if (isdigit(arr[i][j+1])){
          number_of_cubes *=10;
          number_of_cubes += arr[i][j+1] - '0';
          color_of_n = arr[i][j+3];
        }
        switch (color_of_n) {
          case 'r':
            if(number_of_cubes > MAX_RED_CUBES) is_game_possible = false;
            break;
          case 'g':
            if(number_of_cubes > MAX_GREEN_CUBES) is_game_possible = false;
            break;
         case 'b':
            if(number_of_cubes > MAX_BLUE_CUBES) is_game_possible = false;
            break;
        }
      }
      if (is_game_possible == false){
      }
    }
    if (is_game_possible) sum += i+1; //add 1 because the index starts from 0 and not 1
  }
  printf("Sum of all possible games: %d\n", sum);
}


void part_2(char *arr[]){
  int number_of_cubes, sum = 0;
  char color_of_n;
  for (int i = 0; i < FILE_LENGTH; i++){
    int min_possible_red = 0, min_possible_green = 0, min_possible_blue = 0; 
    for (int j = 0; j < strlen(arr[i]); j++){
      if (isdigit(arr[i][j])){
        number_of_cubes = arr[i][j] - '0';
        color_of_n = arr[i][j+2];
        if (isdigit(arr[i][j+1])){
          number_of_cubes *=10;
          number_of_cubes += arr[i][j+1] - '0';
          color_of_n = arr[i][j+3];
        }
        switch (color_of_n) {
          case 'r':
            if(number_of_cubes > min_possible_red) min_possible_red = number_of_cubes;
            break;
          case 'g':
            if(number_of_cubes > min_possible_green) min_possible_green = number_of_cubes;
            break;
         case 'b':
            if(number_of_cubes > min_possible_blue) min_possible_blue = number_of_cubes;
            break;
        }
      }
    }
    sum += (min_possible_red * min_possible_green * min_possible_blue);
  }
  printf("Sum of power of each game: %d\n", sum);
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
    strncpy(values[index], &line[8], end_line-8); //remove Game n: from the string since the index is n
    index++;
  }
  fclose(file);

  part_1(values);
  part_2(values);

  return 0;
}

