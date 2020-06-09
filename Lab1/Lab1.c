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



int
main () 
{	
	int rail, station;
	scanf("%d %d",&rail,&station);
	stack_t * st1 = create_stack(rail, sizeof(int)) ;
	stack_t * st2 = create_stack(station,sizeof(int));
	stack_t * st3 = create_stack(rail,sizeof(int));
	int array[rail];
	for(int i = 0; i<rail; i++){
		scanf("%d",&array[i]);
	}

	int value = rail;
	for(int i = 0; i< rail;value--,i++){
		push(st1,&value);
	}

	int compare;
	for(int i = 0; i< rail; ){
	get_element(st1,get_size(st1)-1,&compare);
	if(compare == array[i]){
		pop(st1,&compare);
		push(st3,&compare);
		i++;
	}
	else if(compare != array[i]){
		get_element(st2,get_size(st2)-1,&compare);
		if(compare == array[i]){
			pop(st2,&compare);
			push(st3,&compare);
			i++;
		}
		else{
			if(is_full(st2)){
				break;
				}
			else {
				pop(st1,&compare);
				push(st2,&compare);
			}
		}
	}
	if(get_element(st1,get_size(st1)-1,&compare)) break;
	}

	int result;

	for(int i = 0; i< station ; i++){
		if(array[i] != *(st3->buffer+i*4)){result = -1;break;}
		result = 1;
		}

		if(result == 1) printf("true");
		else printf("false");
	

}