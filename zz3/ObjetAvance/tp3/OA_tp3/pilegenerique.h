/* 
 * File:   pilegenerique.h
 * Author: Maxime
 *
 * Created on 14 février 2012, 16:10
 */

#ifndef PILEGENERIQUE_H
#define	PILEGENERIQUE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define TAILLE_MAX 20 

#define DEFINE_STACK(TYPE) \
typedef struct stack_##TYPE_t { \
   TYPE tableau[TAILLE_MAX]; \
   int rang; \
}stack_##TYPE; \
\
void push_##TYPE(stack_##TYPE * stack, TYPE element) { \
   if (stack->rang < TAILLE_MAX)\
   {\
      (stack->rang)++; /*maj du rang*/\
      stack->tableau[stack->rang] = element; /*affectation valeur*/\
   }\
}\
\
TYPE top_##TYPE(stack_##TYPE * stack) {\
    return stack->tableau[stack->rang]; \
}\
\
void pop_##TYPE(stack_##TYPE * stack) {\
    (stack->rang)--; /*maj du rang*/\
}\
\
int empty_##TYPE(stack_##TYPE * stack) { \
   return ( (stack->rang < 0)? 1:0 ); \
}\
\
unsigned int size_##TYPE(stack_##TYPE * stack) { \
   return ( stack->rang + 1);\
}\
\
void init_##TYPE(stack_##TYPE * stack) { \
   stack->rang = -1;\
}
    
#ifdef	__cplusplus
}
#endif

#endif	/* PILEGENERIQUE_H */

