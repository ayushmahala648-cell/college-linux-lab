#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message
{
    long type;
    char text[100];
};

int main()
{
    key_t key = 1234;
    int msgid;
    struct message msg;

    // Access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive message
    msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);

    printf("Message received: %s", msg.text);

    // Remove message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}