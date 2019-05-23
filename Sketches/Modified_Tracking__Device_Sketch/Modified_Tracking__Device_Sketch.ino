#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial rx_tx(10,11); // The serial connection to the GPS device RX, TX
TinyGPSPlus gps;   // The TinyGPS++ object
double latitude;
double longitude;
byte Year;
byte Month;
byte Day;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rx_tx.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (rx_tx.available() > 0){
    gps.encode(rx_tx.read());
    if (gps.location.isUpdated()){
      
      // Latitude in degrees (double)
      Serial.print("Latitude= "); 
      latitude = gps.location.lat(), 6;  
          
      // Longitude in degrees (double)
      Serial.print(" Longitude= "); 
      longitude = gps.location.lng(), 6; 
      
       // Year (2000+) (u16)
      Serial.print("Year = "); 
      Year = gps.date.year();
       
      // Month (1-12) (u8)
      Serial.print("Month = "); 
      Month = gps.date.month(); 
      
      // Day (1-31) (u8)
      Serial.print("Day = "); 
      Day = gps.date.day(); 
    } 
  }
}
void init_sms()
{
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"+91**********\"");   // use your 10 digit cell no. here
  delay(400);
}
void send_data(String message)
{
  Serial.println(message);
  delay(200);
}
void send_sms()
{
  Serial.write(26);
}
void tracking()
{
  init_sms();
  Serial.println("Vehicle Tracking Alert:");
  delay(200);
  Serial.println("Your Vehicle Current Location is:");
  delay(200);
  Serial.print("Latitude:");
  delay(200);
  Serial.println(latitude);
  delay(200);
  Serial.print("Longitude:");
  delay(200);
  Serial.println(longitude);
  delay(200);
  Serial.println("Please take some action soon..\nThankyou");
  send_sms();
  delay(2000);

}
