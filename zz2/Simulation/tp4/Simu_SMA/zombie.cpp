/**
 * \file zombie.cpp
 * \brief fichier d'implementation de la classe Zombie
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 26 Janvier 2011
 * \version 1.0
 *
 */

#include <iostream>

#include "zombie.h"
#include "graphic.h"
#include "simulator.h"

/*
 * Choix des valeurs pour la simulation d'un zombie:
 * type = 0
 * Force: entre 8 et 18
 * Vitesse: entre 1 et 2 cases par tour
 * Perception olfactive Primaire entre 50% et 75%
 * Perception olfactive Secondaire entre  30% et 50%
 * Si le zombie tue un humain il y a 70% de chance que l'humain devienne zombie
 */

/**
 * \fn    Zombie::Zombie(int x,int y,Simulator * simu, World * world)
 * \brief constructeur de la classe Zombie
 * \param x     coordonnee de placement initial
 * \param y     coordonnee de placement initial
 * \param simu  pointeur vers l'instance de simulation
 * \param world pointeur sur le monde ou sera contenu l'agent
 */
Zombie::Zombie(int x,int y,Simulator * simu, World * world):Agent(x,y,simu,world)
{
    //initialisation des variables de force et de vitesse et de perception

    _force            = simu->GeneInt(8,18);
    _vitesse          = simu->GeneInt(1,2);
    _percept_olf_prim = simu->GeneInt(50,75);
    _percept_olf_sec  = simu->GeneInt(30,50);
    _type             = 0;

    //rajout au monde
    world->AjouterEntite(x,y,this);
}

/**
 * \fn void Zombie::Action()
 * \brief Cette fonction effectue les operations a effectuer suite a un deplacement
 * \return true si le zombie est toujours vivant
 *
 */

bool Zombie::Action()
{
    bool vivant = true;
    list<Entite *> ** map = _world->getMap();
    list<Entite *> * analyse = &map[_placement._x][_placement._y];
    list<Entite *>::iterator it = (*analyse).begin();

    cout << "Action d'un zombie..." << endl;
    while( (*it) != this && vivant ) //marche car on fait un push back lors du deplacement
    {
        switch((*it)->getType())
        {
            case 0: //zombie detecte
                //ils s'ignore
		++it;
                break;
            case 1: //humain detecte
                vivant = Attaquer((Agent*)(*it));
		it = (*analyse).begin();
                break;
            case 2: //arme detecte
                //vous avez vu un zombie intelligent ???
	        ++it;
                break;
            default :
                cerr << "Zombie:Action: Erreur recuperation type d entite " << endl;
                break;
        }
    }
    return vivant;
}

/**
 * \fn bool Zombie::Attaquer(Agent * Cible)
 * \brief Cette methode simule l'ataque d'un humain vers un zombie
 * \param Cible pointeur sur l'agent qui va etre attaque
 * \return true si l'attaquant est gagnant
 *
 *  Si l'humain meurt la probalite qu'in devienne un zombie est de 70%
 */

bool Zombie::Attaquer(Agent * cible)
{
    int multiplacateurAtt = _simu->GeneInt(8,12);
    int multiplacateurCib = _simu->GeneInt(8,12);
    bool resultat;

    cout << "Attaque d'un zombie sur un humain" << endl;
    if( multiplacateurAtt * _force < multiplacateurCib * cible->getForce() )
    {
        cout << "Zombie Perdant" << endl;
        //Zombie perdant
        cible->Tuer(this);
        resultat = false;
    }
    else
    {
        cout << "Zombie gagnant" << endl;
        this->Tuer(cible);
        if(_simu->GeneInt(0,100) < 70 ) //si le humain est infecte
        {
            cout << "Humain contamine" << endl;
            Contaminer();
        }
        resultat = true;
    }
    return resultat;
}

/**
 * \fn void Zombie::Tour()
 * \brief Cette methode effectue un tour de jeu d'un zombie
 *
 */

void Zombie::Tour()
{
    int i = 0;
    bool vivant = true;
    while(vivant && i++ < _vitesse)
    {
        cout << "--------------------------" << endl;
        cout << "zombie actif" << endl;
        PerceptionOlfactive();
        vivant = Action();
        _world->AfficWorld();
        Graphic::TransitionTour(); //si il y a un delay ou gestion par clic
    }
}

