// Gets the current time from the internet
#include "tasks.h"
#include "config.h"

void TimeSyncTask(void *pvParameters) {
  for (;;) {
    // ask the time server for the time
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

    // wait one hour
    vTaskDelay(pdMS_TO_TICKS(60UL * 60UL * 1000UL));
  }
}
