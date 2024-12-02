#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "defs.h"

// Cola de mensajes global
struct message_queue msg_queue;

void init_msg_queue(void) {
    initlock(&msg_queue.lock, "msg_queue");
    msg_queue.head = 0;
    msg_queue.tail = 0;
    msg_queue.count = 0;
}
