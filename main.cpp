#include <Arduino.h>
#include <Wifi.h>
#include <AsyncUDP.h>

  int pinX = 36;  //Here is the pin which the Xaxis from the joystick has been put in to, defined.
  int pinY = 39;  //Here is the pin which the Yaxis from the joystick has been put in to, defined.
  int buttonClick = 13;  //Here is the pin which the click button from the joystick has been put in to, defined.
  int potPin = 34;  //Here is the pin which the potentiometer has been put in to, defined.
  int potVal;
  int prevX;
  int prevY;
  int tolerance = 20;

  int port = 7000; //Here is the port which the udp message is send over, defined.

  const char * ssid = "DueSoelv"; //Here is the name for the network defined
  const char * password = "halloejpaapissehotellet";  // here is the password for the network defined
  AsyncUDP udp; //Here an udp object is being made from the AsyncUDP library

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(buttonClick, INPUT_PULLUP);
  pinMode(potPin,INPUT);
  prevX = analogRead(pinX);
  prevY = analogRead(pinY); 
}

void direction(int horizontal, int vertical){// heres a class for the joystick which defines whether the joysticks all the way to the right, left, up, down or if its in the middle.
  if(horizontal == 0){
    udp.broadcastTo("moveleft", 7000);
    Serial.println("left");
  } if(horizontal ==4095){
    udp.broadcastTo("moveright", 7000);
    Serial.println("Right");
  } if(vertical == 0){
    udp.broadcastTo("moveup", 7000);
    Serial.println("Up");
  } if(vertical == 4095){
    udp.broadcastTo("movedown", 7000);
    Serial.println("Down");
  } else{
    Serial.println("Still");
    udp.broadcastTo("stop", 7000);
  }
}

void speed(int Speed){ //heres a class over the potentiometer which defines the speed through 4 stages.
  /*if (Speed < 1000){
    udp.broadcastTo("speed 1", 7000);
  }  (Speed >1000 || Speed < 2000){
    udp.broadcastTo("speed 4", 7000);
  } (Speed > 2000 || Speed < 3000){ 
    udp.broadcastTo("speed 7", 7000);
  }Speed > 3000 || Speed <= 4095){ 
    udp.broadcastTo("speed 9", 7000);
  }*/
  switch(Speed){
      case 1:
          udp.broadcastTo("1", 7000);
          Serial.println("speed1");
              break;
      case 2:
          udp.broadcastTo("2", 7000);
          Serial.println("speed2");
      break;
      case 3:
          udp.broadcastTo("3", 7000);
          Serial.println("speed2");
      break;
      case 4:
          udp.broadcastTo("4", 7000);
          Serial.println("speed2");
      break;
      
      /*case 2001 ... 3000:
          udp.broadcastTo("speed 7", 7000);
          Serial.println("speed3");
      
      case 3001 ... 4095:
          udp.broadcastTo("speed 9", 7000);
          Serial.println("speed4");
      */
  }
}

void loop() {
  /*if(abs(analogRead(pinX)-prevX) > tolerance || abs(analogRead(pinY)-prevY) > tolerance){
    Serial.println(map(analogRead(pinX), 0, 4095, -100, 100));
    Serial.println(map(analogRead(pinY), 0, 4095, -100, 100));
    prevX = analogRead(pinX);
  }*/

  direction(analogRead(pinX), analogRead(pinY));
  if(digitalRead(buttonClick) == LOW){
    udp.broadcastTo("init 9 9", 7000);
    Serial.println("Clicked");
  }
  potVal = analogRead(potPin);// here it reads the input from the potentiometer and puts it in the speed class
  
  if(potVal < 1000){
      speed(1);
  }
  if(potVal > 1000 || potVal < 2000){
      speed(2);
  }
  if(potVal > 2000 || potVal < 3000){
      speed(3);
  }
  if(potVal > 3000 || potVal <= 4095){
      speed(4);
  }


 // Serial.println(potVal);

}