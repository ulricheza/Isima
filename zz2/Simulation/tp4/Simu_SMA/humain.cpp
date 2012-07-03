/**
 * \file humain.cpp
 * \brief fichier d'implementation de la classe Humain
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 26 Janvier 2011
 * \version 0.1
 *
 */

#include <iostream>
#include <list>

#include "humain.h"
#include "world.h"
#include "entite.h"
#include "simulator.h"
#include "graphic.h"
#include "zombie.h"


using namespace std;

/*
 * Choix des valeurs pour la simulation d'un humain:
 * type = 1
 * Force: entre 1 et 10
 * Vitesse: entre 1 et 3 cases par tour
 * Perception Visuelle Primaire entre 50% et 75%
 * Perception Visuelle Secondaire entre  20% et 50%
 * Perception Auditive Primaire entre 40% et 60%
 * Perception Auditive Secondaire entre 10% et 30%
 */



/**
 * \fn    Humain::Humain(int x,int y,Simulator * simu, World * world)
 * \brief constructeur de la classe Humain
 * \param x     coordonnee de placement initial
 * \param y     coordonnee de placement initial
 * \param simu  pointeur vers l'instance de simulation
 * \param world pointeur sur le monde ou sera contenu l'agent
 */

Humain::Humain(int x,int y,Simulator * simu, World * world):Agent(x,y,simu,world)
{
    //initialisation des variables de force et de vitesse et de perception

    _force            = simu->GeneInt(1,10);
    _vitesse          = simu->GeneInt(1,3);
    _percept_vis_prim = simu->GeneInt(50,75);
    _percept_vis_sec  = simu->GeneInt(20,50);
    _percept_aud_prim = simu->GeneInt(40,60);
    _percept_aud_sec  = simu->GeneInt(10,30);
    _type             = 1;
    //rajout au monde
    world->AjouterEntite(x,y,this);
}

/**
 * \fn void Humain::Afficher()
 * \brief fonction qui encapsule une fonction d'affichage de la classe Graphics
 *
 */

void Humain::Afficher()
{
    Graphic::AfficherHumain(_placement._x,_placement._y);
}

/**
 * \fn void Humain::Tour()
 * \brief Cette methode effectue un tour de jeu d'un humain
 *
 */

void Humain::Tour()
{
    cout << "--------------------------" << endl;
    cout << "Humain actif..." << endl;
    int i = 0;
    bool vivant = true;
    while(vivant && i++ < _vitesse)
    {

        if(!PerceptionVisuelle())
        {
            PerceptionAuditive();
        }
        vivant = Action();
        _world->AfficWorld();
        Graphic::TransitionTour(); //delay
    }
}

/**
 * \fn bool Humain::Action()
 * \brief Cette fonction effectue les operations a effectuer suite a un deplacement
 * \return true si l'humain est toujours vivant.
 *
 * Les armes sont deposé en premier sur la map or on n'utilise que des push_back sur les listes
 *
 */

bool Humain::Action()
{
    cout << " Action Humaine ... " << endl;
    bool vivant = true;
    list<Entite *> ** map = _world->getMap();
    list<Entite *> * analyse = &map[_placement._x][_placement._y];
    list<Entite *>::iterator it = (*analyse).begin();

    while( (*it) != this && vivant) //si on est pas tout seul bouuuuuuuhhhhhhh
    {
        switch((*it)->getType())
        {
            case 0: //zombie detecte
                cout << " sur zombie" << endl;
                vivant = Attaquer((Agent *)(*it)); //obligation de caster /!\ A TESTER
                it = (*analyse).begin();
                break;
            case 1: //humain detecte
                cout << " sur humain" << endl;
                _force = _force + (*it)->getForce() / 2;
                (*it)->setForce(_force);
		++it;
                break;
            case 2: //arme detecte
                cout << " sur arme" << endl;
                _force += (*it)->getForce();
                _simu->SupprAutre((*it)); //on supprime l'arme du simulateur
		it = (*analyse).begin();
                break;
            default :
                cerr << "Humain:Action: Erreur recuperation type d entite " << endl;
                break;
        }

    }
    return vivant;
}

