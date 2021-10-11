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

#define buzzer_pin 12 //pin d6
#define boton_pin 15  //pin d8
#define on_off_pin 14 //pin d5
#define sens_pin A0   //pin A0

int ALTO = 300; //definir un valor alto de gas
unsigned long ult_tiempo;
int pantalla;

void setup(){
  //Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  Blynk.begin(auth, ssid, pass);

  pinMode(buzzer_pin, OUTPUT);
  pinMode(on_off_pin,INPUT);
  pinMode(sens_pin,INPUT);
  pinMode(boton_pin,INPUT);

  ult_tiempo = 0; //deberia poner -60000 pero es unsigned
  pantalla = 3;
    
}
void ONLINE(){
  if (pantalla != 1){
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ONLINE");
    pantalla = 1;
  }

  if (sens > ALTO){
    if (millis()-ult_tiempo > 60*1000){   //si paso 1 minuto
      Blynk.notify("Se detecto una fuga de gas");
      ult_tiempo = millis();
    }
  }
}

void OFFLINE(){
  if (pantalla != 2){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("OFFLINE");
    pantalla = 2;
  }


  if (sens > ALTO){
    while (boton == LOW){
      digitalWrite(buzzer_pin, HIGH);
      if (pantalla != 3){
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("GAS DETECTADO");
        lcd.setCursor(4, 1);
        lcd.print("*ALERTA*");
        pantalla = 3;
      }
      boton = digitalRead(boton_pin);
    } 
  }
  digitalWrite(buzzer_pin, LOW);
}


void loop(){
  on_off = digitalRead(on_off_pin);  //pin d5 para ver online o offline
  sens = analogRead(sens_pin);     //pin A0 lee sensor de gas
  boton = digitalRead(boton_pin);   //pin d8 boton

  Blynk.virtualWrite(V5, sens);//envia sens por el pin virtual V5

  if (on_off == HIGH){    //si esta ONLINE
    ONLINE();
  }
  else{       //si esta OFFLINE
    OFFLINE();
  }
  
  Blynk.run();
}
