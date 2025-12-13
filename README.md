# Robust AI Navigation in Distributed Environments
### : Handling High Latency & Packet Loss using Hybrid Synchronization

[![Unreal Engine](https://img.shields.io/badge/Unreal_Engine-5.4+-black?logo=unrealengine)](https://www.unrealengine.com/)
[![Language](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus)](https://isocpp.org/)
[![Network](https://img.shields.io/badge/Network-Custom_UDP-green)]()
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)]()

> **Project Status:** Completed (December 2025)  
> **Domain:** Distributed Systems, Real-Time Simulation, Game AI, Network Programming  
> **Key Tech:** Custom UDP Socket, Entity Interpolation, Dead Reckoning (First-Order)

<br>

## Full Research Report
For a detailed analysis of the algorithms and experimental data, please refer to the full report below:

[![Read Full Report](https://img.shields.io/badge/📄_Read_Full_Research_Report_(PDF)-Click_Here-blue?style=for-the-badge)](./Docs/Research_Report.pdf)

---

## Abstract
This project implements a **fault-tolerant state synchronization framework** for Server-Authoritative AI systems operating under unstable network conditions. Bypassing commercial engine replication (e.g., `UNetDriver`), I developed a **custom UDP networking layer** to simulate real-world constraints such as high latency, jitter, and packet loss.

The core contribution is a **Hybrid Prediction Algorithm** that adaptively switches between **Entity Interpolation** and **Dead Reckoning** based on packet arrival gaps. Quantitative experiments demonstrate that the system maintains agent availability and visual continuity even under **300ms latency** and **61% packet loss**, proving its resilience in soft real-time distributed environments.

---

## Visual Demonstration

The left screen shows the raw network view (stuttering/stopped), while the right screen shows the predicted view (smooth/continuous) using the proposed algorithm.

![Split Screen Demo](./Docs/Demo_SplitScreen.gif)

| **Scenario 1: High Latency (300ms)** | **Scenario 2: Critical Packet Loss (60%+)** |
|:---:|:---:|
| **Interpolation** ensures smooth movement despite severe jitter. | **Dead Reckoning** maintains movement during communication blackouts. |

---

## System Architecture

The simulation adopts a strict **Server-Authoritative** architecture to ensure data integrity, decoupling the simulation logic (Brain) from the visualization (Body).

```mermaid
graph LR
    subgraph Server ["Server (Authority)"]
        A[NavMesh A* Pathfinding] -->|Snapshot| B(UDP Sender)
    end
    B -.->|Packet Loss / Jitter| C(UDP Receiver)
    subgraph Client ["Client (Visualizer)"]
        C --> D{Gap Check}
        D -- Sufficient Data --> E[Entity Interpolation]
        D -- Data Loss --> F[Dead Reckoning]
        E --> G[Soft Correction]
        F --> G --> H[Rendering]
    end
````

### 1\. Networking Layer (Custom UDP)

Instead of relying on high-level abstractions, a raw BSD-socket-based networking manager was implemented.

  * **Protocol:** Custom binary packet structure (`Header` + `Payload` + `Timestamp`).
  * **Fault Injection:** Programmable **Latency (0-500ms)** and **Packet Loss (0-100%)** simulation at the application layer.

### 2\. Hybrid Synchronization Algorithm

The client employs a Finite State Machine (FSM) to handle incoming state snapshots:

  * **State A: Entity Interpolation (Normal Operation)**
      * Delays rendering ($T_{render} = T_{server} - T_{delay}$) to buffer incoming packets.
      * Performs linear interpolation (Lerp) to eliminate jitter artifacts.
  * **State B: Dead Reckoning (Packet Loss Fallback)**
      * Triggered when the buffer underruns due to packet loss ($Gap > Threshold$).
      * Extrapolates future positions using the last known kinematic data ($P_{new} = P_{last} + V \times \Delta t$).
  * **Reconciliation:** Uses **Soft Correction** (`VInterpTo`) to smoothly blend the estimated state with the authoritative state upon reconnection.

-----

## Experimental Results & Analysis

Experiments were conducted to measure **Position Error** and **Velocity Maintenance** under varying network conditions.

### 1\. Robustness: Position Error Analysis

**Condition:** Latency 110ms / **Packet Loss 61%**

  * **Observation:** The blue line (ON) shows occasional spikes when Dead Reckoning is active during packet loss.
  * **Analysis:** Crucially, the error **rapidly converges to zero** immediately after the spike. This proves the system's **Resilience**—it recovers from prediction errors without permanent desynchronization or visual snapping.

### 2\. Availability: Velocity Maintenance

**Condition:** Communication Blackout Intervals

  * **Observation:** The red dotted line (OFF) frequently drops to zero, indicating the agent has stopped moving due to data loss.
  * **Analysis:** The blue solid line (ON) maintains a velocity profile similar to the server's ground truth (Green). This proves **System Availability**—the agent continues to function autonomously based on its kinematic model even when the network is down.

-----

## Technology Stack

  * **Core Engine:** Unreal Engine 5.4 (Source Build)
  * **Language:** C++17 (Strict memory management with Smart Pointers)
  * **Networking:** `FSocket` (Low-level UDP implementation)
  * **AI:** Navigation Mesh, A\* Pathfinding
  * **Data Analysis:** Python (Pandas, Matplotlib) for log parsing and visualization

-----

## Author

**Dohun Lee**

  * **Affiliation:** DigiPen Institute of Technology (BS in Computer Science in Real-Time Interactive Simualtion)
  * **Contact:** vbn9302@gmail.com
