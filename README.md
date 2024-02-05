  Fitness Tracker Application
  Using data structures in C programming language
  This C program integrates three health-related logs: a queue for health metrics (heart rate and blood pressure), a hash table for nutrition tracking (calories, protein, carbs, fat), and a linked list for a workout log (exercise, duration, aim duration). Users input health metrics, nutrition data, and workout details. The program calculates and displays total nutrition values, checks if they meet user-set aims, and presents a workout log with achieved or failed aims. The code emphasizes modularity, using data structures to organize and manage health-related information.
Workout Logs Storage: Use a linked list or a tree structure to store workout logs. Each node can represent a workout session, including details like type of exercise, duration, intensity, and any notes. This structure allows for easy traversal and modification of workout data.

Nutrition Information Management: Utilize a hash table or dictionary to manage nutrition information. Keys could be dates or meal times, with values representing nutritional content such as calories, macronutrients, and specific food items consumed.

Health Metrics Storage: A priority queue or a heap could organize health metrics based on importance or urgency. This could include metrics like heart rate, blood pressure, or other vital stats, sorted by relevance or time sensitivity.

Queue:

Struct Name: struct Queue
Abstract Data Type: Represents a queue data structure for storing health metrics (heart rate and blood pressure). It includes operations such as enqueue, dequeue, and checks for full or empty conditions.
Hash Table:

Struct Name: struct HashTable
Abstract Data Type: Represents a hash table for storing nutrition log data (calories, protein, carbs, fat). It includes operations for inserting data, retrieving data, calculating totals, and freeing allocated memory.
Linked List:

Struct Name: struct Workout
Abstract Data Type: Represents a linked list for the workout log. It includes operations for creating a workout entry, adding entries to the log, displaying the log, and freeing allocated memory.
These abstract data types encapsulate specific functionalities and operations, providing a modular and organized structure to the program.
