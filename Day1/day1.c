#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FILE_LENGTH 1000
#define MAX_LINE_LENGTH 50



void part_1(char *arr[]){
  int sum = 0;
  for (int i = 0; i < FILE_LENGTH; i++){
    int first = 0, last;
    for (int j = 0; j <strlen(arr[i]); j++){
      if (isdigit(arr[i][j])&& first == 0){
        first = arr[i][j] - '0';
      }
      if (isdigit(arr[i][j])){
        last = arr[i][j] - '0';
      }
    }
    sum += (first*10 + last);
  }
  printf("Sum of all the calibration values: %d\n", sum);
}


void part_2(char *arr[]){
  int sum = 0;
  for (int i = 0; i < FILE_LENGTH; i++){
    int first = 0, last;
    for (int j = 0; j <strlen(arr[i]); j++){
      
      //very ugly solution 
      switch (arr[i][j]) {
        case 'o':
          if (arr[i][j+1] == 'n' && arr[i][j+2] == 'e') arr[i][j] = '1';
          break;
        case 't':
          if (arr[i][j+1] == 'w' && arr[i][j+2] == 'o') arr[i][j] = '2';
          if (arr[i][j+1] == 'h' && arr[i][j+2] == 'r' && arr[i][j+3] == 'e' && arr[i][j+4] == 'e') arr[i][j] = '3';
          break;
        case 'f':
          if (arr[i][j+1] == 'o' && arr[i][j+2] == 'u' && arr[i][j+3] == 'r') arr[i][j] = '4';
          if (arr[i][j+1] == 'i' && arr[i][j+2] == 'v' && arr[i][j+3] == 'e') arr[i][j] = '5';
         break;
        case 's':
          if (arr[i][j+1] == 'i' && arr[i][j+2] == 'x') arr[i][j] = '6';
          if (arr[i][j+1] == 'e' && arr[i][j+2] == 'v' && arr[i][j+3] == 'e' && arr[i][j+4] == 'n') arr[i][j] = '7';
          break;
        case 'e':
          if (arr[i][j+1] == 'i' && arr[i][j+2] == 'g' && arr[i][j+3] == 'h' && arr[i][j+4] == 't') arr[i][j] = '8';
          break;
        case 'n':
          if (arr[i][j+1] == 'i' && arr[i][j+2] == 'n' && arr[i][j+3] == 'e') arr[i][j] = '9';
          break;
      }

      if (isdigit(arr[i][j])&& first == 0){
        first = arr[i][j] - '0';
      }
      if (isdigit(arr[i][j])){
        last = arr[i][j] - '0';
      }
    }
    sum += (first*10 + last);
  }
  printf("New sum of all the calibration values: %d\n", sum);
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

