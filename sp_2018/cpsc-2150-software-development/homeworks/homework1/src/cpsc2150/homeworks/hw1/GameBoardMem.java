// Dylan Mumm, 2150
// HW3
// April 3rd

package cpsc2150.homeworks.hw1;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @invariant Rows and Columns = 8
 * @invariant board[][] always row * column
 * @invariant board contents always ' ', or player marker
 * Correspondence number_of_rows = rows
 * Correspondence number_of_columns = cols
 * Correspondence this = myGrid[0...numRow-1][0...numCol-1]
 */

public class GameBoardMem implements IGameBoard {

    private  int rows;
    private  int cols;
    private  int toWin;

    private HashMap<Character, List<BoardPosition>> board;

    /**
     * This constructor initializes board with blank spaces
     *
     * @param  r = number of rows for play space
     * @param  c = number of column for play space
     * @param  w = number of spaces in a row necessary for win
     * @requires 0 < rows  <= MAX_SIZE
     * @requires 0 < cols  <= MAX_SIZE
     * @requires 0 < toWin <= rows
     * @requires 0 < toWin <= cols
     * @ensures  All chars in board[][] = ' '
     *
     */
    public GameBoardMem(int r, int c, int w){

        // Initializing board as blank spaces
        board = new HashMap<>(); /*
        for(int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                board[i][j] = ' ';
            }
        } */

        rows = r;
        cols = c;
        toWin = w;

    }

    /* Returns true if the position specified in pos is available, false otherwise */
    public boolean checkSpace(BoardPosition pos) {

        if(pos.getRow() > rows || pos.getRow() < 0 || pos.getColumn() > cols || pos.getColumn() < 0)
            return false;

        for(Map.Entry m: board.entrySet()) {
            if(board.get(m).contains(pos))
                return false;
        }

        return true;

    }

    /* Places the character in marker on the position specified by marker */
    public void placeMarker(BoardPosition lastPos) {
        board.get(lastPos.getPlayer()).add(lastPos);
    }

    /* Checks if inputted board position results in win */
    public boolean checkForWinner(BoardPosition lastPos) {
        return (checkHorizontalWin(lastPos) || checkVerticalWin(lastPos) || checkDiagonalWin(lastPos));
    }


    /* Checks if board has draw */
    public boolean checkForDraw() {

        // Sees if any blank spaces remain
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                BoardPosition t = new BoardPosition(i, j, 'T');
                if(checkSpace(t))
                    return false;

            }
        }
        return true;
    }


    /**
     * code to see if the player c is at row r and column c. Return true if they are
     *
     * @ensures isPlayerAt() = Whether player at coordinate
     * @return true or false
     */
    private boolean isPlayerAt(int r, int c, char p){

        BoardPosition t = new BoardPosition(r, c, p);
        if(board.get(p).contains(t)) {
            return true;
        }

        return false;


    }

    /**
     * Checks if last position caused a horizontal win
     *
     * @ensures checkHorizontalWin() = Whether move caused  horizontal win
     * @requires lastPos's letter not null
     * @return true or false
     */
    private boolean checkHorizontalWin(BoardPosition lastPos) {

        // Looks at inputted column, checks if there is 5 straight on it

        int count = 0;
        for (int j = 0; j < cols; j++) {
            if (isPlayerAt(lastPos.getRow(), j, lastPos.getPlayer())) {
                count++;
                if (count == toWin)
                    return true;
            } else
                count = 0;
        }
        return false;
    }

    /**
     * Checks if last position caused a vertical win
     *
     * @ensures checkVerticalWin() = Whether move caused a vertical win
     * @requires lastPos's letter not null
     * @return true or false
     */
    private boolean checkVerticalWin(BoardPosition lastPos) {

        // Looks at inputted row, checks if there is 5 straight on it

        int count = 0;
        for (int i = 0; i < rows; i++) {
            if (isPlayerAt(i, lastPos.getColumn(), lastPos.getPlayer())) {
                count++;
                if (count == toWin)
                    return true;
            } else
                count = 0;
        }
        return false;
    }


    /**
     * Checks if last position caused a vertical win
     *
     * @ensures checkDiagonalWin() = Whether move caused a vertical win
     * @requires lastPos's row and column >= 0 and < 8
     * @requires lastPos's letter not null
     * @return true or false
     */
    private boolean checkDiagonalWin(BoardPosition lastPos) {

        int count = 0;
        int rowIndex, colIndex;



        // Checking if there is 5 in a row on back slash

        count = 0;
        rowIndex = lastPos.getRow();
        colIndex = lastPos.getColumn();
        while (rowIndex > 0 && colIndex > 0) {
            rowIndex--;
            colIndex--;
        }


        for (int i = rowIndex, j = colIndex; i < rows && j < cols; i++, j++) {
            if (isPlayerAt(i, j, lastPos.getPlayer())) {
                count++;
                if (count == toWin)
                    return true;
            } else
                count = 0;
        }

        // Checking if there is 5 in a row on forward slash

        count = 0;
        rowIndex = lastPos.getRow();
        colIndex = lastPos.getColumn();
        while (rowIndex > 0 && colIndex < 7) {
            rowIndex--;
            colIndex++;
        }


        for (int i = rowIndex, j = colIndex; i < rows && j >= 0; i++, j--) {
            if (isPlayerAt(i, j, lastPos.getPlayer())) {
                count++;
                if (count == toWin)
                    return true;
            } else
                count = 0;
        }

        return false;

    }

    /**
     * Function returns whether objects are equal
     *
     * @return  true or false
     * @ensures this.equals(o) = whether this is equal to o
     *
     */
    @Override
    public boolean equals(Object o) {

        if (o instanceof GameBoardMem) {
            return board.entrySet().equals(((GameBoardMem) o).board.entrySet());
        }
        return false;
    }

    /**
     * Function, when called on an instance, turns its data as a string
     *
     * @requires    this != NULL
     * @ensures     Instance's data will be returned as a string
     * @return      Game board printed out with row and column markers
     */
    @Override
    public String toString() {
        StringBuilder str =  new StringBuilder("   ");
        for (int i = 0; i < cols; i++) {
            if (i > 9) {
                str.append(i);
                str.append("|");
            } else {
                str.append(" ");
                str.append(i);
                str.append("|");
            }
        }
        str.append("\n");
        for (int i = 0; i < rows; i++) {
            if (i > 9) {
                str.append(i);
                str.append("|");
            } else {
                str.append(" ");
                str.append(i);
                str.append("|");
            }

            for (int j = 0; j < cols; j++) {
                str.append(" ");
                for(Map.Entry m: board.entrySet()) {
                    if(checkSpace())

                }
                str.append("|");
            }
            str.append("\n");
        }
        return str.toString();
    }}

