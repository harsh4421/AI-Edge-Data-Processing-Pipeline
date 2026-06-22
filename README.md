# AI Edge Data Processing Pipeline

## B.Tech Semester II — Data Structures & Algorithms Final Project


**Author:** Harsh Kumar

---

# Table of Contents

1. Project Title
2. Problem Statement
3. Objectives
4. System Overview / Architecture
5. Data Structures and Algorithms Used
6. Implementation Approach
7. Time and Space Complexity Analysis
8. Execution Steps
9. Sample Inputs and Outputs
10. Screenshots
11. Results and Observations
12. Conclusion
13. Future Scope
14. Author

---

# 1. Project Title

## AI Edge Data Processing Pipeline

A console-based C++ application that simulates an IoT Edge Computing Data Processing System. The project demonstrates how sensor data can be ingested, cleaned, filtered, analyzed, and searched efficiently using fundamental Data Structures and Algorithms.

The system uses multiple sorting and searching algorithms to process sensor readings and detect anomalies before the data is sent to higher-level AI systems.

---

# 2. Problem Statement

Modern IoT devices continuously generate large volumes of sensor data. Raw sensor readings often contain:

- Noisy measurements
- Invalid values
- Outliers
- Unordered timestamps
- Anomalous readings

Processing such data directly can reduce the accuracy of AI and Machine Learning models.

Without an efficient preprocessing pipeline:

- Sensor data becomes unreliable.
- Outliers affect decision making.
- Data retrieval becomes slower.
- Real-time analytics become difficult.

This project solves these challenges by implementing a complete Edge Data Processing Pipeline using core Data Structures and Algorithms concepts.

---

# 3. Objectives

- Store and manage IoT sensor readings efficiently.
- Maintain timestamp ordering using Insertion Sort.
- Remove noisy data using Bubble Sort.
- Perform feature selection using Selection Sort.
- Enable fast timestamp lookup using Binary Search.
- Detect anomalous readings using Linear Search.
- Demonstrate practical applications of DSA in IoT and AI systems.
- Simulate an edge-computing preprocessing workflow.

---

# 4. System Overview / Architecture

```text
                  Sensor Data Input
                          │
                          ▼
               Data Ingestion Module
                  (Insertion Sort)
                          │
                          ▼
                Noise Filtering Module
                    (Bubble Sort)
                          │
                          ▼
               Feature Selection Module
                  (Selection Sort)
                          │
                          ▼
               Timestamp Lookup Module
                   (Binary Search)
                          │
                          ▼
              Anomaly Detection Module
                   (Linear Search)
                          │
                          ▼
                  Processed Output
```

## Data Flow

```text
User Input
     │
     ▼
Sensor Reading
     │
     ▼
Insertion Sort
     │
     ▼
Bubble Sort
     │
     ▼
Selection Sort
     │
     ▼
Binary Search
     │
     ▼
Linear Search
     │
     ▼
Console Output
```

---

# 5. Data Structures and Algorithms Used

## Data Structures

| Structure | Purpose |
|------------|------------|
| Struct | Represents sensor readings |
| Array | Stores sensor data buffer |
| Temporary Array | Used during filtering |

### Sensor Reading Structure

```cpp
struct SensorReading {
    int timestamp;
    float value;
};
```

---

## Algorithms

| Algorithm | Function | Purpose |
|------------|------------|------------|
| Insertion Sort | insertReading() | Maintain timestamp order |
| Bubble Sort | noiseFilter() | Sort values and remove noise |
| Selection Sort | featureSelection() | Select top sensor features |
| Binary Search | binarySearch() | Fast timestamp lookup |
| Linear Search | anomalyDetection() | Detect abnormal values |

---

# 6. Implementation Approach

## Layer 1 – Data Storage

Sensor readings are stored in a fixed-size array.

```cpp
const int MAX = 100;
SensorReading buffer[MAX];
```

The buffer can hold up to 100 sensor readings.

---

## Layer 2 – Sensor Data Ingestion

### Function

```cpp
insertReading()
```

### Algorithm Used

**Insertion Sort**

When a new reading arrives:

1. Create a new SensorReading object.
2. Compare timestamps.
3. Shift larger timestamps to the right.
4. Insert the reading at the correct position.

### Benefit

Maintains chronological ordering without requiring a complete re-sort.

---

## Layer 3 – Noise Filtering

### Function

```cpp
noiseFilter()
```

### Algorithm Used

**Bubble Sort**

The sensor values are sorted in ascending order.

After sorting, values outside the acceptable range are removed.

```cpp
const float ANOMALY_LOW = 10.0;
const float ANOMALY_HIGH = 90.0;
```

### Example

Removed Values:

```text
2.5
102.5
```

These values are considered noise or outliers.

---

## Layer 4 – Feature Selection

### Function

```cpp
featureSelection()
```

### Algorithm Used

**Selection Sort**

The readings are sorted by value.

The system then selects the Top N highest-value sensor readings.

### Purpose

Simulates feature selection used in AI and Machine Learning systems.

---

## Layer 5 – Timestamp Lookup

### Function

```cpp
binarySearch()
```

### Algorithm Used

**Binary Search**

Steps:

1. Sort readings by timestamp.
2. Divide the search space into halves.
3. Continue until the timestamp is found.

### Benefit

Provides efficient searching with O(log n) complexity.

---

## Layer 6 – Anomaly Detection

### Function

```cpp
anomalyDetection()
```

