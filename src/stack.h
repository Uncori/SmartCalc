#ifndef SRC_STACK_H_
#define SRC_STACK_H_
// stack char
typedef struct stack_char {
    char simbol;
    struct stack_char *next;
} st_c;

st_c *push_char(st_c *ptr, char ham);
char pop_char(st_c **stack);

// stack double
typedef struct stack_double {
    double number;
    struct stack_double *next;
} st_d;

st_d *push_double(st_d *ptr, double ham);
double pop_double(st_d **stack);
#endif // SRC_STACK_H_
