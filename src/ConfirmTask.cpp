// Handles the button press
#include "tasks.h"
#include "config.h"

// runs when the button is pressed
void IRAM_ATTR buttonISR() {
  BaseType_t woken = pdFALSE;
  xSemaphoreGiveFromISR(confirmSemaphore, &woken);
  portYIELD_FROM_ISR(woken);
}

void ConfirmTask(void *pvParameters) {
  for (;;) {
    // wait for the button
    xSemaphoreTake(confirmSemaphore, portMAX_DELAY);

    // turn off the LED and buzzer
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    // stop the 10-minute timer
    xTimerStop(timeoutTimer, 0);
    Serial.println("Dose confirmed");
  }
}
