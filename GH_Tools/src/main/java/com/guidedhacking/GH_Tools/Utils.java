package com.guidedhacking.GH_Tools;

import com.sun.jna.Memory;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.BaseTSD;
import com.sun.jna.platform.win32.WinDef;
import com.sun.jna.platform.win32.WinNT;
import com.sun.jna.win32.W32APIOptions;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.net.URLConnection;
import java.util.Arrays;

public final class Utils {

  static Kernel32 kernel32 = (Kernel32) Native.loadLibrary("kernel32.dll", Kernel32.class, W32APIOptions.ASCII_OPTIONS);
  static PsapiExt psapi = (PsapiExt) Native.loadLibrary("psapi", PsapiExt.class, W32APIOptions.UNICODE_OPTIONS);

  private Utils() {
  }

  public static void saveResource(String resourcePath, boolean replace) {
    if (resourcePath == null || resourcePath.equals("")) {
      throw new IllegalArgumentException("ResourcePath cannot be null or empty");
    }

    resourcePath = resourcePath.replace('\\', '/');
    InputStream in = getResource(resourcePath);
    if (in == null) {
      System.out.println("The embeded resource " + resourcePath + " cannot be found");
      return;
    }
    File outFile = new File(".", resourcePath);
    int lastIndex = resourcePath.lastIndexOf('/');
    File outDir = new File(".", resourcePath.substring(0, lastIndex >= 0 ? lastIndex : 0));

    if (!outDir.exists()) {
      outDir.mkdirs();
    }

    try {
      if (!outFile.exists() || replace) {
        OutputStream out = new FileOutputStream(outFile);
        byte[] buf = new byte[1024];
        int len;
        while ((len = in.read(buf)) > 0) {
          out.write(buf, 0, len);
        }
        out.close();
        in.close();
      } else {
        System.out.println("Couldn't not save " + outFile.getName() + " to " + outFile + " because " + outFile.getName() + " already exists.");
      }
    } catch (IOException ex) {
      ex.printStackTrace();
    }
  }

  public static InputStream getResource(String filename) {
    if (filename == null) {
      throw new IllegalArgumentException("Filename cannot be null");
    }

    try {
      URL url = GHPointer.class.getClassLoader().getResource(filename);

      if (url == null) {
        return null;
      }

      URLConnection connection = url.openConnection();
      connection.setUseCaches(false);
      return connection.getInputStream();
    } catch (IOException ex) {
      return null;
    }
  }

  public static boolean inject(int processID, String dllName) {
    BaseTSD.DWORD_PTR processAccess = new BaseTSD.DWORD_PTR(0x43A);

    WinNT.HANDLE hProcess = kernel32.OpenProcess(processAccess, new WinDef.BOOL(false), new BaseTSD.DWORD_PTR(processID));
    if (hProcess == null) {
      System.out.println("Handle was NULL! Error: " + kernel32.GetLastError());
      return false;
    }

    BaseTSD.DWORD_PTR loadLibraryAddress = kernel32.GetProcAddress(kernel32.GetModuleHandle("KERNEL32"), "LoadLibraryA");
    if (loadLibraryAddress.intValue() == 0) {
      System.out.println("Could not find LoadLibrary! Error: " + kernel32.GetLastError());
      return false;
    }

    WinDef.LPVOID dllNameAddress = kernel32.VirtualAllocEx(hProcess, null, (dllName.length() + 1), new BaseTSD.DWORD_PTR(0x3000), new BaseTSD.DWORD_PTR(0x4));
    if (dllNameAddress == null) {
      System.out.println("dllNameAddress was NULL! Error: " + kernel32.GetLastError());
      return false;
    }

    Pointer m = new Memory(dllName.length() + 1);
    m.setString(0, dllName);

    boolean wpmSuccess = kernel32.WriteProcessMemory(hProcess, dllNameAddress, m, dllName.length(), null).booleanValue();
    if (!wpmSuccess) {
      System.out.println("WriteProcessMemory failed! Error: " + kernel32.GetLastError());
      return false;
    }

    BaseTSD.DWORD_PTR threadHandle = kernel32.CreateRemoteThread(hProcess, 0, 0, loadLibraryAddress, dllNameAddress, 0, 0);
    if (threadHandle.intValue() == 0) {
      System.out.println("threadHandle was invalid! Error: " + kernel32.GetLastError());
      return false;
    }

    kernel32.CloseHandle(hProcess);

    return true;
  }
  
  
  /**
   * Lobs a library onto the program classpath
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
