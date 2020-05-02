#include <stdlib.h>
#include <stdio.h>
#include<string.h>


typedef 
	struct {
		char * buffer ; // capacity X unit
		int unit ; // size of an element
		int capacity ;
		int top ;
	} 
	stack_t ;



stack_t * 
create_stack (int capacity, int unit) 
{
	stack_t * stack = (stack_t *) malloc(sizeof(stack_t)) ;
	stack->capacity = capacity ;
	stack->unit = unit ;
	stack->top = 0 ;

	stack->buffer = (char *) calloc(capacity, unit) ;
	
	return stack ;
}


void
delete_stack (stack_t * stack) 
{
	free(stack->buffer) ;
	free(stack) ;
}

int 
is_empty (stack_t * stack) 
{
	return (stack->top == 0) ;
}

int 
is_full (stack_t * stack) 
{
	return (stack->top == stack->capacity) ;
}

int 
push (stack_t * stack, void * elem)
{
	if (is_full(stack))
		return 1 ;
	
	memcpy((void *) stack->buffer + stack->top * stack->unit, elem, stack->unit) ;
	stack->top += 1 ;
	return 0 ;
}

int
pop (stack_t * stack, void * elem)
{
	if (is_empty(stack)) 
		return 1 ;
	
	memcpy(elem, stack->buffer + (stack->top - 1) * stack->unit, stack->unit) ;
	stack->top -= 1 ;
	return 0;
}


int
get_size (stack_t * stack) 
{
	return stack->top ;
}

int
get_element (stack_t * stack, int index, void * elem)
{
	if (stack->top <= index)
		return 1 ;

	memcpy(elem, stack->buffer + index * stack->unit, stack->unit) ;
	return 0 ;
}


int main (void){
    char array[100];
    stack_t * st1 = create_stack(50, sizeof(char));
    stack_t * st2 = create_stack(50, sizeof(char));
    int count1=0;
    int count2 = 0;
    int level[100];

    for(int i = 0; i<100;i++){
        scanf("%c",&array[i]);
        if(array[i]=='\n') break;
    }

    for(int i = 0 ; i < 100; i++){

        if(array[i]=='('||array[i]=='<'||array[i]=='{'||array[i]=='['){
            push(st1,&array[i]);
            count1++;
            count2++;
            level[i]=count2;
        }

        if(array[i]==')'||array[i]=='>'||array[i]=='}'||array[i]==']'){
                push(st2,&array[i]);
            char compare, remove;
            get_element(st1,get_size(st1)-1,&compare);
            printf("%c",compare);
            if(array[i]-compare<=2&&array[i]-compare>0){//ASCII코드 사용
                pop(st1,&remove);
                count2--;
                level[i]= count2;
            }
        }
    }
   // printf("%d %d\n",count1,get_size(st2));
    int most = level[0];
    for(int i = 0 ; i<100;i++){
        if(level[i+1]>50||level[i+1]<0)break;
        //if(most<level[i+1])most = level[i+1];
       //printf("%d\n",level[i]);
    }


    if(is_empty(st1)&&count1==get_size(st2)) printf("%d",most);
    else printf("invalid");

}