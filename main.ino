#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

double Temp;
int RELAY_PIN = 5;
int HA = 7;
int HB = 8;

void setup(void)
{
  sensors.begin();  // Start up the library
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(HA, OUTPUT);
  pinMode(HB, OUTPUT);
}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  Temp = sensors.getTempCByIndex(0);

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(Temp);
  Serial.print("º");//shows degrees character
  Serial.print("C  |  ");
  Serial.print("\n");

  digitalWrite(HA, HIGH);

  if (Temp > 0) {
  
    if (Temp > 25 and Temp <= 28) {
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(HB, LOW);
      Serial.print("Peltier \n");
    } else if (Temp > 28) {
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(HB, HIGH);
      Serial.print("Relay \n");
    } else {
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(HB, HIGH);
      Serial.print("Nada \n");
    }
  
  }
  
  delay(3000);
}
