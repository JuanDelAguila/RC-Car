

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <EasyTransfer.h>
EasyTransfer ET;
struct SEND_DATA_STRUCTURE{
  float Dir;
  float Acc;
  float GearS;
};
SEND_DATA_STRUCTURE mydata;
int RMapa;
int subir;
int bajar;
int gear = 1;
int power;

void setup() {
  ET.begin(details(mydata), &Serial);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A7, INPUT);
  pinMode (2, INPUT);
  pinMode (8, INPUT);
  pinMode (9, INPUT);
  lcd.begin (16,2);
  Serial.begin(9600);
}


void loop() {
  mydata.Dir = analogRead (A1);
  mydata.Acc = analogRead (A0);
  subir = digitalRead (8);
  bajar = digitalRead (9);
  if (subir == HIGH) {
    gear = gear + 1;
    if (gear > 6) {
      gear = 6;
}
  delay (100);
}
  if (bajar == HIGH) {
    gear = gear - 1;
    if (gear < 1) {
      gear = 1;
}
  delay (100);
} 

  mydata.GearS = gear;
  ET.sendData();
  power = map(gear, 0, 6, 0, 100);
  lcd.setCursor(5,0);
  lcd.print("Gear:");
  lcd.setCursor(10,0);
  lcd.print(gear);
  lcd.setCursor(3,1);
  lcd.print("Power:");
  lcd.setCursor(9,1);
  lcd.print(power);
  if (power < 100){
    lcd.setCursor(12,1);
    lcd.print(" ");
    lcd.setCursor(11,1);
}
  else {
    lcd.setCursor(12,1);
}

  lcd.print("%");
  delay(50);
}


