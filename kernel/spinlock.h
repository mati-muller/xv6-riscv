#ifndef SPINLOCK_H
#define SPINLOCK_H


// Define assembly-only contents here (if needed)
#else
struct spinlock {
    uint locked;
    char *name;
    struct cpu *cpu;
};


#endif // SPINLOCK_H

