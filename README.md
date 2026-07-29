# Smart City Infrastructure — Smart Street Lighting & Smart Traffic Light

<p align="center">
  <img width="245" height="200" alt="LOGO STEAM" src="https://github.com/user-attachments/assets/61bd0c47-2c7a-4d1f-8947-d1add11c7d5e" />
</p>

<p align="center">
  <strong>Team: Smartanci</strong><br/>
  <em>Team project</em>
</p>

**Adaptive street lighting and traffic control by Team Smartanci — Arduino, HC‑SR04, C#, and web dashboard.**

---

## Project overview
This repository contains the implementation and documentation for an integrated **Smart Street Lighting (server)** and **Smart Traffic Light (client)** system. The solution uses Arduino microcontrollers, ultrasonic sensors, UART communication, a WiFi-hosted web dashboard, and a C# administrative application. The system dynamically adapts street lighting and traffic signals in real time based on detected traffic, improving safety, reducing energy consumption and enabling scalable IoT integration.

---

## System architecture
**High-level components**
- **Server** — *Arduino Uno R4 WiFi*: aggregates sensor data, runs lighting control logic, hosts the live web dashboard, and communicates with clients.  
- **Client** — *Arduino Uno R3 (ATmega328P)*: smart traffic light unit that receives commands and controls traffic signals in real time.  
- **Sensors** — four **HC‑SR04** ultrasonic sensors placed along the street for vehicle detection.  
- **C# Administrative System** — desktop application for monitoring, logging, manual control and UART diagnostics.  
- **Web Dashboard** — hosted on the Arduino R4 WiFi; provides live visualization, detection history graphs and UART logs.


**Communication channels**
- **WiFi (HTTP / WebSocket)** — server ↔ web dashboard / C# app (when networked)  
- **UART** — server ↔ traffic light client (low-latency command & status)  
- **Local I/O** — sensors and LEDs connected to Arduinos (PWM for dimming)

---

## Lighting logic and sensor mapping
Four HC‑SR04 sensors are distributed along the street. The system uses **cascading logic** to create a moving light corridor that follows detected vehicles.

| **Sensor** | **Position** | **Activates segments** |
|---:|:---|:---|
| HC1 | street entry (closest to S1) | S1; S2 |
| HC2 | second segment | S2; S3 |
| HC3 | third segment | S3; S4 |
| HC4 | exit segment | S4 |

**Behavior:** when HC1 detects a vehicle, the server sets segments S1 and S2 to active brightness; HC2 detection sets S2 and S3, etc. This forms a dynamic corridor that follows traffic and reduces unnecessary illumination elsewhere.

---

## Hardware & schematic
**Main components**
- **Arduino Uno R4 WiFi** — server (street lighting host & web dashboard)  
- **Arduino Uno R3 (ATmega328P)** — client (smart traffic light)  
- **HC‑SR04** ultrasonic sensors ×4  
- **LEDs** (street lamp simulation) + **220 Ω resistors**  
- **I2C multiplexer** (optional, for many sensors)  
- **5V power supply** sized for LED load  
- **Robust enclosures** and mounting hardware

**Schematic**
<img width="1469" height="709" alt="image" src="https://github.com/user-attachments/assets/9c3a1d22-c97b-4e6a-9c6d-58f682c62101" />

### Assembly diagram

<p align="center">
  <img width="1318" height="749" alt="image" src="https://github.com/user-attachments/assets/54ef561f-41ea-4159-b533-1d97a2a141ee" />
</p>

**Caption:** Assembly diagram showing wiring, connectors, power distribution and mounting points for the traffic light mockup.

## Software, languages & tools

**Development tools**
- **Arduino IDE** — firmware development and upload for Uno R3/R4  
- **Visual Studio Code** — code editing, PlatformIO or Arduino extensions, Git integration  
- **Visual Studio** — C# application development and debugging  
- **KiCad 10.0** — schematic and PCB design  
- **CAD tool** (e.g., FreeCAD, Fusion 360) — 3D model and mockup design

**Languages & frameworks**
- **C++** — Arduino firmware (server & client)  
- **C#** — desktop administrative/monitoring application (Visual Studio solution)  
- **HTML / CSS / JavaScript** — web dashboard UI (hosted on Arduino R4 WiFi or external host)  
- **WebSocket / HTTP** — real-time dashboard communication  
- **UART (serial)** — server ↔ traffic light client command channel

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-Modern-blue?logo=c%2B%2B&logoColor=white" alt="C++" />
  &nbsp;
  <img src="https://img.shields.io/badge/C%23-.NET-239120?logo=c-sharp&logoColor=white" alt="C#" />
  &nbsp;
  <img src="https://img.shields.io/badge/HTML5-HTML-orange?logo=html5&logoColor=white" alt="HTML5" />
  &nbsp;
  <img src="https://img.shields.io/badge/CSS3-CSS-1572B6?logo=css3&logoColor=white" alt="CSS3" />
  &nbsp;
</p>

