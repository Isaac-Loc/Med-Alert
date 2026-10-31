#include "tasks.h"
#include "config.h"

// Runs when the button is pressed (falling edge)
void IRAM_ATTR buttonISR() {
  BaseType_t woken = pdFALSE;
  xSemaphoreGiveFromISR(confirmSemaphore, &woken);
  portYIELD_FROM_ISR(woken);
}

void ConfirmTask(void *pvParameters) {
  for (;;) {
    xSemaphoreTake(confirmSemaphore, portMAX_DELAY);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    xTimerStop(timeoutTimer, 0);
    Serial.println("Dose confirmed");
  }
}
