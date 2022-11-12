#include <Arduino.h>
#include <stdlib.h>
#include <String.h>

String token = "  ";      
String temp_id="  ";      
String hum_id="  ";       
String soil_id="  ";      
String light_id="  ";     

const int light_out = A0;
const int soil_out = A1;
const int temp_out = A2;
const int hum_out = A3;

float temp=0,hum=0;
int soil,light;

void ShowSerialData()
{
  while(Serial2.available()!=0)
  Serial.write(Serial2.read());
}

void save_value(String payload)
{
   String le;                           
   le = String(payload.length());      
    
  for(int i = 0;i<7;i++)
  {
    Serial2.println("AT+CGATT?");      
    delay(2000);
    ShowSerialData();
  }
  
  Serial2.println("AT+CSTT=");                               
  delay(1000);
  ShowSerialData();
  Serial2.println("AT+CIICR");                               
  delay(3000);
  ShowSerialData();
  Serial2.println("AT+CIFSR");                               
  delay(2000);
  ShowSerialData();
  Serial2.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  Serial2.println("AT+CIPSTART=\"tcp\",\"things.thingspeak.com\",\"80\"");     
  delay(3000);
  ShowSerialData();
  Serial2.println("AT+CIPSEND");                          
  delay(3000);
  ShowSerialData();
  Serial2.print(F("POST /api/v1.6/collections/values/?token="));
  delay(100);
  ShowSerialData();
  Serial2.print(token);
  delay(100);
  ShowSerialData();
  Serial2.println(F(" HTTP/1.1"));
  delay(100);
  ShowSerialData();
  Serial2.println(F("Content-Type: application/json"));
  delay(100);
  ShowSerialData();
  Serial2.print(F("Content-Length: "));
  Serial2.println(le);
  delay(100);
  ShowSerialData();
  Serial2.print(F("Host: "));
  Serial2.println(F("things.ubidots.com"));
  Serial2.println(); 
  delay(100);
  ShowSerialData();
  Serial2.println(payload); 
  Serial2.println();
  delay(100);
  ShowSerialData();
  Serial2.println((char)26);
  delay(7000);
  Serial2.println();
  ShowSerialData();
  Serial2.println("AT+CIPCLOSE"); 
  delay(1000);
  ShowSerialData();
}


void setup()
{
  Serial2.begin(9600);                                                             
  Serial.begin(9600);                                                              
  
  delay(2000);
}

void loop()
{
  int cnt=0;
  String payload;                                           
  
  if (Serial2.available())
  {
  Serial.write(Serial2.read());
  }
    
    temp = analogRead(temp_out);                                                     
    temp = map(temp, 0 , 1023, 0, 100);
    Serial.print("temp = ");
    Serial.println(temp);
    
    hum = analogRead(hum_out);                                                     
    hum = map(hum, 0 , 1023, 0, 100);
    Serial.print("hum = ");
    Serial.println(hum);
  
    soil = analogRead(soil_out);                                                     
    soil = map(soil, 0 , 1023, 0, 100);
    Serial.print("soil = ");
    Serial.println(soil);
    
    light = analogRead(light_out);                                                     
    light = map(light, 0 , 1023, 0, 100);
    Serial.print("light = ");
    Serial.println(light);

   while(cnt<5)
   {
   Serial.println();
   Serial.println("Uploading Sensors Data to Thingspeak Cloud Service");
   payload = "[{\"variable\":\"" + temp_id + "\",\"value\":"+ String(temp)+"},{\"variable\":\""+ hum_id+ "\",\"value\":" + String(hum) + "},{\"variable\":\"" +soil_id+ "\",\"value\":" + String(soil) + "},{\"variable\":\"" + light_id + "\",\"value\":" + String(light) + "}]";
   save_value(payload);                                                      
   cnt++;
   delay(20000);
    
    temp = analogRead(temp_out);                                                     
    temp = map(temp, 0 , 1023, 0, 100);

    hum = analogRead(hum_out);                                                     
    hum = map(hum, 0 , 1023, 0, 100);
  
    soil = analogRead(soil_out);                                                     
    soil = map(soil, 0 , 1023, 0, 100);
    
    light = analogRead(light_out);                                                     
    light = map(light, 0 , 1023, 0, 100);
   }
   
   delay(45000);
   delay(45000);
}

