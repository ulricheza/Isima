
#ifndef VISITOREXPRSQUELETTE2_H
#define VISITOREXPRSQUELETTE2_H
#include "VisitorExpr.hpp"
#include "Expr.hpp"
#include "Def.hpp"
#include <stdio.h>
extern char * tab_symb[];
class VisitorExprCalc :  public VisitorExpr{

  public :
    VisitorExprCalc() {v = 0;}
   //une methode par dérivation de Expr 
    virtual void VisitExprI(ExprI *inExpr) ;
    virtual void VisitExprN(ExprN *inExpr) ;
    virtual void VisitExprBop(ExprBop *inExpr) ;
    virtual void VisitExprAff(ExprAff *inExpr) ;
  protected :
    int v;
};
#endif
// fin du fichier VisitorExprSquelette.hpp
