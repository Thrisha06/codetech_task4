# codetech_task4
air quality checker
🌫️ IoT Air Quality Monitoring System
This project is an IoT-based solution to monitor air quality in real time using an MQ135 gas sensor, Arduino, and ESP8266. The data is displayed on a 16x2 LCD and uploaded to ThingSpeak for cloud monitoring.

🚀 Features
Live Air Quality reading (PPM)
Display on LCD (Fresh, Poor, Very Poor)
Data upload to ThingSpeak IoT Cloud
Wi-Fi enabled with ESP8266 (AT commands)
🧰 Hardware Required
Component	Quantity
Arduino Uno	1
ESP8266 (ESP-01)	1
MQ135 Sensor	1
LCD 16x2	1
Breadboard + Jumper Wires	1 set
Power Supply	5V
🔌 Circuit Diagram
(Add diagram in circuit/air_quality_diagram.png)
Basic wiring:

MQ135 → A0
LCD → Digital Pins (13, 12, 6, 5, 4, 3)
ESP8266:
TX → Arduino Pin 8
RX → Arduino Pin 9
VCC and CH_PD → 3.3V
GND → GND
🛠️ How to Use
Open air_quality_monitor.ino in Arduino IDE
Replace SSID and PASSWORD with your Wi-Fi credentials
Replace apiKey with your ThingSpeak write key
Upload the code to Arduino
Open Serial Monitor at 9600 baud
Observe LCD and cloud data at https://thingspeak.com
📈 Sample Output
Air Qual: 350 PPM → Fresh Air
Air Qual: 700 PPM → Poor Air
Air Qual: 1200 PPM → Very Poor

