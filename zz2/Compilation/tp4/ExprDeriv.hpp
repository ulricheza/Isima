
#ifndef EXPRDERIV_H
#define EXPRDERIV_H
#include "Bop.hpp"


//classe pour le cas identificateur
class ExprI :  public Expr{
 public :
   int _i;
  // constructeur
  ExprI(int inLineno, int inI){
    _lineno = inLineno;
    _i = inI;
  }
  // destructeur
  virtual ~ExprI(){};
  // methode qui accepte le visiteur
  virtual void Accepter(VisitorExpr * inV);
};
//classe pour le cas entier
class ExprN :  public Expr{
public :
	int _n;
	// constructeur
	ExprN(int inLineno, int inN){
		_lineno = inLineno;
		_n = inN;
	}
	// destructeur
    virtual ~ExprN(){};
	// methode qui accepte le visiteur
	virtual void Accepter(VisitorExpr *inV);
};

//classe pour le cas Bop
class ExprBop :  public Expr{
 public :
  Expr * _e0;
  enum Bop  _bop;
  Expr * _e1;
  int _val;
  // constructeur
  ExprBop(int inLineno, Expr * inE0,  enum Bop inBop, Expr * inE1)
  {
    _lineno =  inLineno;
    _e0 =  inE0;
    _bop =  inBop;
    _e1 =  inE1;
  };
  // destructeur
    virtual ~ExprBop(){};
  // methode qui accepte le visiteur
	virtual void Accepter(VisitorExpr * inV);
};

// classe pour affectation
class ExprAff : public Expr {
  public:
    Expr * _e0;
    Expr * _e1; 
    int _ident;
    ExprAff(int inlineno,int ident ,Expr * ine0, Expr * ine1)
    {
      _lineno = inlineno;
      _ident = ident;
      _e0 = ine0;
      _e1 = ine1;
    }
    virtual ~ExprAff(){};
    
    virtual void Accepter(VisitorExpr * inV);
    
  
  
};


#endif
// fin du fichier ExprDeriv.hpp
