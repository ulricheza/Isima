#ifndef CLASSE_H
#define CLASSE_H

class Classe
{
public:
    Classe();
    Classe(int min, int max, int valeur);

    bool operator== ( Classe & classe){
        return ( _min == classe._min);
    }

    int getMin()          { return _min; }
	int getMin() const    { return _min; }
    int getMax()          { return _max; }
	int getMax() const    { return _max; }
    int getValeur()       { return _valeur;}
	int getValeur() const { return _valeur;}

    void setMin(int min)       { _min = min; }
    void setMax(int max)       { _max = max; }
    void setValeur(int valeur) { _valeur = valeur; }

private:
    int _min;
    int _max;
    int _valeur;
};

#endif // CLASSE_H
