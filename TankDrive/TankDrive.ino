#include <SPI.h>
#include <Ethernet.h>
#include <RobotOpen.h>
#include <Serial.h>

/* I/O Setup */
USBJoystick usb1('0');  // Assign the logitech USBJoystick object to bundle 0

void setup(){
/* Initiate comms */
RobotOpen.begin();
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  //Shifter Variables
  //int highGear = 200, lowGear = 50; //PWM Values for Servo's   

  //Drive motors
  RobotOpen.setPWM(SIDECAR_PWM1, usb1.makePWM(ANALOG_LEFTY, NORMAL));
  RobotOpen.setPWM(SIDECAR_PWM2, usb1.makePWM(ANALOG_RIGHTY, INVERT));

  //Current Shifter Setup
  RobotOpen.setPWM(SIDECAR_PWM4,usb1.makePWM(BTN1,INVERT)); //THIS WORKS
  RobotOpen.setPWM(SIDECAR_PWM3,usb1.makePWM(BTN1,INVERT)); //THIS WORKS

  if(usb1.getIndex(BTN5)){
    RobotOpen.setPWM(SIDECAR_PWM5, 20); 
  }
  else if(usb1.getIndex(BTN6)){
    RobotOpen.setPWM(SIDECAR_PWM5, 230);
  }
  else
    RobotOpen.setPWM(SIDECAR_PWM5, 127);
}  


/* This is called while the robot is disabled
 * You must make sure to set all of your outputs
 * to safe/disable values here
 */
void disabled() {
// PWMs are automatically disabled
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 * You can use either publishAnalog, publishDigital, publishByte, publishShort, or publishLong
 * Specify a bundle ID with a single character (a-z, A-Z, 0-9) - Just make sure not to use the same twice!
 */
void timedtasks() {
  RobotOpen.publishAnalog(ANALOG0, 'A');   // Bundle A
  RobotOpen.publishAnalog(ANALOG1, 'B');   // Bundle B
  RobotOpen.publishAnalog(ANALOG2, 'C');   // Bundle C
  RobotOpen.publishAnalog(ANALOG3, 'D');   // Bundle D
  RobotOpen.publishAnalog(ANALOG4, 'E');   // Bundle E
  RobotOpen.publishAnalog(ANALOG5, 'F');   // Bundle 
}


/* This is the main program loop that keeps comms operational
* There's no need to touch anything here!!!
*/
void loop() {
  RobotOpen.pollDS();
  if(RobotOpen.enabled())
    enabled();
  else
    disabled();
    timedtasks();
  RobotOpen.outgoingDS();
}


