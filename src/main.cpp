#include <Arduino.h>
#include "Arduino_FreeRTOS.h"

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
