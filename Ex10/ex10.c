//Arrays Of Strings, Looping
#include <stdio.h>

int main(int argc, char const *argv[]) {

  int i = 0;

  //Go through each tring in argv
  for (i = 1; i < argc; i++){
    printf("arg %d: %s\n",i,argv[i]);
  }

  //Make our own array of characters
  char *states[] = {"California", "Oregon", "Washington", "Texas"};

  int num_states = 4;

  for (i = 0; i < num_states; i++){
    printf("state %d: %s\n",i,states[i]);
  }

  return 0;
}
