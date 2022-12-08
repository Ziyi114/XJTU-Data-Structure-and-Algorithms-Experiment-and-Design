#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<math.h>


#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0



typedef struct {
	char* base;
	char* top;
	int stacksize;
}StackCh;//定义运算符栈StackCh

typedef struct {
	double* base;
	double* top;
	int stacksize;
}StackNum;//定义数据类型数栈


int InitStackCh(StackCh& S) {
	S.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!S.base)exit(OVERFLOW);//如果存储分配失败，返回错误
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}//构造一个运算符空栈

int InitStackNum(StackNum& S) {
	S.base = (double*)malloc(STACK_INIT_SIZE * sizeof(double));
	if (!S.base)exit(OVERFLOW);//如果存储分配失败，返回错误
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}//构造一个空操作数栈


double GetTopNum(StackNum S) {
	
	double e;
	e = *(S.top - 1);
	return e;
}//用e返回栈顶元素


char GetTopCh(StackCh S) {
	char e;
	e = *(S.top - 1);
	return e;
}//用e返回S的栈顶元素

int PushNum(StackNum& S, double e) {
	if (S.top - S.base >= S.stacksize) {//若栈满，则追加存储空间
		S.base = (double*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(double));
		if (!S.base) exit(OVERFLOW);//存储分配失败
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return OK;
}//入栈

int PushCh(StackCh& S, char e) {
	if (S.top - S.base >= S.stacksize) {
		S.base = (char*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(char));
		if (!S.base) exit(OVERFLOW);//如果存储分配失败，返回
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}//若栈满，重新分配存储空间
	*S.top = e;
	S.top++;
	return OK;
}//插入新的字符元素

int PopNum(StackNum& S, double& e) {
	if (S.top == S.base) return ERROR;
	S.top--;
	e = *S.top;
	return OK;
}//删除数栈顶元素

int PopCh(StackCh& S, char& e) {
	if (S.top == S.base) return ERROR;
	S.top--;
	e = *S.top;
	return OK;
}//删除字符栈顶元素

//以上为栈的基本操作定义


bool ischar(char c) {
	//判断c是否为算符,是则为真，不是则为假
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'
		|| c == '#' || c == '[' || c == ']' || c == '^' || c == '{' || c == '}')
		return true;
	else return false;
}//用bool类型来判断字符是否为运算字符

char compare(char a, char b) {
	int i, j;
	char m[12] = { '+','-','*','/','(',')','#','[',']','^','{','}' };
	char n[12][12] = {
	{'>','>','<','<','<','>','>','<','>','<','<','>'},
	{'>','>','<','<','<','>','>','<','>','<','<','>'},
	{'>','>','>','>','<','>','>','<','>','<','<','>'},
	{'>','>','>','>','<','>','>','<','>','<','<','>'},
	{'<','<','<','<','<','=',' ',' ',' ','<',' ',' '},
	{'>','>','>','>',' ','>','>',' ','>','>',' ','>'},
	{'<','<','<','<','<',' ','=','<',' ','<','<',' '},
	{'<','<','<','<','<',' ',' ','<','=','<',' ',' '},
	{'>','>','>','>',' ',' ','>',' ','>','>',' ','>'},
	{'>','>','>','>','<','>','>','<','>','>','<','>'},
	{'<','<','<','<','<',' ',' ','<',' ','<','<','='},
	{'>','>','>','>',' ',' ','>',' ',' ','>',' ','>'},
	};
	for (i = 0; i < 12; i++) {
		if (a == m[i]) break;
	}
	for (j = 0; j < 12; j++) {
		if (b == m[j]) break;
	}
	return n[i][j];
}//用以判断运算符优先级


double Operate(double a, char b, double c) {
	switch (b) {
	case'+':return(a + c); break;
	case'-':return(a - c); break;
	case'*':return(a * c); break;
	case'/':return(a / c); break;
	case'^':return(pow(a, c)); break;
	}
	return 0;
}//计算函数





int EvaluateExpression(char m[100]) {
	//算术表达式求值的算符优先算法，设OPTR和OPND分别为运算符栈和操作数栈
	int ml = strlen(m);
	m[ml] = '#';//将表达式加后缀#
	int i;
	char c, op, x, d[100];//用于存储连续的数字字符再转化为浮点数
	double num, re, b, a;
	StackCh OPTR;
	InitStackCh(OPTR);//用于寄存运算符的栈OPTR
	StackNum OPND;
	InitStackNum(OPND);//用于寄存操作数和运算结果的栈OPND
	PushCh(OPTR, '#');//将'#'号作为运算符栈的栈顶
	int j = 0;
	c = m[j];
	if (c == '+' || c == '-' || c == 'x' || c == '/' || c == '^') {
		printf("ERROR_02");
		return 0;
	}//如果第一个字符即为运算符，则错误
	while (c != '#' || GetTopCh(OPTR) != '#') {
		if ((c >= '0' && c <= '9') || c == '.') {
			i = 0;
			do {
				d[i] = c;
				i++;
				j++;
				c = m[j];
			} while ((c >= '0' && c <= '9') || c == '.');
			d[i] = '\0';
			num = atof(d);//将字符串转化为浮点数
			PushNum(OPND, num);
		}
		else if (ischar(c)) {
			switch (compare(GetTopCh(OPTR), c)) {
			case'<':
				PushCh(OPTR, c); j++; c = m[j];
				if (c == *(OPTR.top - 1)) {
					printf("ERROR_02");
					return 0;
				}//如果两个运算符连续出现则错误
				break;//栈顶元素优先权低,则继续将运算符压入运算符栈
			case'=':
				PopCh(OPTR, x); j++; c = m[j];
				break;//遇到括号对应则将两个括号释放
			case'>':
				PopCh(OPTR, op);
				PopNum(OPND, b);
				PopNum(OPND, a);//b先出栈,a后出栈
				re = Operate(a, op, b);
				if (op == '/' && b == 0) {
					printf("ERROR_03");
					return 0;
				}
				PushNum(OPND, re);//计算并压入栈
				break;
			case' ':
				printf("ERROR_02");//出现语法错误
				return 0;
			}
		}
		else {
			printf("ERROR_02");
			return 0;
		}
	}
	PopNum(OPND, re);
	printf("%g", re);//%g保证不输出无意义的0
	return 0;
}
int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		printf("ERROR_01");
		return 0;
	}
	EvaluateExpression(argv[1]);
	return 0;
}