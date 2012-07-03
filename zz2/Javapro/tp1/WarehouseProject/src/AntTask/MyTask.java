package AntTask;

import java.io.File;


import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.Task;
import org.apache.tools.ant.taskdefs.Delete;
import org.apache.tools.ant.taskdefs.Jar;
import org.apache.tools.ant.taskdefs.Javac;
import org.apache.tools.ant.taskdefs.ManifestException;
import org.apache.tools.ant.taskdefs.Mkdir;
import org.apache.tools.ant.taskdefs.Java;
import org.apache.tools.ant.taskdefs.Manifest;
import org.apache.tools.ant.taskdefs.Manifest.Attribute;
import org.apache.tools.ant.types.Path;


public class MyTask extends Task
{
	private String src;
    private String dest;
    private String jarFile;
    private String mainClass;
    private String vers;
    
    public void setSrc(String src) {
		this.src = src;
	}

	public void setDest(String dest) {
		this.dest = dest;
	}

	public void setJarFile(String jarFile) {
		this.jarFile = jarFile;
	}

	public void setMainClass(String mainClass) {
		this.mainClass = mainClass;
	}

	public void setVers(String vers) {
		this.vers = vers;
	}
    
	public void clean()
	{
		
		Delete del = new Delete();
		del.setProject(getProject());
		del.setDir(new File(dest));
		del.execute();
	}
	
	public void init()
	{
		Mkdir mkdir = new Mkdir();
		mkdir.setProject(getProject());
		mkdir.setDir(new File(dest));
		mkdir.execute();
	}
	
	public void compile()
	{
		Javac compiler = new Javac();
		compiler.setProject(getProject());
		compiler.setSource(vers);
		compiler.setSrcdir(new Path(getProject(), src));
		compiler.setDestdir(new File(dest));
		compiler.execute();
	}
	
	public void dist() throws ManifestException
	{
		Mkdir mkdir = new Mkdir();
		mkdir.setDir(new File("dist/lib"));
		mkdir.execute();
		Jar archiv = new Jar();
		archiv.setProject(getProject());
		archiv.setBasedir(new File("build"));
		archiv.setDestFile(new File(jarFile));
		
		Manifest manif = new Manifest();
		Attribute attr = new Attribute();
		attr.setName("Main-Class");
		attr.setValue(mainClass);
		manif.addConfiguredAttribute(attr);
		archiv.addConfiguredManifest(manif);
		
		archiv.execute();
	}
	
	public void run()	
	{
		Java machine = new Java();
		machine.setProject(getProject());
		machine.setJar(new File(jarFile));
		machine.setFork(true);
		machine.execute();
		
	}
	
	public void execute()
	{
		clean();
		/*
		init();
		compile();
		
		try {
			dist();
		} catch (ManifestException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		run();*/
	}
}