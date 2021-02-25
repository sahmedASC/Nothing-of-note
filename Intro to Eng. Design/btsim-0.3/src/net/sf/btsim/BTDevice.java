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

public interface BTDevice {
  public static final byte EVENT_INQUIRY_COMPLETE = 0x01;
  public static final byte EVENT_INQUIRY_RESULT = 0x02;
  public static final byte EVENT_CONNECTION_COMPLETE = 0x03;
  public static final byte EVENT_CONNECTION_REQUEST = 0x04;
  public static final byte EVENT_DISCONNECTION_COMPLETE = 0x05;
  public static final byte EVENT_AUTHENTICATION_COMPLETE = 0x06;
  public static final byte EVENT_REMOTE_NAME_REQUEST_COMPLETE = 0x07;
  public static final byte EVENT_ENCRYPTION_CHANGE = 0x08;
  public static final byte EVENT_CMD_COMPLETE = 0x0E;
  public static final byte EVENT_CMD_STATUS = 0x0F;
  public static final byte EVENT_HARDWARE_ERROR = (byte)0x10;
  public static final byte EVENT_ROLE_CHANGE = (byte)0x12;
  public static final byte EVENT_NUMBER_OF_COMPLETED_PACKETS = (byte)0x13;
  public static final byte EVENT_MODE_CHANGE = (byte)0x14;
  public static final byte EVENT_RETURN_LINK_KEYS = (byte)0x15;
  public static final byte EVENT_PIN_CODE_REQUEST = (byte)0x16;
  public static final byte EVENT_LINK_KEY_ReQUEST = (byte)0x17;
  public static final byte EVENT_LINK_KEY_NOTIFICATION = (byte)0x18;
  public static final byte EVENT_LOOPBACK_COMMAND = (byte)0x19;
  public static final byte EVENT_DATA_BUFFER_OVERFLOW = (byte)0x1A;
  public static final byte EVENT_MAX_SLOTS_CHANGE = (byte)0x1B;
  public static final byte EVENT_READ_CLOCK_OFFSET_COMPLETE = (byte)0x1C;
  public static final byte EVENT_CONNECTION_PACKET_TYPE_CHANED = (byte)0x1D;
  public static final byte EVENT_QOS_VIOLATION = 0x1E;
  public static final byte EVENT_PAGE_SCAN_REPETITION_MODE_CHANGE = (byte)0x20;
  public static final byte EVENT_FLOW_SPECIFICATION_COMPLETE = (byte)0x21;
  public static final byte EVENT_INQUIRY_RESULT_WITH_RSSI = (byte)0x22;
  public static final byte EVENT_READ_REMOTE_EXTENDED_FEATURES_COMPLETE = (byte)0x23;
  public static final byte EVENT_SYNCHRONOUS_CONNECTION_COMPLETE = (byte)0x2C;
  public static final byte EVENT_SYNCHRONOUS_CONNECTION_CHANGED = (byte)0x2D;
  
