#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> //디렉토리와 관련된 함수와 구조체를 포함
#define MAX_ENTRIES_PER_LINE 8

int main() {
    DIR *directory; //디렉토리 스트림(커다란 시스템의 일부를 이루는 하드웨어, 소프트웨어, 또는 데이터의 한 구성요소)
    struct dirent *entry; //디렉토리 엔트리(디렉토리를 표현하는 데에 쓰이는 자료구조 ex)파일이름,속성)
    int count = 0;

    directory = opendir("."); //현재 디렉토리 열기
    if (directory == NULL) {
        printf("디렉토리가 비었습니다.\n");
        return 1;
    }

    while ((entry = readdir(directory)) != NULL) { //엔트리를 하나씩 읽음
        printf("%-20s", entry->d_name);
        count++;

        if (count % MAX_ENTRIES_PER_LINE == 0) { //한 줄에 8개씩 출력
            printf("\n"); 
        }
    }

    closedir(directory);
    return 0;
}
