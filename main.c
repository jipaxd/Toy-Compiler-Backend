#include <stdio.h>
#include "ast.h"

// let x = 5;
// let y = x + 3;
// print(y);
// let z = x * 2;

Expr five = { .kind = EXPR_CONST, .const_value = 5 };
Stmt let_x = { .kind = STMT_LET, .let_stmt = { "x", &five } };

Expr x_var = { .kind = EXPR_VAR, .var_name = "x" };
Expr three = { .kind = EXPR_CONST, .const_value = 3 };
Expr x_plus_3 = { .kind = EXPR_ADD, .add = { &x_var, &three } };
Stmt let_y = { .kind = STMT_LET, .let_stmt = { "y", &x_plus_3 } };

Expr y_var = { .kind = EXPR_VAR, .var_name = "y" };
Stmt print_y = { .kind = STMT_PRINT, .print_stmt = { &y_var } };

Expr two = { .kind = EXPR_CONST, .const_value = 2 };
Expr z_mul = { .kind = EXPR_MUL, .mul = { &x_var, &two } };
Stmt let_z = { .kind = STMT_LET, .let_stmt = { "z", &z_mul } };

Expr z_var = { .kind = EXPR_VAR, .var_name = "z" };
Stmt print_z = { .kind = STMT_PRINT, .print_stmt = { &z_var } };

Stmt* program[] = { &let_x, &let_y, &print_y, &let_z, &print_z };
int program_size = sizeof(program) / sizeof(program[0]);

void generate_code(Stmt* program[], int size);

int main() {
    generate_code(program, program_size);
    return 0;
}
