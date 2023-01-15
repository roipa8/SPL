package bgu.spl.mics.application;
import bgu.spl.mics.Message;
import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.AttackEvent;
import bgu.spl.mics.application.passiveObjects.*;
import bgu.spl.mics.application.services.*;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;


/** This is the Main class of the application. You should parse the input file,
 * create the different components of the application, and run the system.
 * In the end, you should output a JSON.
 */
public class Main {
	public static void main(String[] args) throws IOException {
//		System.out.println("a");
		Diary diary=Diary.getInstance();
		try{
//			String input=args[0];
			String input="C:/Studies/Semester3/SPL/Assignment2/src/main/java/bgu/spl/mics/application/input.json";
//			String tests="C:/Studies/Semester3/SPL/Assignment2/Tests.json";
			Input json = JsonInputReader.getInputFromJson(input);
			Ewoks ewoks=Ewoks.getInstance();
			ewoks.initialize(json.getEwoks());
			Runnable leia=new LeiaMicroservice(json.getAttacks());
			Thread tLeia=new Thread(leia);
			Runnable hanSolo=new HanSoloMicroservice();
			Thread tHanSolo=new Thread(hanSolo);
			Runnable c3po=new C3POMicroservice();
			Thread tC3po=new Thread(c3po);
			Runnable r2d2=new R2D2Microservice(json.getR2D2());
			Thread tR2d2=new Thread(r2d2);
			Runnable lando=new LandoMicroservice(json.getLando());
			Thread tLando=new Thread(lando);
			tLeia.start();
			tHanSolo.start();
			tC3po.start();
			tR2d2.start();
			tLando.start();
			try {
				tLeia.join();
				tHanSolo.join();
				tC3po.join();
				tR2d2.join();
				tLando.join();
			}catch (InterruptedException e){}
		} catch (IOException e){}
//		String output = args[1];
		String output=("C:/Studies/Semester3/SPL/Assignment2/src/main/java/bgu/spl/mics/application/output.json");
		Gson gson=new GsonBuilder().setPrettyPrinting().create();
		FileWriter writer=new FileWriter(output);
		gson.toJson(diary,writer);
		writer.flush();
		writer.close();
	}
}
