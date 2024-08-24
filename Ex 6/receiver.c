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

bool between(int a, int b, int c) {
    return (a <= b && b < c || b <= c && c <= a || a < b);
}

void receive_frame(int *frame_exp, int *WINDOW_BOUND, bool *arrived) {
  //check if the given frames are valid window
    if (between(*frame_exp, r.seq_no, *WINDOW_BOUND)) {
        arrived[r.seq_no % BUFFER] = true;
        // Process the frame if it's the next expected frame
        if (arrived[*frame_exp % BUFFER]) {
            printf("Received Frame %d: seq_no: %d, ack_no: %d, info: %c\n", *frame_exp, r.seq_no, r.ack_no, r.info);
            *frame_exp = (*frame_exp + 1) % BUFFER;
            *WINDOW_BOUND = (*WINDOW_BOUND + 1) % WINDOW_BOUND;
        } else {
            // Frame was not received, handle error
            printf("Frame %d was not received.\n", r.seq_no);
        }
    }
}

int main() {
    int frame_exp = 0;
    int next_frame_to_send = 0;
    int ack_expected = 0;
    char ch[MAX_SEQ];
    bool arrived[BUFFER];

    printf("Enter the characters: ");
    scanf("%s", ch);

    // Initialize arrived array to false
    for (int i = 0; i < BUFFER; i++) {
        arrived[i] = false;
    }

    // Receiving the frame 
    while (ack_expected <= MAX_SEQ) {
        // Receive a frame for each character
        for (int i = 0; i < strlen(ch); i++) {
            receive_frame(&frame_exp, &WINDOW_BOUND, arrived);
        }
    }

    // Check if all frames were received (optional)
    for (int i = 0; i < BUFFER; i++) {
        if (!arrived[i]) {
            printf("Frame %d was not received.\n", i);
        }
    }
  printf("All frames received...Reception Complete!");
}
