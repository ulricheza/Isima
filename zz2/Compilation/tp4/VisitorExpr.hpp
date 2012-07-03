
#ifndef VISITOREXPR_H
#define VISITOREXPR_H
#include "Classes.hpp"

class VisitorExpr{
  protected:
        VisitorExpr()  {}
	virtual ~VisitorExpr(){};

 public :
   //une methode par dérivation de Expr 
	virtual void VisitExprI(ExprI *inExpr) = 0;
	virtual void VisitExprN(ExprN *inExpr) = 0;
  virtual void VisitExprBop(ExprBop *inExpr) = 0;
  virtual void VisitExprAff(ExprAff *inExpr) = 0;
};
#endif
// fin du fichier VisitorExpr.hpp
