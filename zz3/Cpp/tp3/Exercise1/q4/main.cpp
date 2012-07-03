#include <QtCore/QCoreApplication>
#include <iostream>

#include "compteur.hpp"
#include "groupeCompteur.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    GroupeCompteur groupe;
    Compteur c1(8); 
    Compteur c2(0);
    Compteur c3(4);

    groupe.addCompteur(&c1);
    groupe.addCompteur(&c2);

    groupe.setCompteur( 15 );
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "c1 : " << c1.getValeur() << std::endl;
    std::cout << "c2 : " << c2.getValeur() << std::endl;
    std::cout << "c3 : " << c3.getValeur() << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    groupe.addCompteur(&c3);
    groupe.setCompteur( 25);
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "c1 : " << c1.getValeur() << std::endl;
    std::cout << "c2 : " << c2.getValeur() << std::endl;
    std::cout << "c3 : " << c3.getValeur() << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    groupe.removeCompteur(&c1);
    groupe.setCompteur( 45 );
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "c1 : " << c1.getValeur() << std::endl;
    std::cout << "c2 : " << c2.getValeur() << std::endl;
    std::cout << "c3 : " << c3.getValeur() << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}
