// msg_queue.c

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

// Global message queue
struct message_queue msg_queue;

void
init_msg_queue(void) {
    initlock(&msg_queue.lock, "message_queue");
    msg_queue.head = 0;
    msg_queue.tail = 0;
    msg_queue.count = 0;
}

uint64
sys_send(int pid, char *msg) {
    struct proc *p = myproc();
    acquire(&msg_queue.lock);

    if (msg_queue.count >= 32) {
        release(&msg_queue.lock);
        return -1; // Queue is full
    }

    // Add the message to the queue
    msg_queue.messages[msg_queue.tail].sender_pid = p->pid;
    safestrcpy(msg_queue.messages[msg_queue.tail].content, msg, sizeof(msg_queue.messages[msg_queue.tail].content));
    msg_queue.tail = (msg_queue.tail + 1) % 32;
    msg_queue.count++;

    // Wake up any process waiting for a message
    wakeup(&msg_queue);

    release(&msg_queue.lock);
    return 0;
}

uint64
sys_receive(char *buffer) {
    acquire(&msg_queue.lock);

    // Wait for a message to be available
    while (msg_queue.count == 0) {
        sleep(&msg_queue, &msg_queue.lock);
    }

    // Retrieve the message from the queue
    struct message msg = msg_queue.messages[msg_queue.head];
    safestrcpy(buffer, msg.content, 128);
    msg_queue.head = (msg_queue.head + 1) % 32;
    msg_queue.count--;

    release(&msg_queue.lock);
    return msg.sender_pid;
}