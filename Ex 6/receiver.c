#include <stdio.h>
#include <stdbool.h>

#define MAX_SEQ 7
#define BUFFER ((MAX_SEQ + 1) / 2)
#define WINDOW_BOUND BUFFER

struct frame {
    int seq_no;
    int ack_no;
    char info;
};

struct frame r;

// Helper function to determine if a value is within the window
bool between(int a, int b, int c) {
    return ((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a));
}

// Function to simulate receiving a frame
void receive_frame(int *frame_exp, int *window_bound, bool arrived[], char ch) {
    r.seq_no = *frame_exp;
    r.ack_no = *frame_exp;
    r.info = ch;

    // Check if the received frame is within the window
    if (between(*frame_exp, *frame_exp, *window_bound)) {
        arrived[*frame_exp % BUFFER] = true;

        // Process the frame if it's the expected one
        if (arrived[*frame_exp % BUFFER]) {
            // Print ack_no before info
            printf("Received Frame %d: seq_no: %d, ack_no: %d, info: %c\n", *frame_exp,r.seq_no, r.ack_no, r.info);
            // Move to the next expected frame and update window bounds
            *frame_exp = (*frame_exp + 1) % (MAX_SEQ + 1);
            *window_bound = (*window_bound + 1) % (MAX_SEQ + 1);
        } else {
            // Frame was not received, handle error
            printf("Frame %d was not received.\n", r.seq_no);
        }
    } else {
        // Frame is not within the window
        printf("Frame %d is out of the window.\n", *frame_exp);
    }
}

int main() {
    int frame_exp = 0;
    int window_bound = WINDOW_BOUND;
    char ch[MAX_SEQ];
    bool arrived[BUFFER] = { false };

    printf("Enter the characters: ");
    scanf("%s", ch);

    // Receiving the frames
    for(int i = 0; i < BUFFER; i++) {
        receive_frame(&frame_exp, &window_bound, arrived, ch[i]);
    }
    printf("\nAll frames received... Reception Completed!\n");

    return 0;
}
