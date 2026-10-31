#ifndef CONFIG_H
#define CONFIG_H

#define LED_PIN 16
#define BUZZER_PIN 17
#define BUTTON_PIN 4

// Scheduled dose time (24-hour clock, local time)
#define DOSE_HOUR 8
#define DOSE_MINUTE 0

// Time allowed to press the button before a missed-dose alert is sent
#define DOSE_TIMEOUT_MS (10UL * 60UL * 1000UL)

#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC (-5 * 3600)  // Eastern time
#define DAYLIGHT_OFFSET_SEC 3600

#endif
