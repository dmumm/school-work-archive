//  Dylan Mumm

package cpsc2150.lab9;

/**
 * A queue containing T.
 * A queue is a data structure where the first item added to the structure
 * is the first item removed from the structure
 *
 * This queue is bounded by MAX_DEPTH
 *
 *  Initialization ensures the queue is empty
 *  Defines: size:Z
 *  Constraints: 0 <= size <= MAX_DEPTH
 */

public interface IQueue <T> {

    int MAX_DEPTH = 100;

    /**
     * Adds x to the end of the Queue
     *
     * @param x     T to be added to end of queue
     * @requires    x be an T
     * @ensures     x is added to end of queue
     *
     */
     void add(T x);

    /**
     * removes and returns the T at the front of the queue
     *
     * @ensures T at front of queue is returned and removed
     * @returns T at front of queue
     *
     */
    T pop();

    /**
     * returns the number of T in the Queue
     *
     * @ensures size() = number of T in the queue
     * @returns number of T in the queue
     *
     */
     int size();

     default T peek() {
         String[] lines = toString().split(System.getProperty("line.separator"));
         if(size() > 0)
            return  (T)lines[0];
         else
             return null;
     }

     default T endOfQueue() {
         String[] lines = toString().split(System.getProperty("line.separator"));
         if(size() > 0)
             return  (T)lines[size()];
         else
             return null;
     }

     default void insert(T x, int pos) {

         String[] lines = toString().split(System.getProperty("line.separator"));
         for(int i = 0; i < size(); i++) {
             pop();
         }

         for(int i = 0; i < pos; i++) {
             add((T)lines[i]);
         }

         add(x);

         for(int i = pos; i < size(); i++) {
             add((T)lines[i]);
         }


     }

     default T remove(int pos) {

         String[] lines = toString().split(System.getProperty("line.separator"));
         T result = null;

         for(int i = 0; i < size(); i++) {
             if(i == pos)
                 result = pop();
             else
                 pop();
         }

         for(int i = 0; i < pos; i++) {
             add((T)lines[i]);
         }

         for(int i = pos+1; i < size(); i++) {
             add((T)lines[i]);
         }

         return result;

     }

    default T get(int pos) {

        String[] lines = toString().split(System.getProperty("line.separator"));
        T result = null;

        for(int i = 1; i < size()+1; i++) {
            if(i == pos)
                result = pop();
            else
                pop();
        }

        for(int i = 0; i < pos; i++) {
            add((T)lines[i]);
        }

        for(int i = pos+1; i < size()-1; i++) {
            add((T)lines[i]);
        }

        return result;

    }

}
