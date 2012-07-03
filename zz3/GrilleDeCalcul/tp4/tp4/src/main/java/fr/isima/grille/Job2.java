package fr.isima.grille;

import org.ogf.saga.namespace.*;
import org.ogf.saga.logicalfile.LogicalFile;
import org.ogf.saga.logicalfile.LogicalFileFactory;
import org.ogf.saga.job.*;
import org.ogf.saga.url.*;

/**
 *
 * @author maxime
 */
public class Job2 {

    public static void main(String[] args) throws Exception {

        //Copie de povray sur la grille.
        System.out.println("creation src");
        URL src = URLFactory.createURL("http://fc.isima.fr/~passerat/enseignement/grille/tp4/povray.tgz");

        System.out.println("Creation surl");
        URL surl = URLFactory.createURL("srm://cirigridse01.univ-bpclermont.fr/dpm/univ-bpclermont.fr/home/biomed/generated/povrayEscourbi.tgz");

        System.out.println("Create NSEntry");
        NSEntry f = NSFactory.createNSEntry(src, Flags.NONE.getValue());
        System.out.println("Copy");
        f.copy(surl);
        System.out.println("close");
        f.close();

        System.out.println("Create LFN");
        URL lfn = URLFactory.createURL("lfn://lfc-biomed.in2p3.fr/grid/biomed/mip/jopasserat/escourbi/povray.tgz");

        System.out.println("Create Logical");
        LogicalFile file = LogicalFileFactory.createLogicalFile(lfn, Flags.CREATE.getValue());
        System.out.println("Add location");
        file.addLocation(surl);

        System.out.println("Close");
        file.close();

        //Creation du job
        System.out.println("---Description du job---");

        JobDescription desc = JobFactory.createJobDescription();
        desc.setAttribute(JobDescription.EXECUTABLE, "scriptPovray.sh");
        String[] outputFile = new String[22];
        outputFile[0] = "scriptPovray.sh > scriptPovray.sh";
        outputFile[21] = "output.txt < output.txt";
        for (int i = 1; i <= 20; ++i) {
            outputFile[i] = "glsbng" + i + ".png < glsbng" + i + ".png";
        }
        
        desc.setVectorAttribute(JobDescription.FILETRANSFER, outputFile);
        desc.setAttribute(JobDescription.OUTPUT, "output.txt");



        System.out.println("---Connexion au CE---");

        URL creamsurl = URLFactory.createURL("cream://cccreamceli09.in2p3.fr:8443/cream-sge-long");
        JobService cream = JobFactory.createJobService(creamsurl);

        System.out.println("---Lancement du job---");

        Job job = cream.createJob(desc);
        job.run();

        String jobId = job.getAttribute(Job.JOBID);
        System.out.println(jobId);

        System.out.println("---Attente du job---");

        //Heap space exception
        while (!job.waitFor(60)) {
            System.out.println(job.getState());
        }
        System.out.println(job.getState());
    }
}
