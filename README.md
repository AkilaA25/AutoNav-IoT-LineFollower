# AutoNav-IoT-LineFollower
IoT-enabled autonomous car developed for ECE 306 at NC State University. Navigates via Wi-Fi commands, autonomously detects and follows a black line, performs precise maneuvers, and displays real-time status on an LCD. Combines embedded firmware, sensor integration, and motor control.

# ECE 306: Autonomous Embedded Systems Car

This project is the culmination of a semester-long embedded systems course at NC State University (ECE 306), where I developed an autonomous car using a TI MSP430G2553 microcontroller. The course followed a modular progression of ten individual projects, each building on embedded systems fundamentals to gradually develop a fully functioning, sensor-guided robotic car. By the end, the car was capable of line-following navigation using ADC reflectance sensors and motor control via PWM signals.

## 🚗 Project Overview

The autonomous car was built on a two-wheeled chassis with independent DC motor control, powered by a regulated battery supply. It used analog reflectance sensors to detect black lines on a track, feeding into the MSP430’s ADC for threshold-based decision-making. Motion was controlled via an H-bridge and software-generated PWM signals, while real-time feedback was displayed on an LCD. All software was written in embedded C with low-level register manipulation.

This project provided real-world, hands-on experience with microcontroller programming, hardware interfacing, and real-time system design. Each milestone introduced new subsystems or challenges, culminating in a final integrated autonomous vehicle.

## 🧠 Key Features

- **Autonomous Navigation**: Line-following behavior using analog sensors and calibrated ADC thresholds.
- **PWM-Based Motor Control**: Independent control of two DC motors with adjustable speed and direction using software PWM.
- **LCD Output**: Live debugging and data output via a parallel-interface LCD.
- **Real-Time Interrupts**: Debounced user input via interrupt-driven button control.
- **Battery System**: Power management and physical design for mobile operation.
- **Reflectance Sensor Calibration**: Real-time ADC thresholding and tuning for accurate sensor response.
- **Modular Design**: Software written in stages, with reusable C modules and interrupt service routines.

## 🛠 Hardware Components

- MSP430G2553 Microcontroller
- 4x DC Motors + H-Bridge Motor Driver
- 2x Reflectance Sensor
- LCD Module
- Push Button Interface
- Breadboard for signal routing
- Chassis and wheel platform

## 📚 Skills Gained

- Embedded C programming
- Register-level microcontroller configuration
- Real-time systems and interrupt handling
- ADC and PWM configuration
- Peripheral integration (LCD, sensors, motors)
- Breadboarding and embedded hardware design
- Debugging using LEDs, LCD, and serial I/O
- Modular software development in constrained environments

## 🧩 Educational Value

This project simulated real-world embedded development: tight memory constraints, low-level control, real-time deadlines, and debugging without traditional OS support. It prepared me for systems-level firmware development and gave me an appreciation for the complexity of embedded design workflows used in automotive systems, robotics, consumer electronics, and IoT devices.

## 📷 Demo

![Final Car Demo](images/IMG_3876.jpg)
[![Watch the demo](images/demo-thumbnail.jpg)]([https://www.youtube.com/watch?v=YOUR_VIDEO_ID](https://youtube.com/shorts/bu2CRzftjk8))


