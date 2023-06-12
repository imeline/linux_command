#include <utime.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
if (argc < 2) {
fprintf(stderr, "사용법: touch file1 \n");
exit(-1);
}
utime(argv[1], NULL); 
//파일의 최종 접근 시간과 최종 변경 시간을 조정한다.
//times가 NULL 이면, 현재시간으로 설정된다.
//리턴 값 성공하면 0, 실패하면 -1
}
/// touch -c newfile => 현재시간으로 변경
/// touch -t YYYYMMDDhhmm newfile => 마음대로 변경
/// touch -r oldfile newfile => 다른파일 시간으로 변경