package bgu.spl.mics.application.messages;
import bgu.spl.mics.Event;
import bgu.spl.mics.Future;

import java.util.List;

public class AttackEvent implements Event<Boolean> {
	private int duration;
	private List<Integer> serial;
	public AttackEvent(int duration,List<Integer> serial){
	    this.duration = duration;
	    this.serial = serial;
    }
	public int getDuration() {
		return duration;
	}
	public List<Integer> getSerials(){
		return serial;
	}
}
