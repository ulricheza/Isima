#ifndef VALEUR_H
#define VALEUR_H

class Valeur
{

public:
    //Constructeur
    Valeur();
    Valeur(int valeur);

    //Getters et setters
    int getValeur()            { return _valeur; }
    void setValeur(int valeur) { _valeur = valeur; }

private:
    int _valeur;
};

#endif // VALEUR_H
