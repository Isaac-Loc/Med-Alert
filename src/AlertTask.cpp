// Sends the missed-dose notification
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "tasks.h"
#include "secrets.h"

void AlertTask(void *pvParameters) {
  bool missed;
  for (;;) {
    // wait for a missed dose
    xQueueReceive(missedQueue, &missed, portMAX_DELAY);

    // send the notification to ntfy
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    http.begin(client, NTFY_URL);
    int code = http.POST("Missed dose: patient did not confirm");
    Serial.printf("ntfy response: %d\n", code);
    http.end();
  }
}
