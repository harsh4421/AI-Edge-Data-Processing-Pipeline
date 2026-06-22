/*
============================================================
   AI EDGE DATA PROCESSING PIPELINE
   Case Study 155 - DSA with C++
   B.Tech CSE 2025-29, Semester II
   ITM Skills University
============================================================
   Algorithms Used:
   1. Insertion Sort  --> Data Ingestion
   2. Bubble Sort     --> Noise Filtering
   3. Selection Sort  --> Feature Selection
   4. Binary Search   --> Data Lookup
   5. Linear Search   --> Anomaly Detection
============================================================
*/

#include <iostream>   // For input/output (cin, cout)
#include <string>     // For string data type

using namespace std;  // So we don't have to write std::cout every time

// ============================================================
// GLOBAL CONSTANTS
// ============================================================
const int MAX = 100;          // Maximum number of sensor readings we can store
const float ANOMALY_LOW = 10.0;  // Values below this are considered anomalies
const float ANOMALY_HIGH = 90.0; // Values above this are considered anomalies

// ============================================================
// STRUCTURE: SensorReading
// A structure groups related data together (like a record)
// Each sensor reading has a timestamp and a value
// ============================================================
struct SensorReading {
    int timestamp;   // When the reading was taken (e.g., 1, 2, 3, ... seconds)
    float value;     // The actual sensor measurement (e.g., temperature in Celsius)
};

// ============================================================
// GLOBAL ARRAY: acts as our local buffer (edge device memory)
// ============================================================
SensorReading buffer[MAX];  // Stores all sensor readings
int bufferSize = 0;         // Tracks how many readings are currently stored

// ============================================================
// UTILITY FUNCTION: displayBuffer
// Prints all sensor readings currently in the buffer
// ============================================================
void displayBuffer(string label) {
    cout << "\n--- " << label << " ---\n";
    cout << "Timestamp\tValue\n";
    cout << "-------------------\n";
    for (int i = 0; i < bufferSize; i++) {
        cout << buffer[i].timestamp << "\t\t" << buffer[i].value << "\n";
    }
    cout << "Total readings: " << bufferSize << "\n";
}

// ============================================================
// MODULE 1: DATA INGESTION USING INSERTION SORT
//
// How it works:
// - New sensor reading arrives
// - We find the correct position based on timestamp
// - We shift existing readings to make space
// - We insert the new reading in sorted position
//
// Why Insertion Sort?
// - Sensor data arrives nearly sorted by time
// - Insertion Sort is efficient for nearly-sorted data: O(n)
// - Simple to implement on low-power edge devices
// ============================================================
void insertReading(int timestamp, float value) {
    // Step 1: Create the new sensor reading
    SensorReading newReading;
    newReading.timestamp = timestamp;
    newReading.value = value;

    // Step 2: Start from the last element and move backwards
    int i = bufferSize - 1;

    // Step 3: Shift readings that have a LARGER timestamp to the right
    // This creates space for the new reading in the correct position
    while (i >= 0 && buffer[i].timestamp > newReading.timestamp) {
        buffer[i + 1] = buffer[i];  // Move reading one position to the right
        i--;                         // Move one step to the left
    }

    // Step 4: Place the new reading in the correct position
    buffer[i + 1] = newReading;
    bufferSize++;  // Increase the count of readings

    cout << "Ingested: Timestamp=" << timestamp << ", Value=" << value << "\n";
}

// ============================================================
// MODULE 2: NOISE FILTERING USING BUBBLE SORT
//
// How it works:
// - Bubble Sort arranges values in ascending order
// - After sorting, extreme values (outliers) appear at the ends
// - We remove readings with values outside [ANOMALY_LOW, ANOMALY_HIGH]
//
// Why Bubble Sort?
// - Works on small data windows (chunks of sensor data)
// - Simple to understand and implement
// - Good for small arrays on edge devices
// ============================================================
void noiseFilter() {
    cout << "\n[Noise Filtering - Bubble Sort]\n";

    // STEP 1: Sort buffer by VALUE using Bubble Sort
    // Bubble Sort compares adjacent elements and swaps if out of order
    for (int i = 0; i < bufferSize - 1; i++) {        // Outer loop: n-1 passes
        for (int j = 0; j < bufferSize - 1 - i; j++) { // Inner loop: shrinks each pass
            if (buffer[j].value > buffer[j + 1].value) {
                // Swap the two adjacent readings
                SensorReading temp = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = temp;
            }
        }
    }
    cout << "Values sorted for outlier detection.\n";

    // STEP 2: Remove outliers (values outside normal range)
    // We create a new temporary array with only clean data
    SensorReading cleaned[MAX];
    int cleanedSize = 0;

    for (int i = 0; i < bufferSize; i++) {
        if (buffer[i].value >= ANOMALY_LOW && buffer[i].value <= ANOMALY_HIGH) {
            cleaned[cleanedSize++] = buffer[i];  // Keep only valid readings
        } else {
            cout << "Removed outlier: Value=" << buffer[i].value << "\n";
        }
    }

    // STEP 3: Copy cleaned data back to the main buffer
    for (int i = 0; i < cleanedSize; i++) {
        buffer[i] = cleaned[i];
    }
    bufferSize = cleanedSize;

    cout << "Noise filtering complete. " << bufferSize << " readings remain.\n";
}

