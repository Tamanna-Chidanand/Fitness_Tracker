#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Using tables 
// Made some changes
#define TABLE_SIZE 100

// Health Metrics structure
struct HealthMetrics {
    int heartRate;
    int bloodPressure;
};

// Queue structure for Health Metrics
struct Queue {
    struct HealthMetrics* metricsArray;
    int front, rear, itemCount, maxSize;
};

// Function to calculate the hash value for a key
int calculateHash(char key[50]) {
    int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

// Function to initialize the Health Metrics Queue
struct Queue* initializeQueue(int maxSize) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = 0;
    queue->rear = -1;
    queue->itemCount = 0;
    queue->maxSize = maxSize;
    queue->metricsArray = (struct HealthMetrics*)malloc(maxSize * sizeof(struct HealthMetrics));
    return queue;
}

// Function to check if the queue is full
int isFull(struct Queue* queue) {
    return queue->itemCount == queue->maxSize;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->itemCount == 0;
}

// Function to enqueue Health Metrics
void enqueue(struct Queue* queue, struct HealthMetrics metrics) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue more elements.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->maxSize;
    queue->metricsArray[queue->rear] = metrics;
    queue->itemCount++;
}

// Function to dequeue Health Metrics
struct HealthMetrics dequeue(struct Queue* queue) {
    struct HealthMetrics emptyMetrics = {-1, -1}; // Default empty metrics

    if (isEmpty(queue)) {
        printf("Queue is empty. No elements to dequeue.\n");
        return emptyMetrics;
    }
    struct HealthMetrics dequeuedMetrics = queue->metricsArray[queue->front];
    queue->front = (queue->front + 1) % queue->maxSize;
    queue->itemCount--;
    return dequeuedMetrics;
}

// Function to print Health Metrics in the queue
void printHealthMetrics(struct Queue* queue) {
    printf("Health Metrics in Queue:\n");
    int i = queue->front;
    int itemsPrinted = 0;
    while (itemsPrinted < queue->itemCount) {
        printf("Heart Rate: %d, Blood Pressure: %d\n", queue->metricsArray[i].heartRate, queue->metricsArray[i].bloodPressure);
        i = (i + 1) % queue->maxSize;
        itemsPrinted++;
    }
}

// Nutrition Log structure
struct NutritionLog {
    int calories;
    float protein;
    float carbs;
    float fat;
};

// Node structure for the hash table
struct Node {
    char key[50];
    struct NutritionLog data;
    struct Node* next;
};

// Hash Table structure
struct HashTable {
    struct Node* table[TABLE_SIZE];
};

// Function to insert data into the Nutrition Log hash table
void insertData(struct HashTable* hashTable, char key[50], struct NutritionLog data) {
    int index = calculateHash(key);
    struct Node* newNode = malloc(sizeof(struct Node));
    if (newNode) {
        strcpy(newNode->key, key);
        newNode->data = data;
        newNode->next = hashTable->table[index];
        hashTable->table[index] = newNode;
    }
}

// Function to retrieve data from the Nutrition Log hash table
struct NutritionLog retrieveData(struct HashTable* hashTable, char key[50]) {
    int index = calculateHash(key);
    struct Node* current = hashTable->table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->data;
        }
        current = current->next;
    }

    // Return an empty Nutrition Log if the key is not found
    struct NutritionLog emptyLog = {0, 0.0, 0.0, 0.0};
    return emptyLog;
}

// Function to calculate total nutrition values
void calculateTotals(struct HashTable* hashTable, int* totalCalories, float* totalProtein, float* totalCarbs, float* totalFat) {
    *totalCalories = 0;
    *totalProtein = 0.0;
    *totalCarbs = 0.0;
    *totalFat = 0.0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node* current = hashTable->table[i];
        while (current != NULL) {
            *totalCalories += current->data.calories;
            *totalProtein += current->data.protein;
            *totalCarbs += current->data.carbs;
            *totalFat += current->data.fat;
            current = current->next;
        }
    }
}

