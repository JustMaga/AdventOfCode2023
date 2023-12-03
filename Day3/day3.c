#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define FILE_LENGTH 140
#define MAX_LINE_LENGTH 150

int check (char *arr[], int i, int j, bool is_part_1){
  char element = arr[i][j];
  if (is_part_1){
    //all possible cases
    bool left = (j != 0 && !isdigit(arr[i][j-1]) && arr[i][j-1] != '.');
    bool right = (j != (strlen(arr[i])-1) && !isdigit(arr[i][j+1]) && arr[i][j+1] != '.');
    bool up = (i != 0 && ((!isdigit(arr[i-1][j]) && arr[i-1][j] != '.') || (j != 0 && !isdigit(arr[i-1][j-1]) && arr[i-1][j-1] != '.') || (j != (strlen(arr[i])-1) && !isdigit(arr[i-1][j+1]) && arr[i-1][j+1] != '.')));
    bool down = (i != FILE_LENGTH-1 && ((!isdigit(arr[i+1][j]) && arr[i+1][j] != '.') || (j != 0 && !isdigit(arr[i+1][j-1]) && arr[i+1][j-1] != '.') || (j != (strlen(arr[i])-1) && !isdigit(arr[i+1][j+1]) && arr[i+1][j+1] != '.')));
    
    if (left || right || up || down){
      return 1;
    }
  }
  if (!is_part_1){
    int n_adjacent = 0, index;
    double number, gear_ratio = 1;
    bool left = (j != 0 && isdigit(arr[i][j-1]));
    bool right = (j != (strlen(arr[i])-1) && isdigit(arr[i][j+1]));
    bool up = (i != 0 && (isdigit(arr[i-1][j]) || (j != 0 && isdigit(arr[i-1][j-1])) || (j != (strlen(arr[i])-1) && isdigit(arr[i-1][j+1]))));
    bool down = (i != FILE_LENGTH-1 && (isdigit(arr[i+1][j]) || (j != 0 && isdigit(arr[i+1][j-1])) || (j != (strlen(arr[i])-1) && isdigit(arr[i+1][j+1]))));
    
    if (left){
      index = 1;
      number = 0;
      while (index <= j && isdigit(arr[i][j-index])){
        number += (arr[i][j-index] - '0')*pow(10, index-1);
        index ++;
      }
      gear_ratio *= number;
      n_adjacent++;
    }
    if (right){
      index = 1;
      number = 0;
      while (index <= (strlen(arr[i])-j) && isdigit(arr[i][j+index])){
        number *= 10;
        number += (arr[i][j+index] - '0');
        index ++;
      }
      gear_ratio *= number;
      n_adjacent++;

    };
    if (up){
      //check top left
      if (j != 0 && isdigit(arr[i-1][j-1])){
        index = 1;
        number = 0;
        while (index <= j && isdigit(arr[i-1][j-index])){
          number += (arr[i-1][j-index] - '0')*pow(10,index-1);
          index++;
        }
        index = 1;
        while (index <= (strlen(arr[i-1])-j) && isdigit(arr[i-1][j-1+index])){
          number *= 10;
          number += (arr[i-1][j-1+index] - '0');
          index++;
        }
        gear_ratio *= number;
        n_adjacent++;
      }
      //check top center
      if ((j == 0 || !isdigit(arr[i-1][j-1])) && isdigit(arr[i-1][j])){
        number = arr[i-1][j] - '0';
        index = 1;
        while (index <= (strlen(arr[i-1])-j) && isdigit(arr[i-1][j+index])){
          number *= 10;
          number += (arr[i-1][j+index] - '0');
          index++;
        }
        gear_ratio *= number;
        n_adjacent++;
      }
      //check top right
      if (j < strlen(arr[i-1]) && isdigit(arr[i-1][j+1]) && !isdigit(arr[i-1][j])){
        index = 1;
        number = 0;
        while (index <= (strlen(arr[i-1])-j) && isdigit(arr[i-1][j+index])){
          number *= 10;
          number += (arr[i-1][j+index] - '0');
          index++;
        }
        gear_ratio *= number;
        n_adjacent++;
      }
    }
    if (down){
      //check bottom left
      if (j != 0 && isdigit(arr[i+1][j-1])){
        index = 1;
        number = 0;
        while (index <= j && isdigit(arr[i+1][j-index])){
          number += (arr[i+1][j-index] - '0')*pow(10,index-1);
          index++;
        }
        index = 1;
        while (index <= (strlen(arr[i+1])-j) && isdigit(arr[i+1][j-1+index])){
          number *= 10;
          number += (arr[i+1][j-1+index] - '0');
          index++;
        }
        gear_ratio *= number;
        n_adjacent++;
      }
      //check bottom center
      if ((j == 0 || !isdigit(arr[i+1][j-1])) && isdigit(arr[i+1][j])){
        number = arr[i+1][j] - '0';
        index = 1;
        while (index <= (strlen(arr[i+1])-j) && isdigit(arr[i+1][j+index])){
          number *= 10;
          number += (arr[i+1][j+index] - '0');
          index++;
        }
        gear_ratio *= number;
        n_adjacent++;
      }
      //check bottom right
      if (j < strlen(arr[i+1]) && isdigit(arr[i+1][j+1]) && !isdigit(arr[i+1][j])){
        index = 1;
        number = 0;
        while (index <= (strlen(arr[i+1])-j) && isdigit(arr[i+1][j+index])){
          number *= 10;
          number += (arr[i+1][j+index] - '0');
          index++;
        }
        gear_ratio *= number;
        n_adjacent++;
      }
    }
    if (n_adjacent == 2) return (int)gear_ratio;
  }
  return 0;
};


void part_1(char *arr[]){
  int sum = 0; 
  for (int i= 0; i < FILE_LENGTH; i++ ){
    bool is_symbol_near = false;
    int number = 0;
    for (int j = 0; j < strlen(arr[i]); j++){
      if (isdigit(arr[i][j])){

        number *= 10;
        number += arr[i][j] - '0';
        if (is_symbol_near == false && check(arr, i, j, true) == 1){
          is_symbol_near = true;
        }
        if (j == strlen(arr[i])-1 && is_symbol_near){
          sum += number;
          number = 0;
          is_symbol_near = false;
        }
      }
      else{
        if (is_symbol_near) sum += number;
        number = 0;
        is_symbol_near = false;
      }
    }
  }
  printf("Sum of numbers near a symbol: %d\n", sum);
}


void part_2(char *arr[]){
  int sum = 0;
  for (int i = 0; i < FILE_LENGTH; i++){
    int n_adjacent = 0;
    for (int j = 0; j < strlen(arr[i]); j++){
      if (arr[i][j] == '*'){
        sum += check(arr, i, j, false);
      }
    }
  }
  printf("Sum of all the gear ratios: %d\n", sum);
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
    strncpy(values[index], line, end_line);
    index++;
  }
  fclose(file);
  
  part_1(values);
  part_2(values);

  return 0;
}

