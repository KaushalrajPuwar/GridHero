package GameUI.utils;

public class JNIUtils {
    public static native void initializeGrid();
    public static native void getGridState(char[][] gridState);
    public static native boolean movePlayer(int newX, int newY);
    public static native void moveEnemy();
    public static native boolean isPlayerCaught();
    public static native boolean isupgradable();
    
    static{
        System.loadLibrary("Program");
    
    }
}
