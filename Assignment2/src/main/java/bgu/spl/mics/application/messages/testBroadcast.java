package bgu.spl.mics.application.messages;

import bgu.spl.mics.Broadcast;

public class testBroadcast implements Broadcast {
    private int input;
    public testBroadcast(int input){
        this.input=input;
    }
}
