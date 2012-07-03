/* 
 * File:   Classe.cpp
 * Author: maxime
 * 
 * Created on 6 novembre 2011, 00:57
 */

#include "Classe.h"

Classe::Classe()
{
}

Classe::Classe(string name) : _name(name)
{
}

Classe::~Classe()
{
}

string Classe::afficherAttributs()
{
    string att = "";

    for( list<Attribut*>::iterator it = _attributs.begin(); it != _attributs.end() ; ++it)
    {
        att += (*it)->toString() + "\n";
    }

    return att;
}

string Classe::afficherAttributsStatiques()
{
    string att = "";

    for( list<Attribut*>::iterator it = _attributs.begin(); it != _attributs.end() ; ++it)
    {
        if((*it)->isStatic())
        att += (*it)->toString() + "\n";
    }

    return att;
}

string Classe::afficherMethodes()
{
    string att = "";

    for( list<Methode*>::iterator it = _methodes.begin(); it != _methodes.end() ; ++it)
    {
        att += (*it)->toString() + "\n";
    }

    return att;
}

string Classe::afficherMethodesStatiques()
{
    string att = "";

    for( list<Methode*>::iterator it = _methodes.begin(); it != _methodes.end() ; ++it)
    {
        if((*it)->isStatic())
        att += (*it)->toString() + "\n";
    }

    return att;
}

void Classe::genererHppFile(string file)
{
    ofstream      fichier;
    list<Membre*> prive;
    list<Membre*> protege;
    list<Membre*> publi;
    string        parent = "";
    Accesibility  access;

    //tri des attributs selon l'accessibilite
    for(list<Attribut*>::iterator it = _attributs.begin(); it != _attributs.end(); ++it)
    {
        access = (*it)->getAccess();

        if(access == M_PRIVATE)
        {
            prive.push_back((*it));
        }
        else
        {
            if(access == M_PROTECTED)
            {
                protege.push_back((*it));
            }
            else
            {
                publi.push_back((*it));
            }
        }
    }

    //tri des methodes selon l'accessibilite
    for(list<Methode*>::iterator it = _methodes.begin(); it != _methodes.end(); ++it)
    {
        access = (*it)->getAccess();

        if(access == M_PRIVATE)
        {
            prive.push_back((*it));
        }
        else
        {
            if(access == M_PROTECTED)
            {
                protege.push_back((*it));
            }
            else
            {
                publi.push_back((*it));
            }
        }
    }

    //creation de la chaine de caractere represement l'heritage
    if( !_parents.empty())
    {
        list<Specialisation*>::iterator it = _parents.begin();
        parent = ":";

        switch((*it)->getAccess())
        {
            case M_PRIVATE:
                parent += " private ";
                break;
            case M_PROTECTED:
                parent += " protected ";
                break;
            case M_PUBLIC:
                parent += " public ";
                break;
            default:
                break;
        }

        parent += ((*it)->getClasse())->_name;
        ++it;

        while(it != _parents.end())
        {
            switch((*it)->getAccess())
            {
                case M_PRIVATE:
                    parent += " , private ";
                    break;
                case M_PROTECTED:
                    parent += " , protected ";
                    break;
                case M_PUBLIC:
                    parent += " , public ";
                    break;
                default:
                    break;
            }

            parent += ((*it)->getClasse())->_name;
            ++it;
        }
    }


    //ouverturedu fichier
    fichier.open(file.c_str(), ios::out);

    if(fichier)
    {
        fichier << "class " << _name << parent << " {" << endl;

        fichier << "private:" << endl;
        for(list<Membre*>::iterator it = prive.begin(); it != prive.end(); ++it)
        {
            fichier << (*it)->toString() << ";" << endl;
        }

        fichier << "protected:" << endl;
        for(list<Membre*>::iterator it = protege.begin(); it != protege.end(); ++it)
        {
            fichier << (*it)->toString() << ";" << endl;
        }

        fichier << "public:" << endl;
        for(list<Membre*>::iterator it = publi.begin(); it != publi.end(); ++it)
        {
            fichier << (*it)->toString() << ";" << endl;
        }
        fichier << "};" << endl;

        fichier.close();
    }
    else
    {
        cerr << "Erreur: Ouverture du fichier" << endl;
    }
}

void Classe::genererJavaFile(string file)
{
    ofstream      fichier;
    list<Membre*> prive;
    list<Membre*> protege;
    list<Membre*> publi;
    string        parent = "";
    Accesibility  access;

    if(_parents.size() < 2)
    {
        if(_parents.size() == 1 )
        {
            parent = " extends " + ((_parents.front())->getClasse())->_name;
        }
        else
        {
            cerr << "Java ne supporte pas le multi-heritage" << endl;
        }

        fichier.open(file.c_str(), ios::out);

        if(fichier)
        {
            fichier << "public " + _name + parent + "{" << endl;

            for(list<Attribut*>::iterator it = _attributs.begin(); it != _attributs.end(); ++it)
            {
                switch((*it)->getAccess())
                {
                    case M_PRIVATE:
                        fichier << "private ";
                        break;
                    case M_PROTECTED:
                        fichier << "protected ";
                        break;
                    case M_PUBLIC:
                        fichier << "public ";
                        break;
                    default:
                        break;
                }

                fichier << (*it)->toString() << ";" << endl;
            }

            for(list<Methode*>::iterator it = _methodes.begin(); it != _methodes.end(); ++it)
            {
                switch((*it)->getAccess())
                {
                    case M_PRIVATE:
                        fichier << "private ";
                        break;
                    case M_PROTECTED:
                        fichier << "protected ";
                        break;
                    case M_PUBLIC:
                        fichier << "public ";
                        break;
                    default:
                        break;
                }
                fichier << (*it)->toString() << "{" << endl << "}"<< endl;
            }

            fichier << "}";
            fichier.close();
        }
        else
        {
            cerr << "Erreur ouverture fichier" << endl;
        }
    }
}