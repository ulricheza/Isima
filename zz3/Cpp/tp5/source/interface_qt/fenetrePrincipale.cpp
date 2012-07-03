
#include <interface_qt/fenetrePrincipale.hpp>

#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>

FenetrePrincipale::FenetrePrincipale( QWidget * inParent )
    : QMainWindow( inParent )
{
    QHBoxLayout *       layoutGeneral   = new QHBoxLayout;
                        layoutCarte_    = new QGridLayout;
    QGridLayout *       layoutChoix     = new QGridLayout;
    QWidget *           widget          = new QWidget;

    pioche_         = new LabelCarte;
    defausse_       = new LabelCarte;
    for ( int i = 0; i < 4; ++i )
    {
        dock_[ i ]      = new LabelCarte;
    }
    for ( int i = 0; i < 7; ++i )
    {
        colonne_[ i ]   = new ColonneCartes;
    }

    comboBoxColDepart_  = new QComboBox();
    comboBoxColArrivee_ = new QComboBox();
    lineEditNbCarte_    = new QLineEdit( "1" );
    ok_                 = new QPushButton( tr( "Valider" ) );

    // ---------------------------------------------------------- //
    //                                                            //
    //                      Partie Carte                          //
    //                                                            //
    // ---------------------------------------------------------- //
    layoutCarte_->addWidget( new QLabel( tr( "Pioche" ) ), 0, 0 );
    layoutCarte_->addWidget( pioche_, 1, 0 );
    layoutCarte_->addWidget( new QLabel( tr( "Defausse" ) ), 0, 1 );
    layoutCarte_->addWidget( defausse_, 1, 1 );

    layoutCarte_->addWidget( new QLabel( tr( "Dock 1" ) ), 0, 3 );
    layoutCarte_->addWidget( dock_[ 0 ], 1, 3 );
    layoutCarte_->addWidget( new QLabel( tr( "Dock 2" ) ), 0, 4 );
    layoutCarte_->addWidget( dock_[ 1 ], 1, 4 );
    layoutCarte_->addWidget( new QLabel( tr( "Dock 3" ) ), 0, 5 );
    layoutCarte_->addWidget( dock_[ 2 ], 1, 5 );
    layoutCarte_->addWidget( new QLabel( tr( "Dock 4" ) ), 0, 6 );
    layoutCarte_->addWidget( dock_[ 3 ], 1, 6 );

    layoutCarte_->addWidget( new QLabel( tr( "Colonne 1" ) ), 2, 0 );
    layoutCarte_->addWidget( colonne_[ 0 ], 3, 0 );
    layoutCarte_->addWidget( new QLabel( tr( "Colonne 2" ) ), 2, 1 );
    layoutCarte_->addWidget( colonne_[ 1 ], 3, 1 );
    layoutCarte_->addWidget( new QLabel( tr( "Colonne 3" ) ), 2, 2 );
    layoutCarte_->addWidget( colonne_[ 2 ], 3, 2 );
    layoutCarte_->addWidget( new QLabel( tr( "Colonne 4" ) ), 2, 3 );
    layoutCarte_->addWidget( colonne_[ 3 ], 3, 3 );
    layoutCarte_->addWidget( new QLabel( tr( "Colonne 5" ) ), 2, 4 );
    layoutCarte_->addWidget( colonne_[ 4 ], 3, 4 );
    layoutCarte_->addWidget( new QLabel( tr( "Colonne 6" ) ), 2, 5 );
    layoutCarte_->addWidget( colonne_[ 5 ], 3, 5 );
    layoutCarte_->addWidget( new QLabel( tr( "Colonne 7" ) ), 2, 6 );
    layoutCarte_->addWidget( colonne_[ 6 ], 3, 6 );

    layoutCarte_->setRowStretch( 4, 1 );


    // ---------------------------------------------------------- //
    //                                                            //
    //                      Partie Choix                          //
    //                                                            //
    // ---------------------------------------------------------- //
    layoutChoix->addWidget( new QLabel( tr( "Tas de départ : " ) ), 0, 1 );
    layoutChoix->addWidget( comboBoxColDepart_, 0, 2 );
    layoutChoix->addWidget( new QLabel( tr( "Tas d'arrivée : " ) ), 1, 1 );
    layoutChoix->addWidget( comboBoxColArrivee_, 1, 2 );
    layoutChoix->addWidget( new QLabel( tr( "Nb carte : " ) ), 2, 1 );
    layoutChoix->addWidget( lineEditNbCarte_, 2, 2 );
    layoutChoix->addWidget( ok_, 3, 1, 1, 2 );

    layoutChoix->setRowStretch( 4, 1 );
    layoutChoix->setColumnStretch( 0, 1 );

    peuplerComboBox();


    // ---------------------------------------------------------- //
    //                                                            //
    //                      Partie General                        //
    //                                                            //
    // ---------------------------------------------------------- //

    layoutGeneral->addLayout( layoutCarte_ );
    layoutGeneral->addLayout( layoutChoix );

    widget->setLayout( layoutGeneral );
    setCentralWidget( widget );

    setWindowTitle( tr( "Réussite" ) );

    connect( ok_,  SIGNAL( clicked() ),
             this, SLOT( valider() ) );
}

FenetrePrincipale::~FenetrePrincipale()
{
}

void FenetrePrincipale::peuplerComboBox()
{
    for ( int i = 0; i < Zone::nb_zone; ++i )
    {
        comboBoxColDepart_->insertItem( i, Zone::toString( Zone::Enum( i ) ).c_str() );
        comboBoxColArrivee_->insertItem( i, Zone::toString( Zone::Enum( i ) ).c_str() );
    }

    comboBoxColDepart_->setCurrentIndex( 0 );
    comboBoxColArrivee_->setCurrentIndex( 0 );
}

void FenetrePrincipale::valider()
{

    emit demandeDeplacement(
                             Zone::stringtoZone( comboBoxColDepart_->currentText().toStdString() ),
                             Zone::stringtoZone( comboBoxColArrivee_->currentText().toStdString() ),
                             lineEditNbCarte_->text().toInt()
                           );
}

void FenetrePrincipale::miseAJourPioche( const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte )
{
    pioche_->chargementDerniereCarte( inListeCarte );
}

void FenetrePrincipale::miseAJourDefausse( const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte )
{
    defausse_->chargementDerniereCarte( inListeCarte );
}

void FenetrePrincipale::miseAJourDock( const int & inNumeroDock, const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte )
{
    dock_[ inNumeroDock ]->chargementDerniereCarte( inListeCarte );
}

void FenetrePrincipale::miseAJourColonne( const int & inNumeroColonne, const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte )
{
    layoutCarte_->removeWidget( colonne_[ inNumeroColonne ] );

    delete colonne_[ inNumeroColonne ];
    colonne_[ inNumeroColonne ]     = new ColonneCartes( inListeCarte );

    layoutCarte_->addWidget( colonne_[ inNumeroColonne ], 3, inNumeroColonne );
}

void FenetrePrincipale::afficherErreur( const char * inMessage )
{
    QMessageBox message( QMessageBox::Warning, "Erreur", inMessage );
    message.exec();
}
