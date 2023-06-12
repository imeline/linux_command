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