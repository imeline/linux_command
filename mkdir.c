#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if (mkdir(argv[1], 0755) == 0) { //0755 = 소유자에게 읽기, 쓰기 및 실행 권한을 부여하고, 그룹 및 기타 사용자에게는 읽기 및 실행 권한을 부여
        printf("Directory '%s' successfully created.\n", argv[1]);
        return 0;
    } else {
        printf("Error creating directory '%s'.\n", argv[1]);
        return 1;
    }
}
