#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void 
thread_function(int *n) {
    // printf(1, "hey, this is thread function : %d\n", (*n) * (*n));
    // sleep(200);
    int i = 0;
    for(i = 0; i < 10; i++) {
        printf(1, "thread_function\n");
        sleep(50);
    }
    exit();
}

int
main()
{
    int pg_size = 4096;
    void *stack = malloc(pg_size);
    void *join_stack;
    // int stack_add = (uint)stack;
    int n[2];
    int thread_id;
    n[0] = 7;
    n[1] = 9;
    // ((uint*)stack)[0] = stack_add; 
    void (*funptr)(int*) = &thread_function;
    printf(1, "thread id : %d\n", (uint)n);
    thread_id = clone((void*)funptr, stack, (void*)n);
    // thread_id = clone((void*)funptr, stack, (void*)n);
    join(&join_stack);
    // join(&join_stack);
    printf(1, "thread ID : test_clone : %d\n", thread_id);
    printf(1, "join_stack : %d\n", &stack);
    printf(1, "join output : %d\n", ((int*)stack)[0]);
    sleep(200);
    exit();
}