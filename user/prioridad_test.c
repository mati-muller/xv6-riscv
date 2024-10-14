#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void proceso_hijo(int id) {
  sleep(id * 10);  // Introducir un pequeño delay por ID
  printf("Ejecutando proceso %d\n", id);
  exit(0);
}

int main() {
  for (int i = 0; i < 20; i++) {
    if (fork() == 0) {
      proceso_hijo(i);
    }
  }

  // Esperar a que todos los procesos hijos terminen
  for (int i = 0; i < 20; i++) {
    wait(0);
  }
  exit(0);
}

