#include <stdlib.h>
#include <stdio.h>
#include "array_helpers.h"
#include "../stack.h"

int main(void){
    stack p = stack_empty();
    
    stack_elem e = 3;
    p = stack_push(p, e);
    printf("First top element: %d \n", stack_top(p));
    
    p = stack_pop(p);
    printf("Empty? = %d \n", (p == NULL));
    
    p = stack_push(p, 6);
    printf("New top element: %d \n", stack_top(p));
    
    p = stack_push(p, 7);
    p = stack_push(p, 8);      
    p = stack_push(p, 9);
    p = stack_push(p, 10);
    int *a=NULL;
    a = stack_to_array(p);
    array_dump(a, 5);
    
    return 0;    
}