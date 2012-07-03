class TestA: public Testb {
private:
static char attribut1;
double attribut4;
list<double> attribut6;
virtual char * methode2(int,double);
protected:
float attribut2;
virtual string methode3(int,float,double)=0;
public:
int * attribut3;
string attribut5;
static void * methode1(int,char,double);
double methode4(int);
virtual static float methode5()=0;
};
