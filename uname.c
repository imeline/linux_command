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



