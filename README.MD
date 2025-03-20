# 📅 Job Scheduler Project

## 🔎 Overview
An efficient C++ project simulating job scheduling with various policies like Smallest Job First and Best Fit. This project demonstrates job loading from files, scheduling algorithms, and result storage for analysis.

## 🌟 Key Features
- Load jobs dynamically from text files
- Apply multiple scheduling policies
- Save output results into CSV format
- Modular and easily extendable design

## 📊 Results Highlight
- Job distribution analysis
- Policy-wise job scheduling performance
- Easy CSV output for visual analysis

## ⚙ Technical Implementation
### Core Components
- File I/O for job loading
- Scheduling algorithms: SmallestJobFirst, BestFit
- CSV output handling
- Clean, efficient C++ structure

### Technology Stack
- Language: C++
- Data Format: CSV and TXT

## 🚀 Performance
- Handles large job corpuses quickly
- Policy simulations with reliable output

## 📁 Directory Structure Diagram
```plaintext
JobSchedulerProject/
│
├── main.cpp
├── JobArrival.txt
├── Results.csv
└── README.md
```

## 🧩 Code Snippets
### Example Job Loading:
```cpp
scheduler.loadJobs("JobArrival.txt");
```
### Example Scheduling Simulation:
```cpp
scheduler.simulateScheduling("SmallestJobFirst", "BestFit");
```
### Saving Output:
```cpp
scheduler.saveResultsToCSV("Results.csv");
```

## 🏁 Getting Started
1. Clone the repository
2. Add job data in `JobArrival.txt`
3. Compile the C++ code
4. Run the executable

## 📤 Output Files
- `Results.csv`: Stores scheduled job outputs

## 🔭 Future Scope
- Add priority-based policies
- UI-based job scheduling simulation

## 📚 Acknowledgments
Special thanks to:
- The professors and guides
- My academic mentors and peers

### ___________________________________________________
### Created with ❤️ By a passionate Programmer
### RAUNAK KUMAR JHA 

