#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Message type
    msg.type = 1;

    // Get message from user
    printf("Enter message: ");
    fgets(msg.text, 100, stdin);

    // Send message
    msgsnd(msgid, &msg, sizeof(msg.text), 0);

    printf("Message sent successfully.\n");

    return 0;
}