/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku;

import java.rmi.*;
import java.rmi.server.*;
import java.util.*;
import static javafx.application.Application.launch;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;


/**
 *
 * @author alien19766
 */
public final class SudokuServerInterfaceImpl extends Application
        implements SudokuServerInterface{

    private static int client=0;
    public SudokuServerInterfaceImpl() throws RemoteException {
        client++;
    }
    
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"));
        Scene scene = new Scene(root);
        stage.setTitle("Client "+String.format("%d",client));
        stage.setScene(scene);
        stage.show();
    }

    @Override
    public void generateTable() throws RemoteException{
        launch();   
    }
}
