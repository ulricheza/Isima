/*
 *  ListeMot.cpp
 *
 *  Created by Jonathan PASSERAT-PALMBACH on 11/22/10.
 *  Modified by Jonathan CAUX on 12/01/10
 *  Copyright 2010 ISIMA/LIMOS. All rights reserved.
 *
 */

#include "ListeMots.h"
#include <iostream>
#include <iterator>

void ListeMots::ajouterMot(const std::string& mot) {
   liste_.push_back(mot);
   liste_.sort();
}

ListeMots::iterator ListeMots::rechercherMot(const std::string& mot) {
   return std::find(liste_.begin(), liste_.end(), mot);
}

ListeMots::const_iterator ListeMots::rechercherMot(const std::string& mot) const {
   return std::find(liste_.begin(), liste_.end(), mot);
}

void ListeMots::supprimerMot(const std::string& mot) {
   liste_.remove(mot);
}

void ListeMots::insert(ListeMots::iterator startPos, ListeMots::iterator endPos) {
   liste_.insert(liste_.begin(), startPos, endPos);
   liste_.sort();
}

void ListeMots::insert(ListeMots::const_iterator startPos, ListeMots::const_iterator endPos) {
   liste_.insert(liste_.begin(), startPos, endPos);
   liste_.sort();
}

std::ostream& operator<< (std::ostream& os, const ListeMots& l) {
   std::copy(l.begin(), l.end(), std::ostream_iterator<std::string>(os, " "));
   return os;
}
