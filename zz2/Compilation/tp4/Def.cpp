
#include <stdio.h>
#include <stdlib.h>
extern char* tab_symb[];
class Def {
public :
	int _val;
	Def * _next;
	Def(int InVal){
		_val = InVal;
		_next = NULL;
	}
};

Def * alpha[1000];

void init_alpha(){
	for (int i = 0; i < 1000; i++) alpha[i]=NULL;
}

void PushDef(int InIdent, int InVal){
	Def * d = new Def(InVal);
	d->_next = alpha[InIdent];
	alpha[InIdent] = d;
}

void PopDef(int InIdent, int InLine){
	if (alpha[InIdent] != NULL){
		alpha[InIdent] = alpha[InIdent]->_next;
	}else{
		fprintf(stdout, "ERREUR POP ligne %d sur Identificateur %s\n", InLine,tab_symb[InIdent]);	
		exit (1);
	}
}

void ChangeDef(int InIdent, int InVal){
 	if (alpha[InIdent] != NULL) alpha[InIdent]->_val = InVal;
	else PushDef(InIdent, InVal);
}

int GetVal(int InIdent, int InLine){
	if (alpha[InIdent] != NULL){
		return alpha[InIdent]->_val;
	}else{
	  	fprintf(stdout, "ERREUR GetVAl ligne %d sur Identificateur %s\n", InLine,tab_symb[InIdent]);
		exit (1);
	}
	
}

