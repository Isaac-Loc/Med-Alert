// Settings you can change
#ifndef CONFIG_H
#define CONFIG_H

// pin numbers
#define LED_PIN 16
#define BUZZER_PIN 17
#define BUTTON_PIN 4

// dose time, 24-hour clock
#define DOSE_HOUR 8
#define DOSE_MINUTE 0

// time allowed before a missed-dose alert (10 minutes)
#define DOSE_TIMEOUT_MS (10UL * 60UL * 1000UL)

// time settings
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC (-5 * 3600)
#define DAYLIGHT_OFFSET_SEC 3600

#endif
