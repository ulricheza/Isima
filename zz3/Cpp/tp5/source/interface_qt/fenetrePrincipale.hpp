
#ifndef MAINWINDOW_TP5_6_H
#define MAINWINDOW_TP5_6_H

#include <QtGui/QMainWindow>
#include <QtGui/QGridLayout>
#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtCore/QList>

#include <interface_qt/labelCarte.hpp>
#include <interface_qt/colonneCartes.hpp>
#include <interface_qt/idZone.hpp>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

    private:
        LabelCarte *        pioche_;
        LabelCarte *        defausse_;

        LabelCarte *        dock_[ 4 ];

        ColonneCartes *     colonne_[7];

        QGridLayout *       layoutCarte_;

        QComboBox *         comboBoxColDepart_;
        QComboBox *         comboBoxColArrivee_;
        QLineEdit *         lineEditNbCarte_;
        QPushButton *       ok_;

        void peuplerComboBox();

    public:
        FenetrePrincipale( QWidget * inParent = 0 );
        ~FenetrePrincipale();

    public slots:
        void valider();

        void miseAJourPioche( const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte );
        void miseAJourDefausse( const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte );
        void miseAJourDock( const int & inNumeroDock, const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte );
        void miseAJourColonne( const int & inNumeroColonne, const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte );

        void afficherErreur( const char * inMessage );

    signals:
        void demandeDeplacement( const Zone::Enum & inDepart, const Zone::Enum & inArrivee, const int & inNbCarte );

};

#endif // MAINWINDOW_TP5_6_H
