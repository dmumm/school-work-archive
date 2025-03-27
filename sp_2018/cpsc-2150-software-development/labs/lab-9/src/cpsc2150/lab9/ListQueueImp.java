//  Dylan Mumm
package cpsc2150.lab9;


import java.util.*;

/**
 *  Correspondence: this = myQ. The front of myQ is the front of the Queue
 *  Correspondence: size = myQ.size();
 *
 *  @invariant: 0 <= depth <= MAX_DEPTH
 */

public class ListQueueImp <T> implements IQueue <T> {

        private List<T> myQ;

        public ListQueueImp() {

            this.myQ = new ArrayList<>();

        }

        public void add(T x) {
            myQ.add(x);
        }

        public T pop() {
            T result = myQ.get(0);
            myQ.remove(0);
            return result;
        }

        public int size() {
            return myQ.size();
        }

        @Override
        public String toString() {

            StringBuilder str =  new StringBuilder("");

            for (int i = 0; i < size(); i++) {
                str.append(myQ.get(i));
                str.append("\n");
            }

            return str.toString();

    }

    }

