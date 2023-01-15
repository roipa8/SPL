package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;

public class testEvent implements Event <Integer> {
    private int input;
    public testEvent(int input){
        this.input=input;
    }
}
