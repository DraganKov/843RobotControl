#include <SPI.h>
#include <Ethernet.h>
#include <RobotOpen.h>

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
  pinMode(SIDECAR_DIGITAL7, OUTPUT);
  
  //Compressor 
  if(usb1.getIndex(BTN9)){
    digitalWrite(SIDECAR_DIGITAL7, LOW); //LOW == ON
  }
  else{
    digitalWrite(SIDECAR_DIGITAL7, HIGH); //HIGH == OFF
  }

  //Drive motors
  RobotOpen.setPWM(SIDECAR_PWM1, usb1.makePWM(ANALOG_RIGHTY, INVERT));//Right Motor
  RobotOpen.setPWM(SIDECAR_PWM2, usb1.makePWM(ANALOG_LEFTY, NORMAL));//Left Motor

  //Shifter Servos
  RobotOpen.setPWM(SIDECAR_PWM4, usb1.makePWM(RIGHT_ANALOG_BTN, INVERT));//Right Shifter
  RobotOpen.setPWM(SIDECAR_PWM3, usb1.makePWM(RIGHT_ANALOG_BTN, INVERT));//Left Shifter

  //X-axis  
  if(usb1.getIndex(BTN3)){
      RobotOpen.setPWM(SIDECAR_PWM9, 122);//x-axis left rotation
  }
  else if(usb1.getIndex(BTN1)){
      RobotOpen.setPWM(SIDECAR_PWM9, 145);//x-axis right rot
  }
  else{
    RobotOpen.setPWM(SIDECAR_PWM9, 130);
  }
  
  //Y-AXIS
  if(usb1.getIndex(BTN2)){
    RobotOpen.setPWM(SIDECAR_PWM10, 140);
  }
  else if(usb1.getIndex(BTN4){
    RobotOpen.setPWM(SIDECAR_PWM10, 120);
  }
  else{
    RobotOpen.setPWM(SIDECAR_PWM10, 130);
   
    
  //INTAKE ROLLER CODE
  if(usb1.getIndex(BTN5)){
    RobotOpen.setPWM(SIDECAR_PWM5, 40);  //INTAKE
  }
  else if(usb1.getIndex(BTN6)){
    RobotOpen.setPWM(SIDECAR_PWM5, 210); //EXAUST
  }
  else{
    RobotOpen.setPWM(SIDECAR_PWM5, 127); // REST
  }
  
  //Shooter Motors
  if(usb1.getIndex(BTN10)){
    RobotOpen.setPWM(SIDECAR_PWM7, 75);
  }
   else{
     RobotOpen.setPWM(SIDECAR_PWM7, 127);
   }
}


/* This is called while the robot is disabled
 * You must make sure to set all of your outputs
 * to safe/disable values here*/
void disabled(){
  // PWMs are automatically disabled
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 * You can use either publishAnalog, publishDigital, publishByte, publishShort, or publishLong
 * Specify a bundle ID with a single character (a-z, A-Z, 0-9) - Just make sure not to use the same twice!
 */
void timedtasks() {
  
  RobotOpen.publishDigital(usb1.getIndex(BTN1), '1');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN2), '2');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN3), '3');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN4), '4');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN5), '5');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN6), '6');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN7), '7');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN8), '8');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN9), '9');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(BTN10), '10');   // Bundle 
  
  RobotOpen.publishAnalog(usb1.getIndex(ANALOG_RIGHTY), 'A');   // Bundle 
  RobotOpen.publishAnalog(usb1.getIndex(ANALOG_LEFTY), 'B');   // Bundle 
  
  RobotOpen.publishDigital(usb1.getIndex(RIGHT), 'C');   // Bundle 
  RobotOpen.publishDigital(usb1.getIndex(LEFT), 'D');   // Bundle 

  


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



