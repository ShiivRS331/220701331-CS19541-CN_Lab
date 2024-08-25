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

bool between(int a, int b, int c) {
    return (a <= b && b < c || b <= c && c <= a || a < b);
}
//
void receive_frame(int frame_exp, int window_bound, bool arrived[], char ch) {
    r.seq_no = frame_exp;  
    r.ack_no = frame_exp; 
    r.info = ch;  

    // Check if the received frame is within the window
    if (between(frame_exp, r.seq_no, window_bound)) {
        arrived[r.seq_no % BUFFER] = true;
        // Process the frame if it's the next expected frame
        if (arrived[frame_exp % BUFFER]) {
            printf("Received Frame %d: seq_no: %d, info: %c\n", frame_exp, r.seq_no, r.info);
            frame_exp = (frame_exp + 1) % (MAX_SEQ + 1);
            window_bound = (window_bound + 1) % (MAX_SEQ + 1);
        } else {
            // Frame was not received, handle error
            printf("Frame %d was not received.\n", r.seq_no);
        }
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
        // Receive a frame for each character in the input
        receive_frame(frame_exp, window_bound, arrived, ch[i]);
    }
    printf("\nAll frames received... Reception Completed!\n");

    return 0;
}
