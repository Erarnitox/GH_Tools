import ghTools.GH;

public class main {
    public static void main(String...args) {
    	if (GH.openProcess("notepad++.exe")) {
    		System.out.println(GH.getGamePID());
    	}else {
    		System.out.println("Was not able to open Game");
    	}
    }
}
