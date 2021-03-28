#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
    printf(1, "Total No of system calls till now are : %d\n", clone());
    exit();
}