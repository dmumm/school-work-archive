// Dylan Mumm, 2150
// HW3
// April 3rd

package cpsc2150.homeworks.hw1;

/**
 *
 *  IGameBoard represents a 2-dimensional gameboard that has characters
 *  on it as markers. No space on the board can have multiple
 *  players, and there can be a clear winner. Board is NUM_ROWS x NUM_COLS in size.
 *  Indexing of the gameboard starts in the top left corner with 0,0 and goes to NUM_ROWS-1, NUM_COLS-1.
 *
 *  Initialization ensures: the Board does not have any markers on it
 *  Defines: NUM_ROWS: Z
 *  Defines: NUM_COLS: Z
 *  Constraints: 0< NUM_ROWS <= MAX_SIZE
 *  0< NUM_COLS <= MAX_SIZE
 *
 */
public interface IGameBoard {

    int MAX_SIZE = 100;


    /**
     * Returns true if the position specified in pos is available, false otherwise
     *
     * @param pos:   A board position
     * @requires    pos's row and column >= 0 and < MAX_SIZE
     * @ensures     checkSpace() = whether position is occupied
     * @return      true or false
     *
     */
    boolean checkSpace(BoardPosition pos);

    /**
     * places the character in marker on the position specified by marker
     *
     * @param lastPos:  A board position
     * @requires        board position's row and column >= 0 and < MAX_SIZE
     * @ensures         gameboard updated with inputted board position
     *
     */
    void placeMarker(BoardPosition lastPos);

    /**
     * Checks if inputted board position results in win
     *
     * @param lastPos: A board position
     * @requires       lastPos's row and column >= 0 and < 8
     * @requires       lastPos's letter not null
     * @ensures        checkForWinner() = whether a move won game
     * @returns        true or false
     *
     */
    boolean checkForWinner(BoardPosition lastPos);

    /**
     * Checks if board has draw
     *
     * @ensures checkForDraw() = Whether board has draw
     * @return  true or false
     */
    boolean checkForDraw();

}