  public static final int OGF_LINK_CONTROL = 0x01;
  public static final int OCF_INQUIRY = 0x01;
  public static final int OCF_INQUIRY_CANCEL = 0x02;
  public static final int OCF_PERIODIC_INQUIRY_MODE = 0x03;
  public static final int OCF_EXIT_PERIODIC_INQUIRY_MODE = 0x04;
  public static final int OCF_CREATE_CONNECTION = 0x05;
  public static final int OCF_DISCONNECT = 0x06;
  public static final int OCF_CREATE_CONNECTION_CANCEL = 0x08;
  public static final int OCF_ACCEPT_CONNECTION_REQUEST = 0x09;
  public static final int OCF_REJECT_CONNECTION_REQUEST = 0x0A;
  public static final int OCF_LINK_KEY_REQUEST_REPLY = 0x0B;
  public static final int OCF_LINK_KEY_REQUEST_NEGATIVE_REPLY = 0x0C;
  public static final int OCF_PIN_CODE_REQUEST_REPLY = 0x0D;
  public static final int OCF_PIN_CODE_REQUEST_NEGATIVE_REPLY = 0x0E;
  public static final int OCF_CHANGE_CONNECTION_PACKET_TYPE = 0x0F;
  public static final int OCF_AUTHENTICATION_REQUESTED = 0x11;
  public static final int OCF_SET_CONNECTION_ENCRYPTION = 0x13;
  public static final int OCF_CHANGE_CONNECTION_LINK_KEY = 0x15;
  public static final int OCF_MASTER_LINK_KEY = 0x17;
  public static final int OCF_REMOTE_NAME_REQUEST = 0x19;
  public static final int OCF_REMOTE_NAME_REQUEST_CANCEL = 0x1A;
  public static final int OCF_READ_REMOTE_SUPPORTED_FEATURES = 0x1B;
  public static final int OCF_READ_REMOTE_EXTENDED_FEATURES = 0x1C;
  public static final int OCF_READ_REMOTE_VERSION = 0x1D;
  public static final int OCF_READ_CLOCK_OFFSET = 0x1F;
  public static final int OCF_READ_LMP_HANDLE = 0x20;
  public static final int OCF_SETUP_SYNCHRONOUS_CONNECTION = 0x28;
  public static final int OCF_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST = 0x29;
  public static final int OCF_REJECT_SYNCHRONOUS_CONNECTION_REQUEST = 0x2A;
  
  public static final int OGF_LINK_POLICY = 0x02;
  public static final int OCF_READ_LINK_POLICY_SETTINGS = 0x0C;
  public static final int OCF_WRITE_LINK_POLICY_SETTINGS = 0x0D;
  
  public static final int OGF_HCI_CONTROL_AND_BASEBAND = 0x03;
  public static final int OCF_RESET = 0x03;
  public static final int OCF_SET_EVENT_FILTER = 0x05;
  public static final int OCF_WRITE_PIN_TYPE = 0x0A;
  public static final int OCF_WRITE_LOCAL_NAME = 0x13;
  public static final int OCF_READ_LOCAL_NAME = 0x14;
  public static final int OCF_READ_CONN_ACC_TIMEOUT = 0x15;
  public static final int OCF_WRITE_CONN_ACC_TIMEOUT = 0x16;
  public static final int OCF_READ_PAGE_TIMEOUT = 0x17;
  public static final int OCF_WRITE_PAGE_TIMEOUT = 0x18;
  public static final int OCF_READ_SCAN_ENABLE = 0x19;
  public static final int OCF_WRITE_SCAN_ENABLE = 0x1A;
  public static final int OCF_WRITE_CLASS_OF_DEVICE = 0x24;
  public static final int OCF_SET_HOST_FLOW_CONTROL = 0x31; // ctrler to host
  public static final int OCF_HOST_BUFFER_SIZE = 0x33;
  public static final int OCF_HOST_NUMBER_OF_COMPLETED_PACKETS = 0x35;
  public static final int OCF_READ_LINK_SUPERVISION_TIMEOUT = 0x36;
  public static final int OCF_WRITE_LINK_SUPERVISION_TIMEOUT = 0x37;
  
  public static final int OGF_INFORMATIONAL_PARAMETERS = 0x04;
  public static final int OCF_READ_LOCAL_VERSION = 0x01;
  public static final int OCF_READ_LOCAL_SUPPORTED_COMMANDS = 0x02;
  public static final int OCF_READ_LOCAL_SUPPORTED_FEATURES = 0x03;
  public static final int OCF_READ_LOCAL_EXTENDED_FEATURES = 0x04;
  public static final int OCF_READ_BUFFER_SIZE = 0x05;
  public static final int OCF_READ_COUNTRY_CODE = 0x07;
  public static final int OCF_READ_BD_ADDR = 0x09;
  
  public static final int OGF_HCI_VENDOR_COMMANDS = 0x3F;
  
