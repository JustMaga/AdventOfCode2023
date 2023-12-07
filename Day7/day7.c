#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILE_LENGTH 1000
#define MAX_LINE_LENGTH 12
#define N_CARDS 13
#define HAND_LENGHT 5

typedef struct{
  int cards[N_CARDS];
  int type_hand;
  int cards_pos[HAND_LENGHT];
  int bid;
} Hand;

typedef struct{
  Hand list[FILE_LENGTH];
} Hands;

void getHands(char *arr[], Hands *hands);
int cmpHands(const void *p, const void *q);
void printHands(Hands hands);

void part_1(Hands hands){
  int tot = 0;
  int size = sizeof(hands.list) / sizeof(hands.list[0]);
  qsort((void *)hands.list, size, sizeof(hands.list[0]), cmpHands);
  for (int i = 0; i < FILE_LENGTH; i++){
    tot += (i+1) * hands.list[i].bid;
  }
  printf("Total winnings: %d\n", tot);
}


void part_2(Hands hands){
  //edit hands
  for (int i = 0; i < FILE_LENGTH; i++){
    //change value of J to 1
    for (int j = 0; j < HAND_LENGHT; j++){
      if (hands.list[i].cards_pos[j] == 11) hands.list[i].cards_pos[j] = 1;
    }
    //add J occurrences to the most present cart
    int index = 0, max = 0, j_occ = hands.list[i].cards[9];
    if (j_occ != 0){
      hands.list[i].cards[9] = 0;
      for (int j = 0; j < N_CARDS; j++){
        if (hands.list[i].cards[j] > max){
          index = j;
          max = hands.list[i].cards[j];
        }
    }
      if (max == 0) index = N_CARDS-1; //case hand is JJJJJ
      hands.list[i].cards[index] += j_occ;
      //edit type of hand
      hands.list[i].type_hand = 0;
      for (int j = 0; j < N_CARDS; j++){
        int cards_in_hand = hands.list[i].cards[j];
        switch (cards_in_hand){
          case 2:
            hands.list[i].type_hand +=1;
            break;
          case 3:
            hands.list[i].type_hand +=3;
            break;
          case 4:
            hands.list[i].type_hand = 5;
            break;
          case 5:
            hands.list[i].type_hand = 7;
            break;
        }
      }
    }
  }

  int tot = 0;
  int size = sizeof(hands.list) / sizeof(hands.list[0]);
  qsort((void *)hands.list, size, sizeof(hands.list[0]), cmpHands);
  for (int i = 0; i < FILE_LENGTH; i++){
    tot += (i+1) * hands.list[i].bid;
  }
  printf("New total winnings: %d\n", tot);
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
  Hands hands = {0};
  getHands(values, &hands);
  
  part_1(hands);
  part_2(hands);


  return 0;
}


void getHands(char *arr[], Hands *hands){
  for (int i = 0; i < FILE_LENGTH; i++){
    //get cards in hand
    for (int j = 0; j < HAND_LENGHT; j++){
      switch (arr[i][j]) {
        case 'A':
          hands->list[i].cards[12]++;
          hands->list[i].cards_pos[j] = 14;
          break;
        case 'K':
          hands->list[i].cards[11]++;
          hands->list[i].cards_pos[j] = 13;
          break;
        case 'Q':
          hands->list[i].cards[10]++;
          hands->list[i].cards_pos[j] = 12;
          break;
        case 'J':
          hands->list[i].cards[9]++;
          hands->list[i].cards_pos[j] = 11;
          break;
        case 'T':
          hands->list[i].cards[8]++;
          hands->list[i].cards_pos[j] = 10;
          break;
        default:
          hands->list[i].cards[(arr[i][j] - '0')-2]++;
          hands->list[i].cards_pos[j] = (arr[i][j] - '0');
          break;
      }
    }
    //get type of each hand
    for (int j = 0; j < N_CARDS; j++){
      int cards_in_hand = hands->list[i].cards[j];
      switch (cards_in_hand){
        case 2:
          hands->list[i].type_hand +=1;
          break;
        case 3:
          hands->list[i].type_hand +=3;
          break;
        case 4:
          hands->list[i].type_hand = 5;
          break;
        case 5:
          hands->list[i].type_hand = 7;
          break;
      }
    }
    //get bid for each hand
    for (int j = HAND_LENGHT+1; j < strlen(arr[i]); j++){
      hands->list[i].bid *= 10;
      hands->list[i].bid += arr[i][j] - '0';
    }
  }
}


int cmpHands(const void *p, const void *q){
  int l = ((Hand*)p)->type_hand;
  int r = ((Hand*)q)->type_hand;
  if (l == r){
    int i = 0;
    while (l == r && i < HAND_LENGHT){
      l = ((Hand*)p)->cards_pos[i];
      r = ((Hand*)q)->cards_pos[i];
      i++;
    }
  }
  return (l - r);
}






