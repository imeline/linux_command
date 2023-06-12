# sys_linux_command

##ln

```
//하드링크(같은 i-node 가지게끔)
#include <unistd.h>
int main(int argc, char *argv[ ])
{
if (link(argv[1], argv[2]) == -1) {
//link(기존 파일, 생성 링크 파일), 0성공, -1실패
exit(1);
}
exit(0);
}
```
![image](https://github.com/imeline/sys_linux_command/assets/128706341/438def0e-2758-42a7-b93f-c405cf518cb4)
