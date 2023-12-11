#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_LENGTH 140
#define MAX_LINE_LENGTH 140
#define CHECK_LEFT(left) (left == '-' || left == 'F' || left == 'L')
#define CHECK_RIGHT(right) (right == '-' || right == 'J' || right == '7')
#define CHECK_UP(up) (up == '|' || up == 'F' || up == '7')
#define CHECK_DOWN(down) (down == '|' || down == 'J' || down == 'L')


void dfs(char nodes[FILE_LENGTH][MAX_LINE_LENGTH]);

void parts(char nodes[FILE_LENGTH][MAX_LINE_LENGTH]){
  dfs(nodes);
}





int main(){

  FILE *file = fopen("input.txt", "r");
  if (file == 0){
    printf("Error opening the file\n");
    return 1;
  }

  char line[MAX_LINE_LENGTH +2];
  char nodes[FILE_LENGTH][MAX_LINE_LENGTH];
  int index = 0;
  while (fgets(line, sizeof(line), file)) {
    for (int i = 0; i < strlen(line)-1; i++){
      nodes[index][i] = line[i];
    }
    index++;
  }
  fclose(file);

  parts(nodes);
  return 0;
}


void dfs(char nodes[FILE_LENGTH][MAX_LINE_LENGTH]){
  int steps = 0;
  int start[2] = {0,0};
  int direction[2];
  for (int i = 0; i < FILE_LENGTH; i++){
    for (int j = 0; j < MAX_LINE_LENGTH; j++){
      if (nodes[i][j] == 'S'){
        start[0] = i;
        start[1] = j;
        goto found_start;
      }
    }
  }
found_start:
  if (start[1] != 0  && (nodes[start[0]][start[1]-1] == 'L' || nodes[start[0]][start[1]-1] == 'F' || nodes[start[0]][start[1]-1] == '-')) {direction[0] = start[0]; direction[1] = start[1] -1;}
  else if (start[1] != (MAX_LINE_LENGTH -1) && (nodes[start[0]][start[1]+1] == 'J' || nodes[start[0]][start[1]+1] == '7' || nodes[start[0]][start[1]+1] == '|')) {direction[0] = start[0]; direction[1] = start[1] +1;}
  else if (start[0] != 0  && (nodes[start[0] -1][start[1]] == '7' || nodes[start[0] -1][start[1]] == 'F' || nodes[start[0] -1][start[1]] == '|')) {direction[0] = start[0] -1; direction[1] = start[1];}
  else if (start[0] != (FILE_LENGTH -1)  && (nodes[start[0] +1][start[1]] == 'L' || nodes[start[0] +1][start[1]] == 'J' || nodes[start[0] +1][start[1]] == '|')) {direction[0] = start[0] +1; direction[1] = start[1];}
 

  int area = 0;

  //possible next step
  int old_direction[2] = {start[0], start[1]};
  while (start[0] != direction[0] || start[1] != direction[1]){
    //shoelance formula for part 2
    area += ((old_direction[0] * direction[1]) - (old_direction[1] * direction[0]));
    switch (nodes[direction[0]][direction[1]]) {
      case '|':
        if (old_direction[0] < direction[0]){
          old_direction[0] = direction[0];
          direction[0]++;
        }
        else{
          old_direction[0] = direction[0];
          direction[0]--;
        }
        break;
      case '-':
        if (old_direction[1] < direction[1]){
          old_direction[1] = direction[1];
          direction[1]++;
        }
        else{
          old_direction[1] = direction[1];
          direction[1]--;
        }
        break;
      case 'L':
        if (old_direction[0] < direction[0]){
          old_direction[0] = direction[0];
          direction[1]++;
        }
        else{
          old_direction[1] = direction[1];
          direction[0]--;
        }
        break;
      case 'J':
        if (old_direction[0] < direction[0]){
          old_direction[0] = direction[0];
          direction[1]--;
        }
        else{
          old_direction[1] = direction[1];
          direction[0]--;
        }
        break;
      case '7':
        if (old_direction[0] > direction[0]){
          old_direction[0] = direction[0];
          direction[1]--;
        }
        else{
          old_direction[1] = direction[1];
          direction[0]++;
        }
        break;
      case 'F':
        if (old_direction[0] > direction[0]){
          old_direction[0] = direction[0];
          direction[1]++;
        }
        else{
          old_direction[1] = direction[1];
          direction[0]++;
        }
        break;
    }
    steps++;
  }
  steps = (steps % 2 ==0)?(steps /2):(steps /2 +1);
  printf("Numbers of steps to get to the farthest position: %d\n", steps);

  //last part of shoelance formula
  area += (old_direction[0] * direction[1]) - (old_direction[1] * direction[0]);
  //shoelance + pick's
  int sol = (abs(area) /2) - steps +1 ; //steps is already divided
  
  printf("Number of tiles enclosed: %d\n", sol);

}

