TEMPLATE = app
TARGET = 
DEPENDPATH += . \
    interface_qt \
    solitaire
INCLUDEPATH += . \
    interface_qt \
    solitaire
QT += svg

# Input
HEADERS += adaptateur_controleur_graphique.hpp \
    controleur_graphique.hpp \
    controleur_texte.hpp \
    interface_qt/colonneCartes.hpp \
    interface_qt/fenetrePrincipale.hpp \
    interface_qt/gestionnaireImageCarte.hpp \
    interface_qt/idCarte.hpp \
    interface_qt/idZone.hpp \
    interface_qt/labelCarte.hpp \
    solitaire/carte.hpp \
    solitaire/controleur.hpp \
    solitaire/paquet.hpp \
    solitaire/plateau.hpp \
    solitaire/solitaire.hpp \
    solitaire/pioche.h \
    solitaire/dock.h \
    solitaire/colonne.h \
    solitaire/croupier.h \
    solitaire/croupierclassique.h
SOURCES += adaptateur_controleur_graphique.cpp \
    controleur_graphique.cpp \
    controleur_texte.cpp \
    test_solitaire.cpp \
    interface_qt/colonneCartes.cpp \
    interface_qt/fenetrePrincipale.cpp \
    interface_qt/gestionnaireImageCarte.cpp \
    interface_qt/idCarte.cpp \
    interface_qt/idZone.cpp \
    interface_qt/labelCarte.cpp \
    solitaire/paquet.cpp \
    solitaire/solitaire.cpp \
    solitaire/pioche.cpp \
    solitaire/dock.cpp \
    solitaire/colonne.cpp \
    solitaire/croupier.cpp \
    solitaire/croupierclassique.cpp
RESOURCES += tp_5.qrc
