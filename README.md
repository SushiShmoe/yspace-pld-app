# ySpace PLD Thermal Application (LTC2983 + CSP + FreeRTOS)

![Flight Heritage](https://img.shields.io/badge/Flight_Heritage-In_Orbit-critical.svg)
![Mission](https://img.shields.io/badge/Mission-ySpace_PLD-blue.svg)
![Platform](https://img.shields.io/badge/Platform-STM32U5-lightgrey.svg)
![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS-green.svg)

**Mission-Proven Flight Software**
This repository contains the application software currently running in low Earth orbit on the YSpace PLD (Payload). Built on FreeRTOS and an STM32U5 microcontroller, the software manages high-precision thermal data acquisition via the LTC2983 sensor and acts as an active subsystem on the satellite's network using the **CubeSat Space Protocol (CSP)**.

## 🚀 System Architecture

This application bridges the gap between low-level hardware abstraction and high-level satellite network topology. It is divided into three core pillars:

### 1. CSP Networking & Routing
The application integrates the CubeSat Space Protocol (CSP) to operate as a fully addressable endpoint on the spacecraft's I2C bus.
* **Dedicated Tasks:** Uses isolated FreeRTOS tasks for the CSP listener (`cspListenerTask`), the CSP router (`cspRouterTask`), and I2C Rx handling (`cspI2C`).
* **Routing Table:** Implements a static routing table to handle traffic between various subsystems across the satellite.
* **Interrupt-Driven I2C:** Utilizes non-blocking IT sequences (`HAL_I2C_Slave_Seq_Receive_IT`) to receive CSP packets asynchronously, minimizing CPU overhead and preventing bus lock-ups.

### 2. Custom Payload Command Server
A dedicated CSP service handler processes incoming telecommand requests from the On-Board Computer (OBC) over port 10.
* **Command Set:** Supports remote commands to Set Mode (Single/Continuous polling), Get Status, Read Temperature, and dynamically recalibrate the Rsense values.
* **Concurrency Safety:** Ensures thread-safe data access by wrapping temperature reads and configuration updates in FreeRTOS Mutexes.

### 3. Asynchronous LTC2983 Sensor Driver
The hardware layer interacts with the LTC2983 chip using a highly optimized, custom C driver designed strictly for RTOS environments.
* **Non-Blocking SPI:** Replaces blocking delays with DMA-driven SPI transfers (`HAL_SPI_TransmitReceive_DMA`) coupled with a custom state machine to manage hardware sequences without stalling the CPU.
* **Event-Driven:** Uses EXTI hardware interrupts (`HAL_GPIO_EXTI_Rising_Callback`) to detect when an ADC conversion is complete, immediately advancing the state machine without polling.
* **Thread-Safe App Manager:** The main manager task orchestrates the driver, handling measurement modes using FreeRTOS Thread Flags for precise synchronization.

## 📂 Code Structure

* **`app_csp.c`**: Initializes the CSP stack, configures the I2C interface, and spawns the networking tasks.
* **`app_LTC2983.c`**: The main application layer connecting the raw hardware driver to FreeRTOS (Mutexes, Thread Flags, App Manager Task).
* **`server_ltc.c`**: The CSP service endpoint containing the handlers for remote telemetry requests (Parse/Build logic).
* **`LTC2983.c` & `LTC2983_config.c`**: The core, state-machine-driven, non-blocking hardware driver and its configuration structures.
* **State Machine Callbacks:** The SPI Tx/Rx completion callback evaluates the current task state (e.g., `TASK_STATE_READ_TEMP_RESULTS_TRANSFER`) and processes incoming DMA buffers directly in the background.
* **Remote Configuration:** The CSP server allows the ground station or OBC to dynamically adjust the Sense Resistor value or change the polling frequency while in flight, ensuring mission adaptability.
