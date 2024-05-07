#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Define servo objects
Servo armSweepServo;
Servo ShoulderSwivelServo;
Servo gripperServo;
int motor_belt = 5;
int motor_L = 2;
int motor_T = 3;
int ir_sensor = 4;
// Define servo motor pins
const int armSweepPin = 9;
const int ShoulderSwivelPin = 10;
const int gripperPin = 11;
String dataInS = " ";
String stri = "";
int start = 0;
int gripper = 0;
int armSweep = 0;
int ShoulderSwivel = 0;
int elbowExtension = 0;
int count = 0;
int ABPM = 120;
int SBPM = 80;
int GBPM = 0;//
int mode = 0;
int gripp_read = A1;
int targetPosition =0;
unsigned long previousMillis = 0;  // Stores the last time the message was updated
const long interval = 1000;
const int servoIncrement = 1;
const int delayBetweenSteps = 30; // Delay in milliseconds between each servo step
void setup() 
{
    Serial.begin(9600);
    lcd.init();                      // initialize the lcd 
    lcd.init();
    pinMode(gripp_read,INPUT_PULLUP);
    pinMode(ir_sensor,INPUT);
    pinMode(motor_belt,OUTPUT);
    pinMode(motor_L,OUTPUT);
    pinMode(motor_T,OUTPUT);
    lcd.backlight();
  // Print a message to the LCD
    lcd.print("Hello, World!");
  // Attach servo motors to pins
    armSweepServo.attach(armSweepPin);
    ShoulderSwivelServo.attach(ShoulderSwivelPin);
  //elbowExtensionServo.attach(elbowExtensionPin);
  gripperServo.attach(gripperPin);
  //resetservo();
  //moveServoToPosition(gripperServo, 0);//5
 // digitalWrite(motor_L,LOW);
 // digitalWrite (motor_T,HIGH);
  // resetservo();
   pinMode(motor_L,LOW);
  pinMode(motor_T,LOW);
   digitalWrite (motor_belt,HIGH);
  lcd.clear();
  delay(1000);
   moveServoToPosition(ShoulderSwivelServo, 100);
   moveServoToPosition(gripperServo, 0);//5
   delay(2000);
   digitalWrite (motor_belt,LOW);
}
void down()
{
digitalWrite(motor_L,HIGH);
  digitalWrite (motor_T,LOW);
  //delay(10000);
}
void UP()
{
digitalWrite(motor_L,LOW);
  digitalWrite (motor_T,HIGH);
 // delay(6000);
}
void stop()
{
  digitalWrite(motor_L,LOW);
  digitalWrite (motor_T,LOW);
}
void resetservo()
{
  moveServoToPosition(ShoulderSwivelServo, 160);//2
  moveServoToPosition(gripperServo, 180);//5
  moveServoToPosition(armSweepServo, 90);
 
}
void moveServoToPosition(Servo& servo, int targetPosition) 
{
  int currentPosition = servo.read();
  if (currentPosition < targetPosition) 
  {
    for (int pos = currentPosition; pos <= targetPosition; pos += servoIncrement) 
    {
      servo.write(pos);
      delay(delayBetweenSteps);
      }
  } 
   else 
   {
    for (int pos = currentPosition; pos >= targetPosition; pos -= servoIncrement)
     {
      servo.write(pos);
      delay(delayBetweenSteps);
    }
  }
}
void check()
{
  //UP();
   //
   if(count==4)
   {
   moveServoToPosition(ShoulderSwivelServo, 100);
    stop();
   moveServoToPosition(gripperServo, 0);//5
   down();
   delay(25000);
    stop();
    moveServoToPosition(armSweepServo, 90);
   moveServoToPosition(gripperServo, 85);//5
   delay(1000);
   UP();
   delay(25000);
   moveServoToPosition(ShoulderSwivelServo, 0);
   stop();
   // moveServoToPosition(armSweepServo, 0);//rotate 
     delay(1000);
     down();
      delay(25000);
     stop();
    moveServoToPosition(gripperServo, 0);//5
     UP();
     delay(25000);
     moveServoToPosition(ShoulderSwivelServo,100);
      Serial.println("Start");
      //moveServoToPosition(ShoulderSwivelServo, 0);
      count = 0;
    stop();
   }
    if(count<4)
   {
    moveServoToPosition(ShoulderSwivelServo, 100);
    stop();
   moveServoToPosition(gripperServo, 0);//5
   down();
   delay(25000);
    stop();
    moveServoToPosition(armSweepServo, 90);
   moveServoToPosition(gripperServo, 85);//5
   delay(1000);
   UP();
   delay(25000);
   stop();
    moveServoToPosition(armSweepServo, 0);
     delay(1000);
     down();
      delay(25000);
     stop();
    moveServoToPosition(gripperServo, 0);//5
     UP();
     delay(25000);
      Serial.println("Start");
      //moveServoToPosition(ShoulderSwivelServo, 0);
    stop();
   }
   
}
void loop()
 {
  if(digitalRead(ir_sensor)==HIGH)
  {
    mode=1;
    delay(5000);
    digitalWrite (motor_belt,HIGH);
     Serial.println("Start");
    delay(5000);
  }
  //i//f(digitalRead(ir_sensor)==LOW)
  //{
  //   Serial.print("NO");
 //    delay(1000);
 // }
  
        // unsigned long currentMillis = millis();  
  
      if(mode == 1)
      {
        delay(6000);
      if (Serial.available() >0) // Send data only when you receive data:
      { 
             stri = Serial.readStringUntil('\n'); //Read the incoming data and store it into variable data
             delay(10);
            lcd.clear();
          // moveServoToPosition(armSweepServo, 120);
          // moveServoToPosition(ShoulderSwivelServo, 80); 
           //moveServoToPosition(armSweepServo, 90);  
         if (stri.startsWith("0 yes"))//rot
      {
           delay(2000);
          digitalWrite (motor_belt,LOW);
          stri = "";
          mode = 0;
          delay(1000);
      }
           if (stri.startsWith("1 no"))//rot
      {
         count ++;
         delay(10);
         check();
        stri = "";
      }
      //   if (stri.startsWith("down"))//rot
      // {
      //    down();
      //    delay(1000);
      //    stop();
      // }
      //    if (stri.startsWith("up"))//rot
      // {
      //     UP();
      //    delay(1000);
      //    stop();
      // }

      //  if (stri.startsWith("cube_1"))//rot
      // {
      //    dataInS = stri.substring(6, stri.length());
      //     ABPM = dataInS.toInt();
      //    moveServoToPosition(armSweepServo, ABPM);
      // }
      // if (stri.startsWith("cube_2"))//40
      // {
      //    dataInS = stri.substring(6, stri.length());
      //     SBPM = dataInS.toInt();
      //    moveServoToPosition(ShoulderSwivelServo, SBPM);
      //   // SBPM = 80;
      // }
      // if (stri.startsWith("cube_3"))// check()
      // {
      //   dataInS = stri.substring(6, stri.length());
      //     GBPM = dataInS.toInt();
      //    moveServoToPosition(gripperServo, GBPM);//5
      //    //GBPM
      // }
      //  if (stri.startsWith("done"))// check()
      // {
      //   check();
      //   stri = "";
      // }
 }
  delay(1000);
 }
 }
 //       if (stri.startsWith("armsweep"))