/**
 * \fn bool Humain::Attaquer(Agent * Cible)
 * \brief Cette methode simule l'ataque d'un humain vers un zombie
 * \param Cible pointeur sur le zombie qui va etre attaque
 * \return true si l'attaquant est gagnant
 *
 *  Si l'humain meurt la probalite qu'in devienne un zombie est de 70%
 */

bool Humain::Attaquer(Agent * cible)
{
    cout << "attaque sur un zombie : " ;

    bool resultat;
    int multiplacateurAtt = _simu->GeneInt(8,12);
    int multiplacateurCib = _simu->GeneInt(8,12);

    Zombie * ennemi = (Zombie *) cible; // cast autorise car on sait que l'agent ennemi sera toujours un zombie
    if( multiplacateurAtt * _force < multiplacateurCib * ennemi->getForce() )
    {
        //attaquant perdant
        cout << " humain perdant " ;
        ennemi->Tuer(this);
        if(_simu->GeneInt(0,100) < 70 ) //si le humain est infecte
        {
            ennemi->Contaminer();
        }
        cout << "et non contaminer" <<endl;
        resultat = false;
    }
    else
    {
        cout << "Humain gagnant" << endl;
        this->Tuer(ennemi);
        resultat = true;
    }
    return resultat;
}


/**
 * \fn bool Humain::PerceptionVisuelle()
 * \brief cette fonction simule les reactions de l'humain selon les conditions actuelles
 * \return true si une entite a ete detecte
 */

