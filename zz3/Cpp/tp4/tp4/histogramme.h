#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include <set>
#include "comparateurless.h"
#include "echantillon.h"

using std::set;
class Histogramme
{
public:
    Histogramme();

    void addClasse(Classe classe) { _classes.insert(classe); }
    void constructionEchantillion( const Echantillon & echantillon );

protected:
    set<Classe,comparateurLess> _classes;
};

#endif // HISTOGRAMME_H
