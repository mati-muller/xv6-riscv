#include <stdarg.h>
#include <stdint.h>

#define SYS_send 22
#define SYS_receive 23

struct stat;

// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int send(int pid, char *msg);
int receive(char *buffer);

// user library functions
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);

static inline int
syscall(int num, ...)
{
  uint64_t a0, a1, a2, a3, a4, a5;
  va_list ap;

  va_start(ap, num);
  a0 = va_arg(ap, uint64_t);
  a1 = va_arg(ap, uint64_t);
  a2 = va_arg(ap, uint64_t);
  a3 = va_arg(ap, uint64_t);
  a4 = va_arg(ap, uint64_t);
  a5 = va_arg(ap, uint64_t);
  va_end(ap);

  uint64_t ret;
  asm volatile("ecall"
               : "=a" (ret)
               : "a" (num), "D" (a0), "S" (a1), "d" (a2), "r" (a3), "r" (a4), "r" (a5)
               : "memory");
  return ret;
}

int send(int pid, char *msg) {
    return syscall(SYS_send, pid, (uint64_t)msg);
}

int receive(char *buffer) {
    return syscall(SYS_receive, (uint64_t)buffer);
}