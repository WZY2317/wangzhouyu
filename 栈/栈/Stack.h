#define MAXSIZE 50
#include<stdbool.h>
#include<stdlib.h>
typedef int ElemType ;
typedef struct Stack
{
	ElemType* a;
	int top;		// ջ����λ��
	int capacity;	// ����
}ST;
void StackInit(ST* st);
void StackDestory(ST* ps);
bool IsEmpty(ST* st);
bool push(ST* st, ElemType val);
bool pop(ST* ps);
ElemType GetTop(ST* ps);

