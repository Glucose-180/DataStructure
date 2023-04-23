#ifndef __EXPR_H__
#define __EXPR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define STKMAX 20
#define BUFMAX 100

enum OpType { CHAR,DOUBLE };

typedef struct op_t {
	enum OpType type;
	union {
		char c_val;
		double d_val;
	} data;
	int len;
} op_t;

double expr_calc(const char *expr);
op_t get_op(const char *expr);
int operand_push(const double X);
double operand_pop(void);
char operator_gettop(void);
int operator_push(const char C);
char operator_pop(void);
char priority(const char C, const char D);
int operator_get_index(const char C);


#endif
