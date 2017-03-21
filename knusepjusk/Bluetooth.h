#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "Arduino.h"
#include <PlabBTSerial.h>


//...........................................................................
// Always include these two methods .
// They send a message to the BT port, without or with an int value
// 
void BTSerialSendMessage(PLabBTSerial& btSerial, String msgString) {
  btSerial.println(msgString); 
}

void BTSerialSendMessage(PLabBTSerial& btSerial, String msgString,int msgValue) {
  btSerial.print(msgString); 
  btSerial.print(",");
  btSerial.println(msgValue);
}
//...........................................................................

#endif
