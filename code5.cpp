#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<LiquidCrystal_I2C.h>

char auth[] = "NNBoDMxYVUMORbDIuLh8oCPrMm-8r_7Z"; //Auth code sent via Email
char ssid[] = "Alumnos"; //Wifi name
char pass[] = "";  //Wifi Password

LiquidCrystal_I2C lcd(0x27, 16, 2);
bool on_off;
bool boton;
int sens;

#define buzzer_pin D6
#define boton_pin D8
#define on_off_pin D5
#define sens_pin A0

int ALTO = 200; //definir un valor alto de gas
unsigned long ult_tiempo;
int pantalla;

void setup(){
  lcd.init();
  lcd.backlight();

  lcd.print("conectando con");
  lcd.setCursor(0,1);
  lcd.print("el servidor...");
  Blynk.begin(auth, ssid, pass);

  pinMode(buzzer_pin, OUTPUT);
  pinMode(on_off_pin,INPUT);
  pinMode(sens_pin,INPUT);
  pinMode(boton_pin,INPUT);
  pantalla = 3;
    
}

void loop(){
  sens = analogRead(A0);
  boton = digitalRead(boton_pin);
  on_off = digitalRead(on_off_pin);
  Blynk.virtualWrite(V5, sens);//envia sens por el pin virtual V5
  Blynk.virtualWrite(V6, on_off);
  
  if (pantalla != 1){
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ONLINE");
    pantalla = 1;
  }
  if (sens > ALTO){
    Blynk.notify("Se detecto una fuga de gas");
    while (boton == LOW){
      digitalWrite(buzzer_pin,HIGH);
      if (pantalla != 3){
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("GAS DETECTADO");
        lcd.setCursor(4, 1);
        lcd.print("*ALERTA*");
        pantalla = 3;
      }
      boton = digitalRead(boton_pin);
      delay(50);
    }
  }
  digitalWrite(buzzer_pin,LOW);
}
