#include <stdarg.h>
#include <unistd.h>

#ifdef __riscv
static inline int
syscall(int num, ...)
{
  int ret;
  asm volatile("ecall"
               : "=a" (ret)
               : "a" (num)
               : "memory");
  return ret;
}
#else
static inline int
syscall(int num, ...)
{
  va_list args;
  va_start(args, num);
  // Implement syscall using macOS conventions, possibly using syscall() from unistd.h
  // Example:
  // return syscall(num, va_arg(args, ...));
  va_end(args);
  return -1; // Placeholder
}
#endif

#define SYS_send 22
#define SYS_receive 23

int send(int pid, char *msg) {
    return syscall(SYS_send, pid, msg);
}

int receive(char *buffer) {
    return syscall(SYS_receive, buffer);
}