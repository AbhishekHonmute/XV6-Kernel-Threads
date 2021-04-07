#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void 
thread_function(int n) {
    printf(1, "hey, this is thread function : %d\n", n * n);
    return;
}

int
main()
{
    int pg_size = 4096;
    void *stack = malloc(pg_size);
    int stack_add = (uint)stack;
    int n = 5;
    ((uint*)stack)[0] = stack_add;
    int thread_id = clone((void*)thread_function, &n, stack);
    printf(1, "thread id : %d\n", (int)thread_id);
    return 0;
}