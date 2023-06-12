#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("사용법: %s 초\n", argv[0]);
        exit(1);
    }

    unsigned int seconds = atoi(argv[1]); //정수형으로 변환

    printf("프로그램을 일시 중지합니다.\n");
    sleep(seconds);
    printf("프로그램이 다시 실행됩니다.\n");

    return 0;
}

