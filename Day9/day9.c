#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LENGTH 200
#define MAX_LINE_LENGTH 125

typedef struct{
  int *values;
  int size;
} History;

int getPrediction(int *values, int size, int part);
void part_1(History *arr){
  int sum = 0;
  for (int i = 0; i < FILE_LENGTH; i++){
    sum += getPrediction(arr[i].values, arr[i].size, 0);
  }
  printf("Sum of all predictions: %d\n", sum);
}


void part_2(History *arr){
  int sum = 0;
  for (int i = 0; i < FILE_LENGTH; i++){
    sum += getPrediction(arr[i].values, arr[i].size, 1);
  }
  printf("New sum of all predictions: %d\n", sum);
}


int main(){

  History arr[FILE_LENGTH] = {NULL, 0};
  char line[MAX_LINE_LENGTH];
  char *token, c[2] = " ";
  int index = 0;

  FILE *file = fopen("input.txt", "r");
  if (file == 0){
    printf("Error opening the file\n");
    return 1;
  }

  while (fgets(line, sizeof(line), file)) {
    token = strtok(line, c);
    while (token != NULL) {
      arr[index].values = realloc(arr[index].values, (arr[index].size +1) * sizeof(int));
      arr[index].values[arr[index].size] = atoi(token);
      token = strtok(NULL, c);
      arr[index].size++;
    }
    index++;
  }
  fclose(file);

  part_1(arr);
  part_2(arr);

  return 0;
}




int getPrediction(int *values, int size, int part){
  int **tmp = malloc(sizeof(int *));
  tmp[0] = malloc(size * sizeof(int));
  memcpy(tmp[0], values, size * sizeof(int));
  int tmp_size = 1;
  int sum;
  int new_size = size;
  while (1) {
    sum = 0;
    tmp = realloc(tmp, (tmp_size +1) * sizeof(int *));
    tmp[tmp_size] = malloc((new_size -1) * sizeof(int));
    new_size--;
    for (int i = 0; i < new_size; i++){
      tmp[tmp_size][i] = tmp[tmp_size -1][i+1] - tmp[tmp_size -1][i];
      if(tmp[tmp_size][i] == 0) sum++;
    }
    tmp_size++;
    if (sum == new_size) break;
  }
  int pred = 0;
  if (part == 0){
    for (int i = tmp_size -2; i >= 0; i--){
      pred = tmp[i][new_size] + pred;
      new_size++;
    }
  }
  if (part == 1){
    for (int i = tmp_size -2; i >= 0; i--){
      pred = tmp[i][0] - pred;
    }
  }
  for (int i = 0; i < tmp_size; i++){
    free(tmp[i]);
  }
  free(tmp);
  return pred;
}

