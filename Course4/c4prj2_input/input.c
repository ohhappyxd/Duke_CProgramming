#include <stdio.h>
#include <stdlib.h>
#include "future.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {

}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  char * hand = NULL;
  size_t size = 0;
  ssize_t nread;
  deck_t ** hands = NULL;
  *n_hands = 0;
  
  while ((nread = getline(&hand, &size, f)) != -1) {
    hand_from_string(hand, fc);
  }
}
