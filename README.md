<div align="center">

# École 42 Cursus · C Portfolio

42 공통과정 C 프로젝트

![C](https://img.shields.io/badge/C-334155?style=flat-square&logo=c&logoColor=white)
![Unix](https://img.shields.io/badge/Unix_API-0F766E?style=flat-square)
![Algorithms](https://img.shields.io/badge/Algorithms-1D4ED8?style=flat-square)
![Graphics](https://img.shields.io/badge/Computer_Graphics-7C3AED?style=flat-square)

[대표 프로젝트](#featured-projects) · [전체 프로젝트](#all-projects) · [동료 평가](#peer-reviews)

</div>

---

42 공통과정에서 수행한 과제들을 모았습니다. 문자열 함수와 파일 입출력부터 정렬 프로그램, 셸, 그래픽 프로그램까지 C로 구현했습니다. 각 프로젝트 README에 과제 요구사항과 구현 방식, 추가한 기능을 정리했습니다.

<a id="featured-projects"></a>

## 대표 프로젝트

### [cub3D](Circle4/cub3D/README.md) · 1인칭 게임

2차원 맵을 1인칭 화면으로 보여주는 프로그램입니다. DDA로 광선을 추적하고, 픽셀마다 깊이를 비교해 벽·문·캐릭터의 가림 관계를 처리했습니다. 해바라기 수집을 목표로 적의 탐지·추적·공격, 아이템 배치, 최대 10라운드 진행을 구현했습니다. 실패한 라운드는 시작 상태를 복원해 다시 플레이할 수 있습니다.

### [Minishell](Circle3/minishell/README.md) · Unix 셸

입력한 명령어를 토큰과 구문 트리로 분석해 실행하는 셸입니다. 파이프라인·환경변수·논리 연산자를 처리하고, `mandatory/srcs/*/*.c`처럼 경로를 포함한 와일드카드와 `2>` 같은 FD 지정 리다이렉션도 구현했습니다. 토큰과 환경변수 등을 관리하는 동적 배열도 직접 만들었습니다.

### [FdF](Circle2/FdF/README.md) · 와이어프레임 뷰어

높이 값이 담긴 파일을 읽어 지형을 선으로 그립니다. 등각·직교 투영과 확대·이동·3축 회전을 지원합니다. 마우스 메뉴와 글꼴 표시를 직접 구현하고, 확인 팝업을 거쳐 지도 영역을 PPM 이미지로 저장하도록 했습니다. 지도를 열면 크기에 맞춰 초기 배율과 중심을 자동으로 계산합니다.

### [push_swap](Circle2/push_swap/README.md) · 두 스택 정렬

정해진 스택 연산만으로 정수를 정렬합니다. LIS(최장 증가 부분 수열)를 남기고 나머지 원소를 옮긴 뒤, 두 스택의 회전 비용을 비교해 다시 삽입합니다. 같은 방향의 회전은 동시에 실행해 연산 수를 줄이도록 했습니다.

<a id="all-projects"></a>

## 전체 프로젝트

Circle은 42 교육과정의 과제 단계입니다.

| Circle | 프로젝트 | 구현 내용 |
| :---: | :--- | :--- |
| 0 | [Libft](Circle0/Libft/README.md) | 문자열·메모리 처리와 연결 리스트를 정적 라이브러리로 구현 |
| 1 | [ft_printf](Circle1/ft_printf/README.md) | 가변 인자와 형식 문자열을 해석하고 출력 폭·정밀도·플래그 처리 |
| 1 | [get_next_line](Circle1/get_next_line/README.md) | 파일을 한 줄씩 반환하고, 여러 FD의 버퍼를 연결 리스트로 관리 |
| 2 | [pipex](Circle2/pipex/README.md) | 프로세스와 파이프로 여러 명령의 입출력을 연결하고 here_doc 처리 |
| 2 | [push_swap](Circle2/push_swap/README.md) | LIS와 회전 비용을 이용한 두 스택 정렬 |
| 2 | [FdF](Circle2/FdF/README.md) | 높이 지도의 투영·회전, 선 그리기, GUI와 화면 저장 |
| 3 | [Philosophers](Circle3/Philosophers/README.md) | 스레드·뮤텍스 방식과 프로세스·세마포어 방식의 식사 시뮬레이션 |
| 3 | [Minishell](Circle3/minishell/README.md) | 명령어 분석, 내장 명령, 파이프라인과 외부 프로그램 실행 |
| 4 | [cub3D](Circle4/cub3D/README.md) | 레이캐스팅 렌더러, 문·적·아이템과 라운드형 게임 |

## 실행 환경

공통으로 C 컴파일러와 `make`가 필요합니다. Minishell은 GNU Readline을, FdF와 cub3D는 Linux의 X11·Xext와 그래픽 디스플레이 환경을 사용합니다. 빌드와 실행 명령은 각 프로젝트 README에 적었습니다.

`libft`, `ft_printf`, `get_next_line`은 직접 구현해 여러 과제에서 재사용했습니다. `minilibx-linux`는 외부 그래픽 라이브러리입니다.

<a id="peer-reviews"></a>

## 동료 평가

각 프로젝트 README 하단에 평가자 코멘트란이 있습니다.

[Libft](Circle0/Libft/README.md#peer-feedback) · [ft_printf](Circle1/ft_printf/README.md#peer-feedback) · [get_next_line](Circle1/get_next_line/README.md#peer-feedback) · [pipex](Circle2/pipex/README.md#peer-feedback) · [push_swap](Circle2/push_swap/README.md#peer-feedback) · [FdF](Circle2/FdF/README.md#peer-feedback) · [Philosophers](Circle3/Philosophers/README.md#peer-feedback) · [Minishell](Circle3/minishell/README.md#peer-feedback) · [cub3D](Circle4/cub3D/README.md#peer-feedback)

