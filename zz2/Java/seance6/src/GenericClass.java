
public class GenericClass<E> {
	
	@SuppressWarnings("unused")
	public void add(E... es )
	{
		for(E args:es)
		{
			System.out.println("OK");
		}
	}

}
