

template <typename T>
Nuage<T>::Nuage() {
}

template <typename T>
Nuage<T>::~Nuage() {
}

template <typename T>
T Nuage<T>::calculBarycentre()
{
    Cartesien resultat;
    double x = 0.;
    double y = 0.;
    double xtemp,ytemp;

    iterator it; //iterator est defini dans un typedef dans le header

    for(it = _nuage.begin(); it != _nuage.end() ; ++it)
    {
        (*it).bary(xtemp,ytemp);
        x += xtemp;
        y += ytemp;
    }

    resultat.setX(x / (double)_nuage.size());
    resultat.setY(y / (double)_nuage.size());

    T res = resultat;
    return res;
}
