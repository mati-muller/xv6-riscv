#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    if (fork() == 0) {
        // Reader process
        char buffer[128];
        while (1) {
            int sender = receive(buffer);
            printf("Mensaje recibido de %d: %s\n", sender, buffer);
            if (strcmp(buffer, "Adiós") == 0) {
                break; // Exit when "Adiós" is received
            }
            sleep(10); // Delay to observe the behavior
        }
    } else {
        // Writer process
        char *messages[] = {"Hola", "Mensaje 2", "Adiós"};
        for (int i = 0; i < 3; i++) {
            send(getpid(), messages[i]);
            sleep(10); // Delay to observe the behavior
        }
        wait(0);
    }

    exit(0);
}