
#include "Expr.hpp"

void ExprI::Accepter(VisitorExpr *inV){
	inV -> VisitExprI(this); 
}

void ExprN::Accepter(VisitorExpr *inV){
  inV -> VisitExprN(this); 
}

void ExprBop::Accepter(VisitorExpr *inV){
  inV -> VisitExprBop(this); 
}

void ExprAff::Accepter(VisitorExpr *inV){
  inV -> VisitExprAff(this); 
}


// fin du fichier ExprDeriv.cpp
