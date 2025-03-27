// Dylan Mumm, 2151-004
// Lab 4
// February 16th

package cpsc2150.labs.lab4;

/**
 * @invariant totalDistance >= 0
 * @invariant netX >= 0 && netX >= 0
 * @invariant totalTime >= 0
 */

public class DirectionalSpeedster {

    private double totalDistance;
    private double netX;
    private double netY;
    private double totalTime;

    /**
     * This constructor sets the total distance, net travelled on both axes, and total time travelled, all to 0
     *
     * @ensures          totalDistance = 0;
     * @ensures          netX = 0;
     * @ensures          netY = 0;
     * @ensures          totalTime = 0;
     *
     */
    DirectionalSpeedster() {
        totalDistance = 0;
        netX = 0;
        netY = 0;
        totalTime = 0;
    }

    /**
     * This method takes in the change in x and y position and the time taken to complete the travel.
     *
     * @param  xChange   Change in speedster's x coordinate
     * @param  yChange   Change in speedster's y coordinate
     * @param  time      Time it takes for speedster to move to new location
     *
     * @requires   time > 0
     * @ensures    totalDistance incremented by changes in parameter
     * @ensures    netDistance also recorded
     * @ensures    totalTime incremented by parameter
     */
    public void addTravel(double xChange, double yChange, double time) {


        totalDistance += Math.sqrt(Math.pow(((xChange + netX) - netX),2)+(Math.pow(((yChange + netY) - netY),2)));
        netX += xChange;
        netY += yChange;
        totalTime += time;

    }

    /**
     * This method returns the total distance travelled.
     *
     * @return  total distance travelled
     * @ensures getTotalDistance() = total distance travelled
     *
     */
    public double getTotalDistance() {
        return totalDistance;
    }

    /**
     *  This method returns the total time elapsed during travel.
     *
     * @return  Total time elapsed during travel
     * @ensures getTotalTime() = Total time elapsed during travel
     *
     */
    public double getTotalTime() {
        return totalTime;
    }

    /**
     *  This method returns the net distance travelled.
     *
     * @return  Net distance travelled.
     * @ensures getNetDistance() = Net distance travelled.
     *
     */
    public double getNetDistance() {
        return Math.sqrt(Math.pow(netX,2) + Math.pow(netY,2));
    }


    /**
     *  This method returns the average velocity of all travel.
     *
     * @return  the average velocity of all travel.
     * @ensures getAverageVelocity() = the average velocity of all travel.
     *
     */
    public double getAverageVelocity() {
        return (totalDistance / totalTime);
    }


    /**
     *  This method returns the average velocity of all travel.
     *
     * @return  This method returns the net velocity for all travel.
     * @ensures getNetVelocity() = average velocity of all travel.
     *
     */
    public double getNetVelocity() {
        return (Math.sqrt(Math.pow(netX,2) + Math.pow(netY,2)) / totalTime);
    }

}
