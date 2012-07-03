
#include "VisitorExprAffiche.hpp"

void VisitorExprAffiche::VisitExprI(ExprI *inExpr) {
	for (int i=0; i<indent; i++) printf("  ");
	printf ("[identificateur %s(%d)]\n", tab_symb[inExpr->_i], inExpr->_i);
}

void VisitorExprAffiche::VisitExprN(ExprN *inExpr) {
	for (int i=0; i<indent; i++) printf("  ");
	printf ("[entier %d]\n", inExpr->_n);
}

void VisitorExprAffiche::VisitExprBop(ExprBop *inExpr) {
	for (int i=0; i<indent; i++) printf("  ");
	printf("[");
	switch (inExpr-> _bop){
		case plus : 
			printf("operateur +\n");
			break;		
		case minus : 
			printf("operateur -\n");
			break;		
		case mult : 
			printf("operateur *\n");
			break;		
		case divi : 
			printf("operateur /\n");
			break;					
	}
	indent++;
	inExpr->_e0->Accepter(this);
	inExpr->_e1->Accepter(this);
	indent--;
	for (int i=0; i<indent; i++) printf("  ");
	printf("]\n");
}

void VisitorExprAffiche::VisitExprAff(ExprAff *inExpr) {
  /*IL FAUT AFFICHER NOTRE LET*/
  printf ("[identificateur %s(%d)]\n", tab_symb[inExpr->_ident], inExpr->_ident);
  printf(" vaut maintenant ");
  inExpr->_e0->Accepter(this);
  printf(" dans ");
  inExpr->_e1->Accepter(this);
  
  
  
}
// fin du fichier VisitorExprSquelette.cpp
