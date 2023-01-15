package bgu.spl.mics;


import bgu.spl.mics.application.messages.testBroadcast;
import bgu.spl.mics.application.messages.testEvent;
import bgu.spl.mics.application.services.*;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class MessageBusImplTest {
    MessageBus messagebus;

    @Before
    public void setUp() throws Exception {
//        messagebus=new MessageBusImpl(); //We created the tests before the implementation that made the message-bus singleton
        messagebus=MessageBusImpl.getInstance();
    }

    @After
    public void tearDown() throws Exception {
        messagebus=null;
    }

    @Test
    public void subscribeEvent() {
    }

    //we c
    @Test
    public void subscribeBroadcast() {
    }

    @Test
    public void complete() throws InterruptedException {
        testEvent e=new testEvent(2);
        MicroService m1=new TestMicroService();
        MicroService m2=new TestMicroService();
        messagebus.register(m1);
        messagebus.register(m2);
        messagebus.subscribeEvent(testEvent.class,m2);
        Future<Integer> f=m1.sendEvent(e);
        testEvent msg=(testEvent) messagebus.awaitMessage(m2);
        messagebus.complete(msg,2);
        assertNotNull(f);
        int result=f.get();
        assertEquals(2,result);

    }

    /*
     We made a small change that the micro-services that will get the messages
     will be those you gave us because they have a name and the the test-event we created don't have names
     so we adjusted the test to our implementation that happened after we submitted the tests
     */
    @Test
    public void sendBroadcast() throws InterruptedException {
        testBroadcast e = new testBroadcast(2);
        //before the changes
//        TestMicroService m1 = new TestMicroService();
//        TestMicroService m2 = new TestMicroService();
//        TestMicroService m3=new TestMicroService();
        //
        HanSoloMicroservice m1=new HanSoloMicroservice();
        R2D2Microservice m2=new R2D2Microservice(1);
        LandoMicroservice m3=new LandoMicroservice(2);
        messagebus.register(m1);
        messagebus.register(m2);
        messagebus.register(m3);
        messagebus.subscribeBroadcast(testBroadcast.class,m2);
        messagebus.subscribeBroadcast(testBroadcast.class,m3);
        m1.sendBroadcast(e);
        testBroadcast msg1=(testBroadcast) messagebus.awaitMessage(m2);
        testBroadcast msg2=(testBroadcast) messagebus.awaitMessage(m3);
        assertEquals(e,msg1);
        assertEquals(e,msg2);
    }

    @Test
    public void sendEvent() throws InterruptedException {
        testEvent e = new testEvent(2);
        TestMicroService m1 = new TestMicroService();
        TestMicroService m2 = new TestMicroService();
        messagebus.register(m1);
        messagebus.register(m2);
        messagebus.subscribeEvent(testEvent.class,m2);
        Future<Integer> f = m1.sendEvent(e);
        testEvent msg =(testEvent) messagebus.awaitMessage(m2);
        assertEquals(msg,e);
    }

    @Test
    public void register() {
    }

    @Test
    public void unregister() {
    }

    @Test
    public void awaitMessage() throws InterruptedException {
        testEvent e = new testEvent(2);
        TestMicroService m1 = new TestMicroService();
        TestMicroService m2 = new TestMicroService();
        messagebus.register(m1);
        messagebus.register(m2);
        testEvent msg=null;
        m2.subscribeEvent(testEvent.class,null);
        try{
            m1.sendEvent(e);
            msg =(testEvent) messagebus.awaitMessage(m2);
        }
        catch (InterruptedException ex){}
        assertEquals(msg, e);
    }
}