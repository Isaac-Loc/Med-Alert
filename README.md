# Med-Alert

A two-stage medication reminder built on an ESP32 running FreeRTOS.

**Course:** CSE 321: Real Time and Embedded Operating Systems
**Checkpoint:** 1
**Team:** Jian Xi Lu, Isaac Loc

## Problem Statement

Missing medication doses is a serious problem for elderly people who live alone and for anyone who must take medicine on a strict schedule (for example antibiotics, heart medication, or diabetes medication). A missed dose can make the medicine less effective or lead to hospital visits. Family members need a way to know that patients are taking their treatments on time.

Phone alarms are not enough. They are easy to miss and leave no record of whether the medicine was actually taken.

Med-Alert fixes this with a dedicated device:

1. The board gets the current time from the internet.
2. At each scheduled medication time, it lights an LED and sounds a buzzer.
3. A 10-minute countdown starts on the board. If it reaches 0 without a button press, the board sends a notification to the caregiver's phone that the dose was missed.
4. If the patient takes the dose on time, they press the button. This stops the countdown and the alarm, and the board waits for the next scheduled time.

## Hardware

| Component | Purpose | Interaction |
| --- | --- | --- |
| ESP32 Dev Board (ESP-WROOM-32, 30-pin) | Microcontroller with built-in Wi-Fi | Reads the button. Drives the LED and buzzer through a transistor. Sends missed-dose notifications over Wi-Fi. |
| Buzzer | Audible reminder | Switched on and off by the ESP32 through the transistor. |
| LED | Visual reminder | Lit by the ESP32 while a dose is due. Turns off when the patient takes the medication. |
| Button | Patient interaction | Pressing it pulls the signal from HIGH to LOW, which turns off the LED and buzzer if they are on. |
| Resistor | Current limiting | Controls the current through the LED so it does not overheat. |

Final assembly is soldered onto perfboard. A breadboard is used during prototyping.

## Bill of Materials

| Item | Purpose | Price | Status |
| --- | --- | --- | --- |
| ESP32 Dev Board | Microcontroller with Wi-Fi | $8.99 | Order placed |
| Electronics Fun Kit (buzzer, LED, button, transistor, resistors) | Alerts, dose confirmation, and protection components | $9.99 | Order placed |
| Perfboard / solderable breadboard | Soldered final assembly | n/a | Unconfirmed. Not essential to the build process now. Will be ordered later. |
| **Total** | | **$18.98** | |

## Software and Development Environment

- **Visual Studio Code:** main code editor.
- **PlatformIO:** VS Code extension used to build and flash the code.
- **Arduino framework for ESP32:** provides the C++ API and includes FreeRTOS.
- **GitHub:** shared repository for storing and managing the project code.

## RTOS Design

The project uses FreeRTOS, which ships with the Arduino ESP32 framework. No separate FreeRTOS installation is needed. PlatformIO downloads the framework, and FreeRTOS comes with it.

| Task | Priority | Function |
| --- | --- | --- |
| ConfirmTask | High (implement first or second) | Fires an interrupt when the button is pressed. Stops the alarm and logs the dose. |
| AlertTask | High (implement first or second) | Checks the clock against the scheduled times. Starts the buzzer and LED when a dose is due. |
| ReminderTask | Mid (after ReminderTask and ConfirmTask work) | Handles the missed-dose path. When the 10-minute countdown reaches 0, it sets a missed-dose flag and sends a notification to a device over Wi-Fi via ntfy.sh. |
| TimeSyncTask | Mid (after ReminderTask and ConfirmTask work) | Syncs the clock with an internet time source so it stays correct. |

**Why an RTOS:** the system has to keep time, sound the buzzer, run a 10-minute timer, watch the button, and send Wi-Fi notifications at the same time, and it must respond to the patient without delay. With an RTOS, each of these runs as a separate task with its own priority, so one task does not disturb another's timing. The button and alarm tasks have the highest priority, so pressing the button silences the buzzer immediately. FreeRTOS timers, queues, and mutexes pass missed-dose notifications between tasks and protect the dose log.

## Project Status

- Problem statement, hardware design, and RTOS task design are complete (Checkpoint 1).
- ESP32 and electronics kit are ordered.
- Perfboard is not yet ordered.
