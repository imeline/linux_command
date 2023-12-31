# sys_linux_command

## ls
현재 디렉토리의 내용을 표시(옵션이 없는 경우)
```
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

```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/26b6ba3f-4b6d-42fe-a4c6-09771bb498f1)

## cat
파일 내용 출력
```
#include <stdio.h>

int main(int argc, char *argv[])
{
FILE *fp;
int c;

if (argc < 2) fp = stdin; // 명령줄 인수가 없으면 표준입력 사용
else fp = fopen(argv[1],"r"); // 읽기 전용으로 파일 열기

c = getc(fp); // 파일로부터 문자 읽기

while (c != EOF) { // 파일끝이 아니면
putc(c, stdout); // 읽은 문자를 표준출력에 출력
c = getc(fp); // 파일로부터 문자 읽기
}

fclose(fp);
return 0;
}
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/ba8da782-5d75-403e-a7bd-ebdb0673cbb1)

## cat -n
파일에 행 번호 붙여 프린트(공백 줄 포함)
```
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 80

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
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/5cd32ea0-7293-4cb5-abff-53d5afde3801)

## cp
파일 복사
```
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
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/e6c53123-4962-465d-9900-b3234f39e201)


## ln
(링크 = 기존 파일에 대한 또 다른 이름의 파일 생성) <br>
하드링크(같은 i-node 가지게끔)
```
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


## ln -s
소프트링크(원본파일의 주소 링크)
```
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


## touch
파일 시간 정보 변경
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: ./touch <파일 이름>\n");
        return 1;
    }

    const char *filename = argv[1];
    struct stat fileStat;

    // 파일의 상태 확인
    if (stat(filename, &fileStat) == 0) {
        // 파일이 이미 존재하는 경우, 파일의 수정 시간을 현재 시간으로 갱신
        struct utimbuf newTime;
        newTime.actime = fileStat.st_atime;
        newTime.modtime = time(NULL);

        if (utime(filename, &newTime) != 0) {
            //파일의 최종 접근 시간과 최종 변경 시간을 조정한다.
            //times가 NULL 이면, 현재시간으로 설정된다.
            //리턴 값 성공하면 0, 실패하면 -1
            printf("파일의 수정 시간을 갱신할 수 없습니다.\n");
            return 1;
        }
    } else {
        // 파일이 존재하지 않는 경우, 크기가 0인 파일 생성
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("파일을 생성할 수 없습니다.\n");
            return 1;
        }
        fclose(file);
    }

    printf("%s 파일을 생성 또는 수정했습니다.\n", filename);
    return 0;


}
/// touch -c newfile => 현재시간으로 변경
/// touch -t YYYYMMDDhhmm newfile => 마음대로 변경
/// touch -r oldfile newfile => 다른파일 시간으로 변경
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/6ca3ae00-9b9a-4d8d-851b-7aaf9d89b9d0)


## chmod
파일 접근권한을 변경
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

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


## file
파일 타입 확인 
```
#include <sys/types.h> 
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{ 
int i;
struct stat buf; //파일 정보를 저장하는 구조체
for (i = 1; i < argc; i++) {
printf("%s: ", argv[i]);

if (lstat(argv[i], &buf) < 0) { //buf에 파일에 대한 정보를 담음
perror("lstat()"); 
continue;
}

if (S_ISREG(buf.st_mode)) //st_mode - 파일의 모드를 다룸
printf("%s \n", "일반 파일");
if (S_ISDIR(buf.st_mode)) 
printf("%s \n", "디렉터리");
if (S_ISCHR(buf.st_mode)) 
printf("%s \n", "문자 장치 파일");
if (S_ISBLK(buf.st_mode)) 
printf("%s \n", "블록 장치 파일");
if (S_ISFIFO(buf.st_mode)) 
printf("%s \n", "FIFO 파일");
if (S_ISLNK(buf.st_mode)) 
printf("%s \n", "심볼릭 링크");
if (S_ISSOCK(buf.st_mode)) 
printf("%s \n", "소켓");
}
exit(0);
}
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/1c145e34-93c2-44db-9e6b-75593fc4b90b)

## sleep
지정된 시간 동안 프로그램 실행을 유예(기본 값:초 단위)
```
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
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/5e1eb519-1866-4638-b24a-dd8753f6700e)

## mkdir
디렉토리 생성
```
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
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/cba2e104-dddf-47bb-939f-36685b574687)

## rmdir
디렉토리 삭제
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if (rmdir(argv[1]) == 0) {
        printf("Directory '%s' successfully removed.\n", argv[1]);
        return 0;
    } else {
        printf("Error removing directory '%s'.\n", argv[1]);
        return 1;
    }
}
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/f887e78b-7184-48bd-bc38-d189b8ba8251)

## pwd
현재 디렉토리의 절대경로 
```
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
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/d1c184d1-93f9-43d5-a3db-25417459e08a)

## rm
파일 삭제
```
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
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/d6006f52-6bda-478e-95db-33fc8c242450)

## uname
- [옵션 x, -o] : 시스템 정보를 출력
- [-n] : 시스템이나 네트워크 노드의 이름 출력
- [-r] : 커널의 릴리즈 버전을 출력
 (커널의 새로운 기능, 버그 수정, 보안 패치 등이 포함된 최신 버전을 확인하고 적용할 수 있다.)
- [-v] : 커널 버전 출력
- [-m] : 시스템의 하드웨어 타입 또는 CPU 아키텍처(시스템의 구조, 동작 등을 정의하는 개념적인 모형) 출력

```
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int option;
    struct utsname os_info; //시스템 정보를 확인하는 함수 제공

    while ((option = getopt(argc, argv, "rvmo")) != -1) { //"rvmo"안에 동일한 문자가 있어서 option으로 리턴
        switch (option) {
            case 'r':
                if (uname(&os_info) == -1) {
                    perror("uname");
                    return 1;
                }
                printf("%s\n", os_info.release);
                break;
            case 'v':
                if (uname(&os_info) == -1) {
                    perror("uname");
                    return 1;
                }
                printf("%s\n", os_info.version);
                break;
            case 'm':
                if (uname(&os_info) == -1) {
                    perror("uname");
                    return 1;
                }
                printf("%s\n", os_info.machine);
                break;
            case 'o':
                if (uname(&os_info) == -1) {
                    perror("uname");
                    return 1;
                }
                printf("%s\n", os_info.sysname);
                break;
            default:
                printf("Usage: %s [-r|-v|-m|-o]\n", argv[0]);
                return 1;
        }
    }

    if (argc == 1) {
        // 옵션이 지정되지 않은 경우 -o 옵션과 동일하게 동작
        if (uname(&os_info) == -1) {
            perror("uname");
            return 1;
        }
        printf("%s\n", os_info.sysname);
    }

    return 0;
}
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/0db17ae4-edff-4327-81e3-55b965f98502)
