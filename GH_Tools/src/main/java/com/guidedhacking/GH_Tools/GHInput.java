package com.guidedhacking.GH_Tools;

public class GHInput {
	 
	   public static native boolean getKeyDown(int key); //checks if button is pressed
	   
       //checks if button is pressed (only returns true once each press)
       public static native boolean getKeyPress(int key);
       
       public static native int getKeyPressed(); //get the value of a pressed key
       
       public static native void sendKeyPress(int key);  //sends key input
       
       public static native void sendKeyDown(int key);  //press key down input
       
       public static native void sendKeyUp(int key); //let key up input
       
       //set cursor position to point somewhere 
       public static native void SetCursor(int x, int y);
   	
   	   public static native int[] getCursorPos(); //where does the cursor currently point to?
}
