/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku;

/**
 *
 * @author alien19766
 */
import java.rmi.registry.*;
import java.rmi.server.UnicastRemoteObject;

public class RegisterWithRMIServer {
  /** Main method
     * @param args */
  public static void main(String[] args)   {
    try {
         SudokuServerInterfaceImpl obj = new SudokuServerInterfaceImpl();
         SudokuServerInterface sudoku = (SudokuServerInterface) UnicastRemoteObject.exportObject(obj, 0);  
         Registry registry = LocateRegistry.createRegistry(1099);     
         registry.bind("Hello", sudoku);  
         System.err.println("Server ready"); 
         int key = System.in.read();
         System.exit(0);
    }
    catch (Exception ex) {
        System.err.println("Server exception: " + ex.toString()); 
         ex.printStackTrace(); 
    }          
  }
}