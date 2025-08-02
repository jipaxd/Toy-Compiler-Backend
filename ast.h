typedef struct Expr Expr;

struct Expr {
    enum { EXPR_CONST, EXPR_VAR, EXPR_ADD, EXPR_MUL } kind;
    union {
        int const_value;     // For EXPR_CONST
        char* var_name;      // For EXPR_VAR
        struct { Expr* left; Expr* right; } add;  // For EXPR_ADD
        struct { Expr* left; Expr* right; } mul;  // For EXPR_MUL
    };
};

typedef struct Stmt Stmt;

struct Stmt {
    enum { STMT_LET, STMT_PRINT } kind;
    union {
        struct { char* name; Expr* value; } let_stmt; // let x = expr;
        struct { Expr* value; } print_stmt;           // print(expr);
    };
};
