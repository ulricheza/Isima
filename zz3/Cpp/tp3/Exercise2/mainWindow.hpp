#include <QMainWindow>
#include <QMenuBar>
#include <QList>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <math.h>
#include <cstdio>

class mainWindow : public QMainWindow
{
   Q_OBJECT
   public:
      explicit mainWindow(QWidget *parent = 0);

  public slots:
      void openFile();
      void compute();

   private:
      //PRECISION On est pas oblige de mettre tout les elements dans la classe. La desallocation se fait auto si on met this au parent
	  //lors de la construction
      QMenuBar *       _menuBar;
      QList<QMenu *>   _menu;
      QList<QAction *> _actions;
      QMenu *          _fichier;
      QAction *        _actionQuitter;
      QVBoxLayout *    _layout;
      QTextEdit *      _listValeur;
      QLabel *         _nbValeur;
      QLabel *         _moyenne;
      QLabel *         _ecartType;
      QWidget *        _zoneCentrale;
      QPushButton *    _validate;
      QPushButton *    _fileDialog;
	  
};

