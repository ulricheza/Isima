/**
 * 
 */
package model.tests;

import java.util.ArrayList;

import com.isima.library.model.*;

import junit.framework.TestCase;

/**
 * @author escourbi
 *
 */
public class PersonTests extends TestCase {
	
	/*
	 * Teste la methode subscribes de la classe person
	 */
	public void subscribesTest()
	{
		Person pers = new Person("JC","septier");
		
		Library libtest = new Library("BDU","DTC");
		
		//test d'une souscription normale
		pers.subscribes(libtest);
		assertEquals(libtest,pers.getLibrary());
		
		//test d'insertion d'un library null
		Library libnull = null;
		pers.subscribes(libnull);
		assertEquals(null,pers.getLibrary());
		
	}
	
	public void borrowsTest()
	{
		//test d'un emprunt classique
		Person pers = new Person("JC","septier");
		Book booktest = new Book("LOTR","Trucmuche");
		Library libtest = new Library("BU","DTC");
		Book bookFalse = new Book("Harry Crotteur","Moi");
		
		libtest.addBook(booktest);
		pers.subscribes(libtest);
		
		
		assertEquals(true,pers.borrows(booktest));
		
		//test d'un emprunt d'un livre qui n'existe pas
		assertEquals(false,pers.borrows(bookFalse));
	
		//test d'un emprunt d'un livre qui est deja emprunte
		assertEquals(false,pers.borrows(booktest));
		
		//test d'un emprunt d'un livre null
		assertEquals(false,pers.borrows(null));
	}
	
	public void returnTest()
	{
		Person pers = new Person("JC","septier");
		Book booktest = new Book("LOTR","Trucmuche");
		Library libtest = new Library("BU","DTC");
		Book bookFalse = new Book("Harry Crotteur","Moi");
		ArrayList liste;
		Borrowing fiche;
		
		libtest.addBook(booktest);
		pers.subscribes(libtest);
		pers.borrows(booktest); 
		
		//test d'un livre normal
		pers.borrows(booktest);
		liste = pers.getEmpruntliste();
		fiche = (Borrowing) liste.get(0);
		
		assertEquals(true, fiche.isCompleted());
		
		//test d'un livre non emprunte
		pers.returns(bookFalse);
		// comment tester?
	}
}
