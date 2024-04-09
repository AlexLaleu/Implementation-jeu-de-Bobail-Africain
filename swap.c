#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "swap.h"

void swap(int* p_a, int* p_b){
    int temp = *p_a;
    *p_a = *p_b;
    *p_b=temp;
}