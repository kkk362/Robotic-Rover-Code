//In this program we have successfully combined current sensor ,voltage sensor, DHT11 sensor ,HC-05 Bluetooth module ,LCD Screen, Serial monitor with ARDUINO MEGA 


#include "EmonLib.h"             // Include Emon Library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>
#include <SoftwareSerial.h>      
SoftwareSerial BTserial(10,11); // RX, TX

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

#define VOLT_CAL 157
#define CURRENT_CAL 62.6

int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);
EnergyMonitor emon1;             // Create an instance

void setup()
{  
  Serial.begin(9600);
  lcd.begin();
  BTserial.begin(9600);   
  emon1.voltage(1, VOLT_CAL, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(0, CURRENT_CAL);    // Current: input pin, calibration.
}


void loop()
{
  emon1.calcVI(20,2000);                      // Calculate all. No.of half wavelengths (crossings), time-out

  float currentDraw = emon1.Irms;             //extract Irms into Variable
  float supplyVoltage   = emon1.Vrms;         //extract Vrms into Variable

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  if(supplyVoltage>=100)
  {
    
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.println("Failed to read data from DHT11 , Check the output pin connection"); 
  }
  Serial.print("Voltage : ");
  Serial.print(supplyVoltage);
  Serial.println(" V");
  
  Serial.print("Current: ");
  Serial.print(currentDraw);
  Serial.println(" A");

  Serial.print("Watts: ");
  Serial.print(currentDraw * supplyVoltage);
  Serial.println(" W");
 
  Serial.print("Temperature = ");
  Serial.print((int)temperature);
  Serial.print("⁰"); 
  Serial.println(" C "); 
  
  Serial.print("Humidity = ");
  Serial.print((int)humidity); 
  Serial.println(" % ");
  Serial.println("\n");


  lcd.setCursor(0,0); 
  lcd.print("Voltage: ");
  lcd.print(supplyVoltage);
  lcd.print("V");

  lcd.setCursor(0,1); 
  lcd.print("Current: ");
  lcd.print(currentDraw);
  lcd.print("Amp");
  delay(3000);
   
  lcd.setCursor(0,0); 
  lcd.print("Watts: ");
  lcd.print(currentDraw * supplyVoltage);
  lcd.print("  W");
  
  lcd.setCursor(0,1); 
  lcd.print("                ");
  delay(3000);

  lcd.setCursor(0,0); 
  lcd.print("                ");
 
  lcd.setCursor(0,1); 
  lcd.print("                ");

  lcd.setCursor(0,0); 
  lcd.print("Temperature:");
  lcd.print((int)temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity : ");
  lcd.print((int)humidity);
  lcd.print("%");

  
  BTserial.print(supplyVoltage);
  BTserial.print(" V ");
  BTserial.print(",");
  
  BTserial.print(currentDraw);
  BTserial.print(" A ");
  BTserial.print(",");
  
  BTserial.print(currentDraw * supplyVoltage);
  BTserial.print(" W ");
  BTserial.print(",");
  
  BTserial.print((int)temperature);
  BTserial.print(" C");
  BTserial.print(",");
  
  BTserial.print((int)humidity);
  BTserial.print(" % ");
  BTserial.print(";");
  delay(3000);
  }
  else
  {
  Serial.print("No Input Voltage  \n");
  Serial.print("No Current Flowing ");
  Serial.println("\n");
  delay(2000);
  
  lcd.setCursor(0,0); 
  lcd.print("No Input Voltage    \n ");
  lcd.setCursor(0,1); 
  lcd.print("No Current Flowing   \n ");
  delay(3000);

  lcd.setCursor(0,0); 
  lcd.print("                ");
 
  lcd.setCursor(0,1); 
  lcd.print("                ");

  BTserial.print("0 Volts");
  BTserial.print(",");
  BTserial.print("0 Amps");
  BTserial.print(",");
  BTserial.print("0 Watts");
  BTserial.print(",");
  
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.println("Failed to read data from DHT11 , Check the output pin connection"); 
  }

  Serial.print("Temperature = ");
  Serial.print((int)temperature); 
  Serial.print("⁰");
  Serial.println(" C "); 
  Serial.print("Humidity = ");
  Serial.print((int)humidity); 
  Serial.println(" % ");
  
  lcd.setCursor(0,0); 
  lcd.print("Temperature:");
  lcd.print((int)temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity : ");
  lcd.print((int)humidity);
  lcd.print("%");
  delay(3000);
  
  BTserial.print((int)temperature);
  BTserial.print(" C");
  BTserial.print(",");
  BTserial.print((int)humidity);
  BTserial.print(" % ");
  BTserial.print(";");
  } 
} 
