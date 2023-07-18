#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Display Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address may vary, use "i2c_scanner" sketch to find the correct address

// Global Variables
int flameSensor = 5; // Connect to Digital Pin 5
int GasSensor = 6; //Connect to Digital Pin 6
int Buzzer = 7; //Connect to Digital Pin 7

void setup() {
  // Seting Up input and Output Devices Connected to the Microcontroller
  pinMode(flameSensor, INPUT); // Flame Sensor Configured as Input
  pinMode(GasSensor, INPUT);  // Gas Sensor Configured as Input
  pinMode(Buzzer, OUTPUT);   // Buzzer Configured as OUTPUT

  // Initialize LCD Display
  lcd.init();
  lcd.backlight();

  digitalWrite(Buzzer, LOW); //When The system Turns on we make sure the Buzzer is OFF First

  //Booting Message Displayed in the lcd
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("SYSTEM");
  lcd.setCursor(1,1);
  lcd.print("INITIALIZATION");
  delay(2000);

}

void loop() {
  if(digitalRead(flameSensor) == HIGH && digitalRead(GasSensor) == HIGH){ 
    //When Both Flame Sensor & Gas Sensor Dont Detect then Buzzer will Remain Off
    digitalWrite(Buzzer, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LEAKAGE: NO");
    lcd.setCursor(0,1);
    lcd.print("FLAME: NO");
    delay(1000);
  }else if(digitalRead(flameSensor) == LOW && digitalRead(GasSensor) == HIGH){
    //When Flame Sensor Detects & Gas Sensor Dont Detect then Buzzer will Turn ON
    digitalWrite(Buzzer, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LEAKAGE: N0");
    lcd.setCursor(0,1);
    lcd.print("FLAME: DETECTED");
    delay(1000);
  }else if(digitalRead(flameSensor) == HIGH && digitalRead(GasSensor) == LOW){
    //When Flame Sensor Dont Detect & Gas Sensor Detects then Buzzer will Turn ON
    digitalWrite(Buzzer, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LEAKAGE: DETECTED");
    lcd.setCursor(0,1);
    lcd.print("FLAME: NO");
    delay(1000);
  }else if(digitalRead(flameSensor) == LOW && digitalRead(GasSensor) == LOW){
    //When Both Flame Sensor & Gas Sensor Detects then Buzzer will Turn ON
    digitalWrite(Buzzer, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LEAKAGE: DETECTED");
    lcd.setCursor(0,1);
    lcd.print("FLAME: DETECTED");
    delay(1000);
  }

}

