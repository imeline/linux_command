#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
/* 파일 접근권한을 변경한다. */
int main(int argc, char *argv[])
{
long strtol( ); //문자열 long으로 변환
int newmode;
newmode = (int) strtol(argv[1], (char **) NULL, 8);
//strtol(문자열, 변환 멈춰진 포인터, 몇 진수)
if (chmod(argv[2], newmode) == -1) {
perror(argv[2]); //오류메세지 출력
exit(1);
}
exit(0);
}
