# Automotive Co-Simulation with CARLA, Vector CANoe, AUTOSAR, and SIL Kit
## Table of Contents
- [Overview](#overview)
- [Goals](#goals)
- [System Architecture](#system-architecture)
- [Vector CANoe](#vector-canoe)
- [Connecting CANoe with SIL Kit Using the SIL Kit Adapter](#connecting-canoe-with-sil-kit-using-the-sil-kit-adapter)
- [CAN Protocol](#can-protocol)
- [SIL Kit and the C++ Participant](#sil-kit-and-the-c-participant)
- [CARLA and Its Connection to the C++ Participant](#carla-and-its-connection-to-the-c-participant)
- [AUTOSAR Architecture](#autosar-architecture)
- [How to Run](#how-to-run)
- [Results](#results)
- [Conclusion](#conclusion)
  
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
  <img src="https://drive.google.com/uc?export=view&id=1YwJTj7rHoTLUCYsHLDZN634bmLp_Yz8r" alt="System Architecture" width="500"/>
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

The ECUs are connected to a CANoe panel through **system variables**. The panel includes:
- a **switch** that acts as a throttle input
- a **meter/gauge** that displays the vehicle speed
- an **LED indicator** that turns on when the vehicle speed exceeds **40 km/h**

### CANoe Simulation Setup
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1AO_bxw-x2sKZ4sw82MX4YAKEA01aVMps" alt="CANoe Simulation Setup" width="900"/>
</p>
<p align="center"><em>Figure 2: CANoe simulation setup showing the three virtual ECUs connected to the CAN network.</em></p>

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
<p align="center"><em>Figure 3: CANoe panel with throttle control, speed meter, and LED indicator.</em></p>

This virtual setup helped in understanding how CANoe works in practice, including:
- ECU simulation
- CAN database creation
- CAPL scripting
- panel design
- system variables
- signal mapping
- message monitoring and interaction through a virtual CAN path

### Demonstration GIF
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1SNlX3kFiKMms_5dY2hmZhnhfabJKBZpR" alt="CANoe Demo GIF" width="800"/>
</p>
<p align="center"><em>Figure 4: CANoe panel interaction and CAN frame transmission through the virtual CAN path.</em></p>

## Connecting CANoe with SIL Kit Using the SIL Kit Adapter
In this project, the connection between **Vector CANoe** and **Eclipse SIL Kit** is achieved using the **SIL Kit Adapter** provided by **Vector**. This adapter allows CANoe to join the SIL Kit-based co-simulation environment and exchange CAN messages with other participants.

To establish the connection, the adapter is configured with:
- the **virtual network path**
- the **SIL Kit Registry address and port**

Once configured, CANoe can communicate with the SIL Kit environment through the adapter, making it possible to exchange CAN frames with the **C++ participant** connected to CARLA.

This adapter is an important part of the integration because it enables the CANoe virtual CAN setup to participate in the distributed simulation workflow instead of remaining isolated.

### SIL Kit Adapter Connection Demo
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1qKKlXkpdL_iwh-Q1uFtZKrMocPTnzXLk" alt="SIL Kit Adapter Connection Demo" width="850"/>
</p>
<p align="center"><em>Figure 5: GIF showing how CANoe is connected to SIL Kit using the SIL Kit Adapter.</em></p>

## CAN Protocol
Before discussing the communication flow in this project, it is useful to briefly introduce the **CAN frame**, which is the basic communication unit of the **Controller Area Network (CAN)** protocol.

A CAN frame is used to exchange data between nodes in an automotive network. Each frame contains an **identifier** that defines the message meaning and priority, and a **data field** that carries the transmitted information. Additional fields provide length information, control, and error checking.

A typical CAN frame includes:
- **Identifier (ID)**
- **Data Length Code (DLC)**
- **Data field**
- **Control and error-checking fields**

<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=121WhHp4blmAip8JBDqjKKDRoX4j5O9oc" alt="CAN Frame Structure" width="850"/>
</p>
<p align="center"><em>Figure 6: General structure of a CAN frame.</em></p>

In this project, CAN frames are used as the main communication mechanism between **Vector CANoe**, the **SIL Kit environment**, and the **C++ participant**.

## SIL Kit and the C++ Participant
In this project, a **C++ participant** is created in the **Eclipse SIL Kit** environment to manage the communication between the different parts of the co-simulation setup. The participant acts as the central integration component of the project.

Its main functions are:
- receiving **CAN frames** from **Vector CANoe**
- sending **CAN frames** back to CANoe through the SIL Kit environment
- opening a **socket connection** to communicate with **CARLA**
- integrating the **AUTOSAR RTE code** to execute the application logic of the project

Through this design, the C++ participant bridges the automotive communication side and the driving simulation side.

### Role of the C++ Participant
The participant is responsible for:
- joining the SIL Kit environment
- creating the CAN communication interface
- receiving CAN messages from CANoe
- sending CAN messages to CANoe
- opening a socket connection toward CARLA
- exchanging runtime data with CARLA
- interacting with the AUTOSAR RTE logic
- supporting the overall communication loop of the project

The participant therefore acts as the core connection point between:
- **CANoe**, through SIL Kit
- **AUTOSAR RTE**, through the integrated application logic
- **CARLA**, through the socket interface

<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1eBm8xpRggQ5G1VkqN_wyuQQXDWyUWIv1" alt="SIL Kit C++ Participant" width="850"/>
</p>
<p align="center"><em>Figure 7: SIL Kit C++ participant integrated with AUTOSAR RTE code and connected to CARLA through a socket interface.</em></p>

## CARLA and Its Connection to the C++ Participant
In this project, **CARLA** is used as the driving simulator to provide vehicle behavior and runtime data within the co-simulation environment. To connect CARLA with the rest of the system, a **socket-based communication interface** is implemented between **CARLA** and the **C++ participant**.

Although multiple integration methods are possible, **socket programming** was chosen because it provides a simple and flexible way to exchange data. Through this socket connection, CARLA can send vehicle information to the C++ participant and receive data when needed.

In the implemented scenario, a vehicle is added to the CARLA map and its speed is monitored during runtime. The vehicle speed is then sent through the socket connection to the **C++ participant**, which processes the data and forwards the related information through the SIL Kit-based communication environment.

A warning behavior is also implemented in this project. When the vehicle speed exceeds **40**, a warning is triggered and sent to **CANoe**. This demonstrates how data generated in CARLA can directly affect the automotive communication and warning logic in the co-simulation setup.

### CARLA Communication Workflow
1. A vehicle is spawned in the CARLA map.
2. The vehicle speed is read during simulation.
3. The speed value is sent to the **C++ participant** through the socket interface.
4. The C++ participant processes the data and exchanges the corresponding messages with **CANoe** through **SIL Kit**.
5. If the speed becomes greater than **40**, a warning is triggered in **CANoe**.

### CARLA Demonstration
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1N8cOurrBuQhf-aCUyirvi_1OPMRHDzYD" alt="CARLA Demo" width="850"/>
</p>
<p align="center"><em>Figure 8: CARLA runtime demo showing the vehicle behavior and its connection to the C++ participant.</em></p>

## AUTOSAR Architecture
**AUTOSAR** (AUTomotive Open System ARchitecture) is a standardized software architecture for automotive systems. It defines a structured way to design software components, interfaces, runnables, and communication between different parts of an ECU. In this project, AUTOSAR is applied at the **application layer** to organize the software logic used in the co-simulation workflow.

### AUTOSAR Overview
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1Qx9p0dM52PFXMElfjLzZzYtWDCH5sIdd" alt="AUTOSAR Architecture Overview" width="900"/>
</p>
<p align="center"><em>Figure 9: General AUTOSAR architecture overview.</em></p>

In this project, the application logic is structured according to an AUTOSAR-oriented design. The architecture contains **three software components (SWCs)**:

- **Application SWC**
- **Service Application SWC (SA-SWC)**
- **Complex Driver SWC**

### 1. Application SWC
The first software component is an **Application SWC**. It contains **two runnables**:

- **Runnable 1**
  - receives CAN frames coming from **CANoe**
  - is triggered by a **timing event every 10 ms**

- **Runnable 2**
  - takes the processed data
  - sends the relevant information toward **CARLA** to move the vehicle

This SWC is responsible for handling the incoming communication and forwarding the required control data to the simulator side.

### 2. SA-SWC
The second software component is a **Service Application SWC (SA-SWC)**. Its role is to:
- receive the current **vehicle speed**
- pass the speed information to the third SWC

This component acts as an intermediate processing block in the application flow.

### 3. Complex Driver SWC
The third software component is a **Complex Driver SWC**. Its main role is to evaluate the speed value and generate a warning condition.

- if the vehicle speed is **greater than 40**
- the component sends a **warning signal**

This warning is then used in the co-simulation workflow to trigger the corresponding indication.

### Project AUTOSAR Flow
The AUTOSAR-based application flow in the project can be summarized as follows:

1. CAN frames are received from **CANoe**
2. The **Application SWC** processes the incoming data every **10 ms**
3. The processed data is sent toward **CARLA** to control the vehicle
4. The vehicle speed is collected and passed to the **SA-SWC**
5. The **SA-SWC** forwards the speed to the **Complex Driver SWC**
6. If the speed exceeds **40**, the **Complex Driver SWC** generates a warning

### AUTOSAR Architecture Representation
<table align="center">
  <tr>
    <td align="center">
      <img src="https://drive.google.com/uc?export=view&id=16Sl7YgNvsF9VMg0KUqlEUavdMHfegAI3" alt="AUTOSAR Architecture 1" width="400"/>
    </td>
    <td align="center">
      <img src="https://drive.google.com/uc?export=view&id=1OlC35pO_Iq6VjrJNF0y2e5Ketv4RxzC0" alt="AUTOSAR Architecture 2" width="400"/>
    </td>
  </tr>
</table>
<p align="center"><em>Figure 10: AUTOSAR software component architecture representations used in the project.</em></p>

## How to Run

To run this project, you first need to make sure that the required tools and dependencies are available:

- **CARLA Simulator**
- **Vector CANoe** with a valid license
- **Eclipse SIL Kit Registry**

After preparing the environment, follow these steps:

### 1. Start the SIL Kit Registry
Run the SIL Kit Registry so that the simulation participants can connect to the communication environment.

### 2. Start the CARLA server
Launch the CARLA simulator server.

### 3. Run the CARLA Python script
Execute the Python script located at: carla/script.py

### 4. Run the Cpp Executable file
executable located at: Sil-Kit/build/Release/CppSpeedReader.exe
### 5. Run Canoe
start to control with the throttle and seec changes at the speed

## Results
The project demonstrates a complete automotive co-simulation workflow integrating **CARLA**, **Vector CANoe**, **AUTOSAR**, and **Eclipse SIL Kit**.

The achieved results include:
- successful CAN communication between **CANoe** and the **C++ participant**
- integration of **CANoe** with **SIL Kit** through the **SIL Kit Adapter**
- socket-based communication between **CARLA** and the **C++ participant**
- AUTOSAR-based application logic integrated through the **RTE**
- speed monitoring and warning generation based on runtime vehicle behavior
- visual validation through CANoe panels, gauges, LED indicators, and simulation demonstrations

## Conclusion
This project demonstrates an automotive co-simulation environment that combines **CARLA**, **Vector CANoe**, **AUTOSAR architecture**, and **Eclipse SIL Kit** through a **C++ participant**. The system uses **CAN communication**, **socket-based CARLA integration**, and **AUTOSAR-oriented software structure** to build a complete simulation workflow.

The project shows how vehicle simulation, CAN network simulation, AUTOSAR application logic, and distributed communication tools can be integrated into one coherent setup for testing, learning, and demonstration purposes.
