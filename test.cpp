//
// Created by David Paquette on 12/1/15.
//

/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include "Arduino.h"

// The LED is attached to pin 13 on Arduino.
const uint8_t LED_PIN = 13;

// Declare a semaphore handle.
SemaphoreHandle_t sem;

void ThreadHandler(void (*func)(void *));
//------------------------------------------------------------------------------
/*
 * Thread 1, turn the LED off when signalled by thread 2.
 */
// Declare the thread function for thread 1.
void Thread1(void *arg) {
    // Wait for signal from thread 2.
    xSemaphoreTake(sem, portMAX_DELAY);

    // Turn LED off.
    digitalWrite(LED_PIN, LOW);
    ThreadHandler(&Thread1);
}
//------------------------------------------------------------------------------
/*
 * Thread 2, turn the LED on and signal thread 1 to turn the LED off.
 */
// Declare the thread function for thread 2.

void Thread2(void *arg) {
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);

    // Sleep for 200 milliseconds.
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);

    // Signal thread 1 to turn LED off.
    xSemaphoreGive(sem);

    // Sleep for 200 milliseconds.
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
    ThreadHandler(&Thread2);
}

void ThreadHandler(void (*func)(void *)) {
    func(0);
}

//------------------------------------------------------------------------------
void setup() {
    portBASE_TYPE s1, s2;

    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    // initialize semaphore
    sem = xSemaphoreCreateCounting(1, 0);

    // create task at priority two
    s1 = xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // create task at priority one
    s2 = xTaskCreate(Thread2, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // check for creation errors
    if (sem == NULL || s1 != pdPASS || s2 != pdPASS) {
        Serial.println(F("Creation problem"));
        while (1);
    }
    // start scheduler
    vTaskStartScheduler();
    Serial.println(F("Insufficient RAM"));
    while (1);
}

//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
    // Not used.
}