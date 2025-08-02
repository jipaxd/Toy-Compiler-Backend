#include <stdio.h>
#include "ast.h"

int temp_count = 0;

int gen_expr(Expr* e) {
    if (e->kind == EXPR_CONST) {
        int reg = temp_count++;
        printf("  %%t%d = add i32 0, %d\n", reg, e->const_value);
        return reg;
    } else if (e->kind == EXPR_VAR) {
        int reg = temp_count++;
        printf("  %%t%d = load i32, i32* %%%s\n", reg, e->var_name);
        return reg;
    } else if (e->kind == EXPR_ADD) {
        int left = gen_expr(e->add.left);
        int right = gen_expr(e->add.right);
        int reg = temp_count++;
        printf("  %%t%d = add i32 %%t%d, %%t%d\n", reg, left, right);
        return reg;
    } else if (e->kind == EXPR_MUL) {
        int left = gen_expr(e->mul.left);
        int right = gen_expr(e->mul.right);
        int reg = temp_count++;
        printf("  %%t%d = mul i32 %%t%d, %%t%d\n", reg, left, right);
        return reg;
    } else {
        fprintf(stderr, "Unknown expression kind\n");
        return -1;
    }
}

void gen_stmt(Stmt* s) {
    if (s->kind == STMT_LET) {
        // Allocate space for variable if first time
        printf("  %%%s = alloca i32\n", s->let_stmt.name);
        int val_reg = gen_expr(s->let_stmt.value);
        printf("  store i32 %%t%d, i32* %%%s\n", val_reg, s->let_stmt.name);
    } else if (s->kind == STMT_PRINT) {
        int val_reg = gen_expr(s->print_stmt.value);
        printf("  %%t%d = call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %%t%d)\n", temp_count++, val_reg);
    } else {
        fprintf(stderr, "Unknown statement kind\n");
    }
}

void generate_code(Stmt* program[], int size) {
    printf("@.str = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n\n");
    printf("declare i32 @printf(i8*, ...)\n\n");

    printf("define i32 @main() {\n");

    // First allocate all variables at the top
    for (int i = 0; i < size; i++) {
        if (program[i]->kind == STMT_LET) {
            printf("  %%%s = alloca i32\n", program[i]->let_stmt.name);
        }
    }

    // Then generate statements (without alloca)
    for (int i = 0; i < size; i++) {
        if (program[i]->kind == STMT_LET) {
            int val_reg = gen_expr(program[i]->let_stmt.value);
            printf("  store i32 %%t%d, i32* %%%s\n", val_reg, program[i]->let_stmt.name);
        } else if (program[i]->kind == STMT_PRINT) {
            int val_reg = gen_expr(program[i]->print_stmt.value);
            printf("  %%t%d = call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %%t%d)\n", temp_count++, val_reg);
        }
    }

    printf("  ret i32 0\n");
    printf("}\n");
}

