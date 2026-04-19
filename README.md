*This project has been created as part of the 42 curriculum by fgameiro, rucosta.*

```
   $$\      $$\ $$$$$$\ $$\   $$\ $$$$$$\            
   $$$\    $$$ |\_$$  _|$$$\  $$ |\_$$  _|           
   $$$$\  $$$$ |  $$ |  $$$$\ $$ |  $$ |             
   $$\$$\$$ $$ |  $$ |  $$ $$\$$ |  $$ |             
   $$ \$$$  $$ |  $$ |  $$ \$$$$ |  $$ |             
   $$ |\$  /$$ |  $$ |  $$ |\$$$ |  $$ |             
   $$ | \_/ $$ |$$$$$$\ $$ | \$$ |$$$$$$\            
   \__|     \__|\______|\__|  \__|\______|           
                                                     
    $$$$$$\  $$\   $$\ $$$$$$$$\ $$\       $$\       
   $$  __$$\ $$ |  $$ |$$  _____|$$ |      $$ |      
   $$ /  \__|$$ |  $$ |$$ |      $$ |      $$ |      
   \$$$$$$\  $$$$$$$$ |$$$$$\    $$ |      $$ |      
    \____$$\ $$  __$$ |$$  __|   $$ |      $$ |      
   $$\   $$ |$$ |  $$ |$$ |      $$ |      $$ |      
   \$$$$$$  |$$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$$$\ 
    \______/ \__|  \__|\________|\________|\________|
```

> *As beautiful as a shell.*

---

## 👥 Authors

