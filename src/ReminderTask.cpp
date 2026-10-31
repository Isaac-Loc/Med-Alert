#include <time.h>
#include "tasks.h"
#include "config.h"

// Runs when the 10-minute countdown reaches 0 without a button press
void MissedDoseCallback(TimerHandle_t timer) {
  bool missed = true;
  xQueueSend(missedQueue, &missed, 0);
}

void ReminderTask(void *pvParameters) {
  int lastFiredDay = -1;
  for (;;) {
    struct tm now;
    if (getLocalTime(&now, 0) && now.tm_hour == DOSE_HOUR && now.tm_min == DOSE_MINUTE && now.tm_yday != lastFiredDay) {
      lastFiredDay = now.tm_yday;
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      xTimerStart(timeoutTimer, 0);
      Serial.println("Dose due");
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
