// Dylan Mumm, 2150
// HW3
// April 3rd

package cpsc2150.homeworks.hw1;


/**
 * @invariant 0 <= row <= 7
 * @invariant 0 <= col <= 7
 */

public class BoardPosition {

    private int row;
    private int col;
    private char letter;

    /**
     * This constructor sets row, col, and character of position
     *
     * @param r     A row
     * @param c     A col
     * @param l     A letter

     *
     * @requires 0 <= r <= 7
     * @requires 0 <= c <= 7
     * @requires l a single char
     *
     * @ensures  row = r
     * @ensures  col = c
     * @ensures  letter = c
     *
     */
    BoardPosition(int r, int c, char l) {

        row = r;
        col = c;
        letter = l;

    }

    /**
     * Function returns the row
     *
     * @return  row
     * @ensures getRow() = row
     *
     */
    public int getRow() {
        return row;
    }

    /**
     * Function returns the column
     *
     * @return  column
     * @ensures getRow() = col
     *
     */
    public int getColumn() {
        return col;
    }

    /**
     * Function returns the player's character
     *
     * @return  player's character
     * @ensures getPlayer() = player's character
     *
     */
    public char getPlayer() {
        return letter;
    }

    /**
     * Function returns whether objects are equal
     *
     * @param       o  A board position
     * @requires    o != NULL, this != NULL
     * @ensures     this.equals(o) = whether this is equal to o
     * @return      true or false
     */
    @Override
    public boolean equals(Object o) {

        return (o instanceof BoardPosition) && (row == ((BoardPosition)o).getRow() &&
                col == ((BoardPosition)o).getColumn() && letter == ((BoardPosition)o).getPlayer());

    }


    /**
     * Function, when called on an instance, turns its data as a string
     *
     * @requires    this != NULL
     * @ensures     Instance's data will be returned as a string
     * @return      "Player [team letter] at position [row], [col]"  (linebreak)
     */
    @Override
    public String toString() {
        return "Player " + letter + " at position " + row + "," + col + "\n" ;
    }

}
