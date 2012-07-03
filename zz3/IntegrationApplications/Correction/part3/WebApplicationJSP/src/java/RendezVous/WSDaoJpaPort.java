/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package RendezVous;

import RendezVous_client.Clients;
import RendezVous_client.Creneaux;
import RendezVous_client.GetAllClientsResponse;
import RendezVous_client.GetAllCreneauxResponse;
import RendezVous_client.GetAllMedecinsResponse;
import RendezVous_client.GetRvMedecinJourResponse;
import RendezVous_client.Medecins;
import RendezVous_client.Rv;
import RendezVous_client.WSDaoJpa;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.UriInfo;
import javax.xml.bind.JAXBElement;
import javax.xml.namespace.QName;

/**
 * REST Web Service
 *
 * @author lacomme
 */

@Path("wsdaojpaport")
public class WSDaoJpaPort {
    private WSDaoJpa port;
    @Context
    private UriInfo context;

    /** Creates a new instance of WSDaoJpaPort */
    public WSDaoJpaPort() {
        port = getPort();
    }

    /**
     * Invokes the SOAP method getAllClients
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.GetAllClientsResponse>
     */
    @GET
    @Produces("application/xml")
    @Consumes("text/plain")
    @Path("getallclients/")
    public JAXBElement<GetAllClientsResponse> getAllClients() {
        try {
            // Call Web Service Operation
            if (port != null) {
                java.util.List<RendezVous_client.Clients> result = port.getAllClients();

                class GetAllClientsResponse_1 extends RendezVous_client.GetAllClientsResponse {

                    GetAllClientsResponse_1(java.util.List<RendezVous_client.Clients> _return) {
                        this._return = _return;
                    }
                }
                RendezVous_client.GetAllClientsResponse response = new GetAllClientsResponse_1(result);
                return new RendezVous_client.ObjectFactory().createGetAllClientsResponse(response);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     * Invokes the SOAP method getAllMedecins
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.GetAllMedecinsResponse>
     */
    @GET
    @Produces("application/xml")
    @Consumes("text/plain")
    @Path("getallmedecins/")
    public JAXBElement<GetAllMedecinsResponse> getAllMedecins() {
        try {
            // Call Web Service Operation
            if (port != null) {
                java.util.List<RendezVous_client.Medecins> result = port.getAllMedecins();

                class GetAllMedecinsResponse_1 extends RendezVous_client.GetAllMedecinsResponse {

                    GetAllMedecinsResponse_1(java.util.List<RendezVous_client.Medecins> _return) {
                        this._return = _return;
                    }
                }
                RendezVous_client.GetAllMedecinsResponse response = new GetAllMedecinsResponse_1(result);
                return new RendezVous_client.ObjectFactory().createGetAllMedecinsResponse(response);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     * Invokes the SOAP method getAllCreneaux
     * @param arg0 resource URI parameter
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.GetAllCreneauxResponse>
     */
    @POST
    @Produces("application/xml")
    @Consumes("application/xml")
    @Path("getallcreneaux/")
    public JAXBElement<GetAllCreneauxResponse> postGetAllCreneaux(JAXBElement<Medecins> arg0) {
        try {
            // Call Web Service Operation
            if (port != null) {
                java.util.List<RendezVous_client.Creneaux> result = port.getAllCreneaux(arg0.getValue());

                class GetAllCreneauxResponse_1 extends RendezVous_client.GetAllCreneauxResponse {

                    GetAllCreneauxResponse_1(java.util.List<RendezVous_client.Creneaux> _return) {
                        this._return = _return;
                    }
                }
                RendezVous_client.GetAllCreneauxResponse response = new GetAllCreneauxResponse_1(result);
                return new RendezVous_client.ObjectFactory().createGetAllCreneauxResponse(response);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     * Invokes the SOAP method getRvMedecinJour
     * @param arg0 resource URI parameter
     * @param arg1 resource URI parameter
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.GetRvMedecinJourResponse>
     */
    @POST
    @Produces("application/xml")
    @Consumes("application/xml")
    @Path("getrvmedecinjour/")
    public JAXBElement<GetRvMedecinJourResponse> postGetRvMedecinJour(JAXBElement<Medecins> arg0, String arg1) {
        try {
            // Call Web Service Operation
            if (port != null) {
                java.util.List<RendezVous_client.Rv> result = port.getRvMedecinJour(arg0.getValue(), arg1);

                class GetRvMedecinJourResponse_1 extends RendezVous_client.GetRvMedecinJourResponse {

                    GetRvMedecinJourResponse_1(java.util.List<RendezVous_client.Rv> _return) {
                        this._return = _return;
                    }
                }
                RendezVous_client.GetRvMedecinJourResponse response = new GetRvMedecinJourResponse_1(result);
                return new RendezVous_client.ObjectFactory().createGetRvMedecinJourResponse(response);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     * Invokes the SOAP method ajouterRv
     * @param arg0 resource URI parameter
     * @param arg1 resource URI parameter
     * @param arg2 resource URI parameter
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.Rv>
     */
    @POST
    @Produces("application/xml")
    @Consumes("application/xml")
    @Path("ajouterrv/")
    public JAXBElement<Rv> postAjouterRv(String arg0, JAXBElement<Creneaux> arg1, JAXBElement<Clients> arg2) {
        try {
            // Call Web Service Operation
            if (port != null) {
                RendezVous_client.Rv result = port.ajouterRv(arg0, arg1.getValue(), arg2.getValue());
                return new JAXBElement<RendezVous_client.Rv>(new QName("http//RendezVous_client/", "rv"), RendezVous_client.Rv.class, result);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     * Invokes the SOAP method supprimerRv
     * @param arg0 resource URI parameter
     */
    @PUT
    @Consumes("application/xml")
    @Path("supprimerrv/")
    public void putSupprimerRv(JAXBElement<Rv> arg0) {
        try {
            // Call Web Service Operation
            if (port != null) {
                port.supprimerRv(arg0.getValue());
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
    }

    /**
     * Invokes the SOAP method getClientById
     * @param arg0 resource URI parameter
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.Clients>
     */
    @POST
    @Produces("application/xml")
    @Consumes("application/xml")
    @Path("getclientbyid/")
    public JAXBElement<Clients> postGetClientById(JAXBElement<Long> arg0) {
        try {
            // Call Web Service Operation
            if (port != null) {
                RendezVous_client.Clients result = port.getClientById(arg0.getValue());
                return new JAXBElement<RendezVous_client.Clients>(new QName("http//RendezVous_client/", "clients"), RendezVous_client.Clients.class, result);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     * Invokes the SOAP method getMedecinById
     * @param arg0 resource URI parameter
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.Medecins>
     */
    @POST
    @Produces("application/xml")
    @Consumes("application/xml")
    @Path("getmedecinbyid/")
    public JAXBElement<Medecins> postGetMedecinById(JAXBElement<Long> arg0) {
        try {
            // Call Web Service Operation
            if (port != null) {
                RendezVous_client.Medecins result = port.getMedecinById(arg0.getValue());
                return new JAXBElement<RendezVous_client.Medecins>(new QName("http//RendezVous_client/", "medecins"), RendezVous_client.Medecins.class, result);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     * Invokes the SOAP method getRvById
     * @param arg0 resource URI parameter
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.Rv>
     */
    @POST
    @Produces("application/xml")
    @Consumes("application/xml")
    @Path("getrvbyid/")
    public JAXBElement<Rv> postGetRvById(JAXBElement<Long> arg0) {
        try {
            // Call Web Service Operation
            if (port != null) {
                RendezVous_client.Rv result = port.getRvById(arg0.getValue());
                return new JAXBElement<RendezVous_client.Rv>(new QName("http//RendezVous_client/", "rv"), RendezVous_client.Rv.class, result);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     * Invokes the SOAP method getCreneauById
     * @param arg0 resource URI parameter
     * @return an instance of javax.xml.bind.JAXBElement<RendezVous_client.Creneaux>
     */
    @POST
    @Produces("application/xml")
    @Consumes("application/xml")
    @Path("getcreneaubyid/")
    public JAXBElement<Creneaux> postGetCreneauById(JAXBElement<Long> arg0) {
        try {
            // Call Web Service Operation
            if (port != null) {
                RendezVous_client.Creneaux result = port.getCreneauById(arg0.getValue());
                return new JAXBElement<RendezVous_client.Creneaux>(new QName("http//RendezVous_client/", "creneaux"), RendezVous_client.Creneaux.class, result);
            }
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }

    /**
     *
     */
    private WSDaoJpa getPort() {
        try {
            // Call Web Service Operation
            RendezVous_client.WSDaoJpaService service = new RendezVous_client.WSDaoJpaService();
            RendezVous_client.WSDaoJpa p = service.getWSDaoJpaPort();
            return p;
        } catch (Exception ex) {
            // TODO handle custom exceptions here
        }
        return null;
    }
}
