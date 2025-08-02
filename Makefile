# Compiler
CC = gcc
CLANG = clang

# Files
SRCS = main.c codegen.c
OUT_LL = output.ll
OUT_EXE = program

# Default target
all: $(OUT_EXE)

# Compile compiler that emits LLVM IR
compiler: $(SRCS) ast.h
	$(CC) -o compiler $(SRCS)

# Generate LLVM IR from compiler
$(OUT_LL): compiler
	./compiler > $(OUT_LL)

# Compile LLVM IR to executable
$(OUT_EXE): $(OUT_LL)
	$(CLANG) $(OUT_LL) -o $(OUT_EXE)

# Clean build artifacts
clean:
	rm -f compiler $(OUT_LL) $(OUT_EXE)
