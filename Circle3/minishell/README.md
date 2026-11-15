*This project has been created as part of the 42 curriculum by ucho, nalee.*

![minishell screenshot](https://raw.githubusercontent.com/2nani2/assets/main/3circle/minishell/asset/minishell_screenshot.png)

## Description
---
**minishell** is a 42 school team project to create a small Unix shell written in C.
This program reproduces the behavior of a standard Unix shell. It implements redirections and pipelines, heredoc, environment variable expansion, wildcard (`*`) expansion, logical operators, and built-in commands such as `cd`, `echo`, `env`, `exit`, `export`, `pwd`, and `unset`.

It supports both:
- **Interactive mode (TTY)**: colored prompt, readline history, and signal behavior close to bash.
- **Non-interactive mode**: reads commands from stdin (e.g., piped input / script).

## Features
---
### Prompt & Input
- Colored prompt (readline): `🍫 mini$ `
- Secondary prompt for unclosed quotes / multiline input: `> `
- History enabled in interactive mode (`readline/history`)

### Architecture & Memory
- **Custom Vector Implementation**:
  - Implements a generic dynamic array (`t_vec`) similar to C++ vectors to manage tokens, AST nodes, and environment variables efficiently.
  - Supports automatic resizing and memory reservation strategies to optimize allocation overhead.
- **Structured Resource Management**:
  - Utilizes registered destructor callbacks within vectors to ensure clean recursive deallocation of complex data structures (e.g., command pipelines, string arrays).

### Lexing / Parsing
- Operators handled in the lexer/parsing flow include:
  - Pipes: `|`
  - Logical operators: `&&`, `||`
  - Parentheses for subshell grouping: `( ... )`
  - Redirection: `<`, `>`, `<<`, `>>`
- Quote rules:
  - Single quotes `'...'`: no expansion inside
  - Double quotes `"..."`: `$VAR` and `$?` expansion supported
  - If a quote is not closed, the shell keeps reading lines until it closes until the matching execution quote is found.

### Environment expansion
- `$VAR` expands to the environment value
- `$?` expands to the last exit status

### Execution
- Built-ins vs external binaries:
  - External commands are resolved via `PATH` (or directly if the command contains `/`) and executed with `execve`.
  - Exit code rules match typical shells:
    - `126` on permission errors (`EACCES`)
    - `127` for command not found / invalid command
    - `128 + signal` when terminated by a signal
- Pipelines:
  - `cmd1 | cmd2 | cmd3` supported with `pipe`, `fork`, `dup2`, and `waitpid`
  - The pipeline exit status follows the **last command**’s exit status.

### Signals
- One global signal flag is used: `volatile sig_atomic_t g_sig`
- `Ctrl-C (SIGINT)`:
  - In interactive prompt: clears the current input and shows a fresh prompt
  - In child execution: behaves like a real shell (exit code 130)
- `Ctrl-\ (SIGQUIT)`:
  - Restored to default behavior in child processes (so external commands react correctly)

### Built-ins implemented
- `echo` (supports repeated `-n`, e.g., `-n`, `-nnn`)
- `cd`
- `pwd`
- `export`
  - With no args: prints in `declare -x KEY="VALUE"` style
- `unset`
- `env`
- `exit`
  - `exit` prints `exit` when called in the parent context
  - Numeric validation: non-numeric argument -> exit code `2` with error message
  - Too many arguments -> prints error and does not exit immediately

### Built-ins execution policy
To match real shell behavior:
- Executed in the **parent** when they must modify the shell state:
  - `cd`, `export`, `unset`, `exit`
- Executed in the **child** when safe:
  - `echo`, `pwd`, `env`

## Instructions
---
### Requirements
- `cc` (or clang/gcc)
- `make`
- `readline` library (linked with `-lreadline`)

> On some systems you may need extra linker flags (e.g., `-lncurses` or `-ltinfo`) depending on how readline is packaged.
### Build
From the repository root:
- `make` 
- `make bonus` 
> **Note**: Since the shell architecture unifies these features, the mandatory and bonus source codes are effectively identical. The bonus files merely carry the _bonus suffix to comply with the project's file naming requirements.

This produces:
- `./minishell`

### Clean
- `make clean` (removes build objects)
- `make fclean` (removes objects + binary)
- `make re` (rebuild)

### Run
Interactive:
- `./minishell`

Non-interactive examples:
- `printf "echo hello\n" | ./minishell`
- `cat script.sh | ./minishell`

## Usage examples
---
### Mandatory
```bash
echo Hello
```
```bash
export NAME=world
```
```bash
echo "Hello $NAME"
```
```bash
cat < infile | grep foo > outfile
```
```bash
echo test >> log.txt
```
```bash
cat << EOF
```

### Bonus
```bash
true && echo ok
```
```bash
false || echo fallback
```
```bash
(echo a && echo b) | cat
```
```bash
echo *.c
```

## Project structure (overview)
---
Directory structure:
- `main/`: Entry point, shell initialization, main loop, and reset logic.
- `common/`: Core data structures (Vectors), error handling, and memory swap utilities.
- `envs/`: Environment variable storage, management, and conversion.
- `scanning/`: Input handling (readline integration, PS1/PS2 prompt loop).
- `lexing/`: Tokenizer (handles operators, quotes expansion).
- `parsing/`: AST construction (pipeline/cmd/subshell nodes) and command path resolution.
- `globbing/`: Wildcard (`*`) expansion logic.
- `heredoc/`: Heredoc processing and temporary file handling.
- `pipex/`: Execution engine (process forking, piping, redirection setup, executing built-ins vs binaries).
- `builtin/`: Implementation of built-in commands (`cd`, `echo`, `export`, etc.).
- `signal/`: Signal handlers (`SIGINT`, `SIGQUIT`) configuration.
- `utils/`: Generic string helpers and character checks.
- `widget/`: UI elements (ASCII art/logo).
- `libft/`: General-purpose string utilities for Minishell, adapted from libft.

## Resources
---
Classic references:
- Bash manual / POSIX shell overview (`bash(1)`, `sh(1)`)
- man pages: `fork(2)`, `execve(2)`, `pipe(2)`, `dup2(2)`, `waitpid(2)`, `signal(7)`
- GNU Readline documentation
- “Advanced Programming in the UNIX Environment” (Stevens & Rago)

### AI usage
AI was used to assist with:
- Providing basic usage examples for allowed functions
- Suggesting function name ideas
- Generating test cases
