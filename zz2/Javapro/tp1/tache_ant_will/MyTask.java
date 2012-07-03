package task;

import java.io.File;
import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.Task;
import org.apache.tools.ant.taskdefs.Delete;
import org.apache.tools.ant.taskdefs.Echo;
import org.apache.tools.ant.taskdefs.Jar;
import org.apache.tools.ant.taskdefs.Java;
import org.apache.tools.ant.taskdefs.Javac;
import org.apache.tools.ant.taskdefs.Manifest;
import org.apache.tools.ant.taskdefs.Manifest.Attribute;
import org.apache.tools.ant.taskdefs.ManifestException;
import org.apache.tools.ant.taskdefs.Mkdir;
import org.apache.tools.ant.types.Path;

public class MyTask extends Task
{
    private String srcDir;
    private String destDir;
    private String jarFile;
    private String mainClass;
    private String version;
    
    public void setVersion(String version) {
        this.version = version;
    }

    public void setSrcDir(String srcDir) {
        this.srcDir = srcDir;
    }

    public void setDestDir(String destDir) {
        this.destDir = destDir;
    }

    public void setJarFile(String jarFile) {
        this.jarFile = jarFile;
    }

    public void setMainClass(String mainClass) {
        this.mainClass = mainClass;
    }
    
    private void clean()
    {
        Delete delete = new Delete();
        
        delete.setProject(getProject());
	delete.setTaskName("clean");
	delete.setDir(new File(destDir));
        
        delete.execute();
    }

    private void compile()
    {
	Javac javac = new Javac();
	Mkdir mkdir = new Mkdir();
	        
	mkdir.setProject(getProject());
	mkdir.setTaskName("compile");
	mkdir.setDir(new File(destDir));
	
	mkdir.execute();
	
	javac.setProject(getProject());
	javac.setTaskName("compile");
	javac.setSrcdir(new Path(getProject(), srcDir));
	javac.setDestdir(new File(destDir));
	javac.setSource(version);
	
	javac.execute();
    }
    
    private void pack() throws ManifestException
    {
	Jar jar = new Jar();
        
	jar.setProject(getProject());
	jar.setTaskName("package");
	jar.setBasedir(new File(destDir));
	jar.setDestFile(new File(jarFile));        
        
        Manifest manifest = new Manifest();
        Attribute attribute = new Attribute(); 
    
        attribute.setName("Main-Class");
        attribute.setValue(mainClass);
    
        manifest.addConfiguredAttribute(attribute);
        jar.addConfiguredManifest(manifest);

        jar.execute();
    }
    
    private void run()
    {
        Java java = new Java();
        
        java.setProject(getProject());
        java.setTaskName("run");
        java.setJar(new File(jarFile));
        java.setFork(true);
        
        java.execute();        
    }
    
    public void execute() 
    {
	Echo echo = new Echo();
        String projectName = getProject().getProperty("ant.project.name");

        if(srcDir == null)
        {
            throw new BuildException("srcDir is required.");
        }  
        
        if(destDir == null)
        {
            throw new BuildException("destDir is required.");
        }
        

        if(jarFile == null)
        {
            throw new BuildException("jarFile is required.");
        }        
        
        if(mainClass == null)
        {
            throw new BuildException("mainClass is required.");
        }
        
        if(version == null)
        {
            version = "1.4";
        }
        
        echo.setProject(getProject());
        echo.setTaskName(projectName);
        echo.addText("Let's go...");
        
        echo.execute();
        
        clean();
        
        compile();
        
        try
        {
            pack();
        }
        catch (ManifestException e)
        {
            throw new BuildException(e.getMessage());
        }
        
        run();
    }
}
