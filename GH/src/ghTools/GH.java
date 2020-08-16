package ghTools;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class GH {
	
	 static {
	     try {
	         System.loadLibrary("GH_Tools"); 
	    }catch (UnsatisfiedLinkError e) {
	        System.load("/natives/GH_Tools.dll");
	    }
	  }
	
	  public static class Pointer {
		  final private long staticPointer;
		  final private int[] offsets;
		
	      public Pointer(long staticPointer, int ... offsets) {
	          this.staticPointer = staticPointer;
	    	  this.offsets = offsets;
	      }
	       
	      public long getStaticPointer() {
	          return staticPointer;
	      }
	       
	      public int[] getOffsets() {
	          return offsets;
	      }
	  }
	
	  public static native boolean getKeyDown(int key); //checks if button is pressed
	   
      //checks if button is pressed (only returns true once each press)
      public static native boolean getKeyPress(int key);
      
      public static native int getKeyPressed(); //get the value of a pressed key
      
      public static native void sendKeyPress(int key);  //sends key input
      
      public static native void sendKeyDown(int key);  //press key down input
      
      public static native void sendKeyUp(int key); //let key up input
      
      //set cursor position to point somewhere 
      public static native void setCursorPos(int x, int y);
  	
  	  public static native int[] getCursorPos(); //where does the cursor currently point to?
  	  
  	//set cursor position to point somewhere 
      public static native void setGameCursorPos(int x, int y);
  	
  	  public static native int[] getGameCursorPos(); //where does the cursor currently point to?
  	  
  	  public static native void leftClick();
  	  
  	  public static native void rightClick();
  	  
	  //open handle to process of a window:
	  private static native boolean openWindowName(String procName);
	  
	  //open handle to a process:
      private static native boolean openProcess(String procName);
      
      public static native boolean isConnected(); //is the game still running are we connected
      
      public static native long getModuleBaseAddress();
      public static native long getModuleBaseAddress(String moduleName);
      
      //read bit from memory
      public static boolean readBit(long address, int position) {
    	  byte[] mem = readMemory(address, 1);
  		  boolean value = ((mem[0] >> position) & 1) == 1;
  		  return value;
      }
      
      //read byte from memory
      public static byte readByte(long address) {
    	  byte[] mem = readMemory(address, 1);
  		  byte value = mem[0];
  		  return value;
      }
      
      //read short from memory
      public static short readShort(long address) {
    	  ByteBuffer mem = ByteBuffer.wrap(readMemory(address, 2));
    	  mem.order(ByteOrder.nativeOrder());
  		  short value = mem.getShort();
  		  return value;
      }
      
      //read char from memory
      public static char readChar(long address) {
    	  ByteBuffer mem = ByteBuffer.wrap(readMemory(address, 2));
    	  mem.order(ByteOrder.nativeOrder());
  		  char value = mem.getChar();
  		  return value;
      }
      
      //read char from memory
      public static int readInt(long address) {
    	  ByteBuffer mem = ByteBuffer.wrap(readMemory(address, 4));
    	  mem.order(ByteOrder.nativeOrder());
  		  int value = mem.getInt();
  		  return value;
      }
      
      //read long from memory
      public static long readLong(long address) {
    	  ByteBuffer mem = ByteBuffer.wrap(readMemory(address, 8));
    	  mem.order(ByteOrder.nativeOrder());
  		  long value = mem.getLong();
  		  return value;
      }
      
      //read float from memory
      public static float readFloat(long address) {
    	  ByteBuffer mem = ByteBuffer.wrap(readMemory(address, 4));
    	  mem.order(ByteOrder.nativeOrder());
  		  float value = mem.getFloat();
  		  return value;
      }
      
      //read double from memory
      public static double readDouble(long address) {
    	  ByteBuffer mem = ByteBuffer.wrap(readMemory(address, 8));
    	  mem.order(ByteOrder.nativeOrder());
  		  double value = mem.getDouble();
  		  return value;
      }
      
      //read string from memory
      public static String readString(long address , int bytesToRead){
  		  String value = String.valueOf(readMemory(address, bytesToRead));
  		  return value;
  	  }
      
      //read other objects from memory
      public static <T> T read(long address , int bytesToRead) throws ClassNotFoundException{
  		T value = deserialize(readMemory(address, bytesToRead));
  		return value;
  	  }
      
      //read byte array from memory
      public static byte[] readByteArray(long address, int bytesToRead) {
  		return readMemory(address, bytesToRead);
      }
          
      //helper method to read data from memory
      public static native byte[] readMemory(long address,int bytesToRead);
      
      //write bit back to memory
      public static boolean writeBit(long address, boolean data, int position) {
    	byte[] mem = readMemory(address, 1);
    	
    	if(data) {
    		mem[0] = (byte) (mem[0] | (1 << position));
    	} else {
    		mem[0] = (byte) (mem[0] & ~(1 << position));
    	}
    		
    	return writeMemory(address, mem);	
      }
      
      //write byte back to memory
      public static boolean writeByte(long address, byte data) {
    	byte[] mem = {data};	
    	return writeMemory(address, mem);	
      }
      
      //write short back to memory
      public static boolean writeShort(long address, short data) {
    	byte[] mem = ByteBuffer.allocate(2).putShort(data).order(ByteOrder.nativeOrder()).array();
    	return writeMemory(address, mem);	
      }
      
      //write char back to memory
      public static boolean writeChar(long address, char data) {
    	byte[] mem = ByteBuffer.allocate(2).putChar(data).order(ByteOrder.nativeOrder()).array();
    	return writeMemory(address, mem);	
      }
      
      //write byte int to memory
      public static boolean writeInt(long address, int data) {
    	byte[] mem = ByteBuffer.allocate(4).putInt(data).order(ByteOrder.nativeOrder()).array();	
    	return writeMemory(address, mem);	
      }
      
      //write long back to memory
      public static boolean writeLong(long address, long data) {
    	byte[] mem = ByteBuffer.allocate(8).putLong(data).order(ByteOrder.nativeOrder()).array();
    	return writeMemory(address, mem);	
      }
      
      //write float back to memory
      public static boolean writeFloat(long address, float data) {
    	byte[] mem = ByteBuffer.allocate(4).putFloat(data).order(ByteOrder.nativeOrder()).array();
    	return writeMemory(address, mem);	
      }
      
      //write double back to memory
      public static boolean writeDouble(long address, double data) {
    	byte[] mem = ByteBuffer.allocate(8).putDouble(data).order(ByteOrder.nativeOrder()).array();
    	return writeMemory(address, mem);	
      }
      
      //write string back to memory
      public boolean writeString(long address, String string){
  		return writeMemory(address, string.getBytes());
  	  }
      
      //write byte array back to memory
      public static boolean write(long address, byte[] data){
    	return writeMemory(address, data);	
      }
      
      //Generic method to write data back to memory
      public static <T> boolean write(long address, T data) {
    	byte[] mem = serialize(data);
    	return writeMemory(address, mem);	
      }
      
      //write byte array to memory but in code section where memory might be protected
      public static boolean patch(long address, byte[] data){
    	return patchMemory(address, data);	
      }
      
      //write byte array to memory but in code section where memory might be protected
      public static boolean nop(long address, int size){
    	return nopMemory(address, size);	
      }
        
      public static native boolean writeMemory(long address, byte[] write);
      public static native boolean patchMemory(long address, byte[] write);
      public static native boolean nopMemory(long address, int size);
      
      //Convert Object to byte array
      public static byte[] serialize(Object obj) {
    	ByteArrayOutputStream out = new ByteArrayOutputStream();
    	
    	try {
    	ObjectOutputStream os = new ObjectOutputStream(out);
    		os.writeObject(obj);
    		return out.toByteArray();
    	}
    	catch (Exception e) {
    		return null;
    	}
      }
      
      //Convert byte arrays back to Objects
      @SuppressWarnings("unchecked")
	  public static <T> T deserialize(byte[] data) {
    	    ByteArrayInputStream in = new ByteArrayInputStream(data);
    	    
    	    try {
    	     ObjectInputStream is = new ObjectInputStream(in);
    	     return (T) is.readObject();
    	    }
    	    catch(Exception e) {
    	     return null;
    	    }
      }
      
      public static long findDMAAddy(GH.Pointer staticMultiLevelPointer){
    	  return getObjectAddress(staticMultiLevelPointer);
      }
      
      //get the dynamic Object address from its static Pointer
      public static native long getObjectAddress(GH.Pointer staticMultiLevelPointer);
       
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
