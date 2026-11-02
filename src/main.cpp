// Starting point: sets up the board and starts the tasks
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "secrets.h"
#include "tasks.h"

SemaphoreHandle_t confirmSemaphore;
QueueHandle_t missedQueue;
TimerHandle_t timeoutTimer;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // connect to the wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Wi-Fi connected");

  // create the signal, mailbox, and 10-minute timer
  confirmSemaphore = xSemaphoreCreateBinary();
  missedQueue = xQueueCreate(1, sizeof(bool));
  timeoutTimer = xTimerCreate("timeout", pdMS_TO_TICKS(DOSE_TIMEOUT_MS), pdFALSE, NULL, MissedDoseCallback);

  // run buttonISR when the button is pressed
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  // start the tasks: function, name, stack (bytes of memory), parameter, priority, handle
  xTaskCreate(ConfirmTask, "Confirm", 2048, NULL, 3, NULL);     // priority 3, highest
  xTaskCreate(ReminderTask, "Reminder", 4096, NULL, 2, NULL);   // priority 2
  xTaskCreate(AlertTask, "Alert", 8192, NULL, 1, NULL);         // priority 1, needs more memory for HTTPS
  xTaskCreate(TimeSyncTask, "TimeSync", 4096, NULL, 1, NULL);   // priority 1
}

// not used
void loop() {
  vTaskDelay(portMAX_DELAY);
}