| Name | 42 Login | GitHub |
|------|----------|--------|
| Francisco Gameiro | fgameiro | [@kikogameiro](https://github.com/kikogameiro) |
| Rui Costa | rucosta | [@RuiSlayer](https://github.com/RuiSlayer) |

---

## 📖 Description

**minishell** is a 42 School project whose goal is to build a functional Unix shell from scratch in C, modelled after Bash. It is one of the most comprehensive projects in the curriculum, covering process management, file descriptors, signal handling, memory management, and the full pipeline from user input to command execution.

The shell supports interactive use with a prompt and command history, resolves executables via `PATH` or relative/absolute paths, and handles the full suite of features expected from a modern shell — all while respecting strict memory management rules (no leaks allowed in code we wrote; `readline()` internal leaks are exempted by the subject).

The only global variable used is `g_signal` — a `volatile sig_atomic_t` that stores the received signal number and nothing else, as required by the subject.

### Features

| Feature | Details |
|---------|---------|
| **Prompt & history** | Interactive prompt with working command history via `readline` |
| **Executable resolution** | Via `PATH`, relative path, or absolute path |
| **Pipes** `\|` | Full pipeline support — stdout of each command connects to stdin of the next |
| **Redirections** | `<` input, `>` output (overwrite), `>>` output (append), `<<` heredoc |
| **Environment variables** | `$VAR` expansion and `$?` (last exit status) |
| **Quote handling** | Single quotes preserve everything literally; double quotes allow `$` expansion |
| **Signal handling** | `Ctrl+C` shows new prompt, `Ctrl+D` exits, `Ctrl+\` does nothing |
| **Built-in commands** | `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |

#### Built-in commands

| Command | Behaviour |
|---------|-----------|
| `echo [-n]` | Print to stdout; `-n` suppresses trailing newline |
| `cd [path]` | Change directory (relative or absolute path only) |
| `pwd` | Print current working directory |
| `export [var=val]` | Set or display environment variables |
| `unset [var]` | Remove a variable from the environment |
| `env` | Print all exported environment variables |
| `exit [status]` | Exit the shell with an optional status code |

---

## 🚀 Instructions

### Requirements

- GCC or Clang
- GNU Make
- `readline` library

On Debian/Ubuntu:
```bash
sudo apt-get install libreadline-dev
```

### Compilation

```bash
git clone https://github.com/kikogameiro/minishell.git
cd minishell
make
```

### Execution

```bash
./miniShell
```

### Makefile rules

```bash
make          # build the binary
make clean    # remove object files
make fclean   # remove object files and binary
make re       # full rebuild
make valgrind # run with valgrind leak checker
```

### Usage examples

```bash
# Pipes
ls -la | grep ".c" | wc -l

# Redirections
echo "hello world" > out.txt
cat < out.txt >> log.txt
cat << EOF
  this is a heredoc
EOF

# Environment variables
export MY_VAR=42
echo $MY_VAR
echo $?

# Quotes
echo 'No $expansion here'
echo "But $USER is expanded"
```

---

## ⚙️ How It Works

```
User input (readline)
        │
        ▼
  ┌─────────────┐
  │    Lexer    │  ft_tokenization_handler()
  │  (tokens/)  │  Splits raw input into a t_token linked list
  └──────┬──────┘  types: T_IDENTIFIER, T_PIPE, T_LESS, T_GREAT,
         │                T_DLESS, T_DGREAT, T_EOF
         ▼
  ┌─────────────┐
  │   Parser    │  ft_parse() → ft_parse_pipeline() → ft_parse_command()
  │  (parser/)  │  Builds a t_cmd list, each with args[] + t_redir chain
  └──────┬──────┘
         │
         ▼
  ┌─────────────┐
  │  Expander   │  ft_expand() → ft_expand_string()
  │ (expansion/)│  Resolves $VAR and $?, handles quotes, word-splits
  └──────┬──────┘
         │
         ▼
  ┌─────────────┐
  │  Executor   │  execute_pipeline() / run_builtin_in_parent()
  │ (executor/) │  fork() + execve() for externals; built-ins in parent
  └──────┬──────┘
         │
         ▼
  exit status → shell->exit_status  ($?)
```

### Key data structures

```c
typedef struct s_shell {
    t_env   *env;         // environment variable linked list
    t_cmd   *cmds;        // current position in command list
    t_cmd   *cmds_head;   // head of command list (for cleanup)
    short    exit_status; // last command exit code ($?)
    int      cmd_count;   // number of commands in the pipeline
    int      saved_in;    // saved stdin fd (restored after redirections)
    int      saved_out;   // saved stdout fd
    int      is_subshell; // subshell context flag
} t_shell;

typedef struct s_pipe {
    int     pipe_fd[2]; // current pipe read/write ends
    int     prev_fd;    // read end of the previous pipe
    int     pipe_count; // number of pipes remaining
    t_cmd  *cmd;        // command currently being executed
    pid_t   last_pid;   // last child PID (determines exit status)
    pid_t  *pids;       // all child PIDs (for waitpid loop)
} t_pipe;
```

---

## 🗂️ Project Structure

```
minishell/
├── main_exec.c            # Entry point, main REPL loop
├── signal_handle.c        # Signal setup & handlers
├── Makefile
│
├── incs/                  # All header files
│   ├── shell.h            # t_shell — top-level shell state
│   ├── tokens.h           # t_token, t_token_type, tokeniser API
│   ├── parser.h           # t_cmd, t_redir, t_redir_type, parser API
│   ├── expansion.h        # Expansion & word-splitting API
│   ├── env.h              # t_env linked list, env management
│   ├── errors.h           # Syntax error helpers & macros
│   └── miniShell_exec.h   # t_pipe, executor API, built-ins, colour macros
│
├── tokens/                # Lexer / tokeniser
├── parser/                # Token list → command list
├── expansion/             # Variable & quote expansion
├── executor/              # Fork, exec, pipes, redirections
├── built_ins/             # Built-in command implementations
├── env/                   # Environment linked list
├── errors/                # Error handling
├── 42libft/               # Custom C library (libft)
└── ft_get_next_line/      # get_next_line — used for heredoc reading
```

---

## 📚 Resources

### Documentation & references

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — the ground truth for all behavioural questions
- [GNU readline](https://tiswww.case.edu/php/chet/readline/rltop.html) — prompt and history library
- [The Open Group — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — POSIX shell spec
- [Linux `man` pages](https://man7.org/linux/man-pages/) — `fork(2)`, `execve(2)`, `pipe(2)`, `sigaction(2)`, `waitpid(2)`, `dup2(2)`
- [Write a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — great intro tutorial
- [Wildcards & globbing — TLDP](https://tldp.org/LDP/abs/html/globbingref.html)

### 🤖 How AI was used

AI tools (primarily Claude) were used throughout this project for the following purposes:

- **Studying obscure behaviour** — when Bash did something weird and neither of us understood why, we asked AI to explain the POSIX rationale behind it (and then verified it against the man pages).
- **Debugging** — when a segfault had no obvious cause at 2am, AI helped us think through possible root causes, which we then tracked down ourselves in the actual code.
- **Writing functions that would make real programmers cry** — some of the more cursed string manipulation and edge-case handling in the expander were designed with AI assistance. We understood every line before it went in.
- **Writing this README** — yes, this README was written with AI assistance. The content is accurate, the structure follows the subject requirements, and we reviewed every word.

> All AI-generated content was reviewed, tested, and understood by both authors before being used in the project. We can explain every function and every design choice.

---

## 📜 License

This project is part of the 42 School curriculum and is intended for educational purposes.
