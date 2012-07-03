package fr.isima.grille;

import org.apache.commons.cli.*;
import org.ogf.saga.context.Context;
import org.ogf.saga.error.*;
import org.ogf.saga.monitoring.*;
import org.ogf.saga.namespace.*;
import org.ogf.saga.session.Session;
import org.ogf.saga.session.SessionFactory;
import org.ogf.saga.task.Task;
import org.ogf.saga.task.TaskMode;
import org.ogf.saga.url.URL;
import org.ogf.saga.url.URLFactory;

/* ***************************************************
 * *** Centre de Calcul de l'IN2P3 - Lyon (France) ***
 * ***             http://cc.in2p3.fr/             ***
 * ***************************************************
 * File:   NamespaceCopy
 * Author: Sylvain Reynaud (sreynaud@in2p3.fr)
 * Date:   12 sept. 2007
 * ***************************************************
 * Description:                                      */
/**
 *
 */
public class NamespaceCopy {
	private static final String OPT_HELP = "h", LONGOPT_HELP = "help";
	private static final String OPT_NOT_OVERWRITE = "i", LONGOPT_NOT_OVERWRITE = "interactive";
	private static final String OPT_RECURSIVE = "r", LONGOPT_RECURSIVE = "recursive";
	private static final String OPT_PRESERVE_TIMES = "p", LONGOPT_PRESERVE_TIMES = "preserve";
	private static final String OPT_MONITOR = "m", LONGOPT_MONITOR = "monitor";

	private static final int FLAGS_PRESERVETIMES = 8192;


	public void copy(String inSource, String inTarget) throws Exception {
		// get arguments
		URL source = URLFactory.createURL(inSource);
		URL target = URLFactory.createURL(inTarget);

		// execute command
		Session session = SessionFactory.createSession(true);
		NSEntry entry = NSFactory.createNSEntry(session, source, Flags.NONE.getValue());

		Task task = entry.copy(TaskMode.TASK, target);
		try {
			Metric metric = task.getMetric("file.copy.progress");
			metric.addCallback(new Callback(){
					public boolean cb(Monitorable mt, Metric metric, Context ctx) throws NotImplementedException, AuthorizationFailedException {
					try {
					String value = metric.getAttribute(Metric.VALUE);
					String unit = metric.getAttribute(Metric.UNIT);
					System.out.println("Progress: "+value+" "+unit);
					}
					catch (NotImplementedException e) {throw e;}
					catch (AuthorizationFailedException e) {throw e;}
					catch (Exception e) {
					e.printStackTrace();
					}
					// callback must stay registered
					return true;
					}
					});
		} catch(DoesNotExistException e) {
			System.err.println("WARN: Monitoring is not supported for this kind of transfer");
		}
		task.run();
		task.waitFor();
		switch(task.getState()) {
			case DONE:
				System.out.println("File successfully copied !");
				break;
			default:
				task.rethrow();
				break;
		}
		entry.close();
	}
}

