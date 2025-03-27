// Dylan Mumm, 2151-004
// Lab 4
// February 16th

package cpsc2150.labs.lab4;

import org.junit.Test;
import static org.junit.Assert.*;

public class DirectionalSpeedsterTest {

    private final double EPSILON = .0001;

    @Test
    public void testConstructor()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        double expectedDistance = 0;
        double expectedTime = 0;
        double expectedNetDistance = 0;


        double foundDistance = ds.getTotalDistance();
        double foundNetDistance = ds.getNetDistance();
        double foundTime = ds.getTotalTime();

        assertEquals(foundDistance, expectedDistance, EPSILON);
        assertEquals(foundNetDistance, expectedNetDistance, EPSILON);
        assertEquals(foundTime, expectedTime, EPSILON);

    }

    @Test
    public void testAddTravel1()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // A fairly normal test case
        ds.addTravel(5, 5, 5);

        double expectedDistance = 7.0711;
        double expectedTime = 5;

        double foundDistance = ds.getTotalDistance();
        double foundTime = ds.getTotalTime();

        assertEquals(foundDistance, expectedDistance, EPSILON);
        assertEquals(foundTime, expectedTime, EPSILON);

    }

    @Test
    public void testAddTravel_1()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Larger values, and with a negative X
        ds.addTravel(-100, 250, 29);

        double expectedDistance = 269.2582;
        double expectedTime = 29;

        double foundDistance = ds.getTotalDistance();
        double foundTime = ds.getTotalTime();

        assertEquals(foundDistance, expectedDistance, EPSILON);
        assertEquals(foundTime, expectedTime, EPSILON);

    }


    @Test
    public void testAddTravel_2()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Larger values, and with a negative Y
        ds.addTravel(192, -512, 312);

        double expectedDistance = 546.8162;
        double expectedTime = 312;

        double foundDistance = ds.getTotalDistance();
        double foundTime = ds.getTotalTime();

        assertEquals(foundDistance, expectedDistance, EPSILON);
        assertEquals(foundTime, expectedTime, EPSILON);

    }

    @Test
    public void testAddTravel_3()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Decimals
        ds.addTravel(.420, 6.9, 1.01);

        double expectedDistance = 6.9128;
        double expectedTime = 1.01;

        double foundDistance = ds.getTotalDistance();
        double foundTime = ds.getTotalTime();

        assertEquals(foundDistance, expectedDistance, EPSILON);
        assertEquals(foundTime, expectedTime, EPSILON);

    }

    @Test
    public void testAddTravel_4()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Both negative
        ds.addTravel(-500, -500, 13);

        double expectedDistance = 707.1068;
        double expectedTime = 13;

        double foundDistance = ds.getTotalDistance();
        double foundTime = ds.getTotalTime();

        assertEquals(foundDistance, expectedDistance, EPSILON);
        assertEquals(foundTime, expectedTime, EPSILON);

    }

    @Test
    public void testAddTravel_5()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // All zeroes
        ds.addTravel(0, 0, 0);

        double expectedDistance = 0;
        double expectedTime = 0;

        double foundDistance = ds.getTotalDistance();
        double foundTime = ds.getTotalTime();

        assertEquals(foundDistance, expectedDistance, EPSILON);
        assertEquals(foundTime, expectedTime, EPSILON);

    }

    @Test
    public void testGetNetDistance_1()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // No change
        ds.addTravel(0, 0, 0);
        ds.addTravel(0, 0, 0);
        ds.addTravel(0, 0, 0);


        double expectedDistance = 0;
        double foundDistance = ds.getNetDistance();

        assertEquals(foundDistance, expectedDistance, EPSILON);

    }

    @Test
    public void testGetNetDistance_2()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Change, but reversion back
        ds.addTravel(0, 0, 0);
        ds.addTravel(500, 500, 500);
        ds.addTravel(-500, -500, 0);


        double expectedDistance = 0;
        double foundDistance = ds.getNetDistance();

        assertEquals(foundDistance, expectedDistance, EPSILON);

    }


    @Test
    public void testGetNetDistance_3()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Adds, subtracts, adds even more
        ds.addTravel(200, 600, 15);
        ds.addTravel(-100, -300, 500);
        ds.addTravel(200, 600, 12);


        double expectedDistance = 948.6833;
        double foundDistance = ds.getNetDistance();

        assertEquals(foundDistance, expectedDistance, EPSILON);

    }

    @Test
    public void testGetNetDistance_4()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Adds, subtracts into negatives
        ds.addTravel(200, 600, 15);
        ds.addTravel(-600, -1200, 500);


        double expectedDistance = 721.1103;
        double foundDistance = ds.getNetDistance();

        assertEquals(foundDistance, expectedDistance, EPSILON);

    }


    @Test
    public void testGetNetDistance_5()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Effectively swapping coordinates
        ds.addTravel(100, -100, 15);
        ds.addTravel(-200, 200, 500);


        double expectedDistance = 141.4214;
        double foundDistance = ds.getNetDistance();

        assertEquals(foundDistance, expectedDistance, EPSILON);

    }


    @Test
    public void testGetAverageVelocity_1()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // No change
        ds.addTravel(0, 0, 0);
        ds.addTravel(0, 0, 1);


        double expectedVelocity = 0;
        double foundVelocity = ds.getAverageVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }

    @Test
    public void testGetAverageVelocity_2()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Slow and then fast
        ds.addTravel(0, 0, 0);
        ds.addTravel(500, 500, 500);
        ds.addTravel(1000, 1000, 10);


        double expectedVelocity = 4.15945156863;
        double foundVelocity = ds.getAverageVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }


    @Test
    public void testGetAverageVelocity_3()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Quickly totalDistance, low netDistance
        ds.addTravel(500, 500, 15);
        ds.addTravel(-499, -500, 15);


        double expectedVelocity = 47.1168933333;
        double foundVelocity = ds.getAverageVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }

    @Test
    public void testGetAverageVelocity_4()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Extremely fast for tiny distance, slow for long distance
        ds.addTravel(5, 5, .00001);
        ds.addTravel(200, 200, 500);


        double expectedVelocity = 0.57982754897;
        double foundVelocity = ds.getAverageVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }


    @Test
    public void testGetAverageVelocity_5()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Constant velocity
        ds.addTravel(100, 100, 10);
        ds.addTravel(100, 100, 10);


        double expectedVelocity = 14.14213;
        double foundVelocity = ds.getAverageVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }

    @Test
    public void testGetNetVelocity_1()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // No change
        ds.addTravel(0, 0, 0);
        ds.addTravel(0, 0, 1);


        double expectedVelocity = 0;
        double foundVelocity = ds.getNetVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }

    @Test
    public void testGetNetVelocity_2()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Slow and then fast
        ds.addTravel(0, 0, 0);
        ds.addTravel(500, 500, 500);
        ds.addTravel(1000, 1000, 10);


        double expectedVelocity = 4.15945156863;
        double foundVelocity = ds.getNetVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }


    @Test
    public void testGetNetVelocity_3()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Quickly totalDistance, low netDistance
        ds.addTravel(500, 500, 15);
        ds.addTravel(-499, -500, 15);


        double expectedVelocity = 0.0333333333333;
        double foundVelocity = ds.getNetVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }

    @Test
    public void testGetNetVelocity_4()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Extremely fast for tiny distance, slow for long distance
        ds.addTravel(5, 5, .00001);
        ds.addTravel(200, 200, 500);


        double expectedVelocity = 0.57982754897;
        double foundVelocity = ds.getNetVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }


    @Test
    public void testGetNetVelocity_5()
    {

        DirectionalSpeedster ds = new DirectionalSpeedster();

        // Constant velocity
        ds.addTravel(100, 100, 10);
        ds.addTravel(100, 100, 10);


        double expectedVelocity = 14.14213;
        double foundVelocity = ds.getNetVelocity();

        assertEquals(foundVelocity, expectedVelocity, EPSILON);

    }


}
