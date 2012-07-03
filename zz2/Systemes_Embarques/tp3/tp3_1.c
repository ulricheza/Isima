 
   /****************************************************************************/
   /*  SEPTIER ESCOURBIAC                                             ISIMA    */
   /*  Janvier 2009                                                            */
   /*                                                                          */
   /*                     TD 3 - Clics et Doubles clics                        */
   /*                                                                          */
   /*                                                                          */
   /****************************************************************************/

//les fonctions necessaires

#define _capTIME_ ((double)1/18432000)*1024
unsigned short CP_LOW_TIME,CP_HIGH_TIME;
double temp_double_clic;
unsigned char * temp;
double * temp2;

void PPI_Init(void)
{ // Initialisation des ports PA, PB et PC en entrée
  PPI_SetMode(PA,0xff);  PPI_Out    (PA,0xff);
  PPI_SetMode(PB,0xff);  PPI_Out    (PB,0xff);
  PPI_SetMode(PC,0xff);  PPI_Out    (PC,0xff);
}
   
void EXPORT_Init(void)
{  // Initialisation des ports EXPA, EXPB et EXPD en entrée
   PortSetMode(EXPA,0xff);
   PortSetMode(EXPB,0xff);
   PortSetMode(EXPD,0xff);
}

void IRQ_EVENT_(void)
{
   int i;
   switch(GetMsg())
   {
      case MSG_CAPTURE0: //IT provenant de capture
         CaptureRead(0,&CP_LOW_TIME,&CP_HIGH_TIME);
         DebugPrint("duree double clic");
         DebugDOUBLE(_capTIME_ * (CP_HIGH_TIME+CP_LOW_TIME),DEC);
         DebugPrint("sec \n");
	   temp_double_clic = _capTIME_ * (CP_HIGH_TIME+CP_LOW_TIME);
         for(i=0;i<8;i++)
         {
            temp2 =  &temp_double_clic;
            temp = (unsigned char *)temp2 + i; 
	      EepWrite(*temp);
         }
	   CaptureOn(0); //Reactive ma capture
         break;


         
   }
}

void main(void)
{
   PPI_Init();
   EXPORT_Init();

   EepSetAdr(0x000);
   CaptureSet(0, CAPTURE_HIGHCYCLE|CAPTURE_DIV1024);
   CaptureOn(0);
   EventOn();
   while(1);

          
}




