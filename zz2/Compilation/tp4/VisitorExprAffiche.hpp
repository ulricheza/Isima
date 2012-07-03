
#ifndef VISITOREXPRSQUELETTE_H
#define VISITOREXPRSQUELETTE_H
#include "VisitorExpr.hpp"
#include "Expr.hpp"
#include <stdio.h>
extern char * tab_symb[];
class VisitorExprAffiche :  public VisitorExpr{

 public :
	VisitorExprAffiche() {indent = 0;}
   //une methode par dérivation de Expr 
	virtual void VisitExprI(ExprI *inExpr) ;
	virtual void VisitExprN(ExprN *inExpr) ;
  virtual void VisitExprBop(ExprBop *inExpr) ;
  virtual void VisitExprAff(ExprAff *inExpr) ;
protected :
		unsigned int indent;
};
#endif
// fin du fichier VisitorExprSquelette.hpp
