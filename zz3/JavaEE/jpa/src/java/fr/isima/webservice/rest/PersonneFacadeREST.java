/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.isima.webservice.rest;

import fr.isima.entity.Personne;
import fr.isima.entity.PersonnePK;
import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.ws.rs.*;

/**
 *
 * @author maxime
 */
@Stateless
@Path("fr.isima.entity.personne")
public class PersonneFacadeREST extends AbstractFacade<Personne> {
    @PersistenceContext(unitName = "jpaPU")
    private EntityManager em;

    public PersonneFacadeREST() {
        super(Personne.class);
    }

    @POST
    @Override
    @Consumes({"application/xml", "application/json"})
    public void create(Personne entity) {
        super.create(entity);
    }

    @PUT
    @Override
    @Consumes({"application/xml", "application/json"})
    public void edit(Personne entity) {
        super.edit(entity);
    }

    @DELETE
    @Path("{id}")
    public void remove(@PathParam("id") PersonnePK id) {
        super.remove(super.find(id));
    }

    @GET
    @Path("{id}")
    @Produces({"application/xml", "application/json"})
    public Personne find(@PathParam("id") PersonnePK id) {
        return super.find(id);
    }

    @GET
    @Override
    @Produces({"application/xml", "application/json"})
    public List<Personne> findAll() {
        return super.findAll();
    }

    @GET
    @Path("{from}/{to}")
    @Produces({"application/xml", "application/json"})
    public List<Personne> findRange(@PathParam("from") Integer from, @PathParam("to") Integer to) {
        return super.findRange(new int[]{from, to});
    }

    @GET
    @Path("count")
    @Produces("text/plain")
    public String countREST() {
        return String.valueOf(super.count());
    }

    @java.lang.Override
    protected EntityManager getEntityManager() {
        return em;
    }
    
}
