import org.ogf.saga.error.*;
import org.ogf.saga.job.*;
import org.ogf.saga.url.*;
import org.ogf.saga.session.*;
import org.ogf.saga.context.*;
import org.ogf.saga.task.State;
import java.io.*;
import java.util.*;

class classJSagatp3
{
   public static void main(String[]args) throws Exception {

      Context ctx = ContextFactory.createContext();
      ctx.setAttribute(Context.SERVER, "pbs-ssh://hpc1.clermont-universite.fr");
      ctx.setAttribute(Context.TYPE, "SSH");
      ctx.setAttribute(Context.USERPROXY, "/tmp/x509up_u652");
      //Si pas present lance une exception (userkey attributes is missing), par contre je ne connais pas mon userkey ...
      ctx.setAttribute(Context.USERKEY, "???");
      ctx.setAttribute(Context.USERPASS, "???");

      Session session = SessionFactory.createSession(false);
      session.addContext(ctx);

      System.out.println("---Description du job---");

      JobDescription desc = JobFactory.createJobDescription();
      desc.setAttribute(JobDescription.EXECUTABLE, "soumissionBasiqueJobs.sh"); 
      String[] files = {"soumissionBasiqueJobs.sh > soumissionBasiqueJobs.sh",
                        "output.txt < output.txt"};
      desc.setVectorAttribute(JobDescription.FILETRANSFER,files);
      desc.setAttribute(JobDescription.OUTPUT, "output.txt");

      System.out.println("---Connexion au WMS---");

      URL wmsurl = URLFactory.createURL("wms://lapp-wms03.in2p3.fr:7443/glite_wms_wmproxy_server");
      JobService wms = JobFactory.createJobService(wmsurl);
      
      System.out.println("---Lancement du job---");

      Job job = wms.createJob(desc);
      job.run();

      String jobId = job.getAttribute(Job.JOBID);
      System.out.println(jobId);
      
      System.out.println("---Attente du job---");

      while(!job.waitFor(30))
      {
         System.out.println(job.getState());
      }
      System.out.println(job.getState());  
   }
}
