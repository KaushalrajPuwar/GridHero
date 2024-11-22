#include<jni.h>
#include "GameUI_utils_JNIUtils.h"
#include <iostream>
using namespace std;
#include "Algorithm.h"
#include "./models/Player.h"
#include "./models/Enemy.h"
#include "./models/Grid.h"


//#define GRID_SIZE 10  // Assuming a 10x10 grid for this example

// Define the grid as a 2D array of characters
//char grid[GRID_SIZE][GRID_SIZE];
//int playerX,playerY,enemyX,enemyY;
MovementAlgorithm* enemyMovementAlgorithm=nullptr;

// Function to initialize the grid with some default values
JNIEXPORT void JNICALL Java_GameUI_utils_JNIUtils_initializeGrid(JNIEnv *env, jclass cls) {

    // Fill the grid with default values (for example, 'E' for empty)
    Grid grid=new Grid();
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = '.';  // 'E' represents empty space
        }
    }
    //create a player
    Player player=new Player(0,0);
    // Set player initial position
    //playerX = 0; playerY = 0;
    grid[player.x][player.y] = 'P'; // 'P' for Player

    //create an enemy
    Enemy enemy=new Enemy(GRID_SIZE - 1,GRID_SIZE - 1)
    // Set enemy initial position
    grid[enemy.x][enemy.y] = 'E'; // 'E' for Enemy
    cout << "Grid initialized!"<<endl;
}

// Function to move the player in the grid
JNIEXPORT jboolean JNICALL Java_GameUI_utils_JNIUtils_movePlayer(JNIEnv *env, jclass cls, jint x, jint y) {
    // Check if the coordinates are within bounds
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        grid[player.x+x][player.y+y] = 'P';  // 'P' represents the player
        player.x=player.x+x;
        player.y=player.y+y;
        cout << "Player moved to (" << player.x << ", " << player.y << ")" <<endl;
        return JNI_TRUE;
    }
    return JNI_FALSE;  // Return false if the move is out of bounds
}

// Function to move an enemy on the grid (for demonstration purposes, moving randomly)
JNIEXPORT void JNICALL Java_GameUI_utils_JNIUtils_moveEnemy(JNIEnv *env, jclass cls) {
    // Example: Move enemy to a random position within the grid
    if(!enemyMovementAlgorithm){
        enemyMovementAlgorithm=new ShortestPathAlgorithm();
    }
    enemyMovementAlgorithm->move(enemy,player);
}
// Optional: Set a different algorithm dynamically
extern "C" JNIEXPORT void JNICALL Java_GameUI_utils_JNIUtils_setEnemyMovementAlgorithm(JNIEnv* env, jclass cls, jint algorithmType) {
    delete enemyMovementAlgorithm;
    if (algorithmType == 0) {
        enemyMovementAlgorithm = new RandomMovementAlgorithm(enemy,player);
    } else if (algorithmType == 1) {
        enemyMovementAlgorithm = new ShortestPathAlgorithm(enemy,player);
    } else {
        enemyMovementAlgorithm = nullptr;
        std::cerr << "Unknown algorithm type!" << std::endl;
    }
}

// Function to get the grid state and return it to Java
JNIEXPORT void JNICALL Java_GameUI_utils_JNIUtils_getGridState(JNIEnv *env, jclass cls, jobjectArray gridState) {
    // Loop over each row in the grid and set it in the Java array
    for (int i = 0; i < GRID_SIZE; i++) {
        // Get a reference to the row (which is a jcharArray in Java)
        jcharArray row = (jcharArray) env->GetObjectArrayElement(gridState, i);
        jchar* rowElements = env->GetCharArrayElements(row, 0);

        // Copy the grid row into the Java array
        for (int j = 0; j < GRID_SIZE; j++) {
            rowElements[j] = grid[i][j];
        }

        // Release the reference to the row after modifying it
        env->ReleaseCharArrayElements(row, rowElements, 0);
    }
}
JNIEXPORT jboolean JNICALL Java_GameUI_utils_JNIUtils_isPlayerCaught
  (JNIEnv *env, jclass cls){
    if(player.x == enemy.x && player.y=enemy.y){
        return true;
    }
    else{
        return false;
    }
  }
