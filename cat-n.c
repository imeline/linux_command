#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 80

/* 텍스트 파일에 줄 번호 붙여 프린트한다. */
int main(int argc, char *argv[])
{
FILE *fp;
int line = 0;
char buffer[MAXLINE];

if (argc != 2) { //오류
fprintf(stderr, "사용법:line 파일이름\n");
exit(1);
}

if ( (fp = fopen(argv[1],"r")) == NULL) //오류
{
    fprintf(stderr, "파일 열기 오류\n");
    exit(2);
}

while (fgets(buffer, MAXLINE, fp) != NULL) { // 한 줄 읽기
    //fp에서 줄이 끝날 때 까지 최대 MAXLINE-1개의 문자를 읽어 buffer에 저장 
    line++;
    printf("%3d %s", line, buffer); 
    }
    exit(0);
}