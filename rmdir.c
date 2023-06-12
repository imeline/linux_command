#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if (rmdir(argv[1]) == 0) {
        printf("Directory '%s' successfully removed.\n", argv[1]);
        return 0;
    } else {
        printf("Error removing directory '%s'.\n", argv[1]);
        return 1;
    }
}
