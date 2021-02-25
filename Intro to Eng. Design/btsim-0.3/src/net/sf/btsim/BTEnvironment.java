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

import java.util.Vector;

public class BTEnvironment implements BTDeviceListener {
  private Vector devices = new Vector();
  private Vector inquiries = new Vector();
  
  public void addDevice(BTDevice device) {
    devices.add(device);
  }
  
  public void removeDevice(BTDevice device) {
    devices.remove(device);
  }
  
  public void stateChanged(BTDevice device, int newState, int scanEnable, boolean inquiry) {
    // if a device is now inquiring, a list with all devices
    //    that might answer will be created. Each device
    //    has it's own timeout and after that timeout
    //    the inquiry response will be sent      
    // if a device was previously inquiring, a potential
    //    inquiry list will be cancelled
    // if a device changes state and is in an inquiry list,
    //    it will be verified that it is still inquirable,
    //    otherwise it will be removed from the list
    // if a device is added, it will be checked whether any
    //    inquiries occur which could discover the device
    if(device.isInquiry()) {
      for(int i = 0; i < devices.size(); i++) {
        BTDevice dev = (BTDevice)devices.get(i);
	if((dev != device) && canCommunicate(dev, device) && dev.isInquiryScanning()) {
	  inquiries.add(new Inquiry(device, dev));
	}
      }
    } else {
      // remove from the back to avoid indexing problems when elements are removed
      for(int i = (inquiries.size() - 1); i >= 0; i--) {
        Inquiry inq = (Inquiry)inquiries.get(i);
	if(inq.dev1 == device) {
	  inq.interrupt();
	  inquiries.remove(inq);
	}
      }
    }
    if(!device.isInquiryScanning()) {
      for(int i = (inquiries.size() - 1); i >= 0; i--) {
        Inquiry inq = (Inquiry)inquiries.get(i);
	if(inq.dev2 == device) {
	  inq.interrupt();
	  inquiries.remove(inq);
	}
      }
    }
  }
  
  public void parameterChanged(BTDevice device, int parameter) {
    // not used here
  }
  
  public void connectionClosed(BTDevice device) {
    // not used here
  }
  
  public BTDevice getDevice(byte[] bdAddr) {
    BTDevice dev = null;
    for(int i = 0; i < devices.size(); i++) {
      BTDevice device = (BTDevice)devices.get(i);
      if(compareBDAddr(device.getBDAddr(), bdAddr)) {
        dev = device;
        break;
      }
    }
    return dev;
  }
  
  public static boolean compareBDAddr(byte[] addr1, byte[] addr2) {
    boolean ok = true;
    for(int i = 0; i < 6; i++) {
      if(addr1[i] != addr2[i]) {
        ok = false;
        break;
      }
    }
    return ok;
  }
  
  public void requestConnection(BTDevice dev1, BTDevice dev2, boolean allowRoleSwitch) throws NoLinkException {
    if(canCommunicate(dev1, dev2)) {
      dev2.requestConnection(dev1, allowRoleSwitch);
    } else {
      throw new NoLinkException();
    }
  }
  
  public void acceptConnectionRequest(BTDevice dev1, BTDevice dev2, boolean changeRole) throws NoLinkException {
    if(canCommunicate(dev1, dev2)) {
      dev2.acceptConnectionRequest(dev1, changeRole);
    } else {
      throw new NoLinkException();
    }
  }
  
  public void rejectConnectionRequest(BTDevice dev1, BTDevice dev2, byte reason) throws NoLinkException {
    if(canCommunicate(dev1, dev2)) {
      dev2.rejectConnectionRequest(dev1, reason);
    } else {
      throw new NoLinkException();
    }
  }
  
  public void sendACLPacket(BTDevice dev1, BTDevice dev2, int options, byte[] packet) throws NoLinkException {
    if(canCommunicate(dev1, dev2)) {
      dev2.sendACLPacket(dev1, options, packet);
    } else {
      throw new NoLinkException();
    }
  }
  
  public void disconnect(BTDevice dev1, BTDevice dev2, byte reason) throws NoLinkException {
    if(canCommunicate(dev1, dev2)) {
      dev2.disconnect(dev1, reason);
    } else {
      throw new NoLinkException();
    }
  }

  public String requestName(BTDevice dev1, BTDevice dev2) throws NoLinkException {
    if(canCommunicate(dev1, dev2)) {
      return dev2.requestName();
    } else {
      throw new NoLinkException();
    }
  }
  
  private boolean canCommunicate(BTDevice device1, BTDevice device2) {
    // for now assume that all devices can communicate with each other
    return true;
  }
  
  private class Inquiry extends Thread {
    private BTDevice dev1;
    private BTDevice dev2;
    
    public Inquiry(BTDevice dev1, BTDevice dev2) {
      this.dev1 = dev1;
      this.dev2 = dev2;
      start();
    }
    
    public void run() {
      long delay = (long)(dev1.getInquiryTimeRemaining() * Math.random());
      try { sleep(delay); } catch(InterruptedException ie) {}
      if(dev1.isInquiry()
              && dev2.isInquiryScanning()
	      && canCommunicate(dev1, dev2)) {
        dev1.inquiryResult(dev2);
      }
    }
  }
}