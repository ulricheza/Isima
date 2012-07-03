/* 
 * File:   main.c
 * Author: Maxime
 *
 * Created on 14 février 2012, 15:55
 */

#include <stdio.h>
#include <stdlib.h>

#include "pilegenerique.h"

DEFINE_STACK(int);

/*
 * 
 */

int main(int argc, char** argv) {
    
    stack_int pile;
    
    init_int(&pile);
    
    push_int(&pile,12);
    push_int(&pile,24);
    
    if(empty_int(&pile) == 0)
    {
        printf("Top : %d \n",top_int(&pile));
        pop_int(&pile);
        printf("Top : %d \n",top_int(&pile));
    }
    return (EXIT_SUCCESS);
}

