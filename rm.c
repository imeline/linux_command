#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    if (unlink(argv[1]) == 0) { 
        //unlink 함수 대신 remove도 사용가능 하지만 remove는 디렉토리도 삭제 가능하기 때문에 unlink를 사용 
        printf("File '%s' successfully removed.\n", argv[1]);
        return 0;
    } else {
        printf("Error removing file '%s'.\n", argv[1]);
        return 1;
    }
}
