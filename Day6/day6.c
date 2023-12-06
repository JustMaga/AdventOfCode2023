#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILE_LENGTH 2
#define MAX_LINE_LENGTH 40

void getInformation(char *arr[], int **times, int **records, int *size);
int getNumberDigits(int number);

void part_1(int *times, int *records, int size){
  int result = 1;
  for(int i = 0; i < size; i++){
    int winning_setup = 0;
    for (int j = 0; j < times[i]; j++){
      //formula distance_travelled = (time_tot - time_press)*time_press;
      if ((times[i] - j)*j > records[i]) winning_setup++;
    }
    if (winning_setup != 0) result *= winning_setup;
  }
  printf("Multiplication of way to beat the records: %d\n", result);
}


void part_2(int *times, int *records, int size){
  int result = 1, winning_setup = 0;
  long tot_time = 0, tot_record = 0;
  for(int i = 0; i < size; i++){
    tot_time *= pow(10, getNumberDigits(times[i]));
    tot_time += times[i];
    tot_record *= pow(10, getNumberDigits(records[i]));
    tot_record += records[i];
  }
  for (long j = 0; j < tot_time; j++){
    if ((tot_time - j)*j > tot_record) winning_setup++;
  }
  if (winning_setup != 0) result *= winning_setup;

  printf("Multiplication of way to beat the record: %d\n", result);
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

  int *times = NULL, *records = NULL, size = 0;
  getInformation(values, &times, &records, &size);

  part_1(times, records, size);
  part_2(times, records, size);

  return 0;
}



void getInformation(char *arr[], int **times, int **records, int *size){  
  int index = 0;
  char *token, c[] = " ";
  //get time
  token = strtok(arr[0], c);
  token = strtok(NULL, c);
  while (token != NULL){
    *times = realloc(*times, (index+1) * sizeof(int));
    if (!times){
      printf("Allocation error\n");
      exit(EXIT_FAILURE);
    }
    (*times)[index] = atoi(token);
    token = strtok(NULL, c);
    index++;
  }
  //get records
  index = 0;
  token = strtok(arr[1], c);
  token = strtok(NULL, c);
  while (token != NULL){
    *records = realloc(*records, (index+1) * sizeof(int));
    if (!records){
      printf("Allocation error\n");
      exit(EXIT_FAILURE);
    }
    (*records)[index] = atoi(token);
    token = strtok(NULL, c);
    index++;
  }
  *size = index;

}

int getNumberDigits(int number){
  int n_digits = 0;
  while(number != 0){
    number /= 10;
    n_digits++;
  }
  return n_digits;
}
