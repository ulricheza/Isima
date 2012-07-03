/*
 *  ListeMot.h
 *
 *  Created by Jonathan PASSERAT-PALMBACH on 11/22/10.
 *  Modified by Jonathan CAUX on 12/01/10
 *  Copyright 2010 ISIMA/LIMOS. All rights reserved.
 *
 */

#ifndef __LISTE_MOTS_H__
#define __LISTE_MOTS_H__

#include <string>
#include <list>
#include <iosfwd>



class ListeMots {
private:
   std::list<std::string> liste_;
   
public:
   typedef std::list<std::string>::iterator iterator;
   typedef std::list<std::string>::const_iterator const_iterator;
   
   
   void ajouterMot(const std::string&);
   
   ListeMots::iterator rechercherMot(const std::string&);
   ListeMots::const_iterator rechercherMot(const std::string&) const;
   
   void supprimerMot(const std::string&);
   
   /** Remplit la liste avec les elements compris dans la sequence passee en parametre.
    \param startPos Debut de la sequence
    \param endPos   Fin de la sequence
   */
   void insert(ListeMots::iterator startPos, ListeMots::iterator endPos);

   /** Remplit la liste avec les elements compris dans la sequence passee en parametre.
         (version const_iterator)
    \param startPos Debut de la sequence
    \param endPos   Fin de la sequence
    */
   void insert(ListeMots::const_iterator startPos, ListeMots::const_iterator endPos);
   
   inline unsigned getNbElements() const { return liste_.size(); }

   inline ListeMots::iterator       begin()       { return liste_.begin(); }
   inline ListeMots::iterator       end()         { return liste_.end(); }
   inline ListeMots::const_iterator begin() const { return liste_.begin(); }
   inline ListeMots::const_iterator end() const   { return liste_.end(); }
   
};
   
std::ostream& operator<< (std::ostream&, const ListeMots&);


#endif // __LISTE_MOTS_H__
