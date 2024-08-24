#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#define MAX_SEQ 7
#define BUFFER ((MAX_SEQ + 1) / 2)

struct frame {
    int seq_no;
    int ack_no;
    char info;
};
struct frame s;

void send_frame(int frame_no, int frame_expected, char buff[]) {
    s.seq_no = frame_no;
    s.ack_no = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
    s.info = buff[frame_no % BUFFER];
    printf("Sending Frame %d: seq_no: %d, ack_no: %d, info: %c\n",frame_no, s.seq_no, s.ack_no,s.info);
}
int main() {
    int next_frame_to_send = 0;
    int ack_expected = 0;
    char out[BUFFER];
    printf("Enter the message: ");
    scanf("%s",out);
    for (int i = 0; i < strlen(out); i++) {
        send_frame(next_frame_to_send, ack_expected, out);
        next_frame_to_send = (next_frame_to_send + 1) % (MAX_SEQ + 1);
    }
    return 0;
}
