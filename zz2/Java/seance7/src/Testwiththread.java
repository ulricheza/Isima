
public class Testwiththread implements Runnable{

	@Override
	public void run() {
		   int i;
		   for(i=0;i<500000;++i)
		   {
			   System.out.println("Bonjour ;-)");
		   }	
	}
}
