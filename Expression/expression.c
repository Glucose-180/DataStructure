#include "expression.h"

double operand[STKMAX];
char operator[STKMAX];
const char End = '\0';
char buffer[BUFMAX];

int operand_pt = 0, operator_pt = 0;

int main(int argc, char *argv[])
{
	double rt;

	while (--argc)
	{
		strcat(buffer, *++argv);
	}
	rt = expr_calc(buffer);
	if (rt != NAN)
	{
		printf("%g\n", rt);
		return 0;
	}
	else
	{
		fprintf(stderr, "*Error\n");
		return 1;
	}
}

double expr_calc(const char *expr)
{
	op_t op;
	char c;
	double op_a, op_b;

	op = get_op(expr);
	expr += op.len;
	while (!(op.type == CHAR && op.data.c_val == End) || operator_gettop() != End)
	{
		if (op.type == DOUBLE)
		{
			operand_push(op.data.d_val);
			op = get_op(expr);
			expr += op.len;
		}
		else
		{
			switch (priority(operator_gettop(), op.data.c_val))
			{
			case '<':
				operator_push(op.data.c_val);
				op = get_op(expr);
				expr += op.len;
				break;
			case '=':
				if (operator_pop() != '(')
					return NAN;
				op = get_op(expr);
				expr += op.len;
				break;
			case '>':
				op_b = operand_pop();
				op_a = operand_pop();
				switch (operator_pop())
				{
				case '+':
					op_a += op_b;
					break;
				case '-':
					op_a -= op_b;
					break;
				case '/':
					op_a /= op_b;
					break;
				case '*':
					op_a *= op_b;
					break;
				default:
					return NAN;
					break;
				}
				operand_push(op_a);
				break;
			default:
				return NAN;
				break;
			}
		}
	}
	return operand_pop();
}

op_t get_op(const char *expr)
{
	const char *p = expr;
	op_t rt;

	while (isspace(*p))
		++p;
	if (*p == '.' || isdigit(*p))
	{
		rt.type = DOUBLE;
		rt.data.d_val = atof(p);
		while (*p == '.' || isdigit(*p))
			++p;
		rt.len = p - expr;
	}
	else
	{
		rt.type = CHAR;
		rt.data.c_val = *p;
		rt.len = 1;
	}
	return rt;
}

int operand_push(const double X)
{
	if (operand_pt < STKMAX)
		operand[operand_pt++] = X;
	else
		return -1;	/* stack overflow */
	return 0;
}

double operand_pop()
{
	if (operand_pt > 0)
		return operand[--operand_pt];
	else
		return NAN;	/* stack empty */
}

char operator_gettop()
{
	if (operator_pt > 0)
		return operator[operator_pt - 1];
	else
		return End;
}

int operator_push(const char C)
{
	if (operator_pt < STKMAX)
	{
		operator[operator_pt++] = C;
		return 0;
	}
	else
		return -1;
}

char operator_pop()
{
	if (operator_pt > 0)
		return operator[--operator_pt];
	else
		return End;
}

char priority(const char C, const char D)
{
	static const char Priority[][7] = {
		'>', '>', '<', '<', '<', '>', '>',
		'>', '>', '<', '<', '<', '>', '>',
		'>', '>', '>', '>', '<', '>', '>',
		'>', '>', '>', '>', '<', '>', '>',
		'<', '<', '<', '<', '<', '=', '*', /* * is error */
		'>', '>', '>', '>', '*', '>', '>',
		'<', '<', '<', '<', '<', '*', '='
	};
	return Priority[operator_get_index(C)][operator_get_index(D)];
}

int operator_get_index(const char C)
{
	switch (C)
	{
	case '+':
		return 0;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 3;
		break;
	case '(':
		return 4;
		break;
	case ')':
		return 5;
		break;
	default:
		return 6;
		break;
	}
}
