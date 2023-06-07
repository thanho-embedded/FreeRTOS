#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define LED1_PIN  2
#define LED2_PIN  3
#define DTH11_PIN 4
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT_Unified dht(DTH11_PIN, DHTTYPE);

const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);

// put function declarations here:
TaskHandle_t Task1Handle = NULL, Task2Handle = NULL;
void Task1(void* pvParameters);
void Task2(void* pvParameters);


void uTaskBlink(uint8_t pin, uint16_t delay)
{
  digitalWrite(pin, false);
  vTaskDelay(pdMS_TO_TICKS(delay));
  digitalWrite(pin, true);
  vTaskDelay(pdMS_TO_TICKS(delay));
}

void Task1Applications()
{
  // Do some applications here
}

void Task2Applications()
{
  // Do some applications here
}



void setup() 
{
  //... Initialize Serial that using for debug
  Serial.begin(115200);
  while(!Serial);   // wait serial is opened

  //...Create a task 1
  xTaskCreate
  (
    Task1,
    "LED Blinking",         // Name of task
    1024,                   // Stack size 128 bytes
    NULL,                   // Parameters for task (pvParameters)
    2,                      // Priority, 0 is lowest
    &Task1Handle            // Task handle
  );
  //...Create a task 2
  xTaskCreate(Task2, "Debug Monitor", 1024, NULL, 2, &Task2Handle);
  vTaskStartScheduler();
}
void loop() {}

/*.....................Functions.............................
.............................................................
.............................................................
*/

/// @brief Taks 1, Led blinking
/// @param pvParameters 
void Task1(void *pvParameters __attribute__((unused)))
{
  // Inittialze
  pinMode(LED1_PIN, OUTPUT);
  digitalWrite(LED1_PIN, false);

  //...Loop
  while(true)
  {
    Serial.println("Task 1 is running");
    uTaskBlink(LED1_PIN, 500);
  }
}

/// @brief Task 2, Serial debug
/// @param pvParameters 
void Task2(void *pvParameters __attribute__((unused)))
{
  uint32_t delayMS;
  // Initialize
  pinMode(LED2_PIN, OUTPUT);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  // Loop
  while(true)
  {
    Serial.println("Task 2 is running");
    // digitalWrite(LED2_PIN, true);
    // vTaskDelay(pdMS_TO_TICKS(500));
    // digitalWrite(LED2_PIN, false);
    // vTaskDelay(pdMS_TO_TICKS(500));

    // Delay between measurements.
    vTaskDelay(pdMS_TO_TICKS(delayMS));
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));

      if (event.temperature > 30) {
        uTaskBlink(LED2_PIN, 100);
      }
      else {
        uTaskBlink(LED2_PIN, 1000);
      }
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
  }
}