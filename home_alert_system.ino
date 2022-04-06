#include <SoftwareSerial.h>

SoftwareSerial mySerial(9,10);
const int TOUCH_SENSOR_PIN = 7; // Arduino pin connected to touch sensor's pin
const int BUZZ_TOUCH = 3; // Arduino pin connected to Buzzer's pin
const int pirsensor = 11;
const int buzz_pir = 12;
const int gasValue = A0;
const int buzz_smoke = 4;
int data=0;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);               // initialize serial
  pinMode(TOUCH_SENSOR_PIN, INPUT); // set arduino pin to input mode
  pinMode(BUZZ_TOUCH, OUTPUT);   // set arduino pin to output mode
  pinMode(pirsensor, INPUT);
  pinMode(buzz_pir, OUTPUT);
  pinMode(gasValue, INPUT);
  pinMode(buzz_smoke, OUTPUT);
  //digitalWrite(BUZZ_TOUCH,LOW);
  //(buzz_pir,LOW);
  //digitalWrite(buzz_smoke,LOW);

}

void loop() {
  int touchState = digitalRead(TOUCH_SENSOR_PIN); // read new state
  if (touchState == HIGH) {
    SendMessage_touch();
    Serial.println("The sensor is being touched");;
    //digitalWrite(BUZZ_TOUCH, HIGH); // turn on Piezo Buzzer
  }
  else if (touchState == LOW) {
    Serial.println("The sensor is untouched");
    //digitalWrite(BUZZ_TOUCH, LOW);  // turn off Piezo Buzzer
  }
  

  data = analogRead(gasValue);
  Serial.print("Gas Level: ");
  Serial.println(data);
  delay(1000);
  if ( data > 500) //
  {
    SendMessage_smoke();
    Serial.print("Abnormal gas level");
    //digitalWrite(buzz_smoke, HIGH);
    delay(1000);
  }
  else
  {
    Serial.print("Gas Level Low ");
    //digitalWrite(buzz_smoke, LOW);
    delay(1000);
  }


  
  if ( digitalRead(pirsensor) == HIGH) //
  {
    //digitalWrite(buzz_pir, HIGH);
    SendMessage_pir();
    Serial.println("A Person in your Room ");
    Serial.println("message sent.");
    delay(8000);
  }
  if ( digitalRead(pirsensor) == LOW) //
  {
    //digitalWrite(buzz_pir, LOW);
    delay(1000);
  }

  
}
void SendMessage_touch()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+919789826018\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Someone touched the door");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}

void SendMessage_pir()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+919789826018\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Motion Detected.");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}

void SendMessage_smoke()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+919789826018\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Abnormal Gas Detected.");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