bool Humain::PerceptionVisuelle()
{
   
    bool  zombie = false;
    bool  humain = false;
    bool  arme = false;
    bool  result = false;
    int   i;
    int   tirage;
    int   case_valide;
    int   sens_perception; // 0 N, 1O , 2S, 3E
    int   sens_deplacement;
    int   alea;

    Position tab_alea[10];
    Position temp;
    Position analyse;
    Position vierge_correction;
    Position arme_trouvee;
    Position zombie_trouve;
    Position humain_trouve;

    list<Entite*> ** map = _world->getMap();
    list<Entite*> * list_analyse;
    list<Entite*>::iterator it;

    //initialisation map

    sens_perception = CalculSensPerception();
    cout << "Perception Visuelle, sens = " << sens_perception << endl;
    //-----------------------------------------
    //etape de la perception visuelle immediate
    //-----------------------------------------
    //initialisation du tableau des positions

    cout << "Perception visuelle immediate" << endl;
    case_valide = 0;
    switch(sens_perception)
    {
        case 0: //perception vers le nord
            temp._y = _placement._y - 1;
            for(i = -1 ; i <= 1; ++i) //remplissage sur la longeur
            {
                temp._x = _placement._x + i;
                tab_alea[case_valide] = temp;
                ++case_valide;
            }
            //case laterale
            temp._y = _placement._y;
            temp._x = _placement._x + 1;
            tab_alea[case_valide] = temp;
            ++case_valide;
            temp._x = _placement._x - 1;
            tab_alea[case_valide] = temp;
            ++case_valide;
            break;

        case 1: //perception vers l'est
            temp._x = _placement._x + 1;
            for(i = -1 ; i <= 1; ++i) //remplissage sur la longeur
            {
                temp._y = _placement._y + i;
                tab_alea[case_valide] = temp;
                ++case_valide;
            }
            //case laterale
            temp._x = _placement._x;
            temp._y = _placement._y + 1;
            tab_alea[case_valide] = temp;
            ++case_valide;
            temp._y = _placement._y - 1;
            tab_alea[case_valide] = temp;
            ++case_valide;
            break;

        case 2: //perception vers le sud
            temp._y = _placement._y + 1;
            for(i = -1 ; i <= 1; ++i) //remplissage sur la longeur
            {
                temp._x = _placement._x + i;
                tab_alea[case_valide] = temp;
                ++case_valide;

            }
            //case laterale
            temp._y = _placement._y;
            temp._x = _placement._x + 1;
            tab_alea[case_valide] = temp;
            ++case_valide;
            temp._x = _placement._x - 1;
            tab_alea[case_valide] = temp;
            ++case_valide;
            break;

        case 3: //perception vers l'ouest
            temp._x = _placement._x - 1;
            for(i = -1 ; i <= 1; ++i) //remplissage sur la longeur
            {
                temp._y = _placement._y + i;
                tab_alea[case_valide] = temp;
                ++case_valide;

            }
            //case laterale
            temp._x = _placement._x;
            temp._y = _placement._y + 1;
            tab_alea[case_valide] = temp;
            ++case_valide;
            temp._y = _placement._y - 1;;
            tab_alea[case_valide] = temp;
            ++case_valide;
            break;

        default:
            cerr << "Perception: Calcul Sens : valeur non  valide " << endl;
            break;
    }

    //Analyse des cases de la perception
    while(case_valide > 0 && !zombie)
    {
        //on tire une case disponible
        tirage = _simu->GeneInt(0,case_valide - 1);
        analyse = tab_alea[tirage];
        vierge_correction = analyse;
        _world->ConvertisseurCase(analyse);
        tab_alea[tirage] = tab_alea[--case_valide];
        list_analyse = &map[analyse._x][analyse._y];

        it = (*list_analyse).begin();
        while(it != (*list_analyse).end())
        {
            switch((*it)->getType())
            {
                case 0: //zombie detecte
                    cout << "Zombie detecte" << endl;
                    zombie = true;
                    zombie_trouve = vierge_correction;
                    break;
                case 1: //humain detecte
                    cout << "Humain detecte" << endl;
                    if(!humain)
                    {
                        humain_trouve = vierge_correction;
                        humain = true;
                    }
                    break;
                case 2: //arme detecte
                    cout << "Arme detecte" << endl;
                    if(!arme)
                    {
                        arme_trouvee = vierge_correction;
                        arme = true;
                    }
                    break;
                default:
                    cerr << "Humain: Perception: type d'entite non reconnu" << endl;
                    break;
            }
            ++it;
        }
    }
    
    if(!zombie && !humain && !arme)
    {
        //-----------------------------------------
        //etape de la perception visuelle primaire
        //-----------------------------------------
        cout << "Perception Visuelle Primaire" << endl;
        //initialisation des cases valables

        case_valide = 0;

        //partie bande laterale

        switch(sens_perception)
        {
            case 0: //perception dans le nord

                //bande laterale gauche
                temp._x = _placement._x - 2;
                for(i = 0; i < 3 ; ++i)
                {
                    temp._y = _placement._y - i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande laterale droite
                temp._x = _placement._x + 2;
                for(i = 0; i < 3 ; ++i)
                {
                    temp._y = _placement._y - i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande perpendiculaire
                temp._y = _placement._y - 2;
                for(i = -1; i <= 1 ; ++i)
                {
                    temp._x = _placement._x + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }
                break;

            case 1: //perception vers l'est

                //bande laterale gauche
                temp._y = _placement._y - 2;
                for(i = 0; i < 3 ; ++i)
                {
                    temp._x = _placement._x + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande laterale droite
                temp._y = _placement._y + 2;
                for(i = 0; i < 3 ; ++i)
                {
                    temp._x = _placement._x + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande perpendiculaire
                temp._x = _placement._x + 2;
                for(i = -1; i <= 1 ; ++i)
                {
                    temp._y = _placement._y + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }
                break;

            case 2: // perception vers le sud

                //bande laterale gauche
                temp._x = _placement._x + 2;
                for(i = 0; i < 3 ; ++i)
                {
                    temp._y = _placement._y + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande laterale droite
                temp._x = _placement._x - 2;
                for(i = 0; i < 3 ; ++i)
                {
                    temp._y = _placement._y + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande perpendiculaire
                temp._y = _placement._y + 2;
                for(i = -1; i <= 1 ; ++i)
                {
                    temp._x = _placement._x + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }
                
                break;

            case 3 : //perception vers l'ouest

                //bande laterale gauche
                temp._y = _placement._y + 2;
                for(i = 0; i < 3 ; ++i)
                {
                    temp._x = _placement._x - i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande laterale droite
                temp._y = _placement._y - 2;
                for(i = 0; i < 3 ; ++i)
                {
                    temp._x = _placement._x - i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande perpendiculaire
                temp._x = _placement._x - 2;
                for(i = -1; i <= 1 ; ++i)
                {
                    temp._y = _placement._y + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }
                break;

            default:
                cerr << "Perception: Calcul Sens : valeur non  valide " << endl;
                break;
        }

        //Analyse des cases de la perception

        while(case_valide > 0 && !zombie)
        {
            //on tire une case disponible

            tirage = _simu->GeneInt(0,case_valide - 1);
            analyse = tab_alea[tirage];
            vierge_correction = analyse;
            _world->ConvertisseurCase(analyse);
            tab_alea[tirage] = tab_alea[--case_valide];
            list_analyse = &map[analyse._x][analyse._y];

            it = (*list_analyse).begin();
            while(it != (*list_analyse).end())
            {
                alea = _simu->GeneInt(0,100);
                if(alea < _percept_vis_prim )
                {
                    switch((*it)->getType())
                    {
                        case 0: //zombie detecte
                            cout << "Zombie detecte" << endl;
                            zombie = true;
                            zombie_trouve = vierge_correction;
                            break;
                        case 1: //humain detecte
                            cout << "Humain detecte" << endl;
                            if(!humain)
                            {
                                humain_trouve = vierge_correction;
                                humain = true;
                            }
                            break;
                        case 2: //arme detecte
                            cout << "Arme detecte" << endl;
                            if(!arme)
                            {
                                arme_trouvee = vierge_correction;
                                arme = true;
                            }
                            break;
                        default:
                            cerr << "Humain: Perception: type d'entite non reconnu" << endl;
                            break;
                    }
                }
                ++it;
            }
        }
    }

    if(!zombie && !humain && !arme)
    {
        //etape de la perception visuelle secondaire

        //initialisation de la perception visuelle secondaire
        case_valide = 0;
        cout << "Perception Visuelle Secondaire" << endl;
        switch(sens_perception)
        {
            case 0: //perception vers le nord
                temp._y = _placement._y - 3;
                for(i=-2; i<= 2 ; ++i)
                {
                    temp._x = _placement._x + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }
                break;
            case 1: //perception vers l'est
                temp._x = _placement._x + 3;
                for(i=-2; i<= 2 ; ++i)
                {
                    temp._y = _placement._y + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }
                break;
            case 2: //perception vers le sud
                temp._y = _placement._y + 3;
                for(i=-2; i<= 2 ; ++i)
                {
                    temp._x = _placement._x + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }
                break;
            case 3: //perception vers l'ouest
                temp._x = _placement._x - 3;
                for(i=-2; i<= 2 ; ++i)
                {
                    temp._y = _placement._y + i;
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }
                break;
            default:
                    cerr << "Perception: Calcul Sens : valeur non  valide " << endl;
                    break;
        }

        //analyse de la perception visuelle secondaire
        while(case_valide > 0 && !zombie)
        {
            //on tire une case disponible
            tirage = _simu->GeneInt(0,case_valide - 1);
            analyse = tab_alea[tirage];
            vierge_correction = analyse;
            _world->ConvertisseurCase(analyse);
            tab_alea[tirage] = tab_alea[--case_valide];

            list_analyse = &map[analyse._x][analyse._y];
            it = (*list_analyse).begin();
            while(it != (*list_analyse).end())
            {
                alea = _simu->GeneInt(0,100);
                if(alea < _percept_vis_sec )
                {
                    switch((*it)->getType())
                    {
                        case 0: //zombie detecte
                            cout << "Zombie detecte" << endl;
                            zombie = true;
                            zombie_trouve = vierge_correction;
                            break;
                        case 1: //humain detecte
                            cout << "Humain detecte" << endl;
                            if(!humain)
                            {
                                humain_trouve = vierge_correction;
                                humain = true;
                            }
                            break;
                        case 2: //arme detecte
                            cout << "Arme detecte" << endl;
                            if(!arme)
                            {
                                arme_trouvee = vierge_correction;
                                arme = true;
                            }
                            break;
                        default:
                            cerr << "Humain: Perception: type d'entite non reconnu" << endl;
                            break;
                    }
                }
                ++it;
            }
        }
    }

    //------------------------------------------------------------------
    //gestion de deplacement selon la decouverte d'entite
    //------------------------------------------------------------------

    if(zombie) //si un zombie a ete vue
    {
        //l'humain fuit dans le sens oppose
        sens_deplacement = (sens_perception + 2)%4 * 2;
        this->Deplacement(sens_deplacement);
        result = true;
    }
    else //si un zombie n'a pas ete trouve
    {
        if(arme || humain) //si une arme ou un humain a ete trouve
        {
            //traitement similaire on va vers l'objet
            if(arme) //arme prioritaire par rapport aux autres humain
            {
                humain_trouve = arme_trouvee;
            }

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
                        sens_deplacement = 2;
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
            this->Deplacement(sens_deplacement);
            result = true;
        }
        //si rien n'a ete trouve on s'en remet a la perception auditive
    }
    return result;
}

/**
 * \fn bool Humain::PerceptionAuditive()
 * \brief cette fonction simule les reactions de l'humain selon les conditions actuelles
 * \return true si une entite a ete detecte
 *
 * Principe de la perception auditive:
 * l'humain pourra detecter que les entites mouvantes (Zombie et Humain)
 * on considera l'humain peureux si il percoit un bruit il s'enfuit droit devant
 */

bool Humain::PerceptionAuditive()
{
    bool trouve = false;

    int sens_perception;
    int case_valide;
    int tirage;
    int i;
    int alea;

    Position tab_alea[10];
    Position temp;
    Position analyse;

    list<Entite*> ** map = _world->getMap();
    list<Entite*> * list_analyse;
    list<Entite*>::iterator it;

    //initialisation perception
    sens_perception = CalculSensPerception();
    cout << "Perception Auditive, sens = " << sens_perception << endl;
    //---------------------------------------------
    // Perception auditive primaire
    //---------------------------------------------

    //initialisation perception auditive primaire
    case_valide = 0;
    cout << "Perception Auditive Primaire" << endl;
    switch(sens_perception)
    {
        case 0: //perception vers le nord
            //bande laterale
            temp._y = _placement._y + 1;
            for(i = -1; i <= 1; ++i)
            {
                temp._x = _placement._x + i;
                _world->ConvertisseurCase(temp);
                tab_alea[case_valide++] = temp;
            }
            break;
        case 1: //perception vers l'est
            //bande laterale
            temp._x = _placement._x - 1;
            for(i = -1; i <= 1; ++i)
            {
                temp._y = _placement._y + i;
                _world->ConvertisseurCase(temp);
                tab_alea[case_valide++] = temp;
            }
            break;
        case 2: //perception vers le sud
            //bande laterale
            temp._y = _placement._y - 1;
            for(i = -1; i <= 1; ++i)
            {
                temp._x = _placement._x + i;
                _world->ConvertisseurCase(temp);
                tab_alea[case_valide++] = temp;
            }
            break;
        case 3 : //perception vers l'ouest
            //bande laterale
            temp._x = _placement._x + 1;
            for(i = -1; i <= 1; ++i)
            {
                temp._y = _placement._y + i;
                _world->ConvertisseurCase(temp);
                tab_alea[case_valide++] = temp;
            }
            break;
        default :
            cerr << "Humain: Perception auditive: sens_perception errone" << endl;
            break;
    }

    //analyse de des cases de la perception auditive primaire
    while(case_valide > 0 && !trouve)
    {
        //on tire une case disponible
        tirage = _simu->GeneInt(0,case_valide - 1);
        analyse = tab_alea[tirage];
        tab_alea[tirage] = tab_alea[--case_valide];

        list_analyse = &map[analyse._x][analyse._y];

        it = (*list_analyse).begin();
        while(it != (*list_analyse).end())
        {
            alea = _simu->GeneInt(0,100);
            if(alea < _percept_aud_prim )
            {
                switch((*it)->getType())
                {
                    case 0: //zombie detecte
                    case 1: //humain detecte
                        cout << "Agent detecte "<< endl;
                        trouve = true;
                        break;
                    case 2: //arme detecte
                        // Vous avez déja entendu le bruit d'une arme depose au sol?
                        break;
                        default:
                        cerr << "Humain: Perception: type d'entite non reconnu" << endl;
                        break;
                }
            }
            ++it;
        }
    }
    if(!trouve)
    {
        //---------------------------------
        //Perception Auditive secondaire
        //---------------------------------
        cout << "Perception Auditive Secondaire " << endl;
        case_valide = 0;

        //initialisation des cases

        switch(sens_perception)
        {

            case 0: //perception vers le nord
                //bande laterale gauche
                temp._x = _placement._x - 2;
                for(i = 1; i <= 2 ; ++i)
                {
                    temp._y = _placement._y + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande laterale droite
                temp._x = _placement._x + 2;
                for(i = 1; i <= 2 ; ++i)
                {
                    temp._y = _placement._y + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande perpendiculaire
                temp._y = _placement._y + 2;
                for(i = -1; i <= 1 ; ++i)
                {
                    temp._x = _placement._x + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                }
                break;

            case 1: //perception vers l'est
                //bande laterale gauche
                temp._y = _placement._y - 2;
                for(i = -1; i >= -2 ; --i)
                {
                    temp._x = _placement._x + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande laterale droite
                temp._y = _placement._y + 2;
                for(i = -1; i >= -2 ; --i)
                {
                    temp._x = _placement._x + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande perpendiculaire
                temp._x = _placement._x - 2;
                for(i = -1; i <= 1 ; ++i)
                {
                    temp._y = _placement._y + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                }
                break;
            case 2: //perception vers le sud
                //bande laterale gauche
                temp._x = _placement._x + 2;
                for(i = -1; i >= -2 ; --i)
                {
                    temp._y = _placement._y + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande laterale droite
                temp._x = _placement._x - 2;
                for(i = -1 ; i >= -2 ; --i)
                {
                    temp._y = _placement._y + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande perpendiculaire
                temp._y = _placement._y - 2;
                for(i = -1; i <= 1 ; ++i)
                {
                    temp._x = _placement._x + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                }
                break;
            case 3: //perception vers l'ouest
                //bande laterale gauche
                temp._y = _placement._y + 2;
                for(i = 1; i <= 2 ; ++i)
                {
                    temp._x = _placement._x + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande laterale droite
                temp._y = _placement._y - 2;
                for(i = 1; i <= 2 ; ++i)
                {
                    temp._x = _placement._x + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                    ++case_valide;
                }

                //bande perpendiculaire
                temp._x = _placement._x + 2;
                for(i = -1; i <= 1 ; ++i)
                {
                    temp._y = _placement._y + i;
                    _world->ConvertisseurCase(temp);
                    tab_alea[case_valide] = temp;
                }
                break;
            default:
                cerr << "Humain: Perception auditive sens perception non valide" << endl;
        }
        //analyse de des cases de la perception auditive primaire
        while(case_valide > 0 && !trouve)
        {
            //on tire une case disponible
            tirage = _simu->GeneInt(0,case_valide-1);
            analyse = tab_alea[tirage];
            tab_alea[tirage] = tab_alea[--case_valide];

            list_analyse = &map[analyse._x][analyse._y];

            it = (*list_analyse).begin();
            while(it != (*list_analyse).end())
            {
                alea = _simu->GeneInt(0,100);
                if(alea < _percept_aud_sec )
                {
                    switch((*it)->getType())
                    {
                        case 0: //zombie detecte
                        case 1: //humain detecte
                            cout << "Agent detecte" << endl;
                            trouve = true;
                            break;
                        case 2: //arme detecte
                        // Vous avez déja entendu le bruit d'une arme depose au sol?
                            break;
                        default:
                            cerr << "Humain: Perception: type d'entite non reconnu" << endl;
                            break;
                    }
                }
                ++it;
            }
        }
    }

    //gestion du deplacement
    if(trouve) //si un humain ou zombie detecte on fuit droit devant !!!
    {
        this->Deplacement(2*sens_perception);
    }
    else //sinon il se deplace aleatoirement
    {
        this->Deplacement(_simu->GeneInt(0,7));
    }

    return trouve;
}


/**
 * \fn int Humain::CalculSensPerception()
 * \brief calcule le sens de perception d'un agent
 * \return le sens ou la perception doit etre faite
 * 0 : Nord
 * 1 : Est
 * 2 : Sud
 * 3 : Ouest
 */

int Humain::CalculSensPerception()
{
    int sens_perception;
    //calcul du sens de perception

    switch(_prec)
    {
        case 3:
        case 4:
            sens_perception = 0;
            break;
        case 5:
        case 6:
            sens_perception = 1;
            break;
        case 7:
        case 0:
            sens_perception = 2;
            break;
        case 1:
        case 2:
            sens_perception = 3;
            break;
    }
    return sens_perception;
}