
#include "mainWindow.hpp"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
   //Configuration du menu
   _menuBar      = new QMenuBar(NULL);
   _fichier       = new QMenu("Fichier");
   _actionQuitter = new QAction("&Quitter", this);

   connect(_actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
   _fichier->addAction(_actionQuitter);

   _menuBar->addMenu(_fichier);
   setMenuBar(_menuBar);

   //Configuration du layout
   _zoneCentrale = new QWidget(this);
   _layout       = new QVBoxLayout(this);
   _listValeur   = new QTextEdit("",this);
   _nbValeur     = new QLabel("Nb Valeur  = X",this);
   _moyenne      = new QLabel("Moyenne    = X",this);
   _ecartType    = new QLabel("Ecart type = X",this);
   _validate     = new QPushButton("Calcul",this);
   _fileDialog   = new QPushButton("Charger fichier");
   //layoutSecondair

   _layout->addWidget(_nbValeur);
   _layout->addWidget(_moyenne);
   _layout->addWidget(_ecartType);
   _layout->addWidget(_listValeur);
   _layout->addWidget(_fileDialog);
   _layout->addWidget(_validate);

   _zoneCentrale->setLayout(_layout);
   setCentralWidget(_zoneCentrale);

   //configuration des actions des boutons
   connect(_fileDialog, SIGNAL(clicked()), this, SLOT(openFile()));
   connect(_validate, SIGNAL(clicked()), this, SLOT(compute()));

}

void mainWindows::openFile()
{
   QString filename;
   QString line;
   QFile   file;

   filename= QFileDialog::getOpenFileName(this,tr("Open File"), "/",  tr("data Files (*.datQT)"));

   if( filename != "")
   {
      file.setFileName(filename);
      if(file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
         _listValeur->clear();
         _listValeur->append(file.readAll());
         file.close();
      }
   }
}

void mainWindows::compute()
{
   int     nb;
   int *   tab;
   float   moyenne   = 0.0;
   float   ecartType = 0.0;
   char    val[255];
   QString text;

   text = _listValeur->toPlainText();

   text.replace(QString("\n"), QString(" "));

   QTextStream stream(&text);
   stream >> nb;

   tab = new int[nb];

   for(int i = 0; i <nb ; ++i)
   {
      stream >> tab[i];
      moyenne += (float) tab[i];
   }

   moyenne /= (float) nb;

   //calcul de l'ecart type

   for(int i = 0; i <nb ; ++i)
   {
      ecartType += ((float)tab[i] - moyenne)*((float)tab[i] - moyenne);
   }

   ecartType /= (float)nb;
   ecartType = sqrt(ecartType);

   //Affichage des resultats

   sprintf(val,"%d",nb);
   _nbValeur->setText("Nb Valeur  = " + QString(val));

   sprintf(val,"%f",moyenne);
   _moyenne->setText("Moyenne    = " + QString(val));

   sprintf(val,"%f",ecartType);
   _ecartType->setText("Ecart type = " + QString(val));
}
