package bgu.spl.mics.application.services;


import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.AttackEvent;
import bgu.spl.mics.application.messages.TerminationBroadcast;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Ewok;
import bgu.spl.mics.application.passiveObjects.Ewoks;

///**
// * HanSoloMicroservices is in charge of the handling {@link AttackEvents}.
// * This class may not hold references for objects which it is not responsible for:
// * {@link AttackEvents}.
// *
// * You can add private fields and public methods to this class.
// * You MAY change constructor signatures and even add new public constructors.
// */
public class HanSoloMicroservice extends MicroService {
    private Diary diary;
    private Ewoks ewoks;

    public HanSoloMicroservice() {
        super("Han");
        diary=Diary.getInstance();
        ewoks=Ewoks.getInstance();
    }


    @Override
    protected void initialize() {
        subscribeEvent(AttackEvent.class, (AttackEvent event)->{
            ewoks.getResources(event.getSerials());
            Thread.sleep(event.getDuration());
            complete(event, true);
            diary.setHanSoloFinish(System.currentTimeMillis());
            ewoks.releaseResources(event.getSerials());

        });
        subscribeBroadcast(TerminationBroadcast.class,(TerminationBroadcast terminationBroadcast) -> {
            terminate();
            diary.setTotalAttacks(ewoks.getCountofTotalAttacks());
            diary.setHanSoloTerminate(System.currentTimeMillis());
        });
    }




}
