# GH_Tools
#### Game Hacking Tools for Java

### Installing

- To use `GH_Tools` you can either download it from [**here**](https://github.com/Erarnitox/java-sauerbraten-hack/raw/master/bin/GHTools.jar) and import in in your project.

- Or get the source (Eclipse project) for it [**here**](https://github.com/Erarnitox/GH_Tools/GH_Tools).

### Usage
#### Package Overview
All Classes can be found in the package `com.guidedhacking.GH_Tools`. In this Overview we will have a brief look at its classes and their most often used methods.

##### GHArchitecture
Is a pure Enum type with the following Options:
- ###### Win32
- ###### Win64

##### GHInput
Unlike build in methods these will also work when the program is out of focus.

**Methods:**

- ###### boolean getKeyDown(int key)
returns `true` if the key is pressed and `false` otherwise.

- ###### void sendKeyPress(int key)
simulate a full key press and release.

- ###### void sendKeyDown(int key)
simulate a key press.

- ###### void sendKeyUp(int key)
simulate a key release.

- ###### void SetCursor(int x, int y)
set the position of the cursor to the specified position.

- ###### int[] getCursorPos()
returns an int array whit 2 elements. where the first element is the x-coordinate and the second value is the y-coordinate of the cursor.

##### GHMemory
Used to access the memory of another process.

**Methods:**

- ###### boolean openProcess(String processName)
Open a handle to the process with this name to be able to access its memory. Returns `true` if it was successful and `false` otherwise.

- ###### boolean openWindowName(String windowName)
Same as `openProcess` but takes the title of a window instead of the processName

- ###### long getModuleBaseAddress()
Return the base address of the main executable of the currently opened process.

- ###### long getModuleBaseAddress(String moduleName)
Returns the base address of the module with the given name in the currently opened process.

- ###### boolean writeMemory(long address, byte[] write)
Write a byte array to the currently opened process at the given location.

- ###### boolean patchMemory(long address, byte[] write)
Same as write Memory but takes care of memory permissions as well.

- ###### boolean nopMemory(long address, int size)
Replaces code of the currently opened process with code that does nothing at the given address.
Size is the nuber of nops to be written there.

- ###### void setArchitecture(GHArchitecture architecture)
Used to set the architecture to the architecture of the game to use the correct pointer size.

- ###### long getObjectAddress(GHPointer staticMultiLevelPointer)
calculates the runtime address from the static pointer provided.

- ###### void close()
Close the handle you have opened to the game.

- ###### boolean isConnected()
Checks if the handle to the game is still open. Will return `true` if the handle is still open and `false` if its closed.

- ###### boolean readBit(long address, int position)
Used to read a single bit from memory. Return `true` if its 1 or `false` if its 0.

- ###### byte readByte(long address)
Returns the byte that can be found at the provided address in the memory.

- ###### short readShort(long address)
Returns the short that can be found at the provided address in the memory.

- ###### char readChar(long address)
Returns the char that can be found at the provided address in the memory.

- ###### int readInt(long address)
Returns the int that can be found at the provided address in the memory.

- ###### long readLong(long address)
Returns the long that can be found at the provided address in the memory.

- ###### float readFloat(long address)
Returns the float that can be found at the provided address in the memory.

- ###### double readDouble(long address)
Returns the double that can be found at the provided address in the memory.

- ###### readString(long address , int bytestoread)
Returns the String that can be found at the provided address in the memory.

- ###### byte[] readByteArray(long address, int bytesToRead)
Returns the byte[] that starts at the provided address with the provided length.

- ###### boolean writeBit(long address, boolean data, int position)
Write a single bit to memory (`true` for 1 and `false` for 0) to the specified position in the byte that can be found at the specified address.
Will `return` true if successful and `false` otherwise.

- ###### boolean writeByte(long address, byte data)
Write a single byte to the specified address in memory.
Will `return` true if successful and `false` otherwise.

- ###### boolean writeShort(long address, short data)
Write a short to the specified address in memory.
Will `return` true if successful and `false` otherwise.

- ###### boolean writeChar(long address, char data)
Write a single char to the specified address in memory.
Will `return` true if successful and `false` otherwise.

- ###### boolean writeInt(long address, int data)
Write an int to the specified address in memory.
Will `return` true if successful and `false` otherwise.

- ###### boolean writeLong(long address, long data)
Write a long to the specified address in memory.
Will `return` true if successful and `false` otherwise.

- ###### boolean writeFloat(long address, float data)
Write a float to the specified address in memory.
Will `return` true if successful and `false` otherwise.

- ###### boolean writeDouble(long address, double data)
Write a double to the specified address in memory.
Will `return` true if successful and `false` otherwise.

- ###### boolean writeString(long address, String string)
Write a String to the specified address in memory.
Will `return` true if successful and `false` otherwise.

- ###### boolean write(byte[] data, long address)
Write a byte[] to memory starting at the provided address.
Will `return` true if successful and `false` otherwise.

this class also provides some methods for working with objects in memory. If you are interested in them check the source of this class [here](https://github.com/Erarnitox/java-sauerbraten-hack/blob/master/src/com/guidedhacking/GHMemory.java). Please note that these methods are not tested!

##### GHPointer
Used to hold information about the static pointer and the offsets of a value.

**Constructor:**

- ###### GHPointer(long staticPointer, int ... offsets)

**Methods:**

- ###### long getStaticPointer()
- ###### int[] getOffsets()

##### GHTools

**Methods:**

- ###### boolean sleep(int time)
Sleep method with exception handeling.

- ###### int getGamePID()
Returns the process ID of the currently opened process.

- ###### boolean isGameVisible()
Return `true` if the game window is visible and `false` otherwise.

- ###### int getGameHeight()
Returns the height of the game window in pixels.

- ###### int getGameWidth()
Returns the width of the game window in pixels.

- ###### int getGameXPos()
Returns the x-position of the upper left corner of the game window on the sreeen.

- ###### int getGameYPos()
Returns the y-position of the upper left corner of the game window on the sreeen.

### Getting started

Once you have downloaded and imported [**GH_Tools**](https://github.com/Erarnitox/java-sauerbraten-hack/raw/master/bin/GHTools.jar) into your project you can get started coding your first hack for a game.

here is a very simple example on how to use `GHTools`

```
//import everything from the GH_Tools:
import com.guidedhacking.GH_Tools*; 

public class Example {
	
	//create a new pointer with the static address and offsets:
	private static GHPointer healthPtr  = new GHPointer(0x2DEAD,0x13); 
	
	public static void main(String[] args){
		
		//try to open a handle to the game process:
		if(GHMemory.openProcess("Game Window Title")) {
			
			//select the architecture of the game:
			GHMemory.setArchitecture(GHArchitecture.Win32); 
			
			//calculate the runtime address of the health value from the pointer:
			long healthAddy = GHMemory.getObjectAddress(healthPtr); 
			
			//read the health value from the games memory:
			int healthValue = GHMemory.readInt(healthAddy); 
			
			//increase the health value by 1:
			healthValue++; 
			
			//write the new health value back to memory:
			GHMemory.writeInt(healthValue,healthAddy); 
			
		}else{ //if creating a handle to the game failed
			System.out.println("Can not open Game!");
		}
	}
}
```

for a more in depth example please have a look at the example hack i have provided.

## Built With

* [JNA](https://github.com/java-native-access) - Java Native Access

## Acknowledgments

* [**Rake**](https://guidedhacking.com/members/rake.26782/) - for running [guidedhacking.com](https://guidedhacking.com/) and his great tutorials. Without him this repo would probably not exist.
