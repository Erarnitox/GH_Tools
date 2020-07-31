package nyaaa.ghtoolsjava;

import java.io.File;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Arrays;

public final class Utils {

  private Utils(){}
  
  /**
   * Loads a library onto the program classpath
   *
   * @param jar the library to load
   */
  public static synchronized void loadLibrary(File jar) {
    try {
      /*We are using reflection here to circumvent encapsulation; addURL is not public*/
      URLClassLoader loader = (URLClassLoader) ClassLoader.getSystemClassLoader();
      URL url = jar.toURI().toURL();
      /*Disallow if already loaded*/
      for (URL it : Arrays.asList(loader.getURLs())) {
        if (it.equals(url)) {
          return;
        }
      }
      Method method = URLClassLoader.class.getDeclaredMethod("addURL", new Class[]{URL.class});
      method.setAccessible(true);
      /*promote the method to public access*/
      method.invoke(loader, new Object[]{url});
    } catch (NoSuchMethodException | IllegalAccessException | MalformedURLException | InvocationTargetException e) {
      e.printStackTrace();
    }
  }
  
}