  public static final byte ERROR_SUCCESS = (byte)0x00;
  public static final byte ERROR_UNKNOWN_HCI_COMMAND = (byte)0x01;
  public static final byte ERROR_UNKNOWN_CONNECTION_IDENTIFIER = (byte)0x02;
  public static final byte ERROR_HARDWARE_FAILURE = (byte)0x03;
  public static final byte ERROR_PAGE_TIMEOUT = (byte)0x04;
  public static final byte ERROR_AUTHENTICATION_FAILURE = (byte)0x05;
  public static final byte ERROR_PIN_MISSING = (byte)0x06;
  public static final byte ERROR_MEMORY_CAPACITY_EXCEEDED = (byte)0x07;
  public static final byte ERROR_CONNECTION_TIMEOUT = (byte)0x08;
  public static final byte ERROR_CONNECTION_LIMIT_EXCEEDED = (byte)0x09;
  public static final byte ERROR_SYNCHRONOUS_CONNECTION_LIMIT_TO_A_DEVICE_EXCEEDED = (byte)0x0A;
  public static final byte ERROR_ACL_CONNECTION_ALREADY_EXISTS = (byte)0x0B;
  public static final byte ERROR_COMMAND_DISALLOWED = (byte)0x0C;
  public static final byte ERROR_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES = (byte)0x0D;
  public static final byte ERROR_CONNECTION_REJECTED_DUE_TO_SECURITY_REASONS = (byte)0x0E;
  public static final byte ERROR_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR = (byte)0x0F;
  public static final byte ERROR_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED = (byte)0x10;
  public static final byte ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE = (byte)0x11;
  public static final byte ERROR_INVALID_HCI_COMMAND_PARAMETERS = (byte)0x12;
  public static final byte ERROR_REMOTE_USER_TERMINATED_CONNECTION = (byte)0x13;
  public static final byte ERROR_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES = (byte)0x14;
  public static final byte ERROR_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_POWER_OFF = (byte)0x15;
  public static final byte ERROR_CONNECTION_TERMINATED_BY_LOCAL_HOST = (byte)0x16;
  public static final byte ERROR_REPEATED_ATTEMPTS = (byte)0x17;
  public static final byte ERROR_PAIRING_NOT_ALLOWED = (byte)0x18;
  public static final byte ERROR_UNKNOWN_LMP_PDU = (byte)0x19;
  public static final byte ERROR_UNSUPPORTED_REMOTE_FEATURE = (byte)0x1A;
  
  // can be discovered and connected to in idle mode
  // can start inquiries and pages in master or idle mode
  // can do nothing in slave mode
  public static final int STATE_IDLE = 0;
  public static final int STATE_MASTER = 1;
  public static final int STATE_SLAVE = 2; 
  
  public static final int LINK_STATE_ACTIVE = 0;
  public static final int LINK_STATE_HOLD = 1;
  public static final int LINK_STATE_SNIFF = 2;
  public static final int LINK_STATE_PARK = 3;
  
  public static final int SCAN_ENABLE_NONE = 0x00;
  public static final int SCAN_ENABLE_INQUIRY = 0x01;
  public static final int SCAN_ENABLE_PAGE = 0x02;
  public static final int SCAN_ENABLE_INQUIRY_PAGE = 0x03;
  
  public static final int HOST_FLOW_CONTROL_NONE = 0x00;
  public static final int HOST_FLOW_CONTROL_ACL = 0x01;
  public static final int HOST_FLOW_CONTROL_SOC = 0x02;
  public static final int HOST_FLOW_CONTROL_ACL_SOC = 0x03;
  
  public static final int PIN_FIXED = 0x00;
  public static final int PIN_VARIABLE = 0x01;
  
  public void addDeviceListener(BTDeviceListener deviceListener);
  public int getState();
  public boolean isInquiryScanning();
  public boolean isPageScanning();
  public boolean isInquiry();
  public long getInquiryTimeRemaining();
  public void inquiryResult(BTDevice device);
  public byte[] getBDAddr();
  public byte[] getClassOfDevice();
  public void requestConnection(BTDevice device, boolean allowRoleSwitch);
  public void acceptConnectionRequest(BTDevice device, boolean changeRole);
  public void rejectConnectionRequest(BTDevice device, byte reason);
  public void sendACLPacket(BTDevice device, int options, byte[] packet);
  public void disconnect(BTDevice device, byte reason);
  public String requestName();
}