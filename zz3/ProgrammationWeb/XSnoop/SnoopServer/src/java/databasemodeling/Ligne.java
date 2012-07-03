/*
#-------------------------------------------------------------------------------
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v1.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v10.html
#-------------------------------------------------------------------------------
 */
package databasemodeling;

import java.util.ArrayList;

/**
 *
 * @author Maxime
 */
public class Ligne {

    private ArrayList<Attribut> attributs;

    public Ligne() {
        attributs = new ArrayList<Attribut>();
    }

    public void addAttribut(Attribut attribut) {
        attributs.add(attribut);
    }

    public ArrayList<Attribut> getAttributs() {
        return attributs;
    }
}
