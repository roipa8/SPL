package bgu.spl.mics;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.concurrent.TimeUnit;

import static org.junit.Assert.*;

public class FutureTest {
    private Future<String> future;

    @Before
    public void setUp() throws Exception {
        future = new Future<>();
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void get() {
        assertFalse(future.isDone());
        future.resolve("foo");
        assertEquals(future.get(),"foo");
        assertTrue(future.isDone());

    }

    @Test
    public void resolve() {
        String str = "someResult";
        future.resolve(str);
        assertTrue(future.isDone());
        assertEquals(future.get(), str);
    }

    @Test
    public void isDone() {
        String str = "someResult";
        assertFalse(future.isDone());
        future.resolve(str);
        assertTrue(future.isDone());
    }

    @Test
    public void testGetWithTimeOut() throws InterruptedException {
        assertFalse(future.isDone());
        future.get(100, TimeUnit.MILLISECONDS);
        assertFalse(future.isDone());
        future.resolve("foo");
        assertEquals(future.get(100,TimeUnit.MILLISECONDS),"foo");
        assertTrue(future.isDone());
    }
}