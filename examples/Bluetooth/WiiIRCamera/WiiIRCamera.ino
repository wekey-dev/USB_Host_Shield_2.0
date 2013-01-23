/*
Example sketch for the Wii libary showing the IR camera functionality. This example
is for the Bluetooth Wii library developed for the USB shield from Circuits@Home
 
Created by Allan Glover and includes much from what Kristian Lauszus wrote in the existing 
Wii example. Contact Kristian:  http://blog.tkjelectronics.dk/ or send email at kristianl@tkjelectronics.com.
Contact Allan at adglover9.81@gmail.com
 
To test the Wiimote IR camera, you will need access to an IR source. Sunlight will work but is not ideal. 
The simpleist solution is to use the Wii sensor bar, i.e. emitter bar, supplied by the Wii system. Otherwise,
wire up a IR LED yourself.
*/

#include <Wii.h>
#ifndef WIICAMERA // Used to check if WIICAMERA is defined
#error "Uncomment WIICAMERA in Wii.h to use this example"
#endif
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
WII Wii(&Btd,PAIR); // This will start an inquiry and then pair with your Wiimote - you only have to do this once
//WII Wii(&Btd); // After the wiimote pairs once with the line of code above, you can simply create the instance like so and re upload and then press any button on the Wiimote

bool printAngle;
uint8_t printObjects;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nWiimote Bluetooth Library Started"));
}

void loop() {
  Usb.Task();
  if(Wii.wiimoteConnected) {
    if(Wii.getButtonClick(HOME)) { // You can use getButtonPress to see if the button is held down
      Serial.print(F("\r\nHOME"));
      Wii.disconnect();
    }
    else {
      if(Wii.getButtonClick(ONE))
        Wii.IRinitialize(); // Run the initialisation sequence
      if(Wii.getButtonClick(MINUS)) {
        if(!Wii.isIRCameraEnabled())
          Serial.print(F("\r\nEnable IR camera first"));
        else {
          if(printObjects > 0)
            printObjects--;
        }
      }
      if(Wii.getButtonClick(PLUS)) {
        if(!Wii.isIRCameraEnabled())
          Serial.print(F("\r\nEnable IR camera first"));
        else {
          if(printObjects < 4)
            printObjects++;
        }
      }
      if(Wii.getButtonClick(A)) {
        printAngle = !printAngle;
        Serial.print(F("\r\nA"));
      }
      if(Wii.getButtonClick(B)) {
        Serial.print(F("\r\nBattery level: "));
        Serial.print(Wii.getBatteryLevel()); // You can get the battery level as well
      }
    }
    if(printObjects > 0) {
      Serial.print(F("\r\ny1: "));
      Serial.print(Wii.getIRy1());  
      Serial.print(F("\tx1: "));
      Serial.print(Wii.getIRx1()); 
      Serial.print(F("\ts1:"));
      Serial.print(Wii.getIRs1());
      if(printObjects > 1) {
        Serial.print(F("\t\ty2: "));
        Serial.print(Wii.getIRy2());  
        Serial.print(F("\tx2: "));
        Serial.print(Wii.getIRx2()); 
        Serial.print(F("\ts2:"));
        Serial.print(Wii.getIRs2());
        if(printObjects > 2) {
          Serial.print(F("\t\ty3: "));
          Serial.print(Wii.getIRy3());  
          Serial.print(F("\tx3: "));
          Serial.print(Wii.getIRx3()); 
          Serial.print(F("\ts3:"));
          Serial.print(Wii.getIRs3());
          if(printObjects > 3) {
            Serial.print(F("\t\ty4: "));
            Serial.print(Wii.getIRy4());  
            Serial.print(F("\tx4: "));
            Serial.print(Wii.getIRx4()); 
            Serial.print(F("\ts4:"));
            Serial.print(Wii.getIRs4());
          }
        }
      }
    } 
    if(printAngle) { // There is no extension bytes avaliable, so the Motionplus or Nunchuck can't be read
      Serial.print(F("\r\nPitch: "));
      Serial.print(Wii.getPitch());
      Serial.print(F("\tRoll: "));
      Serial.print(Wii.getRoll());
    }
  }
}
