package bgu.spl.mics.application.passiveObjects;

/**
 * Passive data-object representing a forest creature summoned when HanSolo and C3PO receive AttackEvents.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You may add fields and methods to this class as you see fit (including public methods).
 */
public class Ewok {
    private int serialNumber;
    boolean available;

    public Ewok(int serialNumber, boolean available){
        this.serialNumber=serialNumber;
        this.available=available;
    }
    /**
     * Acquires an Ewok
     */
    public synchronized void acquire(){
        while (!isAvailable()){
            try{
                wait();
            } catch (InterruptedException e){}
        }
        available=false;
    }

    public boolean isAvailable(){
        return available;
    }

    /**
     * release an Ewok
     */
    public synchronized void release() {
        notifyAll();
        available=true;
    }
}
