/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku;

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
public class Sudoku {
    public static void main(String[] args) {
        String host = "localhost";
        System.out.println(host);
        try {
         Registry registry = LocateRegistry.getRegistry(1099); 
         SudokuServerInterface stub = (SudokuServerInterface) registry.lookup("Hello"); 
         stub.generateTable();
         System.out.println("Remote method invoked"); 
        } catch (Exception ex) {
            System.err.println("Client exception: " + ex.toString()); 
         ex.printStackTrace(); 
        }
    }
   
    
}
