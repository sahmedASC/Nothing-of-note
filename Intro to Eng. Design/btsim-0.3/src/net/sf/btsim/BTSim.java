/*
 *  BT-Sim - A BlueTooth hardware simulator at the HCI level
 *  Copyright (C) 2004  Urs Hunkeler
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

package net.sf.btsim;

import java.net.*;
import java.io.*;

public class BTSim {
  private static boolean gui = true;
  
  public static void main(String[] args) {
    boolean start = true;
    for(int i = 0; i < args.length; i++) {
      if(args[i].equals("-v")) {
        start = false;
        showInfo();
      } else if(args[i].equals("-w")) {
        start = false;
        showWarranty();
      } else if(args[i].equals("-c")) {
        start = false;
        showCopying();
      } else if(args[i].equals("-h")) {
        start = false;
        showHelp();
      } else if(args[i].equals("-g")) {
        gui = false;
      } else {
        start = false;
        System.out.println(">>> Unknown argument '" + args[i] + "'.");
      }
    }
    if(start) {
      showInfo();
      start();
    }
  }
  
  public static void start() {
    int port = 7007;
    BTEnvironment env = new BTEnvironment();
    BTGui btGui = null;
    if(gui) {
      btGui = new BTGui();
    }
    
    try {
      ServerSocket ss = new ServerSocket(port);
      System.out.println("--> Listening on port " + port);
      while(true) {
        Socket s = ss.accept();
        InetAddress addr = s.getInetAddress();
        System.out.println("--> Connected to " + addr.getHostAddress()
                           + ":" + s.getPort());
        
        SimpleBTDevice device = new SimpleBTDevice(env, s.getInputStream(),
                                                   s.getOutputStream(),
                                                   randomAddress());
        device.addDeviceListener(env);
        if(gui) {
          BTDeviceVisual visual = new BTDeviceVisual(device, addr.getHostAddress()
                                                     + ":" + s.getPort());
          device.addDeviceListener(visual);
          btGui.addDevice(visual);
        }
      }
    } catch(Exception ex) {
      ex.printStackTrace();
    }
    System.out.println("--> Connection setup finished");
    while(true) {
      try { Thread.sleep(1000); } catch(InterruptedException ie) {}
    }
  }
  
  private static byte[] randomAddress() {
    byte[] addr = new byte[6];
    for(int i = 0; i < 6; i++) {
      addr[i] = (byte)(Math.random() * 256);
    }
    return addr;
  }
  
  public static void showInfo() {
    System.out.println("BT-Sim version 0.5, Copyright 2004 by Urs Hunkeler");
    System.out.println();
    System.out.println("BT-Sim comes with ABSOLUTELY NO WARRANTY; "
                       + "for details start it with the -w option.");
    System.out.println("This is free software, and you are welcome "
                       + "to redistribute it");
    System.out.println("under certain conditions; start this program with "
                       + "the -c option for details.");
    System.out.println();
  }
  
  public static void showWarranty() {
    System.out.println(
              "                                  NO WARRANTY\n\n"
            + "   BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY\n"
            + "FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN\n"
            + "OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES\n"
            + "PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED\n"
            + "OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF\n"
            + "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS\n"
            + "TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE\n"
            + "PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,\n"
            + "REPAIR OR CORRECTION.\n\n"
            + "   IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\n"
            + "WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR\n"
            + "REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,\n"
            + "INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING\n"
            + "OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED\n"
            + "TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY\n"
            + "YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER\n"
            + "PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE\n"
            + "POSSIBILITY OF SUCH DAMAGES.\n");
  }
  
  public static void showCopying() {
    System.out.println(
            "You may copy and distribute verbatim copies of the Program's\n"
          + "source code as you receive it, in any medium, provided that you\n"
          + "conspicuously and appropriately publish on each copy an appropriate\n"
          + "copyright notice and disclaimer of warranty; keep intact all the\n"
          + "notices that refer to GNU GPL License and to the absence of any warranty;\n"
          + "and give any other recipients of the Program a copy of this License\n"
          + "along with the Program.\n\n"
          + "You may charge a fee for the physical act of transferring a copy, and\n"
          + "you may at your option offer warranty protection in exchange for a fee.\n\n"
          + "For more details read the GNU General Public License (GPL).\n");
  }
  
  public static void showHelp() {
    System.out.println("BT-Sim supports the following command-line options:");
    System.out.println("   -v  Show version information");
    System.out.println("   -w  Show warranty");
    System.out.println("   -c  Show copying information");
    System.out.println("   -h  Show this help");
    System.out.println("   -g  No GUI");
  }
}