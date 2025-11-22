# Get Next Line

`get_next_line` is a small but powerful utility function written in C as part of the 42 / Codam curriculum. Its purpose is to read **one line at a time** from a file descriptor, handling buffering internally so that the caller can simply loop over lines.

This repository contains my implementation of both the **mandatory part and the bonus part** of the project.fileciteturn3file0

---

## 📚 Overview

The core function:

```c
char *get_next_line(int fd);
```

- Reads from a file descriptor (`fd`) and **returns the next line**.
- The returned string **includes the trailing `\n`** when a newline is present.
- When there is **nothing left to read** or an error occurs, it returns `NULL`.
- It works both with **regular files** and **standard input**.

The reading behavior is controlled by the `BUFFER_SIZE` macro, which is provided at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Different `BUFFER_SIZE` values are used to stress-test the implementation (e.g. `1`, `42`, `9999`, etc.).fileciteturn3file0

---

## 🧱 Project structure

**Mandatory files**

- `get_next_line.c` – main implementation of `get_next_line`.
- `get_next_line_utils.c` – helper functions for string and buffer handling.
- `get_next_line.h` – public header with prototypes and the `BUFFER_SIZE` macro guard.

**Bonus files**

- `get_next_line_bonus.c` – bonus version of `get_next_line` that supports multiple file descriptors.
- `get_next_line_utils_bonus.c` – utils for the bonus implementation.
- `get_next_line_bonus.h` – bonus header.

---

## 🛠 Implementation details

### 1. High-level algorithm

The implementation is based on three core ideas:

1. **Persistent storage per file descriptor**  
   A static pointer (or array of pointers in the bonus part) keeps any **leftover data** between calls. This allows `get_next_line` to resume reading exactly where it left off.

2. **Buffered reads with `read`**  
   Data is fetched using `read(fd, buffer, BUFFER_SIZE)` and appended to the stored string until either:
   - a newline (`'\n'`) is found, or  
   - `read` returns 0 (end of file), or  
   - `read` returns `-1` (error).

3. **Splitting into “line” and “rest”**  
   - `ft_get_line` extracts the next complete line from the stored string.
   - `ft_rest` keeps everything after that line for the next call.
   - If there is no more data, the static storage is freed and set to `NULL`.

All heap allocations are checked, and buffers are freed on error to avoid leaks.

### 2. Helper functions

To avoid using `libft` (forbidden by the subject), a minimal set of utility functions is reimplemented in `get_next_line_utils.c`:

- `ft_strlen` – length of a C-string.
- `ft_strchr` – search for a character in a string.
- `ft_strjoin` / `ft_join` – concatenate two strings into a freshly allocated one.

These helpers are duplicated in `get_next_line_utils_bonus.c` for the bonus version.

---

## ⭐ Bonus: multiple file descriptors

The bonus part extends `get_next_line` so it can **track several file descriptors at once**.

Example: you can read from `fd 3`, then `fd 4`, then `fd 5`, then back to `fd 3`, and so on, without losing the buffered state of each descriptor.fileciteturn3file0  

This is implemented by keeping **separate static storage per file descriptor**:

```c
static char *strread[10000];
```

Each index in this array corresponds to a different `fd`, allowing truly interleaved reading from multiple sources.

---

## 🔧 Building

You can compile the project manually, specifying your own `BUFFER_SIZE`:

```bash
# Mandatory version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42     get_next_line.c get_next_line_utils.c

# Bonus version (multiple file descriptors)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42     get_next_line_bonus.c get_next_line_utils_bonus.c
```

In the actual 42 project, these files are usually wrapped in a `Makefile` with a `bonus` rule so that the evaluator can build both mandatory and bonus parts separately.fileciteturn3file0  

---

## ▶️ Usage example

### Mandatory version

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int   fd;
    char *line;

    fd = open("example.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Bonus version (multiple file descriptors)

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int   fd1 = open("file1.txt", O_RDONLY);
    int   fd2 = open("file2.txt", O_RDONLY);
    char *line1;
    char *line2;

    if (fd1 < 0 || fd2 < 0)
        return (1);
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    printf("file1: %s", line1);
    printf("file2: %s", line2);
    free(line1);
    free(line2);
    close(fd1);
    close(fd2);
    return (0);
}
```

---

## 🚫 Constraints & rules

As required by the subject:fileciteturn3file0  

- **Language**: C, compiled with `cc -Wall -Wextra -Werror`.
- **Allowed functions**: `read`, `malloc`, `free`.
- **Forbidden**:
  - `lseek`.
  - Global variables.
  - Using `libft`.
- The function must **not leak memory** and must not crash (no segfaults, double frees, etc.).
- The project must follow the **42 Norm**.

---

## 🧠 What this project taught me

Implementing `get_next_line` (with bonus) helped me practice:

- Using **static storage** to preserve state across function calls.
- Working with **file descriptors** and the `read` system call.
- Designing a **buffering strategy** that reads only as much data as needed.
- Implementing **robust string utilities** without relying on `libft`.
- Handling **multiple streams in parallel** in C (bonus part).
- Managing dynamic memory carefully to avoid leaks and undefined behavior.

`get_next_line` is now a reusable utility that I can integrate into other C projects whenever I need simple, line-based input handling.
