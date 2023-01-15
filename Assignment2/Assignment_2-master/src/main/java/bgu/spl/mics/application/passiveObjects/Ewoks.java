package bgu.spl.mics.application.passiveObjects;


import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Passive object representing the resource manager.
 * <p>
 * This class must be implemented as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add ONLY private methods and fields to this class.
 */

public class Ewoks {
    private Ewok[] EwoksArr;
    private AtomicInteger countOfTotalAttacks; // count the total numbers of attacks for the diary


    /////////////////////
    //We made it a thread-safe singleton in order that the number of ewoks and attacks in general will be accurate
    private static class SingletonHolder{
        private static Ewoks instance =new Ewoks();
    }
    private Ewoks(){
        countOfTotalAttacks=new AtomicInteger();
    }
    public static Ewoks getInstance(){
        return SingletonHolder.instance;
    }
    /////////////////////

    public void initialize(int ewoksSize){
        EwoksArr=new Ewok[ewoksSize];
        for(int i=0; i<ewoksSize; i++){
            EwoksArr[i]=new Ewok(i+1,true);
        }
    }


    public void getResources(List<Integer> list) throws InterruptedException {
        Collections.sort(list); //Sort the list in order to avoid deadlocks
        for(int i = 0;i<list.size();i++){
            EwoksArr[list.get(i)-1].acquire();
        }
        countOfTotalAttacks.incrementAndGet();
    }

    public AtomicInteger getCountofTotalAttacks(){ // return the total number of attacks for the diary
        return countOfTotalAttacks;
    }

    public void releaseResources(List<Integer> list){
        for(int i=0; i<list.size(); i++){
            EwoksArr[list.get(i)-1].release();
        }

    }



}
