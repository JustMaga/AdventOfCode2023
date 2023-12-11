#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_LENGTH 140
#define MAX_LINE_LENGTH 140

typedef struct{
  char **map;
  int *empty_rows;
  int *empty_cols;
  long **galaxy_coords;
  int sizes[3]; //0 for empty_rows, 1 for empty_cols, 2 for galaxy_coords
} Universe;

void getEmpty(Universe *universe);
long expand(Universe universe, int rate);

void parts(Universe universe){
  printf("Sum of lengths between galaxies: %ld\n", expand(universe, 1));
  printf("New sum of lengths between galaxies: %ld\n", expand(universe, 1000000));
}


int main(){
  Universe universe = {
    NULL,
    NULL,
    NULL,
    NULL,
    {0,0,0}
  };
  universe.map = malloc(FILE_LENGTH * sizeof(int *));
  for (int i = 0; i < FILE_LENGTH; i++){
    universe.map[i] = malloc(MAX_LINE_LENGTH * sizeof(int));
  }

  FILE *file = fopen("input.txt", "r");
  if (file == 0){
    printf("Error opening the file\n");
    return 1;
  }

  char line[MAX_LINE_LENGTH+2];
  int index = 0;
  while (fgets(line, sizeof(line), file)) {
    for (int i = 0; i < strlen(line)-1; i++){
      universe.map[index][i] = line[i];
    }
    index++;
  }
  fclose(file);

  getEmpty(&universe);
  parts(universe);

  return 0;
}


void getEmpty(Universe *universe){
  //get empty_rows
  for (int i = 0; i < FILE_LENGTH; i++){
    if (strchr(universe->map[i], '#') == NULL){
      universe->empty_rows = realloc(universe->empty_rows, (universe->sizes[0] +1) * sizeof(int));
      universe->empty_rows[universe->sizes[0]] = i;
      universe->sizes[0]++;
    }
  }
  //get empty_cols
  for (int j = 0; j < MAX_LINE_LENGTH; j++){
    bool isGalaxy = false;
    for (int i = 0; i < FILE_LENGTH; i++){
      if (universe->map[i][j] == '#'){
        universe->galaxy_coords = realloc(universe->galaxy_coords, (universe->sizes[2] +1) * sizeof(long *));
        universe->galaxy_coords[universe->sizes[2]] = malloc(2 * sizeof(long));
        universe->galaxy_coords[universe->sizes[2]][0] = i;
        universe->galaxy_coords[universe->sizes[2]][1] = j;
        universe->sizes[2]++;
        isGalaxy = true;

      }
    }
    if (!isGalaxy) {
      universe->empty_cols = realloc(universe->empty_cols, (universe->sizes[1] +1) * sizeof(int));
      universe->empty_cols[universe->sizes[1]] = j;
      universe->sizes[1]++;
    }
  }
}



long expand(Universe universe, int rate){
  int expanded_gal[universe.sizes[2]][2];
  for (int i = 0; i < universe.sizes[2]; i++)
  //calculate new galaxies coords
  for (int i = 0; i < universe.sizes[2]; i++){
    int shift_rows = 0, shift_cols = 0;
    //check in galaxy is affected by the expantion of rows and if so by how much
    for (int j = 0; j < universe.sizes[0]; j++){
      if (universe.galaxy_coords[i][0] > universe.empty_rows[j]) shift_rows += rate;
    }
    //check in galaxy is affected by the expantion of cols and if so by how much
      for (int j = 0; j < universe.sizes[1]; j++){
      if (universe.galaxy_coords[i][1] > universe.empty_cols[j]) shift_cols += rate;
    }
    //apply expantion to the galaxies
    expanded_gal[i][0] = (universe.galaxy_coords[i][0] + shift_rows);
    expanded_gal[i][1] = (universe.galaxy_coords[i][1] + shift_cols);
  }
  
  //calculate distance between every galaxy
  long sum = 0;
  for (int i = 0; i < universe.sizes[2]; i++){
    long distance;
    for (int j = i+1; j < universe.sizes[2]; j++){
      distance = (abs(expanded_gal[i][0] - expanded_gal[j][0]) + abs(expanded_gal[i][1] - expanded_gal[j][1]));
      sum +=distance;
    }
  }
  return sum;

}
