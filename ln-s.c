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