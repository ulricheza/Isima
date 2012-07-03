
#ifndef VISITOREXPRSQUELETTE_H
#define VISITOREXPRSQUELETTE_H
#include ``VisitorExpr.hpp''

class VisitorExprSquelette :  public VisitorExpr{

 public :
   //une methode par dérivation de Expr 
  virtual void VisitExpr_n(Expr_n *inExpr) {}
  virtual void VisitExpr_bop(Expr_bop *inExpr) {}
};
#endif
// fin du fichier VisitorExprSquelette.hpp
