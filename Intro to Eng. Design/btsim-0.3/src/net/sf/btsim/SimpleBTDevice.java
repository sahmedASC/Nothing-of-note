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

import java.io.*;
import java.util.Vector;

public class SimpleBTDevice implements BTDevice, Runnable { 
  private static int ID = 0;
  private int id = ++ID;
  
  private InputStream is;
  private OutputStream os;
  private BTEnvironment environment;
  private boolean running = true;
  private Vector deviceListeners = new Vector();
  
  // BT device specific values
  private long connectionAcceptTimeout = 5060; // in ms
  private int pageTimeout = 5120; // in ms
  private int scanEnable = SCAN_ENABLE_NONE;
  private int ctrlACLpkgLength = 0x02A0;
  private int ctrlSOCpkgLength = 0; // not supported
  private int ctrlNumACLpkgs = 8;
  private int ctrlNumSOCpkgs = 0;   // not supported
  private int hostFlowControl = HOST_FLOW_CONTROL_NONE;
  private int hostACLpkgLength = 255;
  private int hostSOCpkgLength = 0; // not supported
  private int hostNumACLpkgs = 16;
  private int hostNumSOCpkgs = 0; // not supported
  private int pinType = PIN_FIXED;
  private String localName = "";
  private byte[] bdAddr;
  private byte[] cod = new byte[] { (byte)0x00, (byte)0x00, (byte)0x00 }; // class of device
  private int state = STATE_IDLE;
  private boolean inquiry = false;
  private InquiryTimer inquiryTimer = null;
  private long inquiryStart = 0;
  private long inquiryDuration = 0;
  private int inquiryNumResults = 0;
  private int inquiryMaxNumResults = 0;
  private Vector connections = new Vector();
  
  public SimpleBTDevice(BTEnvironment env, InputStream is, OutputStream os, byte[] bdAddr) {
    this.environment = env;
    this.is = is;
    this.os = os;
    this.bdAddr = bdAddr;
    
    environment.addDevice(this);
    new Thread(this).start();
  }
  
  public void run() {
    try {
      int c = -1;
      while(running && (c = nextByte()) >= 0) {
        switch(c) {
          case 1:
	    readCommand();
	    break;
	  
          case 2:
            readACLDataPacket();
            break;
          
	  default:
	    System.err.println("[" + id + "]>>> Unhandeld packet type: " + c);
	    break;
        }
      }
    } catch(IOException ie) {
	System.out.println("[" + id + "]--> BTDevice connection closed");
        doConnectionClosed();
    } finally {
      environment.removeDevice(this);
    }
  }
  
  private int nextByte() throws IOException {
    //int c = -1;
    return  is.read();
    //return c;
  }
  
  private void readCommand() throws IOException {
    int ocf = -1;
    int ogf = -1;
    int numParams = -1;
    int[] params = null;
    int c = -1;
    
    c = nextByte();
    if(c < 0) throw new RuntimeException("Error reading cmd 1");
    ocf = c;
    
    c = nextByte();
    if(c < 0) throw new RuntimeException("Error reading cmd 2");
    ocf += (c & 0x03) << 8;
    ogf =  (c & 0xFC) >> 2;
    
    c = nextByte();
    if(c < 0) throw new RuntimeException("Error reading cmd 3");
    numParams = c;
    params = new int[numParams];
    for(int i = 0; i < numParams; i++) {
      c = nextByte();
      if(c < 0) throw new RuntimeException("Error reading cmd params");
      params[i] = c;
    }
    
    System.out.print("[" + id + "]-> Received Command: OGF = 0x" + Integer.toString(ogf, 16));
    System.out.print(", OCF = 0x" + Integer.toString(ocf, 16));
    System.out.print(", numParams = " + numParams);
    if(numParams > 0) {
      System.out.print(":");
      for(int i = 0; i < numParams; i++) {
        System.out.print(" 0x" + Integer.toString(params[i], 16));
      }
    }
    System.out.println();
    
    switch(ogf) {
      case OGF_LINK_CONTROL:
        handleLinkControlCmd(ogf, ocf, params);
	break;
	
      case OGF_LINK_POLICY:
        handleLinkPolicyCmd(ogf, ocf, params);
	break;
	
      case OGF_HCI_CONTROL_AND_BASEBAND:
        handleHCIControlCmd(ogf, ocf, params);
	break;
	
      case OGF_INFORMATIONAL_PARAMETERS:
        handleInformationalParameters(ogf, ocf, params);
	break;
      
      case OGF_HCI_VENDOR_COMMANDS:
        handleVendorCommands(ogf, ocf, params);
	break;
	
      default:
        System.err.println("[" + id + "]>>> Unknown commad.");
	break;
    }
  }
  
