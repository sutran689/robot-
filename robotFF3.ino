#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>    
#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17
#define  pinA1         7
#define  pinA2         6
#define  pinB1         8
#define  pinB2         4
#define  enA           5
#define  enB           3
#define pressures   false

#define rumble      false

PS2X ps2x; // create PS2 Controller Class

Servo myservo; 
int error = 0;
byte type = 0;
byte vibrate = 0;
int speed;
void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
  pinMode (pinA1, OUTPUT);
  pinMode (pinB1, OUTPUT);
  pinMode (pinB2, OUTPUT);
  pinMode (pinA2, OUTPUT);
  pinMode (enA, OUTPUT);
  pinMode (enB, OUTPUT);
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
   
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0)
  {
    Serial.print("Found Controller, configured successful ");
  } 
  type = ps2x.readType(); 
} 
  void motor_off()
  {
        digitalWrite(enA,LOW);
        digitalWrite(enB,LOW);
        digitalWrite(pinA1, LOW);
        digitalWrite(pinA2, LOW);
        digitalWrite(pinB1, LOW);
        digitalWrite(pinB2, LOW);
   }
  void motor_tien(int speed)
  { 
        digitalWrite(pinA2, HIGH);
        digitalWrite(pinA1, LOW);

        digitalWrite(pinB1, HIGH);
        digitalWrite(pinB2, LOW);
       
        analogWrite (enA, speed);
        analogWrite (enB, speed);
 
   }
  
  void motor_lui()
  { 
        digitalWrite(pinA1, HIGH);
        digitalWrite(pinA2, LOW);

        digitalWrite(pinB2, HIGH);
        digitalWrite(pinB1, LOW);
       
        analogWrite (enA, 110);
        analogWrite (enB, 110);
  }
  void trai()
  {
        digitalWrite(pinA1, HIGH);
        digitalWrite(pinA2, LOW);
        analogWrite (enA, 80);
        digitalWrite(pinB1, HIGH);
        digitalWrite(pinB2, LOW);
        analogWrite (enB, 80);
  }
  void phai()
  {
        digitalWrite(pinA2, HIGH);
        digitalWrite(pinA1, LOW);
        analogWrite (enA, 80);
        digitalWrite(pinB2, HIGH);
        digitalWrite(pinB1, LOW);
        analogWrite (enB, 80);
  }
void loop() {


 if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      //Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      delay(100);
 }
  speed = ps2x.Analog(PSS_LY);
  myservo.write(150); 
  motor_off();
  if(error == 1) //skip loop if no controller found
    return; 
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_PAD_UP))
         {     
          motor_tien(speed);
          Serial.print(ps2x.Analog(PSS_LY), DEC);
         }
    
    if(ps2x.Button(PSB_PAD_RIGHT))
         {
          phai();
         }
    
    if(ps2x.Button(PSB_PAD_LEFT))
         {
          trai();
         }
    
    if(ps2x.Button(PSB_PAD_DOWN))
         {
           motor_lui();
         }   
    
    if(ps2x.NewButtonState(PSB_CROSS))  
         {
           Serial.print("ok ");
           myservo.write(180);
           delay(500);
          
           myservo.write(0);  
           delay(500);
          }
     delay(100);  
}
