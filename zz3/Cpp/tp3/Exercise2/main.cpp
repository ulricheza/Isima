#include <QApplication>

#include "mainWindow.hpp"
 
int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
  
   mainWindow * mainForm = new mainWindow(NULL);

   mainForm->show();
   
   return app.exec();
}
