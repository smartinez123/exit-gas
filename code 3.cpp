#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
#include<LiquidCrystal_I2C.h>

char auth[] = "NNBoDMxYVUMORbDIuLh8oCPrMm-8r_7Z"; //Auth code sent via Email
char ssid[] = "Alumnos"; //Wifi name
char pass[] = "";  //Wifi Password

LiquidCrystal_I2C lcd(0x27, 16, 2);
int flag=0;
bool on_off;
bool boton;

void notifyOnFire()
{
  int isButtonPressed = digitalRead(D1);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("notificacion enviada");
    Blynk.notify("Se detecto una fuga de gas");
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    flag=0;
  }
}
void setup()
{
    //Serial.begin(9600);
    lcd.init();
      lcd.backlight();
    
    Blynk.begin(auth, ssid, pass);
    pinMode(D1,INPUT_PULLUP);
    timer.setInterval(1000L,notifyOnFire);

    pinMode(14,INPUT);//entrada de tension
    pinMode(A0,INPUT);//sensor
    pinMode(15,INPUT);//entrada del botón
    
}
void loop()
{
    on_off = digitalRead(14);//pin d5 para ver online o offline
    sens = analogRead(A0);//
    boton = digitalRead(15);//pin d8
    if (sens > x){  //no sabemos cuanto es
      while (boton == HIGH
    }

    if (on_off == HIGH){    //si esta ONLINE
      lcd.setCursor(5, 0);
      lcd.print("ONLINE");

      Blynk.VirtualWrite(V5, sens)//envia sens por el pin virtual V5

      
    }



  
  Blynk.run();
  timer.run();
}