---

## C# admin app & web dashboard
**C# application features**
- Real-time sensor feed (HC1–HC4 values and timestamps)  
- Manual control of lighting segments (`LED1: 1/0`, PWM brightness control)  
- Traffic status view and event log (detections, commands, errors)  
- UART monitor: live serial log between server and client, send/receive raw commands  
- Fault notifications and history export (CSV)  
- Basic admin authentication
  
<img width="1434" height="864" alt="information_system" src="https://github.com/user-attachments/assets/f450d6be-2c16-481c-87df-f273e2f9087b" /> <br>

**Web dashboard features**
- Live visualization of the street with lamp segments and active sensors  
- Detection history graph (timeline of sensor triggers)  
- UART log viewer showing messages exchanged with the client  
- Accessible from any device on the same network (QR code in repo points to hosted demo)  
- Manual override controls and mode selection (AUTO / MANUAL / MAINTENANCE)
  
<img width="1899" height="912" alt="web_server_dashboard" src="https://github.com/user-attachments/assets/3cb3eaef-f940-4301-b3c3-e451b67ee3fb" />

---

## UART & API message formats
All messages are ASCII, CSV-style, newline-terminated (`\n`). Example messages:

| **Message type** | **Direction** | **Example** |
|---|---:|---|
| SENSOR_UPDATE | Server → Dashboard / C# | `SENSOR,HC1,120\n` |
| LIGHT_CMD | Server → Client | `LIGHT,S1,200\n` |
| SEMAFOR_STATUS | Client → Server | `HB,SEMAFOR,OK\n` |
| ADMIN_CMD | C# → Server | `SEMAFOR,MODE,AUTO\n` |

**ACK / error handling:** every command expects an `ACK` or `ERR` response; firmware implements retries and timeouts.

---

## 3D models and physical mockup
This project includes 3D models for the **traffic light housing** and a small-scale **street mockup** used for 3D printing and assembly.

**3D model preview**
<p align="center">
  <img width="210" height="512" alt="3d_model" src="https://github.com/user-attachments/assets/d71a2dfe-54bd-44ed-ba7e-a4fa59660eec" />
<img width="157" height="512" alt="3d_model_2" src="https://github.com/user-attachments/assets/bdfc1ec2-4e21-481f-8b5c-81888b089082" />
</p>

**Caption:** 3D model render of the traffic light housing and mockup used for 3D printing and assembly.

---

## Bill of Materials (summary)
- Arduino Uno R4 WiFi — 1x  
- Arduino Uno R3 — 1x  
- HC‑SR04 ultrasonic sensor — 4x  
- LEDs — quantity per design (e.g., 16)  
- 220 Ω resistors — same count as LEDs  
- I2C multiplexer — optional (1x)  
- 5V power supply — rated for total LED current  
- Enclosures, mounting brackets, wiring

---

## How to run (quick start)
**1. Firmware (server)**  
- Open `/firmware/server` in Arduino IDE or VS Code (PlatformIO).  
- Upload to Arduino Uno R4 WiFi.

**2. Firmware (client / traffic light)**  
- Open `/firmware/client` and upload to Arduino Uno R3.  
- Connect UART TX/RX between server and client (observe common ground).

**3. C# admin app**  
- Open `/software/csharp` solution in Visual Studio.  
- Build and run; configure server IP and serial port for UART monitoring.

**4. Web dashboard**  
- Web files are served by Arduino R4 WiFi; access via the static server IP 

---

## Security and reliability
- **Fallback mode:** if WiFi is lost, the client switches to a safe local cycle (predefined timing).  
- **Authentication:** dashboard and C# app support admin login; use strong local credentials.  
- **Logging & alerts:** automatic fault detection and admin notifications; mobile app allows citizen fault reports.  
- **Firmware update:** OTA update path planned for R4 (secure update recommended).

---

## IoT integration and extensions
The system is designed to integrate with broader smart-city services:
- Traffic management systems — coordinate timing and lighting with city control.  
- Air quality sensors — attach pollution sensors to lamp posts and surface alerts on dashboard.  
- Smart meters — integrate energy consumption per sector for analytics and billing.  
- Predictive maintenance — feed sensor and fault logs into analytics platforms for early fault detection.

---

<p align="center">
  <a href="https://your-hosted-site.example" target="_blank">
    <img width="300" height="300" alt="qrkod" src="https://github.com/user-attachments/assets/6f7c26fe-94a1-416c-a569-ba4a6584b87c" />
  </a>
</p>
<p align="center">
  <strong>Team and Project Website</strong><br/>
  <em>Details about the team, development notes, design files and live demo — scan the QR code or visit <a href="https://statuesque-pudding-4a326c.netlify.app/">web page smartanci</a></em>
</p>

---
## License
This project is licensed under the **MIT License** — see the [LICENSE](./LICENSE) file for full terms.

**Copyright (c) 2026 Team Smartanci**
<a href="./LICENSE"><br><br><img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License" /></a>

