# sys_linux_command

## ls


## ln
```
//하드링크(같은 i-node 가지게끔)
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[ ])
{
if (link(argv[1], argv[2]) == -1) {
//link(기존 파일, 생성 링크 파일), 0성공, -1실패
exit(1);
}
exit(0);
}
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/173ee28d-b8bc-4206-a483-49f6675eae97)
---

## ln -s
```
//소프트링크(원본파일의 주소 링크)
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[ ])
{
if (symlink(argv[1], argv[2]) == -1) {
exit(1);
}
exit(0);
}
```

![image](https://github.com/imeline/sys_linux_command/assets/128706341/8fe7cb07-72a8-4bb7-ba73-7c82b76329a3)
---

## touch
파일 시간 정보 변경
```
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
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/6ca3ae00-9b9a-4d8d-851b-7aaf9d89b9d0)
---

## chmod
```
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
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/84b34ab7-5742-4023-9bbb-b2f853a5e57e)
