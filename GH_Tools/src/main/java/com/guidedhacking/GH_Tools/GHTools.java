package com.guidedhacking.GH_Tools;

public class GHTools {	
	//normal sleep with error handeling
	public static boolean sleep(int time){
		try {
			Thread.sleep(time);
			return true;
		} catch (InterruptedException e) {
			e.printStackTrace();
			return false;
		}
	}
	
	public static native int getGamePID(); //get PID of game
	
	public static native boolean isGameVisible(); //return if game window is visible or not
	
    public static native int getGameHeight(); //get height of the Game Window
    
    public static native int getGameWidth(); //get width of the Game Window
    
    public static native int getGameXPos(); //get x-Pos of game window
    
    public static native int getGameYPos(); //get y-pos of the game window
}
