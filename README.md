# Automotive Co-Simulation with CARLA, Vector CANoe, AUTOSAR, and SIL Kit

## Overview
This project presents an automotive co-simulation environment integrating **CARLA**, **Vector CANoe**, **AUTOSAR architecture**, and **Eclipse SIL Kit** through a **C++ participant**. The system is designed to enable communication between a driving simulator and automotive network simulation tools using the **CAN protocol**.

The project combines:
- **CARLA** for vehicle and environment simulation
- **Vector CANoe** for CAN network simulation, monitoring, and analysis
- **Eclipse SIL Kit** for communication and co-simulation connectivity
- a **C++ participant** that bridges CARLA and the SIL Kit communication layer
- an **AUTOSAR-oriented architecture** to represent the automotive system structure

The documentation explains how CANoe is connected to SIL Kit using the **SIL Kit Adapter**, how CAN communication is handled, how CARLA exchanges data with the C++ participant, and how the project fits within an AUTOSAR-based architectural view. Screenshots, photos, and videos are included throughout the documentation to illustrate the workflow and results.

## Goals
The main goals of this project are to:

- build a closed-loop automotive co-simulation environment
- integrate **CARLA** with **Vector CANoe**
- connect **CANoe** to **Eclipse SIL Kit** through the **SIL Kit Adapter**
- use the **CAN protocol** as the communication mechanism between components
- implement a **C++ participant** to exchange data between CARLA and the SIL Kit network
- represent the system using an **AUTOSAR-oriented project architecture**

## System Architecture
The co-simulation environment consists of the following main components:
<p align="center">
  <img src="data/Screenshot 2026-03-28 062200.png" alt="System Architecture" width="500"/>
</p>
<p align="center"><em>Figure 1: High-level architecture of the co-simulation environment.</em></p>

- **Vector CANoe**
  - simulates and monitors CAN communication

- **SIL Kit Adapter**
  - connects Vector CANoe to the SIL Kit environment

- **Eclipse SIL Kit**
  - provides communication and participant connectivity

- **C++ Participant**
  - acts as the bridge between CARLA and SIL Kit

- **CARLA**
  - provides vehicle dynamics and environment simulation

- **AUTOSAR Architecture**
  - provides the architectural context of the automotive system

## Vector CANoe
In this project, **Vector CANoe** is used to simulate and monitor the CAN communication network within the co-simulation environment. To better understand and apply CANoe features, a virtual CAN setup was created with **three ECUs** connected over a **virtual CAN bus**.

The CANoe configuration includes:
- **three simulated ECUs**
- a custom **CAN database (DBC)**
- **CAPL programs** for ECU behavior
- a **panel** for user interaction and signal visualization

the ECUs are connected to a CANoe panel through **system variables**. The panel includes:
- a **switch** that acts as a throttle input
- a **meter/gauge** that displays the vehicle speed
- an **LED indicator** that turns on when the vehicle speed exceeds **40 km/h**
### CANoe Simulation Setup
### CANoe Simulation Setup
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1AO_bxw-x2sKZ4sw82MX4YAKEA01aVMps" alt="CANoe Simulation Setup" width="900"/>
</p>
<p align="center"><em>Figure 3: CANoe simulation setup showing the three virtual ECUs connected to the CAN network.</em></p>

The workflow is as follows:
1. The user presses the throttle switch on the CANoe panel.
2. The switch is linked to a **system variable**.
3. The system variable is connected to the corresponding ECU logic.
4. The ECU transmits the relevant CAN messages over the **virtual CAN bus**.
5. The data is exchanged with the co-simulation setup and affects the vehicle behavior in **CARLA**.
6. The current speed is received through CAN signals and displayed on the panel meter.
7. When the speed becomes greater than **40**, the **LED indicator** on the panel is activated.
### CANoe Panel
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1aV1nBn6kvP29vpH7-lFECfm6Kw_cJIuq" alt="CANoe Panel" width="700"/>
</p>
<p align="center"><em>Figure 2: CANoe panel with throttle control, speed meter, and LED indicator.</em></p>

This virtual setup helped in understanding how CANoe works in practice, including:
- ECU simulation
- CAN database creation
- CAPL scripting
- panel design
- system variables
- signal mapping
- message monitoring and interaction through a virtual CAN path

### Demonstration Video
<p align="center">
  <video width="800" controls>
    <source src="https://drive.google.com/uc?export=download&id=1LYdlF2GKU6qcSpv8W7oamq5-uRR9T2Ce" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</p>
<p align="center"><em>Figure 4: CANoe panel interaction and CAN frame transmission through the virtual CAN path.</em></p>
