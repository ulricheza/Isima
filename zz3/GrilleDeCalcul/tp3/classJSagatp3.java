import org.ogf.saga.error.*;
import org.ogf.saga.job.*;
import org.ogf.saga.url.*;
import org.ogf.saga.task.State;
import java.io.*;
import java.util.*;

class classJSagatp3
{
   public static void main(String[]args) throws Exception {

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
