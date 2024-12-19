# Compiler2024

This repository contains the programs and code written as part of the Compiler course. The project demonstrates the use of **Lex** and **Yacc** for lexical analysis and syntax parsing, respectively.

## How to Use Lex
To use **Lex** (via Flex), follow these steps:

1. **Generate the Lexer:**
   ```bash
   flex <fileName>.l
   ```
   This command processes the Lex file (`<fileName>.l`) and generates a C source file named `lex.yy.c`.

2. **Compile the Lexer:**
   ```bash
   gcc lex.yy.c -lfl
   ```
   This compiles the lexer code using GCC and links it with the Flex library (`-lfl`).

3. **Optionally Combine with Bison:**
   If you are combining Lex with Bison (Yacc), you can follow these steps:
   
   - Process the Yacc file:
     ```bash
     bison -d <fileName>.y
     ```
     This generates two files:
     - `<fileName>.tab.c`: The C source for the parser.
     - `<fileName>.tab.h`: The header file for the parser.

   - Compile and link the Lex and Yacc code:
     ```bash
     gcc lex.yy.c <fileName>.tab.c -o <executable file name> -lm
     ```
     This compiles both the lexer and parser and links them into an executable. The `-lm` flag links the math library (if needed).

## Notes
- Ensure that the `<fileName>.l` and `<fileName>.y` files are compatible with each other. The Yacc file should define the grammar rules, and the Lex file should handle the tokens.
- Use `-lfl` and `-lm` as needed for linking Flex and math libraries.

## Example
Assume you have the following files:
- `example.l`: Lex file.
- `example.y`: Yacc file.

Steps to build and run the project:
1. Generate parser:
   ```bash
   bison -d example.y
   ```
2. Generate lexer:
   ```bash
   flex example.l
   ```
3. Compile and link:
   ```bash
   gcc lex.yy.c example.tab.c -o example -lm
   ```
4. Execute:
   ```bash
   ./example
   ```
