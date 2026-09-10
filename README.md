# SIH 2026 Project Repository Template

## 1. Project Information

- **Project Title:** Resilient AI-Powered Environmental Monitoring Network For Early Multi-Hazard Detection
- **PS ID:** SIH26178
- **PS Title:** A resilient, AI-powered environmental monitoring network that provides early detection, localized intelligence, and actionable alerts for floods, forest fires, pollution events, and other environmental hazards common in India, enabling authorities and communities to shift from reactive disaster response to proactive risk prevention.
- **Category:** Hardware
- **Theme:** Disaster Management

## 2. Problem Statement

India lacks a real-time, localized system to detect and alert authorities and communities about environmental hazards like floods, forest fires, and pollution before they escalate into disasters.

## 3. Proposed Solution

Smart ESP32-S3 telemetry nodes with on-device TinyML run zero-latency hazard detection on low-cost hardware, streaming filtered alerts to a real-time dashboard while staying resilient offline in remote, disaster-prone zones.

## 4. Key Features

- Multi-sensor edge data collection
- On-device TinyML anomaly detection
- Bandwidth-efficient critical alert filtering
- LoRaWAN long-range wireless transmission
- Solar-powered, rugged, offline-resilient deployment

## 5. Technology Stack

- Frontend: HTML, CSS, JavaScript
- Backend: Python, FastAPI
- Machine Learning: TensorFlow, NumPy
- Database: PostgreSQL
- Deployment: Docker / Cloud

## 6. Architecture

See [docs/architecture.md](docs/architecture.md).

```text
User
  |
  v
Frontend
  |
  v
Backend API
  |
  +----> Database
  |
  v
ML Model
  |
  v
Prediction
```

## 7. Repository Structure

```text
YOUR-SIH-PROJECT/
├── README.md
├── SUBMISSION_GUIDE.md
├── submission/
│   ├── PRESENTATION.md
│   └── DEMO.md
├── src/
│   └── main.py
├── docs/
│   └── architecture.md
├── assets/
│   └── screenshots/
│       └── README.md
├── requirements.txt
├── .gitignore
└── LICENSE
```

### What goes where?

| Item | Location |
|---|---|
| Source code | `src/` or your normal project folders |
| Architecture / technical documentation | `docs/` |
| Project screenshots / hardware photos | `assets/screenshots/` |
| Final PPT / presentation | `submission/` |
| Demo video link | `submission/DEMO.md` |
| Project overview | `README.md` |

## 8. Final Presentation

Keep your final SIH presentation in the repository whenever the file size allows it.

See [submission/PRESENTATION.md](submission/PRESENTATION.md) for the required format.

If the PPT is too large for GitHub, use Google Drive/OneDrive and put the accessible viewer link in `submission/PRESENTATION.md`.

## 9. Demo Video

A demo video is **optional**, but recommended.

Add the YouTube/Google Drive link in [submission/DEMO.md](submission/DEMO.md).

## 10. Screenshots / Prototype Photos

Add important screenshots or hardware/prototype photos to:

`assets/screenshots/`

See [assets/screenshots/README.md](assets/screenshots/README.md) for examples and naming conventions.

## 11. Installation

```bash
git clone <YOUR_REPOSITORY_URL>
cd <YOUR_PROJECT_FOLDER>
pip install -r requirements.txt
```

## 12. Run

```bash
uvicorn src.main:app --reload
```

Replace these commands with the actual setup and run instructions for your project.


## 13. Future Scope

Describe realistic improvements or extensions that can be made to the project.

## Important

Before submission, make sure the repository is accessible to reviewers. Do **not** upload passwords, API keys, access tokens, `.env` files containing secrets, or other confidential credentials.
