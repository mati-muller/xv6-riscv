#include "types.h"
#include "user.h"

uint64
main(void)
{
    int ppid = getpid();
    printf("El ID del proceso padre es %d\n", ppid);
    exit(0);
}