//       {
//         Serial.println("arm");
//         dataInS = stri.substring(8, stri.length());
//        ABPM = dataInS.toInt();
//      //  ABPM_SW = map(ABPM, 0, 120, 50, 110);//100 bottom
//        moveServoToPosition(armSweepServo,  ABPM);
//       }
//        if (stri.startsWith("gripperServo"))
//       {
//         Serial.println("gripperServo");
//         dataInS = stri.substring(12, stri.length());
//        ABPM = dataInS.toInt();
//        //if (ABPM<=50) ABPM=50;if (ABPM>=110) ABPM=110;
//        // ABPM_SW = map(ABPM, 0, 120, 50, 110);//100 bottom
//        // moveServoToPosition(armSweepServo,  ABPM);
//         moveServoToPosition(gripperServo, ABPM);
//            // moveServoToPosition(armSweepServo, 120);
//           ////moveServoToPosition(ShoulderSwivelServo, 80); 
//          // moveServoToPosition(elbowExtensionServo, 75);
//           //moveServoToPosition(pitchServo, 0);
        
//          // moveServoToPosition(gripperServo, 80); //4
//       }
//         if (stri.startsWith("Shoulder"))
//       {
//         Serial.println("Shoulder");
//         dataInS = stri.substring(8, stri.length());
//        ABPM = dataInS.toInt();
//        //if (ABPM<=50) ABPM=50;if (ABPM>=110) ABPM=110;
//      // ABPM_SW = map(ABPM, 0, 120, 50, 110);//100 bottom
//           // moveServoToPosition(armSweepServo,  ABPM);
//         //moveServoToPosition(gripperServo, ABPM);
//            // moveServoToPosition(armSweepServo, 120);
//         moveServoToPosition(ShoulderSwivelServo, ABPM); 
//          // moveServoToPosition(elbowExtensionServo, 75);
//           //moveServoToPosition(pitchServo, 0);
        
