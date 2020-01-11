#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>

#include "panic.h"

void panic(char *message) {
        void *array[10];
        size_t size;

        size = backtrace(array, 10);

        fprintf(stderr, "\n~~~PANICKING~~~\n\n%s\n\n~~~PANICKING~~~\n\n", message);
        backtrace_symbols_fd(array, size, STDERR_FILENO);
        exit(1);
}
