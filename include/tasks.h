#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

// Shared objects, created in main.cpp
extern SemaphoreHandle_t confirmSemaphore;
extern QueueHandle_t missedQueue;
extern TimerHandle_t timeoutTimer;

void buttonISR();
void MissedDoseCallback(TimerHandle_t timer);

void ConfirmTask(void *pvParameters);
void ReminderTask(void *pvParameters);
void AlertTask(void *pvParameters);
void TimeSyncTask(void *pvParameters);

#endif
