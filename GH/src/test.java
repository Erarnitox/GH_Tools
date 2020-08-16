import ghTools.GH;
public class test {

	public static void main(String[] args) {
		if (GH.openWindowName("Task-Manager")) {
    		System.out.println(GH.getGamePID());
    	}else {
    		System.out.println("Was not able to open Game");
    	}
	}

}
