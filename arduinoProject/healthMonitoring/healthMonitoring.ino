#include <DHT.h>                   // Humidity sensor library
# define DHTPIN 11                 // DHT pin
# define DHTTYPE DHT11            
DHT dht(DHTPIN, DHTTYPE);
#define USE_ARDUINO_INTERRUPTS true
#include <Adafruit_Sensor.h>       // Temprature sensor library
#include <PulseSensorPlayground.h> // Heart beat sensor library

int i = 0;
int temp = 0;
int moist = 0;
char buffer [50];
char buffer1 [50];
char buffer2 [50];
String blueData = "";
const int PulseWire = A1;   
const int LED13 = 13;       // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;

PulseSensorPlayground pulseSensor;
 
void setup() {
  Serial.begin(9600);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);    
  pulseSensor.setThreshold(Threshold);
  pulseSensor.begin();
  dht.begin();
}

void loop() {
  i = analogRead(A0);                     // Analog pin A0
  temp = (i / 1024.0) * 500;              // celcius
  int myBPM = pulseSensor.getBeatsPerMinute();
  moist = dht.readHumidity() ;            // Calls function on our pulseSensor object that returns BPM as an "int".
  
  if (pulseSensor.sawStartOfBeat()) {     // Constantly test to see if "a beat happened".
      sprintf (buffer, "b%d#",myBPM);
      Serial.print (buffer);
      sprintf (buffer1, "t%d#",temp);
      Serial.print (buffer1);
      sprintf (buffer2, "m%d#",moist);
      Serial.print (buffer2);
  }
  delay(1000);
}
