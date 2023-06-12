#include <stdio.h>

int main(int argc, char *argv[])
{

char c;
FILE *fp1, *fp2;

if (argc !=3) { //오류
fprintf(stderr, "사용법: %s 파일1 파일2\n", argv[0]);
//fprintf() = 파일에 출력
///stderr = 표준 오류에 대한 FILE 포인터
return 1;
}

fp1 = fopen(argv[1], "r");
if (fp1 == NULL) { //오류
fprintf(stderr, "파일 %s 열기 오류\n", argv[1]);
return 2;
}

fp2 = fopen(argv[2], "w");
while ((c = fgetc(fp1)) != EOF) fputc(c, fp2);
//파일을 문자 단위로 읽고 씀
fclose(fp1);
fclose(fp2);
return 0;
}