// Function to free memory allocated for the hash table
void freeHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node* current = hashTable->table[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Workout Log structure
struct Workout {
    char exercise[50];
    int duration;
    int aimDuration;
    struct Workout* next;
};

// Function to create a Workout entry
struct Workout* createWorkout(char exercise[], int duration, int aimDuration) {
    struct Workout* newWorkout = (struct Workout*)malloc(sizeof(struct Workout));
    if (newWorkout != NULL) {
        strcpy(newWorkout->exercise, exercise);
        newWorkout->duration = duration;
        newWorkout->aimDuration = aimDuration;
        newWorkout->next = NULL;
    }
    return newWorkout;
}

// Function to add a Workout entry to the Workout Log
void addWorkout(struct Workout** head, char exercise[], int duration, int aimDuration) {
    struct Workout* newWorkout = createWorkout(exercise, duration, aimDuration);
    if (*head == NULL) {
        *head = newWorkout;
        return;
    }
    struct Workout* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newWorkout;
}

// Function to display Workout Log
void displayWorkouts(struct Workout* head) {
    if (head == NULL) {
        printf("No workouts logged yet!\n");
        return;
    }
    printf("Workout Log:\n");
    while (head != NULL) {
        printf("Exercise: %s, Duration: %d minutes", head->exercise, head->duration);
        if (head->duration >= head->aimDuration) {
            printf(" - Aim Reached!\n");
        } else {
            printf(" - Aim Failed!\n");
        }
        head = head->next;
    }
}

// Function to free memory allocated for Workout Log
void freeWorkouts(struct Workout** head) {
    struct Workout* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    int maxSize;
    printf("Enter the maximum size of the queue: ");
    scanf("%d", &maxSize);

    // Health Metrics Queue
    struct Queue* healthMetricQueue = initializeQueue(maxSize);

    printf("Enter health metrics (heart rate and blood pressure) for each entry:\n");
    for (int i = 0; i < maxSize; i++) {
        struct HealthMetrics metrics;
        printf("Entry %d - Heart Rate: ", i + 1);
        scanf("%d", &metrics.heartRate);
        printf("Entry %d - Blood Pressure: ", i + 1);
        scanf("%d", &metrics.bloodPressure);
        enqueue(healthMetricQueue, metrics);
    }

    printHealthMetrics(healthMetricQueue);

    // Free allocated memory for Health Metrics Queue
    free(healthMetricQueue->metricsArray);
    free(healthMetricQueue);

    // Nutrition Log Hash Table
    struct HashTable nutritionTable;

    for (int i = 0; i < TABLE_SIZE; i++) {
        nutritionTable.table[i] = NULL;
    }

    char choice;
    do {
        char foodName[50];
        struct NutritionLog nutritionData;

        printf("Enter food name: ");
        scanf("%s", foodName);

        printf("Enter calories: ");
        scanf("%d", &nutritionData.calories);

        printf("Enter protein (in grams): ");
        scanf("%f", &nutritionData.protein);

        printf("Enter carbs (in grams): ");
        scanf("%f", &nutritionData.carbs);

        printf("Enter fat (in grams): ");
        scanf("%f", &nutritionData.fat);

        // Insert user input into the hash table
        insertData(&nutritionTable, foodName, nutritionData);

        printf("Do you want to enter more data? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    // Calculate total nutrition data
    int totalCalories;
    float totalProtein, totalCarbs, totalFat;
    calculateTotals(&nutritionTable, &totalCalories, &totalProtein, &totalCarbs, &totalFat);

    // Display total nutrition values
    printf("\nTotal Nutrition Data:\n");
    printf("Total Calories: %d\nTotal Protein: %.2f g\nTotal Carbs: %.2f g\nTotal Fat: %.2f g\n",
           totalCalories, totalProtein, totalCarbs, totalFat);

    // Check aim and display result
    int aimCalories;
    float aimProtein, aimCarbs, aimFat;
    printf("\nEnter your aims:\n");
    printf("Aim for Calories: ");
    scanf("%d", &aimCalories);
    printf("Aim for Protein (in grams): ");
    scanf("%f", &aimProtein);
    printf("Aim for Carbs (in grams): ");
    scanf("%f", &aimCarbs);
    printf("Aim for Fat (in grams): ");
    scanf("%f", &aimFat);

    if (totalCalories > aimCalories || totalProtein > aimProtein || totalCarbs > aimCarbs || totalFat > aimFat) {
        printf("\nAim Failed! Total values exceeded aim.\n");
    } else {
        printf("\nAim Successful! Total values are within aim.\n");
    }

    // Free allocated memory for the hash table
    freeHashTable(&nutritionTable);

    // Workout Log
    struct Workout* workoutLog = NULL;
    char exercise[50];
    int duration;
    int aimDuration;  // Added aimDuration for Workout Log
    char workoutChoice;

    do {
        printf("Enter the exercise: ");
        scanf("%s", exercise);

        printf("Enter the duration (in minutes): ");
        scanf("%d", &duration);

        printf("Enter the aim duration (in minutes): ");
        scanf("%d", &aimDuration);

        addWorkout(&workoutLog, exercise, duration, aimDuration);

        printf("Do you want to add another workout? (y/n): ");
        scanf(" %c", &workoutChoice);
    } while (workoutChoice == 'y' || workoutChoice == 'Y');

    displayWorkouts(workoutLog);

    // Free allocated memory for the Workout Log
    freeWorkouts(&workoutLog);

    return 0;
}