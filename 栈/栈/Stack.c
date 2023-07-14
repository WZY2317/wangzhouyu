#include"Stack.h"
void StackInit(ST* st)
{
	st->top = -1;
}
void StackDestory(ST* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->capacity = 0;
	ps->top = 0;
}
bool IsEmpty(ST* st)
{
	return st->top == -1;
}
bool push(ST* st, ElemType val)
{
	if (st->top == st->capacity)
	{
		int newCapacity = st->capacity == 0 ? 4 : st->capacity;
		st->a = (ElemType*)realloc(st->a, newCapacity*sizeof(ElemType));
		if (!st->a)
		{
			return false;
		}
	}
	else
	{
		st->a[st->top] = val;
		st->top++;
		return true;
	}
		
}
bool pop(ST* ps)
{
	if (ps->top == 0)
		return false;
	else
		ps->top--;
}
ElemType GetTop(ST* ps)
{
	if (ps->top == 0)
		return false;
	else
		return ps->a[ps->top];
}

