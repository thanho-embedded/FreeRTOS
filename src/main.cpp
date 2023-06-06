#include <Arduino.h>
#include "Arduino_FreeRTOS.h"

#define LED1_PIN  2
#define LED2_PIN  3



// put function declarations here:
void Task1(void* pvParameters);
void Task2(void* pvParameters);


void setup() 
{
  // put your setup code here, to run once:

  //...Create a task 1
  xTaskCreate
  (
    Task1,
    "LED Blinking", // Name of task
    128,            // Stack size 128 bytes
    NULL,           // Parameters for task (pvParameters)
    2,              // Priority, 0 is lowest
    NULL            // Task handle
  );
  //...Create a task 2
  xTaskCreate
  (
    Task2,
    "Debug Monitor",  // Name of task
    128,              // Stack size 128 bytes
    NULL,             // Parameters for task (pvParameters)
    2,                // Priority, 0 is lowest
    NULL              // Task handle
  );
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
    digitalWrite(LED1_PIN, false);
    vTaskDelay(100);
    digitalWrite(LED1_PIN, true);
    vTaskDelay(100);
  }
}

/// @brief Task 2, Serial debug
/// @param pvParameters 
void Task2(void *pvParameters __attribute__((unused)))
{

}