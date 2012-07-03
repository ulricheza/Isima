package com.isima.axe.tests;

import java.util.Date;
import java.util.GregorianCalendar;

import com.isima.axe.model.Borrowing;

import junit.framework.TestCase;

public class BorrowingTest extends TestCase {
	
	public static void testIsInProgress()
	{
		Borrowing b = new Borrowing();
		
		assertTrue("isInprogress erreur ",b.isInProgress());
		assertFalse("erreur le livre n'est pas en retard",b.isLate());
		
		GregorianCalendar g = new GregorianCalendar(2010,01,01);
		
		b.setBorrowingDate(g.getTime());
		assertTrue("isInprogress erreur ",b.isInProgress());
		assertTrue("erreur le livre devrait être en retard",b.isLate());
		
		b.setActualReturnDate(new Date());
		assertFalse("isInprogress doit être faux",b.isInProgress());
		assertTrue("erreur le livre devrait être en retard",b.isLate());
		
		g = new GregorianCalendar();
		b.setBorrowingDate(g.getTime());
		g.add(GregorianCalendar.HOUR_OF_DAY, 23);
		b.setActualReturnDate(g.getTime());
		
		assertFalse("isInprogress doit être faux",b.isInProgress());
		assertFalse("erreur le livre devrait être en retard",b.isLate());
	
	}

}
