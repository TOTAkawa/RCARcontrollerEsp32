# ESP32 Wireless Motor Control System (Wi-Fi & Bluetooth)

[![Platform](https://img.shields.io/badge/platform-ESP32-blue)](https://www.espressif.com/en/products/socs/esp32)
[![Language](https://img.shields.io/badge/language-C-green)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Framework](https://img.shields.io/badge/framework-ESP--IDF-red)](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)

Complete embedded firmware for an ESP32-based mobile robot platform. The system receives remote commands via **Wi-Fi (TCP sockets)** and **Bluetooth (SPP)** to control two geared DC motors in real-time.

This project was built as a hands-on prototype on a **wooden board chassis**, using off-the-shelf components (L298N, power banks, and geared motors) to validate the control logic and wireless communication stack.

---

## ✨ Features

- **Dual Wireless Control**: Supports both **Wi-Fi (TCP/UDP)** and **Bluetooth (SPP)** simultaneously.
- **Real-time Motor Control**: Uses hardware **PWM** (Pulse Width Modulation) for precise speed regulation of two DC motors.
- **Command Interpreter**: Parses incoming wireless packets into steering and throttle actions (Forward, Reverse, Turn, Stop, Speed percentage).
- **RTOS Task Management**: Built with **FreeRTOS** on the ESP-IDF framework, ensuring concurrent network handling and motor driver logic without blocking.
- **Modular Design**: Hardware abstraction layer makes it easy to adapt to different motor drivers (L298N, DRV8833, or TB6612).
- **Portable Power**: Designed to run on standard 5V USB **Power Banks**, making the prototype battery-operated and easy to test anywhere.

---

## 🛠️ Hardware Required

- **ESP32** Development Board (Standard 30/38 pins).
- **L298N** Dual H-Bridge Motor Driver Module.
- **2x Geared DC Motors** with wheels (6V-12V).
- **2x Power Banks** (5V USB) – *One for the ESP32 logic, one for the motor driver (or a dedicated battery for the L298N depending on your wiring).*
- **Wooden board / plank** (used as the chassis base).
- Jumper wires, screws, and zip ties for cable management.

---

## 🔌 Pin Mapping (Wiring Example)

*Adjust these pins to match your actual wiring in the source code:*

| ESP32 Pin | L298N / Component Connection |
| :--- | :--- |
| GPIO 13 | ENA (Enable A / PWM Speed for Motor A) |
| GPIO 12 | IN1 (Direction A) |
| GPIO 14 | IN2 (Direction A) |
| GPIO 27 | ENB (Enable B / PWM Speed for Motor B) |
| GPIO 26 | IN3 (Direction B) |
| GPIO 25 | IN4 (Direction B) |
| 5V / USB | Power Bank #1 (ESP32 logic power) |
| 12V / VIN | Power Bank #2 or external battery (L298N motor power) |
| GND | Common Ground between ESP32, L298N, and Power Supplies |

---

## 🚀 How It Works (Architecture)

1.  The ESP32 initializes the Wi-Fi stack (SoftAP or Station mode) and Bluetooth SPP stack.
2.  A **FreeRTOS task** handles incoming Wi-Fi packets.
3.  Another **task** manages the Bluetooth serial interface.
4.  Both tasks feed commands into a shared **Command Interpreter**.
5.  The interpreter translates commands (e.g., `F150` -> Forward at 50% speed) into PWM duty cycles.
6.  Motor driver pins are updated in real-time, controlling the vehicle movement.

---

## 🏗️ Build & Flash (ESP-IDF)

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/yourusername/esp32-wireless-motor-control.git
    cd esp32-wireless-motor-control
