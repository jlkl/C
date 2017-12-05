/*
*
*	Name:顺序栈_十进制数转换 
*	Author:Str3am
*	Version:1.0
*	Time:2017/12/4
*
*/

#include <stdio.h>
#include <stdlib.h>//malloc 函数 
#include <malloc.h>

#define PARAM_ERROR -1
#define MALLOC_ERROR -2
#define REALLOC_ERROR -3
#define STACK_INIT_SIZE 100//栈初始化大小 
#define STACK_INCREASE_SIZE 10 
//以单个int值为结点的顺序栈 
typedef struct seqstack
{
	int *base;//栈底元素
	int *top;//栈顶元素的下一个 
	int stacksize;//当前栈能存储的元素的最大个数；	
}seqstack;

//initialise stack
int InitStack(seqstack **ppstack)
{
	if(ppstack == NULL)
		return PARAM_ERROR;
	*ppstack = (seqstack *)malloc(sizeof(seqstack)); 
	if(*ppstack == NULL)
		return MALLOC_ERROR;
	(*ppstack)->base = (int *)malloc(sizeof(int)*STACK_INIT_SIZE);
	if((*ppstack)->base == NULL)
		return MALLOC_ERROR;
	(*ppstack)->top = (*ppstack)->base;
	(*ppstack)->stacksize = STACK_INIT_SIZE;
	return 0;
}

//进栈 
int Push(seqstack *pstack,int value)
{
	if(pstack == NULL || value < 0 || value > 15)
		return PARAM_ERROR;
	/*if(pstack->top-pstack->base >= pstack->stacksize)
	{
		pstack->base = (seqstack *)realloc(pstack->base,(pstack->stacksize+STACK_INCREASE_SIZE)*sizeof(int));
		if(pstack->base == NULL)
			return REALLOC_ERROR;
		pstack->top = pstack->base+pstack->stacksize;
		pstack->stacksize += STACK_INCREASE_SIZE;
	}*/
	*(pstack->top) = value;
	pstack->top++;
	return 0; 
}
 
//出栈 
int Pop(seqstack *pstack,int *value)
{
	if(pstack == NULL || value == NULL)
		return PARAM_ERROR;
	if(pstack->base == pstack->top)
		return PARAM_ERROR;
	pstack->top--;
	*value = *pstack->top;
	return 0; 
}

//摧毁栈 
int Destory(seqstack **pstack) 
{
	if(*pstack == NULL)
		return PARAM_ERROR;
	free((*pstack)->base);
	(*pstack)->base = NULL;
	free(*pstack);
	*pstack = NULL;
	return 0;
}


int main()
{
	int x,n,xtemp,*temp;//x存储要转换的数，n存储转换的进制数 ,xtemp存储x的值，temp存储转换出的每一位 
	temp = (int *)malloc(sizeof(int));
	seqstack *pstack;//以地址方式控制栈，使控制力更强
	InitStack(&pstack);
	printf("请输入要转换的十进制数:");
	scanf("%d",&x);
	printf("请输入要转换的进制n(2,8,16)：");
	scanf("%d",&n);
	xtemp = x;
	printf("%d转换成%d进制数的结果为:",x,n);
	while(xtemp != 0)
	{
		Push(pstack,xtemp%n);
		xtemp /= n;
	} 
	while(pstack->top != pstack->base)
	{
		Pop(pstack,temp);
		if(*temp > 9)
		{
			*temp = *temp%10;
			printf("%c",'A'+*temp);
		}
		else
		{
			printf("%d",*temp);
		}
	}
	Destory(&pstack);
	return 0;
}
