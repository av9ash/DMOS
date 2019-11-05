#include "sem.h"

typedef struct msg
{
    int data[10];
}MSG;

typedef struct port
{
    int count_unread, count_read;
    MSG msgs[10];
    semaphore_t mutex,Full,Empty;
}PORT;

//Declare a set (array of ports). The ports are numbered 0 to 99
PORT ports[100];

void init_port()
{
    for(int i=0;i<100;i++)
    {
        ports[i].count_unread = 0;
        ports[i].count_read = 0;

        ports[i].Full = create_sem(0);
        ports[i].mutex = create_sem(1);
        ports[i].Empty = create_sem(10);
    }
}

void send(PORT *port, MSG *msg)
{
    P(&ports->Empty);
    P(&ports->mutex);

    int msg_num = port->count_unread;
    port->msgs[msg_num] = *msg;
    port->count_unread = (msg_num+1)%10;

    V(&ports->mutex);
    V(&ports->Full);
}

MSG receive(PORT *port)
{
    P(&port->Full);
    P(&ports->mutex);

    int msg_num = port->count_read;
    MSG msg = port->msgs[msg_num];
    port->count_read = (msg_num+1)%10;

    V(&ports->mutex);
    V(&ports->Empty);
    return msg;
}
