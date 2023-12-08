#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LENGTH 752
#define MAX_LINE_LENGTH 280
#define C_LINE_LENGTH 20 
#define ALPHABET 26

typedef struct{
  char string[4];
  char left[4];
  char right[4];
} Node;
typedef struct{
  Node *nodes;
  int *starts;
  int sizes[2];
} Graph;

void getNodes(char *arr[], Graph *graph);
int searchString(Graph haystack, char *needle);
int findSteps(Graph graph, char *instructions, int pos_start, int part);
long gcd(long a, long b);
long lcm(long a, long b);


void part_1(char *instructions, Graph graph){
  printf("Number of steps required: %d\n", findSteps(graph, instructions, graph.starts[0], 0));
}


void part_2(char *instructions, Graph graph){
  graph.sizes[1] = 0;
  graph.starts = NULL;
  int n_A = 0;
  int n_Z = 0;
  //get start and end positions
  for (int i = 0; i < graph.sizes[0]; i++){
    if (graph.nodes[i].string[2] == 'A'){
      int* temp_starts = realloc(graph.starts, (graph.sizes[1]+1) * sizeof(int));
      if (!temp_starts) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
      }
      graph.starts = temp_starts;
      graph.starts[graph.sizes[1]] = i;
      graph.sizes[1]++;
    }   
  }
  //get steps necessary for every node that ends with A
  int *pos = malloc(graph.sizes[1] * sizeof(int));
  for (int i = 0; i < graph.sizes[1]; i++){
    pos[i] = findSteps(graph, instructions, graph.starts[i], 1);
  }

  //get lcm of all steps
  long steps = pos[0];
  for (int i = 1; i < graph.sizes[1]; i++){
    steps = lcm(steps, pos[i]);
  }

  printf("Steps before all nodes ends with Z: %ld\n", steps);
}


int main(){
  FILE *file = fopen("input.txt", "r");
  if (file == 0){
    printf("Error opening the file\n");
    return 1;
  }

  char line[MAX_LINE_LENGTH];
  char *values[FILE_LENGTH];
  values[0] = malloc(MAX_LINE_LENGTH);
  for (int i = 1; i < FILE_LENGTH; i++){
    values[i]= malloc(C_LINE_LENGTH);
  }

  int index = 0;
  while (fgets(line, sizeof(line), file)) {
    int end_line = 0;
    for (end_line; line[end_line] != '\n'; end_line++){}
    strncpy(values[index], line, end_line);
    index++;
  }
  fclose(file);
  
  char instructions[strlen(values[0]+1)];
  strcpy(instructions, values[0]);
  Graph graph = {
    NULL,
    NULL,
    {0,0}
  };
  getNodes(values, &graph);

  for (int i = 0; i < FILE_LENGTH; i++){
    free(values[i]);
  }
  part_1(instructions, graph);
  part_2(instructions, graph);
  return 0;
}


void getNodes(char *arr[], Graph *graph){
  for (int i = 2; i < FILE_LENGTH; i++){
    //allocate new node
    graph->nodes = realloc(graph->nodes, (graph->sizes[0] +1) * sizeof(Node));
    if (!graph->nodes){
      fprintf(stderr, "Allocation error\n");
      exit(EXIT_FAILURE);
    }

    strncpy(graph->nodes[graph->sizes[0]].string, arr[i], 3);
    graph->nodes[graph->sizes[0]].string[3] = '\0';
    strncpy(graph->nodes[graph->sizes[0]].left, &arr[i][7], 3);
    graph->nodes[graph->sizes[0]].left[3] = '\0';
    strncpy(graph->nodes[graph->sizes[0]].right, &arr[i][12], 3);
    graph->nodes[graph->sizes[0]].right[3] = '\0';
    graph->sizes[0]++;
  }

  graph->starts = malloc(sizeof(int));
  if (!graph->starts){
    fprintf(stderr, "Allocation error\n");
    exit(EXIT_FAILURE);
  }
  graph->starts[0] = searchString(*graph, "AAA");
  graph->sizes[1]++;
}


int searchString(Graph haystack, char *needle){
  for (int i = 0; i < haystack.sizes[0]; i++){
    if (strcmp(haystack.nodes[i].string, needle) == 0) return i;
  }
  return -1;
}

int findSteps(Graph graph, char *instructions, int pos_start, int part){
  int steps = 0;
  int pos = pos_start;
  int index_inst = 0;
  if (!part){
    while (strcmp(graph.nodes[pos].string, "ZZZ") != 0) {
      switch (instructions[index_inst]) {
        case 'L':
          pos = searchString(graph, graph.nodes[pos].left);
          break;
        case 'R':
          pos = searchString(graph, graph.nodes[pos].right);
          break;
      }
      index_inst++;
      if (index_inst == strlen(instructions)) index_inst = 0;
    steps++;
    }
  }
  if (part){
    while (graph.nodes[pos].string[2] != 'Z') {
      switch (instructions[index_inst]) {
        case 'L':
          pos = searchString(graph, graph.nodes[pos].left);
          break;
        case 'R':
          pos = searchString(graph, graph.nodes[pos].right);
          break;
      }
      index_inst++;
      if (index_inst == strlen(instructions)) index_inst = 0;
    steps++;
    }
  }

  return steps;
}

long gcd(long a, long b){
  if (b == 0) return a;
  return gcd(b, a%b);
}
long lcm(long a, long b){
  return (a / gcd(a, b) * b);
}

