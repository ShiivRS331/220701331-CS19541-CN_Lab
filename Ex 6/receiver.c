#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SEQ 7
#define BUFFER (MAX_SEQ + 1) / 2
#define WINDOW_BOUND BUFFER

struct frame {
  int seq_no;
  int ack_no;
  char info;
};
struct frame r;
bool between(int a, int b, int c){
    return (a<=b && b<c || b<=c && c<=a || a<b);
}

void receive_frame() {
  struct frame r;
  r.seq_no=
}
int main() {
  int frame_exp = 0,
       next_frame_to_send = 0,
       ack_expected = 0;
  char ch[MAX_SEQ];
  bool arrived[BUFFER];

  printf("Enter the characters: ");
  scanf("%s", ch);

  // Initialize arrived array to false
  for (int i = 0; i < BUFFER; i++) {
    arrived[i] = false;
  }

  // Simulate sending and receiving frames
  while (ack_expected <= MAX_SEQ) {
    // Send frames within the window
    if(between(frame_exp,r.seq_no,WINDOW_BOUND)){
        arrived[r.seq_no%BUFFER]=true;
        if(arrived[r.seq_no%BUFFER]==true){
          frame_exp =  (frame_exp+1)%BUFFER;
          WINDOW_BOUND = (WINDOW_BOUND+1)%WINDOW_BOUND;
          printf("%d", frame_exp);
        }
    }
  }
    for(int i=0;i<BUFFER;i++){
        if(arrived[i]!=true){
            break;
        }
        else{
            printf("%d ",i);
        }
    }
}
    
    
 
