/* 
 * File:   main.cpp
 * Author: maxime
 *
 * Created on 5 novembre 2011, 22:56
 */

#include <stdlib.h>
#include "Classe.h"

/*
 * 
 */
int main(int argc, char** argv) {

    Classe a("TestA");
    Classe b("Testb");
    
    list<string> list1;
    list1.push_back("int");
    list1.push_back("char");
    list1.push_back("double");
    
    list<string> list2;
    list2.push_back("int");
    list2.push_back("double");
    
    list<string> list3;
    list3.push_back("int");
    list3.push_back("float");
    list3.push_back("double");
    
    list<string> list4;
    list4.push_back("int");
    
    list<string> list5;

    Methode * met1 = new Methode("methode1", "void *", M_PUBLIC    , M_STATIC                  , list1 );
    Methode * met2 = new Methode("methode2", "char *", M_PRIVATE   , M_VIRTUAL                 , list2 );
    Methode * met3 = new Methode("methode3", "string", M_PROTECTED , M_PURE_VIRTUAL            , list3 );
    Methode * met4 = new Methode("methode4", "double", M_PUBLIC    , 0                         , list4 );
    Methode * met5 = new Methode("methode5", "float" , M_PUBLIC    , M_PURE_VIRTUAL | M_STATIC , list5 );

    Attribut * att1 = new Attribut("attribut1", "char"        , M_PRIVATE   , M_STATIC);
    Attribut * att2 = new Attribut("attribut2", "float"       , M_PROTECTED , 0);
    Attribut * att3 = new Attribut("attribut3", "int *"       , M_PUBLIC    , M_VIRTUAL);
    Attribut * att4 = new Attribut("attribut4", "double"      , M_PRIVATE   , M_PURE_VIRTUAL);
    Attribut * att5 = new Attribut("attribut5", "string"      , M_PUBLIC    , 0);
    Attribut * att6 = new Attribut("attribut6", "list<double>", M_PRIVATE   , 0);

    a.addAttribut(att1);
    a.addAttribut(att2);
    a.addAttribut(att3);
    a.addAttribut(att4);
    a.addAttribut(att5);
    a.addAttribut(att6);
    a.addMethod(met1);
    a.addMethod(met2);
    a.addMethod(met3);
    a.addMethod(met4);
    a.addMethod(met5);

    Specialisation * spe = new Specialisation(&b,M_PUBLIC);
    a.addParent(spe);

    cout << "-------------------" << endl;
    cout << "Affichage attributs" << endl;
    cout << a.afficherAttributs() << endl;

    cout << "-------------------" << endl;
    cout << "Affichage attributs statiques" << endl;
    cout << a.afficherAttributsStatiques() << endl;

    cout << "-------------------" << endl;
    cout << "Affichage methodes" << endl;
    cout << a.afficherMethodes() << endl;

    cout << "-------------------" << endl;
    cout << "Affichage methodes statiques" << endl;
    cout << a.afficherMethodesStatiques() << endl;

    a.genererHppFile("Testcpp.hpp");
    a.genererJavaFile("test.java");
    
    return (EXIT_SUCCESS);
}

