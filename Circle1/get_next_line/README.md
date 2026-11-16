[← 전체 프로젝트](../../README.md)

<div align="center">

# get_next_line

**여러 번의 read 호출을 하나의 줄 단위 인터페이스로**

![C](https://img.shields.io/badge/C-334155?style=flat-square&logo=c&logoColor=white)
![IO](https://img.shields.io/badge/Buffered_IO-0F766E?style=flat-square)
![FD](https://img.shields.io/badge/Multiple_FDs-1D4ED8?style=flat-square)

`정적 버퍼` · `가변 읽기 크기` · `FD별 연결 리스트`

</div>

## 무엇을 만들었는가

파일 디스크립터에서 한 줄을 읽어 반환하는 함수입니다. 한 번의 `read`가 줄 중간에서 끝나거나 여러 줄을 함께 읽는 상황을 다루기 위해, 남은 데이터를 함수 호출 사이에 보관합니다.

**사용 기술:** C, `read`, `malloc`/`free`, 정적 변수, 단일 연결 리스트.

```c
char *get_next_line(int fd);
```

줄바꿈이 있으면 반환 문자열에 `\n`이 포함됩니다. 마지막 줄에 줄바꿈이 없으면 남은 문자열을 반환하고, 이후 EOF에서는 `NULL`을 반환합니다. 반환받은 문자열은 호출자가 해제합니다.

## 과제에서 요구한 범위

[Subject v12](en.subject.pdf)을 기준으로 기본·보너스를 나누었습니다.

| 구분 | 명세의 요구사항 |
| :--- | :--- |
| 필수 | 파일·표준 입력에서 한 줄씩 반환, 줄바꿈·EOF 처리, 다양한 `BUFFER_SIZE` 지원 |
| 보너스 | static 변수 하나로 상태를 보관하면서 여러 FD를 번갈아 읽기 |

다중 FD는 보너스에 지정되어 있습니다. 이 코드에서는 **FD별 버퍼를 연결 리스트로 관리**하는 방식을 선택해, FD 번호를 인덱스로 쓰는 고정 크기 배열 없이 상태를 보관합니다.

## 구현에서 주목할 부분

### 읽기·줄 추출·나머지 보관을 분리

[`get_next_line.c`](get_next_line.c)는 읽은 데이터를 누적한 뒤 줄바꿈 위치를 찾습니다. `set_nl`은 한 줄을 분리하고 나머지를 보관하며, `set_eof`와 `set_err`는 종료와 읽기 오류 경로를 처리합니다.

### 입력 크기를 고정된 줄 길이와 분리

[헤더](get_next_line.h)의 `BUFFER_SIZE`는 한 번에 읽을 바이트 수이며 기본값은 `1000`입니다. 줄의 길이는 여러 번의 읽기와 문자열 결합으로 처리합니다.

### 다중 FD를 연결 리스트로 관리

[보너스 구현](get_next_line_bonus.c)은 `fd`, `buffer`, `next`를 가진 노드를 사용합니다. 이미 등록된 FD의 노드를 찾거나 새 노드를 추가하고, EOF·읽기 오류 시 해당 노드를 제거합니다. FD 번호를 고정 크기 배열의 인덱스로 사용하는 방식과 구분되는 구조입니다.

| 구현 | 호출 사이에 보관하는 상태 | 소스 |
| :--- | :--- | :--- |
| 기본 | 하나의 정적 버퍼 | [기본 구현](get_next_line.c) · [유틸리티](get_next_line_utils.c) |
| 보너스 | FD별 버퍼 노드의 연결 리스트 | [보너스 구현](get_next_line_bonus.c) · [유틸리티](get_next_line_utils_bonus.c) |

## 빌드와 사용

이 프로젝트에는 Makefile이 없습니다. 호출할 `main` 함수와 함께 소스를 컴파일합니다.

사용 예시를 `demo.c`로 저장합니다.

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int  fd;
    char *line;

    fd = open("README.md", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    while (line)
    {
        write(1, line, ft_strlen(line));
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

```sh
cc -Wall -Wextra -Werror -DBUFFER_SIZE=42 \
    demo.c get_next_line.c get_next_line_utils.c -o demo
./demo
```

다중 FD를 사용하는 프로그램에서는 `get_next_line_bonus.h`를 포함하고, 두 소스 파일을 `get_next_line_bonus.c`와 `get_next_line_utils_bonus.c`로 교체해 빌드합니다. 기본·보너스 소스는 같은 함수 이름을 정의하므로 한 실행 파일에는 한 쪽을 선택합니다.

## 구현 범위

현재 구현은 호출마다 `read`를 수행한 뒤 버퍼의 줄바꿈을 확인합니다. 파일 읽기 예제와 별개로, 입력을 계속 기다리는 스트림에서의 동작이나 메모리 할당 실패 경로는 추가 검증할 항목입니다.

<a id="peer-feedback"></a>

## 동료 평가

### 평가자 `j**`

안녕하세요. 우선 테스트 함수를 만들어서 돌려봤을데 잘 작동하는 것을 확인했습니다. BUFFER_SIZE에 음수를 넣고 잘못된 값을 넣었을때도 잘 작동하는 점도 보았습니다. 이 부분에서 제 함수에서는 처리하는 과정이 조금 복잡했는데 아주 간단하게 처리하셔서 인상깊었습니다. NULL가드도 아주 휼륭하게 처리하셨습니다. 코드 구조도 아주 깔끔하고 읽기 쉽게 되어있어서 코드 리뷰도 금방할 수 있었습니다. 제가 중간에 테스트케이스 만들때 실수를 해서 NULL이 떠서 둘다 긴장했지만 어쨋든 평가가 잘 끝나서 다행인거 같습니다.. 그럼 남은 평가도 파이팅~~~~!!

---

### 평가자 `j**`

안녕하세요. 과제에 필요한 함수들이 어떻게 쓰이는지 모두 자세하게 설명해주셨고, 제가 bonus 파트에서 fd가 바뀔 때 어떻게 코드를 작성해야하는지 헤매고 있었는데 덕분에 잘 이해하고 마저 과제를 할 수 있을 것 같습니다. 수고하셨습니다~

---

### 평가자 `j**`

제가 현재 가장 힘쓰고 있는 GNL를 볼 수 있어서, 이해하고 제 코드와 비교하는 재미가 있었습니다. FREE부분에서 많은 어려움이 있었는데, 함수의 발동 조건을 세분화 하셔서, free가 필요한 부분을 정하신 부분이 감명깊었습니다. 또한 연결리스트를 활용한 다중 fd 처리를 보니 막혀있던 부분의 해결책을 확인한 것 같았습니다. 다만 보너스 부분에서 리스트를 처리하는 함수 안의 변수 이름을 다른 함수에서 동일하게 사용되는 backup이 아닌 ls_backup이라면 다른 분들도 설명 없이 코드를 이해하는데 좀 더 도움이 될 것 같았습니다.