### Algorithm Used

**Linear Search**

Each sensor reading is scanned.

If:

```cpp
value < ANOMALY_LOW
```

or

```cpp
value > ANOMALY_HIGH
```

An alert is generated.

### Example

```text
ALERT!
Timestamp: 3
Value: 2.5
```

---

## Layer 7 – User Interface

A menu-driven interface allows users to interact with the pipeline.

```text
1. Add Sensor Reading
2. Filter Noise
3. Select Features
4. Lookup by Timestamp
5. Detect Anomalies
6. Display Current Buffer
7. Load Sample Data
0. Exit
```

---

# 7. Time and Space Complexity Analysis

## Time Complexity

| Operation | Algorithm | Complexity |
|------------|------------|------------|
| Insert Reading | Insertion Sort | O(n) |
| Noise Filtering | Bubble Sort | O(n²) |
| Feature Selection | Selection Sort | O(n²) |
| Binary Search | Binary Search | O(log n) |
| Anomaly Detection | Linear Search | O(n) |
| Display Buffer | Traversal | O(n) |

---

## Space Complexity

| Component | Complexity |
|------------|------------|
| Sensor Buffer | O(n) |
| Cleaned Array | O(n) |
| Search Variables | O(1) |

### Total Space Complexity

```text
O(n)
```

where n = number of sensor readings.

---

# 8. Execution Steps

## Prerequisites

- C++ Compiler (GCC/G++)
- C++11 or later
- Terminal / Command Prompt

---

## Step 1 – Save the Code

Save the source file as:

```text
main.cpp
```

---

## Step 2 – Compile

### Linux / macOS

```bash
g++ main.cpp -o pipeline
```

### Windows

```bash
g++ main.cpp -o pipeline.exe
```

---

## Step 3 – Run

### Linux / macOS

```bash
./pipeline
```

### Windows

```bash
pipeline.exe
```

---

# 9. Sample Inputs and Outputs

## Load Sample Data

### Input

```text
7
```

### Output

```text
Sample data loaded successfully!
```

---

## Display Buffer

### Output

```text
Timestamp    Value
------------------
1            40.0
2            38.7
3            2.5
4            41.8
5            45.3
6            52.1
7            55.0
8            102.5
9            48.9
10           50.3
```

---

## Noise Filtering

### Input

```text
2
```

### Output

```text
Removed outlier: Value = 2.5
Removed outlier: Value = 102.5
```

```text
Noise filtering complete.
8 readings remain.
```

---

## Feature Selection

### Input

```text
3
Top N = 3
```

### Output

```text
Timestamp    Value
------------------
6            52.1
7            55.0
10           50.3
```

---

## Binary Search

### Input

```text
Timestamp = 6
```

### Output

```text
Found!
Timestamp: 6
Value: 52.1
```

---

## Anomaly Detection

### Output

```text
ALERT!
Timestamp: 3
Value: 2.5
```

```text
ALERT!
Timestamp: 8
Value: 102.5
```

---

# 10. Screenshots


<img width="527" height="312" alt="Screenshot 2026-06-22 at 10 52 38 AM" src="https://github.com/user-attachments/assets/cc47871b-e996-4600-a90b-7f4f3bc37d42" />

<img width="610" height="651" alt="Screenshot 2026-06-22 at 10 53 10 AM" src="https://github.com/user-attachments/assets/0f448a05-f0e7-472f-aa7e-64c852547ac2" />

<img width="506" height="389" alt="Screenshot 2026-06-22 at 10 53 35 AM" src="https://github.com/user-attachments/assets/27703a00-2348-4548-aeb1-bd8104ac1624" />

<img width="600" height="202" alt="Screenshot 2026-06-22 at 10 54 01 AM" src="https://github.com/user-attachments/assets/200966c0-72e6-4455-ab23-cad331b2b57f" />

<img width="365" height="266" alt="Screenshot 2026-06-22 at 10 54 22 AM" src="https://github.com/user-attachments/assets/dcd53f8c-c703-46a6-a881-197f4c0c3df9" />





# 11. Results and Observations

| Observation | Result |
|------------|------------|
| Timestamp ordering maintained | Successful |
| Noise filtering removes outliers | Successful |
| Feature selection identifies important readings | Successful |
| Binary Search retrieves timestamps efficiently | Successful |
| Linear Search detects anomalies correctly | Successful |
| Complete edge processing workflow simulated | Successful |

---

# 12. Conclusion

The AI Edge Data Processing Pipeline successfully demonstrates how fundamental Data Structures and Algorithms can be applied to real-world IoT and Edge Computing systems.

The project integrates:

- Insertion Sort
- Bubble Sort
- Selection Sort
- Binary Search
- Linear Search

into a complete sensor data processing workflow.

The system improves data quality, supports anomaly detection, and enables efficient retrieval of sensor information, making it a valuable educational example of DSA applications in AI and IoT.

---

# 13. Future Scope

- Real-time sensor integration
- CSV data import/export
- Database connectivity
- Cloud synchronization
- Machine Learning-based anomaly detection
- Data visualization dashboard
- Multi-sensor support
- Edge AI deployment
- Predictive analytics

---

# 14. Author

**Harsh Kumar**

B.Tech Computer Science & Engineering  
ITM Skills University, Kharghar  
Semester II – Data Structures & Algorithms

### Technologies Used

- C++
- Data Structures & Algorithms
- IoT Concepts
- Edge Computing
- Console-Based Application

---
