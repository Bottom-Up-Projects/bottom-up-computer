# Project 03. Sequential Circuits

## Instructions

-   You need to implement the functions given in the source code. You may not use operators such as `&`, `|`, `!`, etc.
-   You may use functions you implemented in project01 and project02.
-   You may introduce additional `bit_t` variables to implement the functions.
-   You may not use any flow control codes (ex `if`, `for`, `while`, etc.) except the ones provided as skeleton.
-   You must not introduce additional `DFF`s other than the `n` dffs provided by the parameter.
-   When using the chips implemented in this project, do not change the value of `n`.
-   DFFs in the parameter are allocated by the caller(The test function). So you don't need to call functions such as `malloc` or `new`.

## Specification

### DFF(Data Flip-Flop)

| Type     | Description                                              |
| -------- | -------------------------------------------------------- |
| Input    | `bit_t in`                                               |
| Output   | `bit_t out`                                              |
| Function | `out(t) = in(t-1)`                                       |
| Usage    | `out = dffptr->DFF(in)` <br> `current_value = dffptr->val` |

TBD
