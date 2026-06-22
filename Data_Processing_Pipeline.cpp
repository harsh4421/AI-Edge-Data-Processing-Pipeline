#include <iostream>
#include <string>

using namespace std;

const int MAX = 100;
const float ANOMALY_LOW = 10.0;
const float ANOMALY_HIGH = 90.0;

struct SensorReading {
    int timestamp;
    float value;
};

SensorReading buffer[MAX];
int bufferSize = 0;

void displayBuffer(string label) {
    cout << "\n--- " << label << " ---\n";
    cout << "Timestamp\tValue\n";
    cout << "-------------------\n";
    for (int i = 0; i < bufferSize; i++) {
        cout << buffer[i].timestamp << "\t\t" << buffer[i].value << "\n";
    }
    cout << "Total readings: " << bufferSize << "\n";
}

void insertReading(int timestamp, float value) {
    SensorReading newReading;
    newReading.timestamp = timestamp;
    newReading.value = value;

    int i = bufferSize - 1;

    while (i >= 0 && buffer[i].timestamp > newReading.timestamp) {
        buffer[i + 1] = buffer[i];
        i--;
    }

    buffer[i + 1] = newReading;
    bufferSize++;

    cout << "Ingested: Timestamp=" << timestamp << ", Value=" << value << "\n";
}

void noiseFilter() {
    cout << "\n[Noise Filtering - Bubble Sort]\n";

    for (int i = 0; i < bufferSize - 1; i++) {
        for (int j = 0; j < bufferSize - 1 - i; j++) {
            if (buffer[j].value > buffer[j + 1].value) {
                SensorReading temp = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = temp;
            }
        }
    }
    cout << "Values sorted for outlier detection.\n";

    SensorReading cleaned[MAX];
    int cleanedSize = 0;

    for (int i = 0; i < bufferSize; i++) {
        if (buffer[i].value >= ANOMALY_LOW && buffer[i].value <= ANOMALY_HIGH) {
            cleaned[cleanedSize++] = buffer[i];
        } else {
            cout << "Removed outlier: Value=" << buffer[i].value << "\n";
        }
    }

    for (int i = 0; i < cleanedSize; i++) {
        buffer[i] = cleaned[i];
    }
    bufferSize = cleanedSize;

    cout << "Noise filtering complete. " << bufferSize << " readings remain.\n";
}

void featureSelection(int topN) {
    cout << "\n[Feature Selection - Selection Sort]\n";

    for (int i = 0; i < bufferSize - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < bufferSize; j++) {
            if (buffer[j].value < buffer[minIndex].value) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            SensorReading temp = buffer[i];
            buffer[i] = buffer[minIndex];
            buffer[minIndex] = temp;
        }
    }

    cout << "Top " << topN << " features selected (highest sensor values):\n";
    cout << "Timestamp\tValue\n";
    cout << "-------------------\n";

    int start = bufferSize - topN;
    if (start < 0) start = 0;

    for (int i = start; i < bufferSize; i++) {
        cout << buffer[i].timestamp << "\t\t" << buffer[i].value << "\n";
    }
}

int binarySearch(int targetTimestamp) {
    for (int i = 1; i < bufferSize; i++) {
        SensorReading key = buffer[i];
        int j = i - 1;
        while (j >= 0 && buffer[j].timestamp > key.timestamp) {
            buffer[j + 1] = buffer[j];
            j--;
        }
        buffer[j + 1] = key;
    }

    int low = 0;
    int high = bufferSize - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (buffer[mid].timestamp == targetTimestamp) {
            return mid;
        } else if (buffer[mid].timestamp < targetTimestamp) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

void anomalyDetection() {
    cout << "\n[Anomaly Detection - Linear Search]\n";
    bool anomalyFound = false;

    for (int i = 0; i < bufferSize; i++) {
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

void loadSampleData() {
    cout << "\n[Loading Sample IoT Sensor Data...]\n";

    bufferSize = 0;

    insertReading(5, 45.3);
    insertReading(2, 38.7);
    insertReading(8, 102.5);
    insertReading(1, 40.0);
    insertReading(6, 52.1);
    insertReading(3, 2.5);
    insertReading(9, 48.9);
    insertReading(4, 41.8);
    insertReading(7, 55.0);
    insertReading(10, 50.3);

    cout << "\nSample data loaded successfully!\n";
}

int main() {
    int choice;
    int timestamp;
    float value;

    cout << "Welcome to the AI Edge Data Processing Pipeline!\n";
    cout << "Normal sensor range: " << ANOMALY_LOW << " to " << ANOMALY_HIGH << "\n";

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter timestamp (integer): ";
                cin >> timestamp;
                cout << "Enter sensor value (float): ";
                cin >> value;
                insertReading(timestamp, value);
                break;
            }

            case 2: {
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
                if (bufferSize == 0) {
                    cout << "Buffer is empty! Load data first.\n";
                } else {
                    anomalyDetection();
                }
                break;
            }

            case 6: {
                if (bufferSize == 0) {
                    cout << "Buffer is empty!\n";
                } else {
                    displayBuffer("Current Buffer");
                }
                break;
            }

            case 7: {
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

    } while (choice != 0);

    return 0;
}