
#ifndef EXPR_H
#define EXPR_H
#include "VisitorExpr.hpp"
class Expr{
 public :
  int _lineno; // numéro de ligne
	Expr(){};
	virtual ~Expr(){};
  // methode qui accepte le visiteur
  virtual void Accepter(VisitorExpr *inV) = 0;
};

#include "ExprDeriv.hpp"
#endif
// fin du fichier Expr.hpp
