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

import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class BTGui extends JFrame {
  private JDesktopPane desktop;
  
  public BTGui() {
    super("BT-Sim: A BlueTooth Simulator");
    desktop = new JDesktopPane();
    setContentPane(desktop);
    
    addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent we) {
        System.exit(0);
      }
    });
    
    JMenuBar menu = new JMenuBar();
    JMenu mnuFile = new JMenu("File");
    JMenu mnuHelp = new JMenu("Help");
    JMenuItem mniFileExit = new JMenuItem("Exit");
    mniFileExit.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent ae) {
          System.exit(0);
        }
    });
    mnuFile.add(mniFileExit);
    menu.add(mnuFile);
    menu.add(new JSeparator(SwingConstants.VERTICAL));
    menu.add(mnuHelp);
    setJMenuBar(menu);
    
    setSize(500, 300);
    setVisible(true);
  }
  
  public void addDevice(BTDeviceVisual visual) {
    visual.setVisible(true);
    desktop.add(visual);
    visual.toFront();
  }
}

