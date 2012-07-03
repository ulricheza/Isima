import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;


public class Serializer<T> {
	
	private String path;
	
	public Serializer(String path)
	{
		this.path = path;
	}
	
	public void serialise(T obj) throws IOException
	{
		FileOutputStream   fos = null;
		ObjectOutputStream oos = null;

		fos = new FileOutputStream(path);
		oos = new ObjectOutputStream(fos);
		oos.writeObject(obj);
		oos.flush();
		if(oos!=null) oos.close();
		if(fos!=null) fos.close();
	}
	
	@SuppressWarnings("unchecked")
	public T deserialiser() throws IOException
	{
		Object objects = null;
		
		FileInputStream   fis = null;
		ObjectInputStream ois = null;
		
		fis = new FileInputStream(path);
		ois = new ObjectInputStream(fis);
		try {
			objects = ois.readObject();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if(ois!=null) ois.close();
		if(fis!=null) fis.close();
		
		return (T)objects;
	}

}
