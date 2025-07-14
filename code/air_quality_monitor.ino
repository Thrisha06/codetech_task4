#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// LCD pin configuration: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(13, 12, 6, 5, 4, 3);

// Air quality value
float t = 0;

// ThingSpeak API key
String apiKey = "XBQDVORXXGAROWDW";

// ESP8266 communication (Connect ESP TX to pin 8, RX to pin 9)
SoftwareSerial ser(8, 9); // RX, TX

void setup() {
  Serial.begin(9600);     // Serial monitor
  ser.begin(9600);        // ESP8266 serial
  lcd.begin(16, 2);       // Initialize LCD

  // Welcome messages
  lcd.setCursor(0, 0); lcd.print("    Welcome");
  lcd.setCursor(0, 1); lcd.print("       To");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("     AIR");
  lcd.setCursor(0, 1); lcd.print("QUALITY MONITOR");
  delay(3000);

  // ESP8266 Initialization
  ser.println("AT"); delay(1000);
  ser.println("AT+GMR"); delay(1000);
  ser.println("AT+CWMODE=3"); delay(1000);
  ser.println("AT+RST"); delay(5000);
  ser.println("AT+CIPMUX=1"); delay(1000);

  // Connect to WiFi (update with your SSID & PASSWORD)
  String cmd = "AT+CWJAP=\"SSID\",\"PASSWORD\"";
  ser.println(cmd); delay(1000);

  ser.println("AT+CIFSR"); delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("      WIFI");
  lcd.setCursor(0, 1); lcd.print("   CONNECTED");
}

void loop() {
  delay(1000);
  t = analogRead(A0);  // Read air quality from MQ135 sensor

  Serial.print("Airquality = "); Serial.println(t);

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air Qual: ");
  lcd.print(t);
  lcd.print(" PPM");

  lcd.setCursor(0, 1);
  if (t <= 500) {
    lcd.print("Fresh Air");
    Serial.println("Fresh Air");
  } else if (t > 500 && t <= 1000) {
    lcd.print("Poor Air");
    Serial.println("Poor Air");
  } else {
    lcd.print("Very Poor");
    Serial.println("Very Poor");
  }

  delay(10000);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("  SENDING DATA");
  lcd.setCursor(0, 1); lcd.print("    TO CLOUD");

  sendToThingSpeak();
}

// Send data to ThingSpeak via ESP8266
void sendToThingSpeak() {
  String cmd = "\nAT+CIPSTART=4,\"TCP\",\"184.106.153.149\",80"; // ThingSpeak IP
  ser.println(cmd);
  Serial.println(cmd);

  if (ser.find("Error")) {
    Serial.println("AT+CIPSTART error");
    return;
  }

  String getStr = "GET /update?api_key=" + apiKey + "&field1=" + String(t) + "\r\n\r\n";
  cmd = "AT+CIPSEND=4," + String(getStr.length());

  ser.println(cmd);
  Serial.println(cmd);
  delay(1000);

  ser.print(getStr);
  Serial.println(getStr);

  delay(17000); // Wait between ThingSpeak updates
}
