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
