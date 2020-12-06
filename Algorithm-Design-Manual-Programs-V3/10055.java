
/*   @JUDGE_ID:   15451CF   10055   Java   "Esse e ridiculo"   */

import java.io.*;
import java.util.*;

class Main {

  public static void main(String[] args) {
    Main myWork = new Main();
    myWork.begin();
  }

  void begin () {
    String s;
    StringTokenizer st;
    long a, b;

    while ((s = Main.readLn(255)) != null) {
      st = new StringTokenizer(s);
      a = Long.parseLong(st.nextToken());
      b = Long.parseLong(st.nextToken());
      System.out.println(Math.abs(a - b));
    }
  }
 
  static String readLn (int maxLg) {
    byte lin[] = new byte [maxLg];
    int lg = 0, car = -1;
    String line = "";
 
    try {
      while (lg < maxLg) {
        car = System.in.read();
        if ((car < 0) || (car == '\n')) break;
        lin [lg++] += car;
       }
    }
    catch (IOException e) { return (null); }
 
    if ((car < 0) && (lg == 0)) return (null);
    return (new String (lin, 0, lg));
  }
}
