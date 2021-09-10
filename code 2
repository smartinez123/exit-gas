#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

char auth[] = "NNBoDMxYVUMORbDIuLh8oCPrMm-8r_7Z"; //Auth code sent via Email
char ssid[] = "Alumnos"; //Wifi name
char pass[] = "";  //Wifi Password
int flag=0;

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
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(D1,INPUT_PULLUP);
timer.setInterval(1000L,notifyOnFire); 
}
void loop()
{
  Blynk.run();
  timer.run();
}
