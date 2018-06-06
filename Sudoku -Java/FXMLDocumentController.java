/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URL;
import java.rmi.RemoteException;
import java.util.ResourceBundle;
import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;

/**
 *
 * @author alien19766
 */
public class FXMLDocumentController implements Initializable {

    private TableGen sudoku;
    private TextField[][] board;
    private String filename = "results.txt";
    private FileReader fileread;
    private FileWriter filewrite;
    private int seconds = 0;
    private int minutes = 0;
    private String textTime;
    private Timer timer;
    private TimerTask task;
    @FXML
    private Label result5;
    @FXML
    private Label result4;

    @FXML
    private Label result3;

    @FXML
    private Label result2;

    @FXML
    private Label result1;
    @FXML
    private Label time;

    @FXML
    private Button start;

    @FXML
    private VBox gamesPlayed;

    @FXML
    private Button pause;

    @FXML
    private Button solve;

    @FXML
    private GridPane puzzel;

    @FXML
    private RadioButton medium;

    @FXML
    private RadioButton hard;

    @FXML
    private RadioButton easy;

    @FXML
    void setEasy(ActionEvent event) {
        if (hard.isSelected()) {
            hard.setSelected(false);
        }
        if (medium.isSelected()) {
            medium.setSelected(false);
        }
        easy.setSelected(true);
    }

    @FXML
    void setMedium(ActionEvent event) {
        if (easy.isSelected()) {
            easy.setSelected(false);
        }
        if (hard.isSelected()) {
            hard.setSelected(false);
        }
        medium.setSelected(true);
    }

    @FXML
    void setHard(ActionEvent event) {
        if (easy.isSelected()) {
            easy.setSelected(false);
        }
        if (medium.isSelected()) {
            medium.setSelected(false);
        }
        hard.setSelected(true);
    }

