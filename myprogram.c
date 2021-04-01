#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
    printf(1, "Output from clone : %d\n", clone(7));
    exit();
}