  private void readACLDataPacket() throws IOException {
    int handle = -1;
    int length = -1;
    int options = -1;
    byte[] packet = null;
    int c = -1;
    
    c = nextByte();
    if(c < 0) throw new RuntimeException("Error reading acl 1 (LSB handle)");
    handle = c;
    
    c = nextByte();
    if(c < 0) throw new RuntimeException("Error reading acl 2 (MSB handle)");
    handle += (c & 0x0F) << 8;
    options = (c >> 4) & 0x0F;
    
    c = nextByte();
    if(c < 0) throw new RuntimeException("Error reading acl 3 (LSB length)");
    length = c;
    
    c = nextByte();
    if(c < 0) throw new RuntimeException("Error reading acl 4 (MSB length)");
    length += c << 8;
    
    packet = new byte[length + 4];
    packet[2] = (byte)(length & 0xFF);
    packet[3] = (byte)(length >> 8);
    for(int i = 0; i < length; i++) {
      c = nextByte();
      if(c < 0) throw new RuntimeException("Error reading acl data");
      packet[i + 4] = (byte)c;
    }
    
    System.out.print("[" + id + "]-> Received ACL Data Packet: handle = 0x" + Integer.toString(handle, 16));
    System.out.println(", length = " + length);
    
    boolean found = false;
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.handle == handle) {
        found = true;
        try {
          environment.sendACLPacket(this, con.peer, options, packet);
          sendNumberOfCompletedPacketsEvent(handle, 1);
        } catch(NoLinkException nle) {
          System.err.println("[" + id + "]>>> sending ACL packet: no link to peer");
        }
        break;
      }
    }
    if(!found) {
      System.err.println("[" + id + "]>>> Sending ACL packet: could not find given handle");
    }
  }
  
  public void sendACLPacket(BTDevice device, int options, byte[] packet) {
    boolean found = false;
    int handle = -1;
    
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.peer == device) {
        handle = con.handle;
        found = true;
      }
    }
    
    if(found) {
      packet[0] = (byte)(handle & 0xFF);
      packet[1] = (byte)(((handle >> 8) & 0x0F) + ((options & 0x0F) << 4));
      try {
        os.write((byte)0x02); // ACL packet identifier
        os.write(packet);
      } catch(IOException ioe) {
        ioe.printStackTrace();
      }
    } else {
      System.err.println("[" + id + "]>>> Requested connection to peer not found");
    }
  }
  
  private void handleLinkControlCmd(int ogf, int ocf, int[] params) {
    switch(ocf) {
      case OCF_INQUIRY:
        startInquiry(ogf, ocf, params);
	break;
        
      case OCF_INQUIRY_CANCEL:
	cancelInquiry(ogf, ocf, params);
	break;
	
      case OCF_CREATE_CONNECTION:
        createConnection(ogf, ocf, params);
	break;
        
      case OCF_DISCONNECT:
        disconnect(ogf, ocf, params);
        break;
        
      case OCF_ACCEPT_CONNECTION_REQUEST:
        acceptConnectionRequest(ogf, ocf, params);
        break;
        
      case OCF_CHANGE_CONNECTION_PACKET_TYPE:
        changeConnectionPacketType(ogf, ocf, params);
        break;
        
      case OCF_REMOTE_NAME_REQUEST:
	remoteNameRequest(ogf, ocf, params);
	break;
	
      default:
        System.err.println("[" + id + "]>>> Link Control command not yet supported");
	break;
    }
  }
  
  private void handleLinkPolicyCmd(int ogf, int ocf, int[] params) {
      switch(ocf) {
      case OCF_WRITE_LINK_POLICY_SETTINGS:
	  writeLinkPolicySettings(ogf, ocf, params);
	  break;
          
      default:
	  System.err.println("[" + id + "]>>> link policy command not yet supported");
	  break;
      }
  }
  
  private void handleHCIControlCmd(int ogf, int ocf, int[] params) {
    switch(ocf) {
      case OCF_RESET:
        reset(ogf, ocf);
	break;
	
      case OCF_SET_EVENT_FILTER:
        setEventFilter(ogf, ocf, params);
	break;
	
      case OCF_WRITE_PIN_TYPE:
        writePinType(ogf, ocf, params);
	break;
	
      case OCF_WRITE_LOCAL_NAME:
        writeLocalName(ogf, ocf, params);
	break;
        
      case OCF_READ_LOCAL_NAME:
        readLocalName(ogf, ocf, params);
        break;
	
      case OCF_READ_CONN_ACC_TIMEOUT:
        readConnectionAcceptTimeout(ogf, ocf, params);
        break;
        
      case OCF_WRITE_CONN_ACC_TIMEOUT:
        writeConnectionAcceptTimeout(ogf, ocf, params);
	break;
        
      case OCF_READ_PAGE_TIMEOUT:
	readPageTimeout(ogf, ocf, params);
	break;
	
      case OCF_WRITE_PAGE_TIMEOUT:
        writePageTimeout(ogf, ocf, params);
	break;
	
      case OCF_READ_SCAN_ENABLE:
        readScanEnable(ogf, ocf, params);
        break;
        
      case OCF_WRITE_SCAN_ENABLE:
        writeScanEnable(ogf, ocf, params);
	break;
        
      case OCF_WRITE_CLASS_OF_DEVICE:
	writeClassOfDevice(ogf, ocf, params);
	break;
	
      case OCF_SET_HOST_FLOW_CONTROL:
        setHostFlowControl(ogf, ocf, params);
	break;
	
      case OCF_HOST_BUFFER_SIZE:
        setHostBufferSize(ogf, ocf, params);
	break;
        
      case OCF_HOST_NUMBER_OF_COMPLETED_PACKETS:
        hostNumberOfCompletedPackets(ogf, ocf, params);
        break;
        
      case OCF_READ_LINK_SUPERVISION_TIMEOUT:
        readLinkSupervisionTimeout(ogf, ocf, params);
        break;
        
      case OCF_WRITE_LINK_SUPERVISION_TIMEOUT:
        writeLinkSupervisionTimeout(ogf, ocf, params);
        break;
	
      default:
        System.err.println("[" + id + "]>>> Unknown HCI Control command");
	break;
    }
  }
  
  private void handleInformationalParameters(int ogf, int ocf, int[] params) {
    switch(ocf) {
      case OCF_READ_LOCAL_VERSION:
        readLocalVersion(ogf, ocf, params);
	break;

    case OCF_READ_LOCAL_SUPPORTED_FEATURES:
	readLocalFeatures(ogf, ocf, params);
	break;
	
      case OCF_READ_BUFFER_SIZE:
        readBufferSize(ogf, ocf, params);
	break;
        
      case OCF_READ_COUNTRY_CODE:
        readCountryCode(ogf, ocf, params);
        break;
	
      case OCF_READ_BD_ADDR:
        readBDaddr(ogf, ocf, params);
	break;
	
      default:
        System.err.println("[" + id + "]>>> Unknown Informational Parameter command");
	//sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_UNKNOWN_HCI_COMMAND } );
	break;
    }
  }
  
  private void handleVendorCommands(int ogf, int ocf, int[] params) {
    // ignore for the time geing
    // todo: check what we have to do with such commands
    System.out.println("[" + id + "]>>> Vendor specific command (ignored).");
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }    
  
  private void startInquiry(int ogf, int ocf, int[] params) {
    long lap = params[0] + (params[1] >> 8) + (params[2] >> 16);
    // todo: if lap is not one of the specified types -> error
    // todo: do we care about the lap type?
    // todo: check that we are in a state where we can do inquiries
    inquiryStart = System.currentTimeMillis();
    inquiryDuration = params[3] * 1280;
    inquiryMaxNumResults = params[4];
    inquiryNumResults = 0;
    inquiry = true;
    
    doStateChanged(state, scanEnable, inquiry);
    
    inquiryTimer = new InquiryTimer(inquiryDuration);
    
    System.out.println("[" + id + "]--> Start inquiry for " + inquiryDuration + "ms or "
            + inquiryMaxNumResults + ". LAP = " + lap);
    
    sendStatusEvent(ERROR_SUCCESS, ogf, ocf, 4);
  }

  private void cancelInquiry(int ogf, int ocf, int[] params) {
    if(inquiry) {
      doStateChanged(state, scanEnable, false);
    }
    inquiry = false;
    inquiryTimer.interrupt();
    inquiryTimer = null;
    
    System.out.println("[" + id + "]--> cancel inquiry");
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS });
  }
  
  private void createConnection(int ogf, int ocf, int[] params) {
    byte[] bdAddr = new byte[6];
    for(int i = 0; i < 6; i++) {
      bdAddr[i] = (byte)params[5 - i];
    }
    int packetType = params[6] + (params[7] << 8); // ignored
    int pageScanRepetitionMode = params[8]; // ignored
    int reserved = params[9]; // reserved, must be 0x00
    int clockOffset = params[10] + (params[11] << 8); // ignored
    boolean allowRoleSwitch = false;
    if(params[12] == 0x00) {
      allowRoleSwitch = false;
    } else if(params[12] == 0x01) {
      allowRoleSwitch = true;
    } else {
      System.err.println("[" + id + "]>>> parameter for allowRoleSwitch has invalid value");
    }
    
    System.out.print("[" + id + "]--> createConnection: ");
    for(int i = 0; i < 6; i++) {
      if(i > 0) System.out.print(":");
      System.out.print(Integer.toString(bdAddr[i], 16));
    }
    System.out.print(", packetType = " + packetType);
    System.out.print(", pageScanRepMode = " + pageScanRepetitionMode);
    System.out.print(", reserved = " + reserved);
    System.out.print(", clockOffset = " + clockOffset);
    System.out.println(", allowRoleSwitch = " + allowRoleSwitch);

    sendStatusEvent(ERROR_SUCCESS, ogf, ocf, 4);
    
    BTDevice device = environment.getDevice(bdAddr);
    if(device == null) {
      System.err.println("[" + id + "]>>> requested device not found");
      // suppose that paging did not succeed
      // there is no handle yet, so use 0x00
      // the device address is needed for the host to know which con attempt failed
      sendConnectionCompleteEvent(ERROR_PAGE_TIMEOUT, 0x00, bdAddr);
    } else {
      // by default we are master since it is us who initiates the connection setup
      Connection con = new Connection(device, true, allowRoleSwitch);
      connections.add(con);
       try {
        environment.requestConnection(this, device, allowRoleSwitch);
      } catch(NoLinkException nle) {
        con.setupPending = false;
	con.interrupt();
	connections.remove(con);
        sendConnectionCompleteEvent(ERROR_PAGE_TIMEOUT, 0x00, bdAddr);
      }
    }
  }
  
  private void disconnect(int ogf, int ocf, int[] params) {
    int handle = -1;
    byte reason = -1;
    
    handle = params[0];
    handle += (params[1] & 0x0F) << 8;
    reason = (byte)params[2];
    
    System.out.println("[" + id + "]--> Disconnect: handle = " + handle + ", reason = " + reason);

    sendStatusEvent(ERROR_SUCCESS, ogf, ocf, 4);
    
    boolean found = false;
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.handle == handle) {
        found = true;
        connections.remove(con);
        try {
          environment.disconnect(this, con.peer, reason);
        } catch(NoLinkException nle) {
          System.err.println("[" + id + "]>>> Disconnect: no link to peer");
        }
        break;
      }
    }
    if(found) {
      sendDisconnectionCompleteEvent(ERROR_SUCCESS, handle, ERROR_SUCCESS);
    } else {
      System.err.println("[" + id + "]>>> Disconnect: peer not found");
    }
  }
  
  public void disconnect(BTDevice device, byte reason) {
    boolean found = false;
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.peer == device) {
        found = true;
        connections.remove(con);
        sendDisconnectionCompleteEvent(ERROR_SUCCESS, con.handle, reason);
        break;
      }
    }
    if(!found) {
      System.err.println("[" + id + "]>>> received disconnect event but connection not found");
    }
  }
  
  private void cancelConnectionSetup(Connection con) {
    if(con.setupPending) {
      if(con.master) {
        con.setupPending = false;
        con.interrupt();
        connections.remove(con);
        byte[] bdAddr = con.peer.getBDAddr();
        sendConnectionCompleteEvent(ERROR_PAGE_TIMEOUT, 0x00, bdAddr);
      } else {
        con.setupPending = false;
        con.interrupt();
        connections.remove(con);
        try {
          environment.rejectConnectionRequest(this, con.peer, ERROR_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED);
        } catch(NoLinkException nle) {}
      }
    }
  }
  
  public void requestConnection(BTDevice device, boolean allowRoleSwitch) {
    // todo: if this controller doesn't get an answer from it's host, then the
    //        connection setup has to be cancelled on both bt devices
    Connection con = new Connection(device, false, allowRoleSwitch, connectionAcceptTimeout);
    connections.add(con);
    sendConnectionRequestEvent(device.getBDAddr(), device.getClassOfDevice());
    System.out.println("[" + id + "]-> received connection request");
  }
  
  private void acceptConnectionRequest(int ogf, int ocf, int[] params) {
    byte[] bdAddr = new byte[6];
    for(int i = 0; i < 6; i++) {
      bdAddr[i] = (byte)params[5 - i];
    }
    int role = params[6];
    boolean found = false;

    System.out.print("[" + id + "]--> acceptConnectionRequest: ");
    for(int i = 0; i < 6; i++) {
      if(i > 0) System.out.print(":");
      System.out.print(Integer.toString(bdAddr[i], 16));
    }
    System.out.println(", role = " + role);
    
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(BTEnvironment.compareBDAddr(con.peer.getBDAddr(), bdAddr)) {
        if(!con.setupPending) {
          System.err.println("[" + id + "]>>> Error trying to accept an existing connection");
        } else {
          con.setupPending = false;
          con.interrupt();
          
          boolean changeRole = (role == 0x00) && con.roleChangeAllowed;
          try {
            environment.acceptConnectionRequest(this, con.peer, changeRole);
            sendConnectionCompleteEvent(ERROR_SUCCESS, con.handle, con.peer.getBDAddr());
          } catch(NoLinkException nle) {
            connections.remove(con);
            sendConnectionCompleteEvent(ERROR_CONNECTION_TIMEOUT, 0x00, bdAddr);
          }
        }
      }
      found = true;
    }
    if(!found) {
      System.err.println("[" + id + "]>>> error trying to accept a connection that does not exist");
    }
  }
  
  public void acceptConnectionRequest(BTDevice device, boolean changeRole) {
    System.out.println("[" + id + "]-> connection setup completed");
    // todo: make sure that the role can only be changed when this was explicitly allowed from
    //        this controller's host
    boolean found = false;
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.peer == device) {
        if(!con.setupPending) {
          System.err.println("[" + id + "]>>> Error acceptConnection: the connection exists already");
        } else {
          con.setupPending = false;
          con.interrupt();
          if(changeRole) {
            if(con.roleChangeAllowed) {
              con.master = false;
            } else {
              System.err.println("[" + id + "]>>> Error acceptConnection: roleChange disallowed");
            }
          }
          sendConnectionCompleteEvent(ERROR_SUCCESS, con.handle, con.peer.getBDAddr());
        }
        found = true;
        break;
      }
    }
    if(!found) {
      System.err.println("[" + id + "]>>> connection to accept does not exist");
    }
  }
  
  public void rejectConnectionRequest(BTDevice device, byte reason) {
    boolean found = false;
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.peer == device) {
        if(!con.setupPending) {
          System.err.println("[" + id + "]>>> Error acceptConnection: the connection exists already");
        } else {
          con.setupPending = false;
          con.interrupt();
          connections.remove(con);
          sendConnectionCompleteEvent(reason, 0x00, con.peer.getBDAddr());
        }
        found = true;
        break;
      }
    }
    if(!found) {
      System.err.println("[" + id + "]>>> connection to reject does not exist");
    }
  }
  
  private void completeInquiry() {
    if(inquiry) {
      inquiry = false;
      doStateChanged(state, scanEnable, inquiry);
      sendInquiryCompleteEvent();
      if(inquiryTimer != null) {
        inquiryTimer.interrupt();
      }
    }
  }
 
  public String requestName() {
    return localName;
  }
  
  private void changeConnectionPacketType(int ogf, int ocf, int[] params) {
    // todo: inform peer of packet type change
    int handle = params[0] + ((params[1] & 0x0F) << 8);
    int packetType = (params[2] + (params[3] << 8)) | 0x08;
    boolean found = false;

    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.handle == handle) {
        con.packetTypes = packetType;
        found = true;
        break;
      }
    }
    
    sendStatusEvent(ERROR_SUCCESS, ogf, ocf, 4);
    
    System.out.println("[" + id + "]--> changeConnectionPacketType");
    
    if(found) {
      sendConnectionPacketTypeChangedEvent(ERROR_SUCCESS, handle, packetType);
    } else {
      sendConnectionPacketTypeChangedEvent(ERROR_UNKNOWN_CONNECTION_IDENTIFIER, handle, packetType);
    }
  }
  
  private void remoteNameRequest(int ogf, int ocf, int[] params) {
    byte[] bdAddr = new byte[6];
    for(int i = 0; i < 6; i++) {
      bdAddr[i] = (byte)params[5 - i];
    }
    int pageScanRepetitionMode = params[6];
    int reserved = params[7];
    int clockOffset = params[8] + (params[9] << 8);
    
    System.out.print("[" + id + "]--> remoteNameRequest: ");
    for(int i = 0; i < 6; i++) {
      if(i > 0) System.out.print(":");
      System.out.print(Integer.toString((int)bdAddr[i], 16));
    }
    System.out.print(", pageScanRepetitionMode = " + pageScanRepetitionMode);
    System.out.print(", reserved = " + reserved);
    System.out.println(", clockOffset = " + clockOffset);

    sendStatusEvent(ERROR_SUCCESS, ogf, ocf, 4);

    BTDevice device = environment.getDevice(bdAddr);
    if(device == null) {
      System.out.println("[" + id + "]>>> remoteNameRequest: device not found");
    } else {
      try {
        String name = environment.requestName(this, device);
        sendRemoteNameRequestCompleteEvent(ERROR_SUCCESS, bdAddr, name);
      } catch(NoLinkException nle) {
        System.err.println("[" + id + "]>>> remoteNameRequest: remote device is unreachable");
      }
    }
  }

  private void writeLinkPolicySettings(int ogf, int ocf, int[] params) {
    int handle = params[0] + ((params[1] & 0x0F) << 8);
    
    System.out.print("[" + id + "]--> writeLinkPolicySettings: handle = " + handle);
    System.out.print(", roleChangeAllowed = " + ((params[2] & 0x01) != 0));
    System.out.print(", enableHoldMode = " +    ((params[2] & 0x02) != 0));
    System.out.print(", enableSniffMode = " +   ((params[2] & 0x04) != 0));
    System.out.println(", enableParkMode = " +  ((params[2] & 0x08) != 0));

    boolean found = false;
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.handle == handle) {
        found = true;
        con.roleChangeAllowed = ((params[2] & 0x01) != 0);
        con.enableHoldMode =    ((params[2] & 0x02) != 0);
        con.enableSniffMode =   ((params[2] & 0x04) != 0);
        con.enableParkMode =    ((params[2] & 0x08) != 0);

        byte[] data = new byte[3];
        data[0] = ERROR_SUCCESS;
        data[1] = (byte)(handle & 0xFF);
        data[2] = (byte)((handle >> 8) & 0x0F);

        sendCommandCompleteEvent(ogf, ocf, 4, data);

        break;
      }
    }
    if(!found) {
      System.err.println("[" + id + "]>>> writeLinkPolicySettings: handle not found");
    }
  }
  
  private boolean bit(int value, int bit) {
    return ((value & (1 << bit)) != 0);
  }

  private void reset(int ogf, int ocf) {
    // todo: the real reset stuff
    state = STATE_IDLE;
    connectionAcceptTimeout = 5060; // in ms
    pageTimeout = 5120; // in ms
    scanEnable = SCAN_ENABLE_NONE;
    hostFlowControl = HOST_FLOW_CONTROL_NONE;
    hostACLpkgLength = 255;
    hostSOCpkgLength = 0; // not supported
    hostNumACLpkgs = 16;
    hostNumSOCpkgs = 0; // not supported
    pinType = PIN_FIXED;
    localName = "";
    connections.removeAllElements();
    // todo: shutdown all links, etc.
    
    System.out.println("[" + id + "]--> Reset");
    doStateChanged(state, scanEnable, inquiry);
    doParameterChanged(BTDeviceListener.PARAMETER_NAME);
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }
  
  private void setEventFilter(int ogf, int ocf, int[] params) {
    System.out.println("[" + id + "]--> setEventFilter:");
    
    System.out.println("[" + id + "]  > Inquiry Complete Event:             " + bit(params[0], 0));
    System.out.println("[" + id + "]  > Inquiry Result Event:               " + bit(params[0], 1));
    System.out.println("[" + id + "]  > Connection Complete Event:          " + bit(params[0], 2));
    System.out.println("[" + id + "]  > Connection Request Event:           " + bit(params[0], 3));
    System.out.println("[" + id + "]  > Disconnection Complete Event:       " + bit(params[0], 4));
    System.out.println("[" + id + "]  > Authentication Complete Event:      " + bit(params[0], 5));
    System.out.println("[" + id + "]  > Remote Name Request Complete Event: " + bit(params[0], 6));
    System.out.println("[" + id + "]  > Encryption Change Event:            " + bit(params[0], 7));

    if(params.length >= 6) {
      System.out.println("[" + id + "]  > Change Connection Link Key Event:   " + bit(params[1], 0));
      System.out.println("[" + id + "]  > Master Link Key Complete Event:     " + bit(params[1], 1));
      System.out.println("[" + id + "]  > Read Remote Supported Features Complete Event: " + bit(params[1], 2));
      System.out.println("[" + id + "]  > Read Remote Version Information Complete Event: " + bit(params[1], 3));
      System.out.println("[" + id + "]  > QoS Setup Complete Event:           " + bit(params[1], 4));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[1], 5));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[1], 6));
      System.out.println("[" + id + "]  > Hardware Error Event:               " + bit(params[1], 7));

      System.out.println("[" + id + "]  > Flush Occured Event:                " + bit(params[2], 0));
      System.out.println("[" + id + "]  > Role Change Event:                  " + bit(params[2], 1));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[2], 2));
      System.out.println("[" + id + "]  > Mode Change  Event:                 " + bit(params[2], 3));
      System.out.println("[" + id + "]  > Return Linnk Keys Event:            " + bit(params[2], 4));
      System.out.println("[" + id + "]  > PIN Code Request Event:             " + bit(params[2], 5));
      System.out.println("[" + id + "]  > Link Key Request Event:             " + bit(params[2], 6));
      System.out.println("[" + id + "]  > Link Key Notification Event:        " + bit(params[2], 7));

      System.out.println("[" + id + "]  > Loopback Command Event:             " + bit(params[3], 0));
      System.out.println("[" + id + "]  > Data Buffer Overflow Event:         " + bit(params[3], 1));
      System.out.println("[" + id + "]  > Max Slots Change Event:             " + bit(params[3], 2));
      System.out.println("[" + id + "]  > Read Clock Offset Event:            " + bit(params[3], 3));
      System.out.println("[" + id + "]  > Connection Packet Type Changed Event: " + bit(params[3], 4));
      System.out.println("[" + id + "]  > QoS Violation Event:                " + bit(params[3], 5));
      System.out.println("[" + id + "]  > Page Scan Mode Change Event:        " + bit(params[3], 6));
      System.out.println("[" + id + "]  > Page Scan Repetition Mode Change Event: " + bit(params[3], 7));

      System.out.println("[" + id + "]  > Flow Specification Complete Event:  " + bit(params[4], 0));
      System.out.println("[" + id + "]  > Inquiry Result with RSSI Event:     " + bit(params[4], 1));
      System.out.println("[" + id + "]  > Read Remote Extended Features Complete Event: " + bit(params[4], 2));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[4], 3));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[4], 4));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[4], 5));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[4], 6));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[4], 7));

      System.out.println("[" + id + "]  > Reserved: " + bit(params[5], 0));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[5], 1));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[5], 2));
      System.out.println("[" + id + "]  > Synchronous Connection Complete Event:        " + bit(params[5], 3));
      System.out.println("[" + id + "]  > Synchronous Connection Changed Event:         " + bit(params[5], 4));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[5], 5));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[5], 6));
      System.out.println("[" + id + "]  > Reserved: " + bit(params[5], 7));
    }

    // todo: implement event filters
    if(params[0] == 0x00) {
      System.out.println("[" + id + "]--> Clear all event filters");
    } else {
      System.out.println("[" + id + "]>>> Complex event filters not supported yet");
    }
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }    
  
  private void writePinType(int ogf, int ocf, int[] params) {
    // todo: test range
    pinType = params[0];
    
    System.out.println("[" + id + "]--> Pin Type is set: " + pinType);
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }    
  
  private void writeLocalName(int ogf, int ocf, int[] params) {
    StringBuffer str = new StringBuffer(248);
    for(int i = 0; i < 248; i++) {
      if(params[i] == 0) break;
      str.append((char)params[i]);
    }
    localName = str.toString();
    doParameterChanged(BTDeviceListener.PARAMETER_NAME);
    System.out.println("[" + id + "]--> new local name: " + localName);
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }
  
  private void readLocalName(int ogf, int ocf, int[] params) {
    byte[] data = new byte[249];
    data[0] = ERROR_SUCCESS;
    for(int i = 0; i < 248; i++) {
      if(i < localName.length()) {
        data[i + 1] = (byte)localName.charAt(i);
      } else {
        data[i + 1] = 0;
      }
    }
    
    System.out.println("[" + id + "] --> Read local name");
    sendCommandCompleteEvent(ogf, ocf, 4, data);
  }
  
  private void readConnectionAcceptTimeout(int ogf, int ocf, int[] params) {
    int slots = (int)(connectionAcceptTimeout / 0.625f);
    byte[] data = new byte[3];
    data[0] = ERROR_SUCCESS;
    data[1] = (byte)(slots & 0xFF);
    data[2] = (byte)((slots >> 8) & 0xFF);
    
    System.out.println("[" + id + "]--> read connection accept timeout");
    sendCommandCompleteEvent(ogf, ocf, 4, data);
  }
  
  private void writeConnectionAcceptTimeout(int ogf, int ocf, int[] params) {
    int slots = params[0] + (params[1] << 8);
    // todo: test for valid range
    connectionAcceptTimeout = (long)(slots * 0.625f);
    System.out.println("[" + id + "]--> new connection accept timeout: "
            + connectionAcceptTimeout + "ms");
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }
  
  private void readPageTimeout(int ogf, int ocf, int[] params) {
    System.out.println("[" + id + "]--> read page timeout");
    byte[] data = new byte[3];
    int slots = (int)(pageTimeout / 0.625f);
    
    data[0] = ERROR_SUCCESS;
    data[1] = (byte)(slots & 0xFF);
    data[2] = (byte)(slots >> 8);
    
    sendCommandCompleteEvent(ogf, ocf, 4, data);
  }
  
  private void writePageTimeout(int ogf, int ocf, int[] params) {
    int slots = params[0] + (params[1] << 8);
    // todo: test for slots == 0 and issue an error
    pageTimeout = (int)(slots * 0.625f);
    System.out.println("[" + id + "]--> new page timeout: " + pageTimeout + "ms");
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }
  
  private void readScanEnable(int ogf, int ocf, int[] params) {
    System.out.println("[" + id + "]--> read scan enable");
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS, (byte)scanEnable });
  }
  
  private void writeScanEnable(int ogf, int ocf, int[] params) {
    scanEnable = params[0];
    System.out.println("[" + id + "]--> Scan enable paprameter changed: " + scanEnable);

    doStateChanged(state, scanEnable, inquiry);
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }

  private void writeClassOfDevice(int ogf, int ocf, int[] params) {
    System.out.print("[" + id + "]--> Write Class Of Device: 0x");
    for(int i = 2; i >= 0; i--) {
      String str = "00" + Integer.toString(params[i], 16);
      str = str.substring(str.length() - 2);
      System.out.print(str);
    }
    System.out.println();

    cod[2] = (byte)params[0];
    cod[1] = (byte)params[1];
    cod[0] = (byte)params[2];
    
    doParameterChanged(BTDeviceListener.PARAMETER_COD);
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS });
  }
  
  private void setHostFlowControl(int ogf, int ocf, int[] params) {
    // todo: verify valid range
    // todo: verify state (no connections otherwise error)
    hostFlowControl = params[0];
    System.out.println("[" + id + "]--> Flow Control from Controller to Host set: " + hostFlowControl);
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }  
  
  private void setHostBufferSize(int ogf, int ocf, int[] params) {
    // todo: verify valid ranges
    hostACLpkgLength = params[0] + (params[1] << 8);
    hostSOCpkgLength = params[2];
    hostNumACLpkgs = params[3] + (params[4] << 8);  
    hostNumSOCpkgs = params[5] + (params[6] << 8);
    
    System.out.print("[" + id + "]--> Set Host Buffer Size: ACL pkg length = " + hostACLpkgLength);
    System.out.print(", SOC pkg length = " + hostSOCpkgLength);
    System.out.print(", num. ACL pkgs = " + hostNumACLpkgs);
    System.out.println(", num. SOC pkgs = " + hostNumSOCpkgs);
    
    sendCommandCompleteEvent(ogf, ocf, 4, new byte[] { ERROR_SUCCESS } );
  }
  
  private void hostNumberOfCompletedPackets(int ogf, int ocf, int[] params) {
    // todo: update information about host pbuffer size
    System.out.println("[" + id + "]--> Host Number Of Completed Packets:");
    int num = params[0];
    for(int i = 0; i < num; i++) {
      int handle = params[i + 1] + ((params[i + 2] & 0x0F) << 8);
      int numCompleted = params[i + 3] + (params[i + 4] << 8);
      System.out.println("[" + id + "]  > Handle " + handle + ": " + numCompleted);
    }
  }
  
  public void readLinkSupervisionTimeout(int ogf, int ocf, int[] params) {
    int handle = params[0] + ((params[1] & 0x0F) << 8);
    int to = 0;
    boolean found = false;
    byte[] data = new byte[5];
    
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.handle == handle) {
        to = con.linkSupervisionTimeout;
        found = true;
        break;
      }
    }
    if(found) {
      data[0] = ERROR_SUCCESS;
    } else {
      data[0] = ERROR_UNKNOWN_CONNECTION_IDENTIFIER;
    }
    data[1] = (byte)(handle & 0xFF);
    data[2] = (byte)((handle >> 8) & 0x0F);
    data[3] = (byte)(to & 0xFF);
    data[4] = (byte)((to >> 8) & 0xFF);
    
    System.out.println("[" + id + "]--> Read link supervision timeout");
    
    sendCommandCompleteEvent(ogf, ocf, 4, data);
  }
  
  public void writeLinkSupervisionTimeout(int ogf, int ocf, int[] params) {
    int handle = params[0] + ((params[1] & 0x0F) << 8);
    int to = params[2] + (params[3] << 8);
    boolean found = false;
    byte[] data = new byte[3];
    
    for(int i = 0; i < connections.size(); i++) {
      Connection con = (Connection)connections.get(i);
      if(con.handle == handle) {
        con.linkSupervisionTimeout = to;
        found = true;
        break;
      }
    }
    if(found) {
      data[0] = ERROR_SUCCESS;
    } else {
      data[0] = ERROR_UNKNOWN_CONNECTION_IDENTIFIER;
    }
    data[1] = (byte)(handle & 0xFF);
    data[2] = (byte)((handle >> 8) & 0x0F);
    
    System.out.println("[" + id + "]--> Write link supervision timeout");
    
    sendCommandCompleteEvent(ogf, ocf, 4, data);
  }
  
  private void readLocalVersion(int ogf, int ocf, int[] params) {
    // todo: verify values
    byte[] data = new byte[9];
    data[0] = ERROR_SUCCESS;; // status
    data[1] = (byte)0x01; // HCI version: 1.1
    data[2] = (byte)0x03; // current revision (?)
    data[3] = (byte)0x7F; // current revision (?)
    data[4] = (byte)0x01; // LMP version: 1.1
    data[5] = (byte)0xFF; // manufacturer: reserved for tests
    data[6] = (byte)0xFF; // manufacturer: reserved for tests
    data[7] = (byte)0x40; // LMP subversion
    data[8] = (byte)0x75; // LMP subversion
    
    System.out.println("[" + id + "]--> Read local version information");
    
    sendCommandCompleteEvent(ogf, ocf, 4, data);    
  }

  private void readLocalFeatures(int ogf, int ocf, int[] params) {
    System.out.println("[" + id + "]--> read local features");

    byte[] data = new byte[9];
    data[0] = ERROR_SUCCESS;
    data[1] = (byte)0xFF;
    data[2] = (byte)0xFB;
    data[3] = (byte)0x01;
    data[4] = (byte)0x00;
    data[5] = (byte)0x00;
    data[6] = (byte)0x00;
    data[7] = (byte)0x00;
    data[8] = (byte)0x00;

    sendCommandCompleteEvent(ogf, ocf, 4, data);
  }
  
  private void readBufferSize(int ogf, int ocf, int[] params) {
    // todo: use real values (see what the BTNode answers)
    byte[] data = new byte[8];
    data[0] = ERROR_SUCCESS;  // status
    data[1] = (byte)(ctrlACLpkgLength & 0xFF);  // length of ACL data (LS)
    data[2] = (byte)(ctrlACLpkgLength >> 8);    // length of ACL data (MS)
    data[3] = (byte)(ctrlSOCpkgLength);         // No support of synchronous data packets
    data[4] = (byte)(ctrlNumACLpkgs & 0xFF);    // number of ACL packets (LS)
    data[5] = (byte)(ctrlNumACLpkgs >> 8);      // number of ACL packets (MS)
    data[6] = (byte)(ctrlNumSOCpkgs & 0xFF);    // number of SOC packets (LS) (not supported)
    data[7] = (byte)(ctrlNumSOCpkgs >> 8);      // number of SOC packets (MS) (not supported)
    
    System.out.println("[" + id + "]--> Read Buffer Size");
    
    sendCommandCompleteEvent(ogf, ocf, 4, data);    
  }
  
  private void readCountryCode(int ogf, int ocf, int[] params) {
    System.out.println("[" + id + "]--> Read Country Code (deprecated)");
    
    byte[] data = new byte[2];
    data[0] = ERROR_SUCCESS;
    data[1] = (byte)0x00; //basically the whole world except France
    
    sendCommandCompleteEvent(ogf, ocf, 4, data);
  }
  
  private void readBDaddr(int ogf, int ocf, int[] params) {
    byte[] data = new byte[7];
    data[0] = ERROR_SUCCESS; // status
    for(int i = 0; i < 6; i++) {
      data[i + 1] = bdAddr[5 - i];
    }
    
    System.out.println("[" + id + "]--> Read BT device addr");
    
    sendCommandCompleteEvent(ogf, ocf, 4, data);    
  }
  
  private void sendEvent(int eventCode, byte[] data) {
    byte[] pkt = new byte[data.length + 3];
    pkt[0] = 0x04; // event packet
    pkt[1] = (byte)eventCode;
    pkt[2] = (byte)data.length;
    for(int i = 0; i < data.length; i++) {
      pkt[i + 3] = data[i];
    }
    
    try {
      os.write(pkt);
    } catch(IOException ioe) {
      ioe.printStackTrace();
    }
  }
  
  private void sendInquiryCompleteEvent() {
    System.out.println("[" + id + "]--> Send Inquiry Complete Event");
    
    sendEvent(EVENT_INQUIRY_COMPLETE, new byte[] { ERROR_SUCCESS } );
  }
  
  private void sendInquiryResultEvent(BTDevice device) {
    byte[] data = new byte[15];
    byte[] devAddr = device.getBDAddr();
    byte[] cod = device.getClassOfDevice();
   
    data[ 0] = 1; // we send only one device per event
    for(int i = 0; i < 6; i++) {
      data[i + 1] = devAddr[5 - i];
    }
    data[ 7] = (byte)0x00; // scan repetition mode is ignored by the emulator
    data[ 8] = (byte)0x00; // scan period mode is ignored by the emulator
    data[ 9] = (byte)0x00; // reserved: must be 0x00
    data[10] = cod[2];     // class of device (LSB)
    data[11] = cod[1];     // class of device
    data[12] = cod[0];     // class of device (MSB)
    data[13] = (byte)0x00; // clock offset is ignored
    data[14] = (byte)0x00; // clock offset is ignored
    
    System.out.println("[" + id + "]--> Send Inquiry Result Event");
    sendEvent(EVENT_INQUIRY_RESULT, data);
  }
  
  private void sendDisconnectionCompleteEvent(byte status, int handle, byte reason) {
    byte[] data = new byte[4];
    
    data[0] = status;
    data[1] = (byte)(handle & 0xFF); // LSB handle
    data[2] = (byte)((handle >> 8) & 0x0F); // MSB handle
    data[3] = reason;
    
    System.out.println("[" + id + "]--> Send Disconnection Complete Event");
    
    sendEvent(EVENT_DISCONNECTION_COMPLETE, data);
  }

  private void sendRemoteNameRequestCompleteEvent(byte status, byte[] bdAddr, String name) {
    byte[] data = new byte[255];
    data[0] = ERROR_SUCCESS;
    for(int i = 0; i < 6; i++) {
      data[i + 1] = bdAddr[5 - i];
    }
    for(int i = 0; i < name.length(); i++) {
      data[i + 7] = (byte)name.charAt(i);
    }
    
    System.out.println("[" + id + "]--> Send Remote Name Request Complete Event");
    
    sendEvent(EVENT_REMOTE_NAME_REQUEST_COMPLETE, data);
  }
  
  private void sendConnectionCompleteEvent(byte status, int connectionHandle, byte[] bdAddr) {
    byte[] data = new byte[11];
    
    data[0] = status;
    data[1] = (byte)(connectionHandle & 0xFF);
    data[2] = (byte)(connectionHandle >> 8);
    for(int i = 0; i < 6; i++) {
      data[i + 3] = bdAddr[5 - i];
    }
    data[ 9] = (byte)0x01; // for the time being we only support ACL connections
    data[10] = (byte)0x00; // for the time being there is no encryption
    
    System.out.println("[" + id + "]--> Send Connection Complete Event");
    
    sendEvent(EVENT_CONNECTION_COMPLETE, data);
  }
  
  private void sendConnectionRequestEvent(byte[] bdAddr, byte[] cod) {
    byte[] data = new byte[10];
    
    for(int i = 0; i < 6; i++) {
      data[i] = bdAddr[5 - i];
    }
    data[6] = cod[2]; // device class
    data[7] = cod[1]; // device class
    data[8] = cod[0]; // device class
    data[9] = (byte)0x01; // for the time being we only support ACL links
    
    System.out.println("[" + id + "]--> Send Connection Request Event");
    
    sendEvent(EVENT_CONNECTION_REQUEST, data);
  }
  
  private void sendStatusEvent(byte status, int ogf, int ocf, int numCmds) {
    byte[] data = new byte[4];
    
    data[0] = status;     // status
    data[1] = (byte)numCmds;    // number of HCI command packets that can be received
    data[2] = (byte)(ocf & 0xFF);
    data[3] = (byte)((ocf >> 8) + (ogf << 2));
    
    System.out.println("[" + id + "]--> Send Status Event");
    
    sendEvent(EVENT_CMD_STATUS, data);
  }
  
  private void sendCommandCompleteEvent(int ogf, int ocf, int numCmds, byte[] params) {
    byte[] data = new byte[3 + params.length];
    data[0] = (byte)numCmds;
    data[1] = (byte)(ocf & 0xFF);
    data[2] = (byte)((ocf >> 8) + (ogf << 2));
    for(int i = 0; i < params.length; i++) {
      data[i + 3] = params[i];
    }
    
    System.out.println("[" + id + "]--> Send Command Complete Event");
    
    sendEvent(EVENT_CMD_COMPLETE, data);
  }
  
  private void sendNumberOfCompletedPacketsEvent(int handle, int numCompletedPackets) {
    byte[] data = new byte[5];
    data[0] = (byte)1;
    data[1] = (byte)(handle & 0xFF);
    data[2] = (byte)((handle >> 8) & 0x0F);
    data[3] = (byte)1;
    data[4] = (byte)0;
    
    System.out.println("[" + id + "]--> Send Number of Completed Packets Event");
    
    sendEvent(EVENT_NUMBER_OF_COMPLETED_PACKETS, data);
  }
  
  private void sendConnectionPacketTypeChangedEvent(byte status, int handle, int packetType) {
    byte[] data = new byte[5];
    data[0] = status;
    data[1] = (byte)(handle & 0xFF);
    data[2] = (byte)((handle >> 8) & 0x0F);
    data[3] = (byte)(packetType & 0xFF);
    data[4] = (byte)((packetType >> 8) & 0xFF);
    
    System.out.println("[" + id + "]--> Send ConnectionPacketTypeChangedEvent");
    
    sendEvent(EVENT_CONNECTION_PACKET_TYPE_CHANED, data);
  }
  
  public int getState() {
    return state;
  }
  
  public boolean isInquiryScanning() {
    return (state == STATE_IDLE)
           && (scanEnable == SCAN_ENABLE_INQUIRY
	       || scanEnable == SCAN_ENABLE_INQUIRY_PAGE);
  }
  
  public boolean isPageScanning() {
    // todo: a device is also page scanning if it was just inquired
    return (state == STATE_IDLE)
           && (scanEnable == SCAN_ENABLE_PAGE
	       || scanEnable == SCAN_ENABLE_INQUIRY_PAGE);
  }
  
  public boolean isInquiry() {
    return inquiry;
  }
  
  public long getInquiryTimeRemaining() {
    long remaining = 0;
    if(inquiry) {
      remaining = inquiryStart + inquiryDuration - System.currentTimeMillis();
      if(remaining < 0) remaining = 0;
    }
    return remaining;
  }
  
  public void inquiryResult(BTDevice device) {
    if(inquiry) {
      inquiryNumResults++;
    
      sendInquiryResultEvent(device);
    
      if(inquiryMaxNumResults > 0 
              && inquiryNumResults >= inquiryMaxNumResults) {
        completeInquiry();
      }
    } else {
      System.err.println("[" + id + "]>>> Got inquiry result but not in inquiry mode");
    }
  }
  
  public byte[] getBDAddr() {
    return bdAddr;
  }

  public byte[] getClassOfDevice() {
    return cod;
  }
  
  private int getHandle() {
    int handle = 0;
    boolean found = false;
    do {
      handle++;
      found = false;
      for(int i = 0; i < connections.size(); i++) {
        Connection con = (Connection)connections.get(i);
	if(con.handle == handle) {
	  found = true;
	  break;
	}
      }
    } while(found);
    return handle;
  }
  
  public void addDeviceListener(BTDeviceListener deviceListener) {
    deviceListeners.add(deviceListener);
  }
  
  private void doStateChanged(int newState, int scanEnable, boolean inquiry) {
    for(int i = 0; i < deviceListeners.size(); i++) {
      ((BTDeviceListener)deviceListeners.get(i)).stateChanged(this, newState, scanEnable, inquiry);
    }
  }
  
  private void doParameterChanged(int parameter) {
    for(int i = 0; i < deviceListeners.size(); i++) {
      ((BTDeviceListener)deviceListeners.get(i)).parameterChanged(this, parameter);
    }
  }
  
  private void doConnectionClosed() {
    for(int i = 0; i < deviceListeners.size(); i++) {
      ((BTDeviceListener)deviceListeners.get(i)).connectionClosed(this);
    }
  }
  
  // --- Inner Classes ---
  private class InquiryTimer extends Thread {
    private long delay;
    
    public InquiryTimer(long delay) {
      this.delay = delay;
      start();
    }
    
    public void run() {
      try { sleep(delay); } catch(InterruptedException ie) {}
      completeInquiry();
    }
  }
  
  private class Connection extends Thread {
    private BTDevice peer;
    private boolean setupPending = true;
    private int handle;
    private boolean master;
    private boolean roleChangeAllowed;
    private long timeout; 
    private int linkSupervisionTimeout = 0x7D00; // n * 0.625ms, default 20s
    private int packetTypes = 0x0008 | 0x0010 | 0x0400 | 0x0800 | 0x4000 | 0x8000;
    private boolean enableHoldMode  = false;
    private boolean enableSniffMode = false;
    private boolean enableParkMode  = false;
    
    public Connection(BTDevice peer, boolean master, boolean rca) {
      // default is 30s (waiting for an answer from the peer)
      this(peer, master, rca, 30000);
    }
    
    public Connection(BTDevice peer, boolean master, boolean rca, long timeout) {
      this.peer = peer;
      this.master = master;
      this.roleChangeAllowed = rca;
      this.handle = getHandle();
      this.timeout = timeout;
      start();
    }
    
    public void run() {
      try { sleep(timeout); } catch(InterruptedException ie) {}
      if(setupPending) {
        // if master, the
        //  - on this host, connectionCompleteEvent(page timeout)
        //  if the peer answers later, then an error will be returned
        // if slave, then
        //  - on peer, cancelConnectionRequest
        //  if this host reacts too late, an error will be returned to the host
        cancelConnectionSetup(this);
      }
    }
  }
}
