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
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Wi-Fi connected");

  confirmSemaphore = xSemaphoreCreateBinary();
  missedQueue = xQueueCreate(1, sizeof(bool));
  timeoutTimer = xTimerCreate("timeout", pdMS_TO_TICKS(DOSE_TIMEOUT_MS), pdFALSE, NULL, MissedDoseCallback);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  xTaskCreate(ConfirmTask, "Confirm", 2048, NULL, 3, NULL);
  xTaskCreate(ReminderTask, "Reminder", 4096, NULL, 2, NULL);
  xTaskCreate(AlertTask, "Alert", 8192, NULL, 1, NULL);
  xTaskCreate(TimeSyncTask, "TimeSync", 4096, NULL, 1, NULL);
}

void loop() {
  vTaskDelay(portMAX_DELAY);
}
