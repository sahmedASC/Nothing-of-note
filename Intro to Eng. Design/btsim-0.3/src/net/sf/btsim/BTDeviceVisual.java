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

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class BTDeviceVisual extends JInternalFrame implements BTDeviceListener {
  private static int frameCount = 0;
  
  private BTDevice device;
  private JLabel lblName;
  private JLabel lblState1;
  private JLabel lblState2;
  private JLabel lblState3;
  private JLabel lblAddr;
  private JLabel lblCOD;
  
  public BTDeviceVisual(BTDevice device, String title) {
    super(title, true, false, true, true);
    
    this.device = device;
    
    Container pnl = getContentPane();
    pnl.setLayout(new GridBagLayout());
    GridBagConstraints gbc = new GridBagConstraints();
    gbc.ipadx = 5; gbc.ipady = 5;
    
    gbc.gridx = 0; gbc.gridy = 0;
    gbc.anchor = GridBagConstraints.EAST;
    JLabel lblTAddr = new JLabel("Address:");
    pnl.add(lblTAddr, gbc);
    gbc.gridx = 1; gbc.gridy = 0;
    gbc.anchor = GridBagConstraints.WEST;
    lblAddr = new JLabel("xx xx xx xx xx xx");
    pnl.add(lblAddr, gbc);
    
    gbc.gridx = 0; gbc.gridy = 1;
    gbc.anchor = GridBagConstraints.EAST;
    JLabel lblTName = new JLabel("Name:");
    pnl.add(lblTName, gbc);
    gbc.gridx = 1; gbc.gridy = 1;
    gbc.anchor = GridBagConstraints.WEST;
    lblName = new JLabel("");
    pnl.add(lblName, gbc);
    
    gbc.gridx = 0; gbc.gridy = 2;
    gbc.anchor = GridBagConstraints.EAST;
    JLabel lblTState = new JLabel("State:");
    pnl.add(lblTState, gbc);
    gbc.gridx = 1; gbc.gridy = 2;
    gbc.anchor = GridBagConstraints.WEST;
    lblState1 = new JLabel("-");
    pnl.add(lblState1, gbc);
    gbc.gridx = 1; gbc.gridy = 3;
    gbc.anchor = GridBagConstraints.WEST;
    lblState2 = new JLabel("-");
    pnl.add(lblState2, gbc);
    gbc.gridx = 1; gbc.gridy = 4;
    gbc.anchor = GridBagConstraints.WEST;
    lblState3 = new JLabel("-");
    pnl.add(lblState3, gbc);
    
    gbc.gridx = 0; gbc.gridy = 5;
    gbc.anchor = GridBagConstraints.EAST;
    JLabel lblTCOD = new JLabel("COD:");
    pnl.add(lblTCOD, gbc);
    gbc.gridx = 1; gbc.gridy = 5;
    gbc.anchor = GridBagConstraints.WEST;
    lblCOD = new JLabel("xx xx xx xx");
    pnl.add(lblCOD, gbc);
    
    addInternalFrameListener(new InternalFrameAdapter() {
      public void internalFrameClosed(InternalFrameEvent ife) {
        System.out.println("Internal Frame was closed.");
      }
    });
    
    updateAddress();
    updateName();
    updateCOD();
    
    setSize(300, 200);
    setLocation(frameCount * 30, frameCount * 30); frameCount++;
  }
  
  private void updateName() {
    String name = device.requestName();
    lblName.setText(name);
  }
  
  private void updateAddress() {
    byte[] addr = device.getBDAddr();
    String sAddr = "";
    for(int i = 0; i < addr.length; i++) {
      if(i > 0) sAddr += ":";
      String str = "0" + Integer.toString(((int)addr[i]) & 0xFF, 16);
      sAddr += str.substring(str.length() - 2);
    }
    lblAddr.setText(sAddr);
  }
  
  private void updateCOD() {
    byte[] cod = device.getClassOfDevice();
    String sCod = "";
    for(int i = 0; i < cod.length; i++) {
      if(i > 0) sCod += ":";
      String str = "0" + Integer.toString(((int)cod[i]) & 0xFF, 16);
      sCod += str.substring(str.length() - 2);
    }
    lblCOD.setText(sCod);
  }
  
  public void stateChanged(BTDevice device, int newState, int scanEnable, boolean inquiry) {
    switch(newState) {
      case BTDevice.STATE_IDLE:
        lblState1.setText("Idle");
        break;
        
      case BTDevice.STATE_MASTER:
        lblState1.setText("Master");
        break;
        
      case BTDevice.STATE_SLAVE:
        lblState1.setText("Slave");
        break;
    }
    
    switch(scanEnable) {
      case BTDevice.SCAN_ENABLE_NONE:
        lblState2.setText("Scan Disabled");
        break;
        
      case BTDevice.SCAN_ENABLE_INQUIRY:
        lblState2.setText("Inquiry Scan Enabled");
        break;
        
      case BTDevice.SCAN_ENABLE_PAGE:
        lblState2.setText("Page Scan Enabled");
        break;
        
      case BTDevice.SCAN_ENABLE_INQUIRY_PAGE:
        lblState2.setText("Inquiry And Page Scan Enabled");
        break;
    }
    
    if(inquiry) {
      lblState3.setText("Inquiry in Progress");
    } else {
      lblState3.setText("");
    }
  }
  
  public void parameterChanged(BTDevice device, int parameter) {
    switch(parameter) {
      case BTDeviceListener.PARAMETER_ADDRESS:
        updateAddress();
        break;
        
      case BTDeviceListener.PARAMETER_NAME:
        updateName();
        break;
        
      case BTDeviceListener.PARAMETER_COD:
        updateCOD();
        break;
    }
  }
  
  public void connectionClosed(BTDevice device) {
    dispose();
  }
}
