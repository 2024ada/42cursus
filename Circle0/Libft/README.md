[← 전체 프로젝트](../../README.md)

<div align="center">

# Libft

**후속 프로젝트의 기반이 된 C 유틸리티 라이브러리**

![C](https://img.shields.io/badge/C-334155?style=flat-square&logo=c&logoColor=white)
![Memory](https://img.shields.io/badge/Memory-0F766E?style=flat-square)
![Linked List](https://img.shields.io/badge/Linked_List-1D4ED8?style=flat-square)

`34개 기본 함수` · `9개 연결 리스트 함수` · `libft.a`

</div>

## 무엇을 만들었는가

문자 판별, 문자열·메모리 처리, 숫자 변환, 파일 디스크립터 출력, 연결 리스트 연산을 직접 구현한 정적 라이브러리입니다. 포인터와 메모리 소유권을 다루고, 여러 프로그램에서 공통 기능을 재사용하는 기반을 만들었습니다.

| 구성 | 구현 범위 |
| :--- | :--- |
| 문자·문자열 | 문자 판별, 대소문자 변환, 검색·비교·복사, 부분 문자열 |
| 메모리 | 초기화, 복사, 겹치는 영역 이동, 검색·비교, 할당 |
| 문자열 가공 | `split`, `join`, `trim`, 숫자→문자열, 콜백 기반 변환 |
| 출력 | 지정한 파일 디스크립터에 문자·문자열·정수 출력 |
| 연결 리스트 | 노드 생성·연결·삭제, 순회, 크기 계산, 매핑 |

## 과제에서 요구한 범위

[Subject v16.1](en.subject.pdf)의 필수·보너스 함수 목록을 기준으로 구현했습니다.

| 구분 | 명세의 요구사항 |
| :--- | :--- |
| 필수 | 문자·문자열·메모리 처리, 문자열 가공, FD 출력 등 34개 함수 |
| 보너스 | `t_list`와 연결 리스트 함수 9개 |

겹친 메모리 처리, 할당 실패 시 정리, `void *`와 콜백을 쓰는 리스트 API도 명세에 포함됩니다. 아래에서는 그 동작을 코드로 어떻게 구성했는지 설명합니다.

## 구현에서 주목할 부분

### 겹치는 메모리와 할당 크기 처리

[`ft_memmove.c`](ft_memmove.c)는 원본과 목적지 영역의 관계에 따라 복사 방향을 바꿉니다. [`ft_calloc.c`](ft_calloc.c)는 할당 크기 곱셈의 오버플로를 확인한 뒤 메모리를 초기화합니다.

### 여러 번의 할당을 하나의 작업으로 관리

[`ft_split.c`](ft_split.c)는 단어별 문자열을 할당하다 실패하면 이미 만든 문자열들을 해제합니다. [`ft_lstmap.c`](ft_lstmap.c)는 변환한 데이터와 새 노드를 구성하고, 노드 생성 실패 시 삭제 콜백으로 중간 결과를 정리합니다.

### 자료형을 고정하지 않는 리스트 API

[`libft.h`](libft.h)의 리스트는 `void *`로 데이터를 보관합니다. `ft_lstiter`, `ft_lstmap`, `ft_lstdelone`, `ft_lstclear`는 함수 포인터를 받아 데이터 처리와 해제 방법을 호출자가 지정하도록 구성했습니다.

## 빌드와 사용

C 컴파일러, `make`, `ar`가 필요합니다.

```sh
make
# 기본 함수가 포함된 libft.a 생성

make bonus
# 연결 리스트 함수까지 포함
```

사용 예시:

```c
#include "libft.h"

int main(void)
{
    char **words;
    int  i;

    words = ft_split("memory strings lists", ' ');
    if (!words)
        return (1);
    i = 0;
    while (words[i])
    {
        ft_putendl_fd(words[i], 1);
        free(words[i]);
        i++;
    }
    free(words);
    return (0);
}
```

위 예시를 `demo.c`로 저장한 경우:

```sh
cc -Wall -Wextra -Werror demo.c -L. -lft -o demo
./demo
```

`make clean`은 오브젝트 파일, `make fclean`은 라이브러리까지 삭제하고, `make re`는 다시 빌드합니다.

## 다른 프로젝트와의 연결

이 라이브러리의 함수는 [ft_printf](../../Circle1/ft_printf/README.md), [pipex](../../Circle2/pipex/README.md), [push_swap](../../Circle2/push_swap/README.md), [FdF](../../Circle2/FdF/README.md)에서 재사용됩니다. Minishell과 cub3D에는 확장·수정한 유틸리티가 포함되어 있습니다.

<a id="peer-feedback"></a>

## 동료 평가

### 평가자 `j**`

이 과제를 위한 강의를 만든다면 피평가자님이 저에게 설명해주신 것을 그대로 녹화한 것이 완벽한 강의라 할 수 있을 정도로 자세하게 설명을 해주셨습니다. 덕분에 제가 막히던 함수들에 대해 해답을 얻을 수 있었고, 연결리스트에 대한 개념을 새롭게 배워갈 수 있었습니다. 수고하셨습니다!

---

### 평가자 `y**`

Makefile부터 Source Code 한 줄 한 줄 아주 열정적으로 설명해주시는 모습이 피신 때와 변함이 없으시네요. 굿굿굿 ! 저는 평가를 받으면서 calloc overflow 체킹 로직을 인지하게 되었는데 미리 구현이 되어 있으신거 보면서 대단하다고 느꼈습니다. b^^d ft_itoa 의 경우 높은 자리수부터 분리하는 로직이 신선했습니다. 그리고 ft_split 의 경우 제 코드와 다른 기준으로 함수 분리가 되어 있음에도 가독성이 좋아 쉽게 이해가 되었습니다. 첫과제 해결하느라 고생하셨고 한방에 통과하셨으면 좋겠네요 고생하셨습니다.!

---

### 평가자 `h**`

제가 아직 Not Solve한 Problems도 Understand를 할 수 있도록 자세하게 설명해주셔서 Help주신 점에 대해 Thank you very much입니다. 전반적으로 Function에 대한 이해가 뛰어나시며 Bonus문제에서 노드를 이용하여 설명해주신 점 인상, Very Deep. 평가받으시느라 수고많으셨습니다. Thank you.