// ============================================================
// MODULE 3: FEATURE SELECTION USING SELECTION SORT
//
// How it works:
// - Selection Sort finds the MINIMUM value repeatedly
// - This sorts readings by value in ascending order
// - The top N readings (highest values) are selected as features
//   because high sensor values often carry the most information
//
// Why Selection Sort?
// - Makes exactly O(n^2) comparisons (predictable on edge devices)
// - Simple logic: find minimum, place it at front, repeat
// ============================================================
void featureSelection(int topN) {
    cout << "\n[Feature Selection - Selection Sort]\n";

    // Selection Sort: sort by value in ascending order
    for (int i = 0; i < bufferSize - 1; i++) {
        int minIndex = i;  // Assume current position is the minimum

        // Find the actual minimum in the remaining unsorted part
        for (int j = i + 1; j < bufferSize; j++) {
            if (buffer[j].value < buffer[minIndex].value) {
                minIndex = j;  // Update minimum index
            }
        }

        // Swap the found minimum with the current position
        if (minIndex != i) {
            SensorReading temp = buffer[i];
            buffer[i] = buffer[minIndex];
            buffer[minIndex] = temp;
        }
    }

    // Select the top N features (highest values are at the end after ascending sort)
    cout << "Top " << topN << " features selected (highest sensor values):\n";
    cout << "Timestamp\tValue\n";
    cout << "-------------------\n";

    int start = bufferSize - topN;  // Start index for top N values
    if (start < 0) start = 0;       // Safety check

    for (int i = start; i < bufferSize; i++) {
        cout << buffer[i].timestamp << "\t\t" << buffer[i].value << "\n";
    }
}

// ============================================================
// MODULE 4: DATA LOOKUP USING BINARY SEARCH
//
// How it works:
// - Buffer must be sorted by timestamp (maintained by Insertion Sort)
// - Binary Search divides the search range in half each step
// - Much faster than checking every element
//
// Why Binary Search?
// - Time complexity: O(log n) vs O(n) for Linear Search
// - Data is already sorted by Insertion Sort, so Binary Search applies
// - Fast retrieval is critical for real-time monitoring
//
// Returns: index of found reading, or -1 if not found
// ============================================================
int binarySearch(int targetTimestamp) {
    // First, re-sort buffer by timestamp (it may be sorted by value from feature selection)
    // Simple re-sort by timestamp using insertion sort logic
    for (int i = 1; i < bufferSize; i++) {
        SensorReading key = buffer[i];
        int j = i - 1;
        while (j >= 0 && buffer[j].timestamp > key.timestamp) {
            buffer[j + 1] = buffer[j];
            j--;
        }
        buffer[j + 1] = key;
    }

    // Binary Search
    int low = 0;                // Left boundary
    int high = bufferSize - 1; // Right boundary

    while (low <= high) {
        int mid = (low + high) / 2;  // Find the middle index

        if (buffer[mid].timestamp == targetTimestamp) {
            return mid;  // Found! Return the index
        } else if (buffer[mid].timestamp < targetTimestamp) {
            low = mid + 1;   // Target is in the RIGHT half
        } else {
            high = mid - 1;  // Target is in the LEFT half
        }
    }

    return -1;  // Not found
}

// ============================================================
// MODULE 5: ANOMALY DETECTION USING LINEAR SEARCH
//
// How it works:
// - Goes through EVERY sensor reading one by one
// - Checks if value falls outside the normal range
// - Reports any abnormal readings as anomalies
//
// Why Linear Search?
// - Data does NOT need to be sorted
// - Can check any condition (custom anomaly rules)
// - Flexible for detecting unusual patterns
// ============================================================
void anomalyDetection() {
    cout << "\n[Anomaly Detection - Linear Search]\n";
    bool anomalyFound = false;

    // Check each reading sequentially (one by one)
    for (int i = 0; i < bufferSize; i++) {
        // Define anomaly condition: value outside normal operating range
        if (buffer[i].value < ANOMALY_LOW || buffer[i].value > ANOMALY_HIGH) {
            cout << "ALERT! Anomaly detected -> Timestamp: "
                 << buffer[i].timestamp
                 << ", Value: " << buffer[i].value << "\n";
            anomalyFound = true;
        }
    }

    if (!anomalyFound) {
        cout << "No anomalies detected. All readings are within normal range.\n";
    }
}

