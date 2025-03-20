#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <climits> // Add this for INT_MAX

struct Job {
    int JobId;
    int ArrivalDay;
    int ArrivalHour;
    int MemReq;
    int CPUReq;
    int ExeTime;

    Job(int id, int day, int hour, int mem, int cpu, int exe)
        : JobId(id), ArrivalDay(day), ArrivalHour(hour), MemReq(mem), CPUReq(cpu), ExeTime(exe) {}
};

struct WorkerNode {
    int AvailableCores = 24;
    int AvailableMemory = 64;

    bool allocateJob(const Job &job) {
        if (job.MemReq <= AvailableMemory && job.CPUReq <= AvailableCores) {
            AvailableMemory -= job.MemReq;
            AvailableCores -= job.CPUReq;
            return true;
        }
        return false;
    }

    void releaseResources(const Job &job) {
        AvailableMemory += job.MemReq;
        AvailableCores += job.CPUReq;
    }
};

class MasterScheduler {
private:
    std::vector<Job> jobs;
    std::vector<WorkerNode> workerNodes;

public:
    MasterScheduler(int numNodes) : workerNodes(numNodes) {}

    void loadJobs(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int id, day, hour, mem, cpu, exe;
            if (iss >> id >> day >> hour >> mem >> cpu >> exe) {
                jobs.emplace_back(id, day, hour, mem, cpu, exe);
            }
        }
        file.close();
    }

    void simulateScheduling(const std::string &queuePolicy, const std::string &allocationPolicy) {
        // Sort jobs based on queueing policy
        if (queuePolicy == "SmallestJobFirst") {
            std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) {
                return (a.ExeTime * a.CPUReq * a.MemReq) < (b.ExeTime * b.CPUReq * b.MemReq);
            });
        } else if (queuePolicy == "ShortestDurationFirst") {
            std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) {
                return a.ExeTime < b.ExeTime;
            });
        }

        // Simulate scheduling
        for (auto &job : jobs) {
            bool allocated = false;

            if (allocationPolicy == "FirstFit") {
                for (auto &node : workerNodes) {
                    if (node.allocateJob(job)) {
                        allocated = true;
                        break;
                    }
                }
            } else if (allocationPolicy == "BestFit") {
                auto bestNode = workerNodes.end();
                int minWasted = INT_MAX;

                for (auto it = workerNodes.begin(); it != workerNodes.end(); ++it) {
                    int wastedMemory = it->AvailableMemory - job.MemReq;
                    int wastedCores = it->AvailableCores - job.CPUReq;

                    if (wastedMemory >= 0 && wastedCores >= 0) {
                        int totalWasted = wastedMemory + wastedCores;
                        if (totalWasted < minWasted) {
                            minWasted = totalWasted;
                            bestNode = it;
                        }
                    }
                }

                if (bestNode != workerNodes.end()) {
                    bestNode->allocateJob(job);
                    allocated = true;
                }
            } else if (allocationPolicy == "WorstFit") {
                auto worstNode = workerNodes.end();
                int maxWasted = -1;

                for (auto it = workerNodes.begin(); it != workerNodes.end(); ++it) {
                    int wastedMemory = it->AvailableMemory - job.MemReq;
                    int wastedCores = it->AvailableCores - job.CPUReq;

                    if (wastedMemory >= 0 && wastedCores >= 0) {
                        int totalWasted = wastedMemory + wastedCores;
                        if (totalWasted > maxWasted) {
                            maxWasted = totalWasted;
                            worstNode = it;
                        }
                    }
                }

                if (worstNode != workerNodes.end()) {
                    worstNode->allocateJob(job);
                    allocated = true;
                }
            }

            if (!allocated) {
                std::cerr << "Job " << job.JobId << " could not be allocated.\n";
            }
        }
    }

    void saveResultsToCSV(const std::string &filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        file << "| Worker Node | Available Cores | Available Memory |\n";
        file << "|-------------|-----------------|------------------|\n";

        for (size_t i = 0; i < workerNodes.size(); ++i) {
            file << "| Worker Node " << (i + 1) << " | "
                 << std::setw(15) << workerNodes[i].AvailableCores << " | "
                 << std::setw(16) << workerNodes[i].AvailableMemory << " |\n";
        }

        file.close();
    }
};

int main() {
    MasterScheduler scheduler(128); // 128 worker nodes

    scheduler.loadJobs("JobArrival.txt"); // Load jobs from file

    scheduler.simulateScheduling("SmallestJobFirst", "BestFit"); // Apply policies

    scheduler.saveResultsToCSV("Results.csv"); // Save results to CSV file

    return 0;
}
