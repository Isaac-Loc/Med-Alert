#include "tasks.h"
#include "config.h"

void TimeSyncTask(void *pvParameters) {
  for (;;) {
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
    vTaskDelay(pdMS_TO_TICKS(60UL * 60UL * 1000UL));  // resync every hour
  }
}