    @FXML
    private void handleButtonAction(ActionEvent event) throws RemoteException {
        if (textTime != null) {
            try {
                saveFile();
            } catch (IOException ex) {
                Logger.getLogger(FXMLDocumentController.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        try {
            loadFile();
        } catch (FileNotFoundException ex) {
            System.out.println("Unable to open file");
        } catch (IOException ex) {
            Logger.getLogger(FXMLDocumentController.class.getName()).log(Level.SEVERE, null, ex);
        }
        puzzel.disableProperty().set(false);
        start.disableProperty().set(true);
        pause.disableProperty().set(false);
        solve.disableProperty().set(false);
        board = new TextField[9][9];
        puzzel.getChildren().clear();
        puzzel.setStyle("-fx-border-style: solid inside;"
                + "-fx-border-width: 2;"
                + "-fx-border-insets: 0;"
                + "-fx-border-color: black;");
        int difficulty = 0;
        if (easy.isSelected()) {
            difficulty = 20;
        } else if (medium.isSelected()) {
            difficulty = 30;
        } else if (hard.isSelected()) {
            difficulty = 41;
        }
        sudoku = new TableGen(difficulty);
        int[][] a = sudoku.getNotSolvedBoard();
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[i].length; j++) {
                if (a[i][j] == 0) {
                    setDesignTextFields(a, i, j, a[i][j]);
                    puzzel.add(board[i][j], j, i);
                } else {
                    setDesignTextFields(a, i, j, a[i][j]);
                    puzzel.add(board[i][j], j, i);
                }
            }
        }
        seconds = 0;
        minutes = 0;
        if(timer!=null)timer.cancel();
        timer = new Timer();
        task = new TimerTask() {
            @Override
            public void run() {
                seconds++;
                if (seconds == 60) {
                    minutes++;
                    seconds = 0;
                }
                if (minutes < 10) {
                    if (seconds < 10) {
                        textTime = String.format("%d%d:%d%d", 0, minutes, 0, seconds);
                    } else {
                        textTime = String.format("%d%d:%d", 0, minutes, seconds);
                    }
                } else {
                    if (seconds < 10) {
                        textTime = String.format("%d:%d%d", minutes, 0, seconds);
                    } else {
                        textTime = String.format("%d:%d", minutes, seconds);
                    }
                }

                Platform.runLater(() -> time.setText(textTime));
            }

        };
        timer.scheduleAtFixedRate(task, 1000, 1000);
    }

    private void setCssField(int i, int j, String background) {
        if (i % 3 == 0 && j % 3 == 0 && i != 0 && j != 0) {
            board[i][j].setStyle("-fx-border-insets: 0;"
                    + "-fx-border-width: 2px;"
                    + "-fx-border-color: black lightgray lightgray black;"
                    + background);
        } else if (i % 3 == 0 && i != 0) {
            board[i][j].setStyle("-fx-border-insets: 0;"
                    + "-fx-border-width: 2px;"
                    + "-fx-border-color: black lightgray lightgray lightgray;"
                    + background);
        } else if (j % 3 == 0 && j != 0) {
            board[i][j].setStyle("-fx-border-insets: 0;"
                    + "-fx-border-width: 2px;"
                    + "-fx-border-color: lightgray lightgray lightgray black;"
                    + background);
        } else {
            board[i][j].setStyle("-fx-border-insets: 0;"
                    + "-fx-border-width: 2px;"
                    + "-fx-border-color: lightgray lightgray lightgray lightgray;"
                    + background);
        }
    }

    private void setDesignTextFields(int[][] a, int i, int j, int empty) {
        String background;
        if (empty == 0) {
            background = "-fx-control-inner-background: #f5f5ef";
            board[i][j] = new TextField("");
            board[i][j].setEditable(true);
            final int i1 = i;
            final int j1 = j;
            board[i][j].focusedProperty().addListener((observable, oldValue, newValue) -> {
                if (!newValue) {
                    if (!board[i1][j1].getText().matches("[1-9]")) {
                        board[i1][j1].setText("");
                    }
                }
            });
        } else {
            background = "";
            board[i][j] = new TextField(a[i][j] + "");
            board[i][j].setEditable(false);
        }
        board[i][j].setAlignment(Pos.CENTER);
        board[i][j].fontProperty().set(Font.font(17));
        board[i][j].setPrefSize(40, 40);
        setCssField(i, j, background);
    }

    private boolean isSolved() {
        int[][] a = sudoku.getBoard();
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[i].length; j++) {
                if (board[i][j].getText().equals("")) {
                    return false;
                } else if (a[i][j] != (Integer.parseInt(board[i][j].getText()))) {
                    return false;
                }
            }
        }
        return true;
    }

    private void setNotSolved() {
        int[][] a = sudoku.getBoard();
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[i].length; j++) {
                if (board[i][j].getText().equals("")) {
                    setCssField(i, j, "-fx-control-inner-background: #f5f5ef");
                    //board[i][j].setStyle("-fx-control-inner-background: #B22222");
                } else if (a[i][j] != (Integer.parseInt(board[i][j].getText()))) {
                    setCssField(i, j, "-fx-control-inner-background: #ff9980");
                    //board[i][j].setStyle("-fx-control-inner-background: #B22222");
                } else {
                    if (board[i][j].isEditable()) {//ako e vqrno populneno
                        setCssField(i, j, "-fx-control-inner-background: #ddff99");
                    }
                }
            }
        }
    }

    @FXML
    private void solve(ActionEvent event) throws IOException {
        if (isSolved()) {
            saveFile();
            Alert alert = new Alert(AlertType.INFORMATION);
            alert.setTitle("Sudoku Game");
            alert.setHeaderText(null);
            alert.setContentText("Congratulations! You solved the puzzel");
            alert.showAndWait();
            textTime=null;
            handleButtonAction(event);
        } else {
            setNotSolved();
            Alert alert = new Alert(AlertType.ERROR);
            alert.setTitle("Sudoku Game");
            alert.setHeaderText(null);
            alert.setContentText("Your puzzel is wrong!");
            alert.showAndWait();
        }
    }

    @FXML
    void start(ActionEvent event) {
        pause.disableProperty().set(false);
        solve.disableProperty().set(false);
        start.disableProperty().set(true);
        puzzel.disableProperty().set(false);
        timer = new Timer();
        task = new TimerTask() {
            @Override
            public void run() {
                seconds++;
                if (seconds == 60) {
                    minutes++;
                    seconds = 0;
                }
                if (minutes < 10) {
                    if (seconds < 10) {
                        textTime = String.format("%d%d:%d%d", 0, minutes, 0, seconds);
                    } else {
                        textTime = String.format("%d%d:%d", 0, minutes, seconds);
                    }
                } else {
                    if (seconds < 10) {
                        textTime = String.format("%d:%d%d", minutes, 0, seconds);
                    } else {
                        textTime = String.format("%d:%d", minutes, seconds);
                    }
                }

                Platform.runLater(() -> time.setText(textTime));
            }

        };
        timer.scheduleAtFixedRate(task, 1000, 1000);
    }

    @FXML
    void pause(ActionEvent event) throws InterruptedException {
        pause.disableProperty().set(true);
        solve.disableProperty().set(true);
        start.disableProperty().set(false);
        puzzel.disableProperty().set(true);
        timer.cancel();
    }

    @FXML
    private void exit(ActionEvent event) {
        Platform.exit();
        System.exit(0);
    }

    private void clearResults() {
        result1.setText("");
        result2.setText("");
        result3.setText("");
        result4.setText("");
        result5.setText("");
    }

    private String progress() {
        int[][] a = sudoku.getBoard();
        int cntEditable = 0;
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j].isEditable()) {
                    cntEditable++;
                }
            }
        }
        double cntNotCorrect = 0;
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j].isEditable()
                        && ((board[i][j].getText()).equals("") || a[i][j] != (Integer.parseInt(board[i][j].getText())))) {
                    cntNotCorrect++;
                }
            }
        }
        double result = ((cntEditable-cntNotCorrect) / cntEditable) * 100;
        return String.format("%.0f", result);
    }

    private void loadFile() throws FileNotFoundException, IOException {
        clearResults();
        String line = null;
        fileread = new FileReader(filename);
        BufferedReader buffreader = new BufferedReader(fileread);
        if ((line = buffreader.readLine()) != null) {
            result1.setText(line);
        } else {
            buffreader.close();
            return;
        }
        if ((line = buffreader.readLine()) != null) {
            result2.setText(line);
        } else {
            buffreader.close();
            return;
        }
        if ((line = buffreader.readLine()) != null) {
            result3.setText(line);
        } else {
            buffreader.close();
            return;
        }
        if ((line = buffreader.readLine()) != null) {
            result4.setText(line);
        } else {
            buffreader.close();
            return;
        }
        if ((line = buffreader.readLine()) != null) {
            result5.setText(line);
        } else {
            buffreader.close();
            return;
        }

    }

    private void saveFile() throws IOException {
        String line = null;
        String buff = "";
        if (new File(filename).exists()) {

            fileread = new FileReader(filename);
            BufferedReader buffreader = new BufferedReader(fileread);
            while ((line = buffreader.readLine()) != null) {
                buff += line;
                buff += "\n";
            }
            buffreader.close();
        }
        filewrite = new FileWriter(filename);
        BufferedWriter buffwrite = new BufferedWriter(filewrite);
        buffwrite.write(progress());
        buffwrite.write("% ");
        buffwrite.write(textTime);
        buffwrite.newLine();
        if (buff != "") {
            buffwrite.write(buff);
        }
        buffwrite.close();
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {

    }

}
