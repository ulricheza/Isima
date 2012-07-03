/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package feutricolore;

import model.AtomicModel;
import types.DEVS_Integer;
import exception.DEVS_Exception;
import types.DEVS_Enum;
import types.DEVS_String;


/**
 *
 * @author dubujet
 */
public class Mft extends AtomicModel {

    enum States {
        v,
        oar,
        oav,
        r,
        c,
        ap,
        pp
    }

    String[] couleurs = {"vert","orange","rouge","cligotant"};

    States st;
    double sigma;

    public Mft(String name, String desc) {
        super(name, desc);
        this.addInputPortStructure(new DEVS_String(), "Panne", "Panne");
        this.addOutputPortStructure(new DEVS_Enum(couleurs), "Couleur", "Couleur du feu");
        st = States.v;
        sigma = 5;
    }

    @Override
    public void lambda() throws DEVS_Exception {
        String name = "";
        switch(st){
           case v:
               name = couleurs[1];
               break;
           case oar:
               name = couleurs[2];
               break;
           case oav:
               name = couleurs[0];
               break;
           case r:
               name = couleurs[1];
               break;
           case ap:
               name = couleurs[3];
               break;
           case pp:
               name = couleurs[0];
               break;
        }
        setOutputPortData("Couleur",name);
    }

    @Override
    public void deltaInt() {
       switch(st){
           case v:
               st = States.oar;
               sigma = 1;
               break;
           case oar:
               st = States.r;
               sigma = 3;
               break;
           case oav:
               st = States.v;
               sigma = 5;
               break;
           case r:
               st = States.oav;
               sigma = 1;
               break;
           case ap:
               st = States.c;
               sigma = Double.POSITIVE_INFINITY;
               break;
           case pp:
               st = States.v;
               sigma = 5;
               break;
       }
    }

    @Override
    public void deltaExt(double e) throws DEVS_Exception {
        int arg0 = ((DEVS_Integer)getInputPortData("Panne")).getInteger();
        if(arg0 == 0) {
            st = States.ap;
            sigma = Double.POSITIVE_INFINITY;
        } else if(arg0 == 1) {
            if(st==States.c) {
                st = States.pp;
                sigma = 0;
            } else {
                sigma -= e;
            }            
        }
    }

    @Override
    public double ta() {
        return sigma;
    }

}
