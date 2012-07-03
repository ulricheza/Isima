/**
 * 
 */
package com.isima.axe.main;

import java.io.IOException;

import com.isima.axe.data.LoadData;

/**
 * @author julien
 *
 */
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		LoadData ld=null;
	    try {
			ld= new LoadData("./data/");
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("--------- BOOKS ----------");
		System.out.println(ld.getBooks().toString());
		System.out.println("--------- LIBRARYS ----------");
		System.out.println(ld.getLibrarys().toString());
		System.out.println("--------- PERSONS ----------");
		System.out.println(ld.getPersons().toString());
		System.out.println("--------- BORROWING ----------");
		System.out.println(ld.getBorrowing().toString());

	}

}