// ============================================================
// MENU DISPLAY FUNCTION
// ============================================================
void displayMenu() {
    cout << "\n========================================\n";
    cout << "   AI EDGE DATA PROCESSING PIPELINE\n";
    cout << "========================================\n";
    cout << "1. Add Sensor Reading (Insertion Sort)\n";
    cout << "2. Filter Noise (Bubble Sort)\n";
    cout << "3. Select Features (Selection Sort)\n";
    cout << "4. Lookup by Timestamp (Binary Search)\n";
    cout << "5. Detect Anomalies (Linear Search)\n";
    cout << "6. Display Current Buffer\n";
    cout << "7. Load Sample Data\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Enter choice: ";
}

// ============================================================
// SAMPLE DATA LOADER
// Pre-loads realistic sensor readings for demonstration
// Includes some noisy/outlier values for testing
// ============================================================
void loadSampleData() {
    cout << "\n[Loading Sample IoT Sensor Data...]\n";

    // Reset buffer
    bufferSize = 0;

    // Insert readings out of order to demonstrate Insertion Sort
    insertReading(5, 45.3);   // Normal temperature reading
    insertReading(2, 38.7);   // Normal
    insertReading(8, 102.5);  // OUTLIER - too high (sensor noise)
    insertReading(1, 40.0);   // Normal
    insertReading(6, 52.1);   // Normal
    insertReading(3, 2.5);    // OUTLIER - too low (sensor noise)
    insertReading(9, 48.9);   // Normal
    insertReading(4, 41.8);   // Normal
    insertReading(7, 55.0);   // Normal
    insertReading(10, 50.3);  // Normal

    cout << "\nSample data loaded successfully!\n";
}

// ============================================================
// MAIN FUNCTION
// Entry point of the program
// Controls the menu and calls all pipeline modules
// ============================================================
int main() {
    int choice;      // Stores user's menu selection
    int timestamp;   // For reading input
    float value;     // For reading input

    cout << "Welcome to the AI Edge Data Processing Pipeline!\n";
    cout << "Normal sensor range: " << ANOMALY_LOW << " to " << ANOMALY_HIGH << "\n";

    // Main program loop - keeps running until user chooses to exit
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                // MODULE 1: Add a new sensor reading
                cout << "Enter timestamp (integer): ";
                cin >> timestamp;
                cout << "Enter sensor value (float): ";
                cin >> value;
                insertReading(timestamp, value);
                break;
            }

            case 2: {
                // MODULE 2: Apply noise filtering
                if (bufferSize == 0) {
                    cout << "Buffer is empty! Load data first.\n";
                } else {
                    displayBuffer("Before Noise Filtering");
                    noiseFilter();
                    displayBuffer("After Noise Filtering");
                }
                break;
            }

            case 3: {
                // MODULE 3: Feature selection
                if (bufferSize == 0) {
                    cout << "Buffer is empty! Load data first.\n";
                } else {
                    int topN;
                    cout << "How many top features to select? ";
                    cin >> topN;
                    featureSelection(topN);
                }
                break;
            }

            case 4: {
                // MODULE 4: Binary search lookup
                if (bufferSize == 0) {
                    cout << "Buffer is empty! Load data first.\n";
                } else {
                    cout << "Enter timestamp to search: ";
                    cin >> timestamp;
                    int result = binarySearch(timestamp);
                    if (result != -1) {
                        cout << "Found! -> Timestamp: " << buffer[result].timestamp
                             << ", Value: " << buffer[result].value << "\n";
                    } else {
                        cout << "Timestamp " << timestamp << " not found in buffer.\n";
                    }
                }
                break;
            }

            case 5: {
                // MODULE 5: Anomaly detection
                if (bufferSize == 0) {
                    cout << "Buffer is empty! Load data first.\n";
                } else {
                    anomalyDetection();
                }
                break;
            }

            case 6: {
                // Display current buffer
                if (bufferSize == 0) {
                    cout << "Buffer is empty!\n";
                } else {
                    displayBuffer("Current Buffer");
                }
                break;
            }

            case 7: {
                // Load sample data
                loadSampleData();
                displayBuffer("Buffer After Loading Sample Data");
                break;
            }

            case 0: {
                cout << "\nExiting pipeline. Goodbye!\n";
                break;
            }

            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }

    } while (choice != 0);  // Loop continues until user enters 0

    return 0;  // Program ends successfully
}