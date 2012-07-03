/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */

package chucknorrisfact.controlleur;

import android.content.Context;
import android.util.Log;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import chucknorrisfact.modele.ListFact;
import chucknorrisfact.pro.R;


/**
 * Parser des fichiers de type csv
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 * 
 */
public class ParserCSV {

	private static String mTagLog = "ParserCSV";

	/**
	 * Methode statique qui lit un fichier de format csv pour en recuperer une liste de fact
	 * @param context Contexte de l'application
	 * @return La liste de fact actuelle.
	 * @throws FileNotFoundException Emit si la ressource n'est pas trouve.
	 * @throws IOException Probleme de lecture de la ressource.
	 */
	public static ListFact readFacts(Context context) throws FileNotFoundException, IOException {

		// Variables de lecture
		String[] fields;
		String line;
		// Element de la fact lue
		Integer id;
		String text;
		ArrayList<String> type;

		BufferedReader input = new BufferedReader(new InputStreamReader(context
				.getResources().openRawResource(R.raw.chucknorris)));
		ListFact list = ListFact.getInstance();

		line = input.readLine();
		while (line != null) {
			fields = line.split(";");
			if (fields.length > 2) {
				try {
					id = Integer.parseInt(fields[0]);
					text = fields[1];
					type = new ArrayList<String>();
					//lecture des types de l'id
					for (int i = 2; i < fields.length; ++i) {
						type.add(fields[i]);
					}
					if (type.get(type.size() - 1).contains("chuck norris") == true) {
						list.addFact(id, text, type);
					} else {
						Log.w(mTagLog,"Warning: Le dernier type de la fact n'est pas Chuck Norris");
					}
				} catch (NumberFormatException ex) {
					Log.w(mTagLog, "Warning: L'ID n'est pas valide");
				}
			} else {
				Log.w(mTagLog, "Warning: Le nombre de colonne est incorrect");
			}
			line = input.readLine();
		}
		input.close();
		return list;
	}
}
