

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

const int ledPin = 19;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
const int btn1 = 17;
const int btn2 = 16;
int duty = 0;

void setup()
{
  ledcSetup(ledChannel, freq, resolution); // 채널, 주파수, 해상도
  ledcAttachPin(ledPin, ledChannel);       // 핀번호, 채널
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print(F("Sensor Type: "));
  Serial.println(sensor.name);
  Serial.print(F("Driver Ver:  "));
  Serial.println(sensor.version);
  Serial.print(F("Unique ID:   "));
  Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:   "));
  Serial.print(sensor.max_value);
  Serial.println(F("°C"));
  Serial.print(F("Min Value:   "));
  Serial.print(sensor.min_value);
  Serial.println(F("°C"));
  Serial.print(F("Resolution:  "));
  Serial.print(sensor.resolution);
  Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));

  delayMS = sensor.min_delay / 1000;
}

void loop()
{

  if (Serial.available())
  {
    int prev = duty;
    String strduty = Serial.readStringUntil('\n');
    duty = strduty.toInt();
    if (duty != -1)
    {
      if (duty >= 255)
      {
        duty = 255;
      }
      if (duty <= 10)
      {
        duty = 0;
      }
      Serial.println(duty);
      ledcWrite(ledChannel, duty);
    }
    else
      duty = prev;
  }

  delay(100);

  // delay(delayMS);
  // sensors_event_t event;
  // dht.temperature().getEvent(&event);
  // Serial.print(F("Temperature: "));
  // Serial.print(event.temperature);
  // Serial.println(F("°C"));
  Serial.print(F("PWM: "));
  Serial.print(duty);
  Serial.println(F(""));

  delay(15);
}
