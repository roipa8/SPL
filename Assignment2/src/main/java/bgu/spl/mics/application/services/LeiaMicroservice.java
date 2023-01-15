package bgu.spl.mics.application.services;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

import bgu.spl.mics.Event;
import bgu.spl.mics.Future;
import bgu.spl.mics.MessageBusImpl;
import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.AttackEvent;
import bgu.spl.mics.application.messages.BombDestroyerEvent;
import bgu.spl.mics.application.messages.DeactivationEvent;
import bgu.spl.mics.application.messages.TerminationBroadcast;
import bgu.spl.mics.application.passiveObjects.Attack;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Ewoks;

/**
 * LeiaMicroservices Initialized with Attack objects, and sends them as  {@link AttackEvent}.
 * This class may not hold references for objects which it is not responsible for:
 * {@link AttackEvent}.
 * <p>
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class LeiaMicroservice extends MicroService {
    private Attack[] attacks;
    private Diary diary;
    private ArrayList<Future<Boolean>> futureAttackList;
    private AtomicInteger numOfResolvedFutures;

    public LeiaMicroservice(Attack[] attacks) {
        super("Leia");
        this.attacks = attacks;
        diary=Diary.getInstance();
        futureAttackList=new ArrayList<>();
        numOfResolvedFutures=new AtomicInteger(0);
    }

    @Override
    protected void initialize() {
        subscribeBroadcast(TerminationBroadcast.class,(TerminationBroadcast terminationBroadcast) -> {
            terminate();
            diary.setLeiaTerminate(System.currentTimeMillis());
        });
        try {
            Thread.sleep(10); //To make sure that the other threads already registered and subscribed to their events
        } catch (InterruptedException e){}
        for (int i = 0; i < attacks.length; i++) {
            AttackEvent attackEvent = new AttackEvent(attacks[i].getDuration(), attacks[i].getSerials());
            Future <Boolean> future = sendEvent(attackEvent);
            futureAttackList.add(future);
        }
        boolean moveToDeactivation=false;
        //Checking if all the future attacks resolved
        while (!moveToDeactivation){
            if(futureAttackList.get(numOfResolvedFutures.intValue()).get()){
                numOfResolvedFutures.incrementAndGet();
            }
            if(numOfResolvedFutures.intValue()==futureAttackList.size()){
                moveToDeactivation=true;
            }
        }
        Future<Boolean> Deactivationfuture= sendEvent(new DeactivationEvent());
        if(Deactivationfuture.get()){
            sendEvent(new BombDestroyerEvent());
        }
    }






}
