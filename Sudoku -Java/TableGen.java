/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.Stack;

/**
 *
 * @author alien19766
 */
public class TableGen {

    private int[][] board;
    private int[][] notSolvedBoard;
    private Random rand;
    private int difficulty;

    public TableGen(int difficulty) {
        rand = new Random();
        notSolvedBoard = new int[9][9];
        setDifficulty(difficulty);
        setBoard();
        setNotSolvedBoard();
        
    }

    public TableGen() {
        this(0);
    }

    public void setDifficulty(int difficulty) {
        this.difficulty = difficulty;
    }

    public int[][] getNotSolvedBoard() {
        return notSolvedBoard;
    }

    public void setNotSolvedBoard() {
        generateNotSolved(difficulty);
    }

    public int[][] getBoard() {
        return board;
    }

    public void setBoard() {
        generator();
    }

    private void generator() {
        this.board = new int[9][9];
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                board[i][j] = 0;
            }
        }
        generate(0, 0);
    }
    
    private void generateNotSolved(int difficulty)
    {
        for (int i = 0; i < notSolvedBoard.length; i++) {
            for (int j = 0; j < notSolvedBoard[i].length; j++) {
                notSolvedBoard[i][j]= board[i][j];
            }
        }
        int x,y;
        for (int i = 0; i < difficulty;) {
            x=rand.nextInt(9);
            y=rand.nextInt(9);
            if(notSolvedBoard[x][y]==0)continue;
            else{
                notSolvedBoard[x][y]=0;
                i++;
            }
        }
    }

    public void printBoard() {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                System.out.printf("%d ", board[i][j]);
            }
            System.out.printf("%n");
        }
        System.out.printf("%n");
    }

    private boolean isSolved() {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
    private boolean generate(int i, int j) {
        if (isSolved()) {
            return true;
        }
        List<Integer> solution = new ArrayList<>();
        for (int z = 1; z <10; z++) {
            solution.add(z);
        }
        Collections.shuffle(solution);
        int k;
        while (!solution.isEmpty()) {
            k=solution.remove(0);
            if (checkRow(i, k) && checkCol(j, k) && inSegment(i, j, k)) {
                board[i][j] = k;
                if (j < 8) {
                    if (generate(i, j + 1)) {
                        return true;
                    } else {
                        board[i][j] = 0;
                    }
                } else {
                    if (generate(i + 1, 0)) {
                        return true;
                    } else {
                        board[i][j] = 0;
                    }
                }
            }
        }
        return false;
    }

    private boolean inSegment(int i, int j, int num) {
        int newi = i - i % 3;
        int newj = j - j % 3;
        if (i < 3 && i >= 0) {
            newi = 0;
        }
        if (j < 3 && j >= 0) {
            newj = 0;
        }

        int tempj = newj;
        for (int k = 0; k < 3; k++) {
            for (int l = 0; l < 3; l++) {
                if (board[newi][tempj++] == num) {
                    return false;
                }
            }
            newi++;
            tempj = newj;
        }
        return true;
    }

    private boolean checkRow(int i, int num) {
        for (int j = 0; j < board[i].length; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
        return true;
    }

    private boolean checkCol(int j, int num) {
        for (int i = 0; i < board.length; i++) {
            if (board[i][j] == num) {
                return false;
            }
        }
        return true;
    }
}
