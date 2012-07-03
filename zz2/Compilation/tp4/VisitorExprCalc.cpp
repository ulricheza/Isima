
#include "VisitorExprCalc.hpp"

void VisitorExprCalc::VisitExprI(ExprI *inExpr) {
	v = inExpr->_i;
}

void VisitorExprCalc::VisitExprN(ExprN *inExpr) {
  v = inExpr->_n;
}

void VisitorExprCalc::VisitExprBop(ExprBop *inExpr) {
  
  inExpr->_e0->Accepter(this);
  int v0 = inExpr->_val;
  inExpr->_e1->Accepter(this);
  int v1 = inExpr->_val;
  
  
  
  switch (inExpr-> _bop){
    case plus : 
      v = v0 + v1;
      break;		
    case minus : 
      v = v0 - v1;
      break;		
    case mult : 
      v = v0 * v1;
      break;		
    case divi : 
      v = v0 / v1;
      break;
      	
  }
}


void VisitorExprCalc::VisitExprAff(ExprAff *inExpr) {
  /*IL FAUT CalcR NOTRE LET*/
//   printf ("[identificateur %s(%d)]\n", tab_symb[inExpr->_ident], inExpr->_ident);
//   printf(" vaut maintenant ");
  inExpr->_e0->Accepter(this);
  PushDef(inExpr->_ident,v);
//   printf(" dans ");
  inExpr->_e1->Accepter(this);
  PopDef(inExpr->_ident,inExpr->_lineno);
  
  
  
}




// fin du fichier VisitorExprSquelette.cpp
