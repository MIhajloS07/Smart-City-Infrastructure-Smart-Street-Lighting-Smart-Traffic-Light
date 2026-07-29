// ═══════════════════════════════════════════════════════════════
//  CLIENT ARDUINO – Uno (semaphore)                 
//    RX = pin 2  
//    TX = pin 13 
//
//    A1 (TX) ──→ (RX)
//    13(TX) ──→ (RX)
//    GND ─────────── GND
//
//  Libraries:
//    - TM1637Display (Avishay Orpaz)
//    - DHT sensor library (Adafruit)
//    - Adafruit Unified Sensor
// ═══════════════════════════════════════════════════════════════

#include <SoftwareSerial.h>
#include <TM1637Display.h>
#include <DHT.h>

// ── SoftwareSerial ───────────────────────────────────────────
SoftwareSerial softSerial(2, 13);  // RX=2, TX=13

// ── DHT sensor ───────────────────────────────────────────────
#define DHT_PIN  A2   // DATA pin 
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// ── TM1637 display ───────────────────────────────────────────
// TL1: CLK=10, DIO=9  
// TL2: CLK=11, DIO=A2  
#define CLK_PIN_1 10
#define DIO_PIN_1  9
#define CLK_PIN_2 11
#define DIO_PIN_2 12
TM1637Display tm(CLK_PIN_1, DIO_PIN_1);
TM1637Display tm2(CLK_PIN_2, DIO_PIN_2);

// ── Semaphore pins ──────────────────────────────────────────
const int TL1_red = 3, TL1_yellow = 4, TL1_green = 5;
const int TL2_red = 6, TL2_yellow = 7, TL2_green = 8;

// ── Times (seconds) ────────────────────────────────────────
int greenTime  = 6;
int redTime    = 6;
int yellowTime = 2;

// ── DHT timer ───────────────────────────────────────────────
unsigned long lastTempSend = 0;
#define TEMP_SEND_INTERVAL 5000  // every 5 seconds

// ── Forward declarations ──────────────────────────────────────
void phase(String name, int duration,
           bool tl1r, bool tl1y, bool tl1g,
           bool tl2r, bool tl2y, bool tl2g,
           bool showDisplay);
void handleSerial(String data);
void showCountdown(int seconds);
void sendTemperature();
void setupDHT();
void sendTemperature();

// ════════════════════════════════════════════════════════════
void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);

  pinMode(TL1_red,    OUTPUT); pinMode(TL1_yellow, OUTPUT); pinMode(TL1_green, OUTPUT);
  pinMode(TL2_red,    OUTPUT); pinMode(TL2_yellow, OUTPUT); pinMode(TL2_green, OUTPUT);

  tm.setBrightness(5);  tm.clear();
  tm2.setBrightness(5); tm2.clear();

  setupDHT();

  Serial.println("Semaphore ready.");
}

// ════════════════════════════════════════════════════════════
void loop() {
  // ── Receive commands from server ─────────────────────────────
  if (softSerial.available()) {
    String data = softSerial.readStringUntil('\n');
    data.trim();
    Serial.println("Received: " + data);
    handleSerial(data);
  }

  // ── Send temperature to server every 5s ──────────────────
  if (millis() - lastTempSend >= TEMP_SEND_INTERVAL) {
    sendTemperature();
    lastTempSend = millis();
  }

  // ── Semaphore cycle ───────────────────────────────────────
  phase("TL1=RED  | TL2=GREEN",       6,          true,  false, false, false, false, true,  true);
  phase("TL2=YELLOW",                        yellowTime, true,  false, false, false, true,  false, false);
  phase("TL1=RED+YELLOW | TL2=RED",   yellowTime, true,  true,  false, true,  false, false, false);
  phase("TL1=GREEN  | TL2=RED",        greenTime,  false, false, true,  true,  false, false, true);
  phase("TL1=YELLOW    | TL2=RED",        yellowTime, false, true,  false, true,  false, false, false);
  phase("TL1=RED  | TL2=RED+YELLOW",  yellowTime, true,  false, false, true,  true,  false, false);
}

// ── Processing received commands ────────────────────────────────
void handleSerial(String data) {
  if (data.startsWith("AUTO")) {
    int colonIdx = data.indexOf(':');
    if (colonIdx != -1) {
      int t = data.substring(colonIdx + 1).toInt();
      if (t >= 6 && t <= 20) {
        greenTime = t;
        redTime   = t;
        Serial.print("AUTO: greenTime=redTime=");
        Serial.print(t); Serial.println("s");
      }
    }
  } else if (data.startsWith("RESET")) {
    greenTime = 6;
    redTime   = 6;
    Serial.println("RESET: 6s/6s");
  }
}

// ── Semaphore phase ─────────────────────────────────────────────
void phase(String name, int duration,
           bool tl1r, bool tl1y, bool tl1g,
           bool tl2r, bool tl2y, bool tl2g,
           bool showDisplay) {

  digitalWrite(TL1_red,    tl1r ? HIGH : LOW);
  digitalWrite(TL1_yellow, tl1y ? HIGH : LOW);
  digitalWrite(TL1_green,  tl1g ? HIGH : LOW);
  digitalWrite(TL2_red,    tl2r ? HIGH : LOW);
  digitalWrite(TL2_yellow, tl2y ? HIGH : LOW);
  digitalWrite(TL2_green,  tl2g ? HIGH : LOW);

  for (int i = duration; i > 0; i--) {
    // Check for UART
    if (softSerial.available()) {
      String data = softSerial.readStringUntil('\n');
      data.trim();
      Serial.println("Received (mid-phase): " + data);
      handleSerial(data);
    }

    // Send temp if is time
    if (millis() - lastTempSend >= TEMP_SEND_INTERVAL) {
      sendTemperature();
      lastTempSend = millis();
    }

    if (showDisplay) showCountdown(i);

    Serial.print(name);
    Serial.print(" | Left: ");
    Serial.print(i);
    Serial.println("s");
    delay(1000);
  }
}

// ─────────  TM1637  ──────────
void showCountdown(int seconds) {
  int val = seconds % 100;
  uint8_t segs[4];
  segs[0] = 0x00;
  segs[1] = 0x00;
  segs[2] = (val >= 10) ? tm.encodeDigit(val / 10) : 0x00;
  segs[3] = tm.encodeDigit(val % 10);
  tm.setSegments(segs);
  tm2.setSegments(segs);
}

void sendTemperature() {
  // Simulate DHT values 
  float temp = random(200, 301) / 10.0;  // generate 20.0 - 30.0

  String msg = "TEMP:" + String(temp, 1);
  softSerial.println(msg);
  Serial.println("TX -> " + msg);
}

void setupDHT() {
  pinMode(DHT_PIN, INPUT_PULLUP);  // pull-up (~25kΩ)
  dht.begin();
  delay(2000);     
  // Read for activate sensor
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("First read failed, trying again...");
    delay(1000);
    temp = dht.readTemperature();
    if (isnan(temp)) {
      Serial.println("DHT error - cant read temperature.");
    } else {
      Serial.println("DHT readed temp: " + String(temp, 1) + "°C");
    }
  } else {
    Serial.println("DHT read: " + String(temp, 1) + "°C");
  }

  // Send temperature to server
  sendTemperature();
}