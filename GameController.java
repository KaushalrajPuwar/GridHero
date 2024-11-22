package GameUI;

import GameUI.utils.JNIUtils;
//import java.util.Scanner;

import javax.swing.*;
import java.awt.event.*;

//import java.awt.*;
public class GameController extends JFrame{
    public GameController(){
        setTitle("Grid Game");
        setSize(400,400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e){
                handleKeyPress(e.getKeyCode());
            }
        });
    }
    public void startGame(){

        JNIUtils.initializeGrid();
        System.out.println("game started!use W(up),A(left),S(down),D(right)");
    }
        
private void handleKeyPress(int keyCode){
    int dx=0,dy=0;
    //Map key presses to directions
    switch(keyCode){
        case KeyEvent.VK_W ->dy=-1;
        case KeyEvent.VK_A->dx=-1;
        case KeyEvent.VK_S ->dy=1;
        case KeyEvent.VK_D ->dx=1;
        default->{
            System.out.println("Invalid key! Use W,A,S,D for movement.");
            return;
        }
    }
    if(!JNIUtils.movePlayer(dx, dy)){
        System.out.println("Invalid move");
    }
    //JNIUtils.setEnemyMovementAlgorithm(1);
    JNIUtils.moveEnemy();
    //get the updated grid state and display it
    if(JNIUtils.isPlayerCaught()){
        System.out.println("Game Over! The enemy caught you!");
        JNIUtils.isupgradable();
        return;
    }
    char[][] grid=new char[10][10];
    JNIUtils.getGridState(grid);
    printGrid(grid);
}
private void printGrid(char[][] grid) {
    for (char[] row : grid) {
        for (char cell : row) {
            System.out.print(cell + " ");
        }
        System.out.println();
    }
}


    
}
