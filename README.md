# Toy Compiler Backend

## Overview

This is a simple compiler backend for a toy language. It manually builds an Abstract Syntax Tree (AST) in C and generates LLVM IR code. The LLVM IR can be compiled with clang into a runnable program.

---

## Features

- Integer constants
- Variables with `let` statements
- Arithmetic expressions: addition (`+`) and multiplication (`*`)
- `print` statement for output
- Manual AST construction (no parser yet)
- LLVM IR code generation
- Automated build system using Makefile

---

## Project Structure

```
toy-compiler/
├── ast.h           # AST node definitions
├── codegen.c       # LLVM IR code generation functions
├── main.c          # Manual AST creation and entry point
├── Makefile        # Build automation
└── output.ll       # Generated LLVM IR (after running compiler)
```

---

## Build and Run

### Requirements

- GCC (for compiling the compiler)
- Clang (for compiling generated LLVM IR)

### Commands

```bash
make            # Build compiler, generate IR, compile executable
./program       # Run the compiled program
make clean      # Clean build artifacts
```

#### Manual Build Steps

```bash
make compiler               # Build the compiler
./compiler > output.ll      # Generate LLVM IR
clang output.ll -o program  # Compile LLVM IR to executable
./program                   # Run the program
make clean                  # Clean build artifacts
```

---

## Example Toy Language Code

```toy
let x = 5;
let y = x + 3;
print(y);
let z = x * 2;
print(z);
```

---

## How it Works

1. `main.c` manually builds the AST for the toy program.
2. `codegen.c` walks the AST and prints LLVM IR code.
3. The Makefile compiles the compiler, runs it to produce LLVM IR (`output.ll`), then compiles that IR to an executable.
4. Running the executable prints the results of the toy program.

---

## Next Steps (Optional)

- Add support for more operators (subtraction, division)
- Write an optimizer pass (constant folding)
- Implement a parser for the toy language
- Support control flow statements (if, while)
- Add backend codegen for RISC-V or ARM assembly

---

## License

This project is released under the MIT License.

---

## Author

Stefan Jipa

---
