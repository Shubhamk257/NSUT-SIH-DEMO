# System Architecture — AI-Powered Environmental Monitoring Network

## 1. Overview

A resilient, AI-powered environmental monitoring network that provides early detection, localized intelligence, and actionable alerts for floods, forest fires, pollution events, and other environmental hazards common in India — enabling authorities and communities to shift from reactive disaster response to proactive risk prevention.

The system follows an **Edge → Gateway → Cloud → Dashboard** pipeline, with AI inference running on-device to minimize latency and bandwidth usage.

---

## 2. High-Level Architecture

```
┌─────────────────────────┐
│   SENSOR NODE (EDGE)    │
│                         │
│  DHT11 (Temp/Humidity)  │
│  MQ-2 (Smoke/Gas)       │
│  Water Level Sensor     │
│  Air Quality (PM2.5/10) │
│  Soil Moisture/Vibration│
│  Gas/Chemical Leak      │
│                         │
│  ┌───────────────────┐  │
│  │   ESP32-S3 MCU    │  │
│  │  + TinyML (Edge   │  │
│  │    Impulse model) │  │
│  └─────────┬─────────┘  │
│            │ Filtered   │
│            │ critical   │
│            │ alerts only│
│  Solar Panel + Battery  │
│  Weatherproof Enclosure │
└────────────┬────────────┘
             │ LoRaWAN
             ▼
┌─────────────────────────┐
│    LoRaWAN GATEWAY      │
│  Aggregates node data   │
│  Forwards to cloud      │
└────────────┬────────────┘
             │ Internet (MQTT/HTTPS)
             ▼
┌─────────────────────────┐
│      CLOUD PLATFORM     │
│                         │
│  Supabase (PostgreSQL)  │
│  - Sensor data storage  │
│  - Trend analysis       │
│  - Geospatial mapping   │
└────────────┬────────────┘
             │ REST/Realtime API
             ▼
┌─────────────────────────┐
│  DASHBOARD & ALERTS     │
│                         │
│  HTML5 + Tailwind CSS   │
│  Chart.js (analytics)   │
│  Leaflet.js (live map)  │
│                         │
│  Notifications:         │
│  Mobile / SMS / Email   │
│  → Authorities (NDMA,   │
│    Forest Dept, Local   │
│    Municipal Councils)  │
│  → Communities          │
└─────────────────────────┘
```

---

## 3. Component Breakdown

### 3.1 Hardware Layer (Sensor Node)

| Component | Function |
|---|---|
| ESP32-S3 | Edge AI microcontroller; runs TinyML inference |
| DHT11 | Temperature & humidity monitoring |
| MQ-2 | Smoke / gas detection (fire & hazardous pollution events) |
| Solar Panel + Battery | Continuous power in remote/off-grid areas |
| LoRaWAN Antenna | Long-range, low-power wireless transmission |
| Weatherproof Enclosure | Outdoor / forest / disaster-prone deployment |

> **Planned additions (Future Scope):** Water level, air quality (PM2.5/PM10), soil moisture/vibration, and gas/chemical leak sensors — to extend coverage to floods, landslides, and broader pollution monitoring.

### 3.2 Edge AI Layer

- **Framework:** TensorFlow Lite (via Edge Impulse)
- **Function:** Runs anomaly/hazard detection models directly on ESP32-S3
- **Benefit:** Zero-latency detection, works fully offline, reduces cloud dependency
- **Output:** Only critical/summarized alerts are transmitted (reduces bandwidth cost)

### 3.3 Communication Layer

- **Protocol:** LoRaWAN
- **Path:** Sensor Node → LoRaWAN Gateway → Internet → Cloud
- **Why LoRaWAN:** Long range, low power, ideal for remote forest/rural/disaster-prone zones with limited connectivity

### 3.4 Cloud Layer

- **Database:** Supabase (PostgreSQL)
- **Responsibilities:**
  - Long-term data storage
  - Trend/historical analysis
  - Geospatial data for mapping
  - API layer for dashboard consumption

### 3.5 Application Layer (Dashboard)

- **Frontend:** HTML5, Tailwind CSS
- **Visualization:** Chart.js (trends/metrics), Leaflet.js (live hazard map)
- **Features:**
  - Real-time risk maps
  - Sensor status monitoring
  - Historical trend charts
- **Alerting:** Mobile push / SMS / Email to authorities (NDMA, forest departments, municipal councils) and local communities

---

## 4. Data Flow (Step-by-Step)

1. **Data Collection** — Sensors continuously monitor environmental parameters (temperature, humidity, smoke, gas, water level, etc.)
2. **On-Device AI Analytics** — TinyML model on ESP32-S3 detects anomalies in real time, even without connectivity
3. **Alert Generation** — Only critical/summarized alerts are generated locally, reducing data volume
4. **Data Transmission** — Alerts sent via LoRaWAN to a gateway, then relayed to the cloud
5. **Cloud Storage & Processing** — Data stored in Supabase for persistence, trend analysis, and geospatial mapping
6. **Dashboard & Notifications** — Real-time risk maps and alerts pushed to authorities and communities

---

## 5. Technology Stack

| Layer | Technology |
|---|---|
| Hardware / Microcontroller | ESP32-S3 |
| Sensors | DHT11 (Temperature & Humidity), MQ-2 (Smoke & Gas) |
| Programming Languages | C++, HTML5, JavaScript |
| AI/ML Frameworks | TinyML, Edge Impulse Studio, TensorFlow Lite for Microcontrollers |
| Frontend / UI | HTML5, Leaflet.js (GIS Mapping), Chart.js (Real-time Telemetry) |
| Backend & Database | Supabase, REST APIs |
| Development Tools | Arduino IDE |
| Communication | LoRaWAN |
| Alerts | Mobile / SMS / Email |

---

## 6. Design Principles

- **Solar-powered & low maintenance** — sustainable for long-term remote deployment
- **Rugged & weatherproof** — built for forest and disaster-prone conditions
- **Edge-first AI** — detection doesn't depend on constant connectivity
- **Bandwidth-efficient** — only critical alerts leave the node, not raw data
- **Modular & scalable** — architecture supports expansion from a few nodes to large-scale statewide networks

---

