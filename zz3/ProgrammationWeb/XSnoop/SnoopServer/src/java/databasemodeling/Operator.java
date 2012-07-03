/*
 * -------------------------------------------------------------------------------
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *-------------------------------------------------------------------------------"
 */
package databasemodeling;

/**
 * Modelisation de l'operateur de comparaison pour une contrainte donnee
 * @author Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 */
public enum Operator {

    /**
     * ==
     */
    EGAL,
    /**
     * !=
     */
    DIFFERENT,
    /**
     * > 
     */
    SUPERIEUR,
    /**
     * >=
     */
    SUPERIEUREGAL,
    /**
     * <
     */
    INFERIEUR,
    /**
     * <=
     */
    INFERIEUREGAL
};
