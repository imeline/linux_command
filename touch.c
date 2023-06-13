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
 

}
/// touch -c newfile => 현재시간으로 변경
/// touch -t YYYYMMDDhhmm newfile => 마음대로 변경
/// touch -r oldfile newfile => 다른파일 시간으로 변경