/**
 * \fn void Zombie::Contaminer()
 * \brief fonction qui creer un nouveau zombie a la place d'un humain tuer
 *
 */

void Zombie::Contaminer()
{
    Zombie * nouveau = new Zombie(_placement._x,_placement._y,_simu,_world);
    //le constructeur rajoute automatique le zombie au monde

    //on le rajoute au pool du simulateur
    _simu->AjoutAgent(nouveau);
}

/**
 * \fn void Zombie::PerceptionOlfactive()
 * \brief Effectue la perception du zombie
 *
 * Perception sur 360°
 */
void Zombie::PerceptionOlfactive()
{
    int case_restante,tirage;
    int i;
    int alea;
    int sens_deplacement;

    bool humain = false;
    
    Position tab_alea[24];
    Position temp;
    Position analyse;
    Position vierge_correction;
    Position humain_trouve;

    list<Entite*> ** map = _world->getMap();
    list<Entite*> * list_analyse;
    list<Entite*>::iterator it;

    cout << "Perception olfactive d'un zombie" << endl;
    //--------------------------
    //perception imediate
    //--------------------------
    cout << "Perception immediate" << endl;
    case_restante = 0;
    //bande au nord
    temp._y = _placement._y - 1;
    for(i=-1;i<=1;++i)
    {
        temp._x = _placement._x + i;
        tab_alea[case_restante++] = temp;
    }
    //bande au sud
    temp._y = _placement._y + 1;
    for(i=-1;i<=1;++i)
    {
        temp._x = _placement._x + i;
        tab_alea[case_restante++] = temp;
    }
    temp._y = _placement._y;
    //case ouest
    temp._x = _placement._x -1;
    tab_alea[case_restante++] = temp;
    //case est
    temp._x = _placement._x +1;
    tab_alea[case_restante++] = temp;

    //analyse des cases
    while(case_restante > 0 && !humain)
    {
       //on tire une case disponible
       tirage = _simu->GeneInt(0,case_restante - 1);
       analyse = tab_alea[tirage];
       vierge_correction = analyse;
       _world->ConvertisseurCase(analyse);
       tab_alea[tirage] = tab_alea[--case_restante];
       list_analyse = &map[analyse._x][analyse._y];
       it = (*list_analyse).begin();
       while(it != (*list_analyse).end())
       {
            switch((*it)->getType())
            {
                case 0: //zombie detecte

                    break;
                case 1: //humain detecte
                    cout << "Humain detecte" << endl;
                    humain_trouve = vierge_correction;
                    humain = true;
                    break;
                case 2: //arme detecte
                    break;
                default:
                    cerr << "Zombie: Perception: type d'entite non reconnu" << endl;
                    break;
            }
            ++it;
       }
    }

    if(!humain)
    {
        //---------------------------------
        //Analyse primaire
        //---------------------------------
        cout << "Perception Primaire" << endl;
        case_restante = 0;

        //cases au nord
        temp._y = _placement._y - 2;
        for(i = -2 ; i <= 2 ; ++i)
        {
            temp._x = _placement._x + i;
            tab_alea[case_restante++] = temp;
        }
        //case au sud
        temp._y = _placement._y + 2;
        for(i = -2 ; i <= 2 ; ++i)
        {
            temp._x = _placement._x + i;
            tab_alea[case_restante++] = temp;
        }
        // a l'ouest
        temp._x = _placement._x - 2;
        for(i = -1 ; i <= 1 ; ++i)
        {
            temp._y = _placement._y + i;
            tab_alea[case_restante++] = temp;
        }
        //a l'est
        temp._x = _placement._x + 2;
        for(i = -1 ; i <= 1 ; ++i)
        {
            temp._y = _placement._y + i;
            tab_alea[case_restante++] = temp;
        }

        //analyse des cases
        while(case_restante > 0 && !humain)
        {
            //on tire une case disponible
            tirage = _simu->GeneInt(0,case_restante - 1);
            analyse = tab_alea[tirage];
            vierge_correction = analyse;
            _world->ConvertisseurCase(analyse);
            tab_alea[tirage] = tab_alea[--case_restante];
            list_analyse = &map[analyse._x][analyse._y];
            it = (*list_analyse).begin();
            while(it != (*list_analyse).end())
            {
                alea = _simu->GeneInt(0,100);
                if(alea < _percept_olf_prim )
                {
                    switch((*it)->getType())
                    {
                        case 0: //zombie detecte
                            break;
                        case 1: //humain detecte
                            cout << "Humain detecte" << endl;
                            humain_trouve = vierge_correction;
                            humain = true;
                            break;
                        case 2: //arme detecte
                            break;
                        default:
                            cerr << "Zombie: Perception: type d'entite non reconnu" << endl;
                            break;
                    }
                }
                ++it;
            }
        }

        if(!humain)
        {
            //----------------------
            //perception secondaire
            //----------------------
            case_restante = 0;
            cout << "Perception Secondaire" << endl;
            //cases au nord
            temp._y = _placement._y - 3;
            for(i = -3 ; i <= 3 ; ++i)
            {
                temp._x = _placement._x + i;
                tab_alea[case_restante++] = temp;
            }
            //case au sud
            temp._y = _placement._y + 3;
            for(i = -3 ; i <= 3 ; ++i)
            {
                temp._x = _placement._x + i;
                tab_alea[case_restante++] = temp;
            }
            // a l'ouest
            temp._x = _placement._x - 3;
            for(i = -2 ; i <= 2 ; ++i)
            {
                temp._y = _placement._y + i;
                tab_alea[case_restante++] = temp;
            }
            //a l'est
            temp._x = _placement._x + 3;
            for(i = -2 ; i <= 2 ; ++i)
            {
                temp._y = _placement._y + i;
                tab_alea[case_restante++] = temp;
            }

            //analyse des cases
            while(case_restante > 0 && !humain)
            {
                //on tire une case disponible
                tirage = _simu->GeneInt(0,case_restante - 1);
                analyse = tab_alea[tirage];
                vierge_correction = analyse;
                _world->ConvertisseurCase(analyse);
                tab_alea[tirage] = tab_alea[--case_restante];
                list_analyse = &map[analyse._x][analyse._y];
                it = (*list_analyse).begin();
                while(it != (*list_analyse).end())
                {
                    alea = _simu->GeneInt(0,100);
                    if(alea < _percept_olf_sec )
                    {
                        switch((*it)->getType())
                        {
                            case 0: //zombie detecte
                                break;
                            case 1: //humain detecte
                                cout << "Humain detecte" << endl;
                                humain_trouve = vierge_correction;
                                humain = true;
                                break;
                            case 2: //arme detecte
                                break;
                            default:
                                cerr << "Zombie: Perception: type d'entite non reconnu" << endl;
                                break;
                        }
                    }
                    ++it;
                }
            }
        }
    }

    //--------------------------
    //Analyse du deplacement
    //--------------------------
    if(humain)
    {
        if(humain_trouve._x > _placement._x) // entite se trouve a l'est de l'humain
        {
            if(humain_trouve._y > _placement._y) // entite se trouve au sudest
            {
                sens_deplacement = 3;
            }
            else
            {
                if(humain_trouve._y < _placement._y) // entite se trouve au nord est
                {
                    sens_deplacement = 1;
                }
                else //entite se trouve a l'est
                {
                    sens_deplacement = 2;

                }
            }
        }
        else
        {
            if(humain_trouve._x < _placement._x) // entite se trouve a l'ouest de l'humain
            {
                if(humain_trouve._y > _placement._y) // entite se trouve au sudouest
                {
                    sens_deplacement = 5;
                }
                else
                {
                    if(humain_trouve._y < _placement._y) // entite se trouve au nord ouest
                    {
                        sens_deplacement = 7;
                    }
                    else //entite se trouve a l'ouest
                        sens_deplacement = 3;
                }

            }
            else // le entite se trouve soit au nord soit au sud
            {
                if(humain_trouve._y > _placement._y) // le entite se trouver au sud
                    sens_deplacement = 4;
                else                                 //le entite est donc au nord
                    sens_deplacement = 0;
            }
        }
    }
    else
    {
        cout << "Deplacement aleatoire" << endl;
        sens_deplacement = _simu->GeneInt(0,7);
    }
    Deplacement(sens_deplacement);
}
/**
 * \fn void Zombie::Afficher()
 * \brief fonction qui encapsule une fonction d'affichage de la classe Graphics
 *
 */

void Zombie::Afficher()
{
    Graphic::AfficherZombie(_placement._x,_placement._y);
}

