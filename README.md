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

### High-Level Data Flow
```text
CARLA <--> C++ Participant <--> Eclipse SIL Kit <--> SIL Kit Adapter <--> Vector CANoe