//          // moveServoToPosition(gripperServo, 80); //4
//       }
//         if (stri.startsWith("pitch"))
//       {
//         Serial.println("pitch");
//         dataInS = stri.substring(5, stri.length());
//        ABPM = dataInS.toInt();
//        //if (ABPM<=50) ABPM=50;if (ABPM>=110) ABPM=110;
//        // ABPM_SW = map(ABPM, 0, 120, 50, 110);//100 bottom
//           // moveServoToPosition(armSweepServo,  ABPM);
//         //moveServoToPosition(gripperServo, ABPM);
//            // moveServoToPosition(armSweepServo, 120);
//         //moveServoToPosition(ShoulderSwivelServo, ABPM); 
//          // moveServoToPosition(elbowExtensionServo, 75);
//           moveServoToPosition(pitchServo,  ABPM);
        
//          // moveServoToPosition(gripperServo, 80); //4
//       }

//  }
      //   if(start == 1)
      //     {
      //   Serial.println("s1");
      //   moveServoToPosition(armSweepServo, ABPM_SW);
      //   delay(100);
      //   //  if(start==0)
      //   //   {
      //  // dataInS = stri.substring(8, stri.length());
      //  // SBPM = dataInS.toInt();
      //     SBPM = 25;
      //   Serial.print("shoulder = ");
      //   Serial.print(SBPM);
      //   moveServoToPosition(gripperServo, 0);
      //   if (SBPM>=100) SBPM=100;
      //   if (SBPM<=10) SBPM=10;
      //   if(SBPM<=40)
      //   {
      //       Value = map(SBPM, 25, 40, 85, 20);//100 bottom
      //     moveServoToPosition(elbowExtensionServo,Value);
      //     Serial.print(" elbow = ");
      //     Serial.println(Value);
      //     if(Value>=50)
      //     {
      //    Value1 = map(Value, 50, 90, 20, 50);
      //    Serial.print(" pitch = ");
      //    Serial.println(Value1);
      //    moveServoToPosition(pitchServo, Value1); //4
      //     }
      //     moveServoToPosition(ShoulderSwivelServo, 22); 
      //     delay(1000);
      //   }
      //    start=2;
      //    delay(100);
      //     }
      //     if(start==2)
      //     {
      //        Serial.println("s2");
      //     moveServoToPosition(gripperServo, 80); //4 
      //     start=3;

      //     }
      //     if(start==3)
      //     {
      //       targetPosition = 0;
      //        Serial.println("s3");
      //   moveServoToPosition(ShoulderSwivelServo, 50); 
      //   delay(500);
      //   moveServoToPosition(armSweepServo, 0);
      //     start=4;
      //     }
      //     if(start==4)
      //     { 
      //        Serial.println("stp");
      //     moveServoToPosition(gripperServo, 0);
      //     moveServoToPosition(ShoulderSwivelServo, 80); 
      //     moveServoToPosition(elbowExtensionServo, 75);
      //      moveServoToPosition(pitchServo, 0);
      //      moveServoToPosition(armSweepServo, 120);
      //      moveServoToPosition(gripperServo, 80); //4
      //       start=5;
      //     }
      //     if (stri.startsWith("gripper"))
      //     {
      //   dataInS = stri.substring(7, stri.length());
      //   GBPM = dataInS.toInt();
      //   GBPM = map(GBPM, 0, 10, 80, 0);//100 bottom
      //   moveServoToPosition(gripperServo, GBPM-4);
      //   }
      //   Serial.println(GBPM);
      
      //}
      //if (stri.startsWith("pitch")){dataInS = stri.substring(5, stri.length());PBPM = dataInS.toInt(); if (PBPM>=100) PBPM=100;moveServoToPosition(pitchServo, PBPM);}
      //if (stri.startsWith("elbow")){dataInS = stri.substring(5, stri.length());EBPM = dataInS.toInt();moveServoToPosition(elbowExtensionServo, EBPM);}
      
     // if (stri.startsWith("shoulder")){dataInS = stri.substring(8, stri.length());SBPM = dataInS.toInt();moveServoToPosition(ShoulderSwivelServo, SBPM);}
     // if (stri.startsWith("shoulder"))
      //{
       

     // }
     
    //  lcd.setCursor(0,0);
    //  lcd.print("A ");
    //  lcd.print(ABPM);
    //  lcd.setCursor(0,1);
    //  lcd.print("S ");
    //  lcd.print(SBPM);
    //  lcd.setCursor(6,0);
    //  lcd.print("P ");
    //  lcd.print(PBPM);
    //  lcd.setCursor(6,1);
    //  lcd.print("E ");
    //  lcd.print(EBPM);
    //  lcd.setCursor(11,0);
    //  lcd.print("G ");
    //  lcd.print(GBPM);
    //}
     //moveServoToPosition(armSweepServo, ABPM);
     // moveServoToPosition(ShoulderSwivelServo, SBPM); 
     // moveServoToPosition(elbowExtensionServo, EBPM);
     //moveServoToPosition(gripperServo, 0);//GBPM
     // moveServoToPosition(pitchServo, PBPM); //4
 // }
   //runn();
   //runstart();
 //}