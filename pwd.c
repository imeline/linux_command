#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        //cwd에 현재 작업 디렉토리의 절대경로 저장 
        printf("현재 작업 디렉토리: %s\n", cwd);
    } else {
        printf("현재 작업 디렉토리를 얻어오는데 실패했습니다.\n");
    }
    
    return 0;
}
