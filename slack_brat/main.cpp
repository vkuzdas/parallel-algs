#include <iostream>
#include <vector>
#include "limits.h"

using namespace std;

vector<int> duration; //
vector<int> release; //
vector<int> deadline; //
vector<int> slack;

vector<int> upperBound = {-1,0,1};
int cnt;
vector<int> best;


bool bratley_branchAndBound(const vector<int>& scheduled, vector<int> unscheduled, int currentScheduleTime);


void load(char *input_path) {
    FILE *file = fopen(input_path, "r");
    if (file == nullptr) {
        cout << "Input file not found\n";
        return;
    }

    // First line contains n
    int n = 0; // Number of tasks
    fscanf(file, "%i", &n);

    // Next n lines contain duration, release, and deadline
    for (int i = 0; i < n; ++i) {
        int p, r, d;
        fscanf(file, "%i %i %i", &p, &r, &d);
        cnt++;
        duration.emplace_back(p);
        deadline.emplace_back(d);
        release.emplace_back(r);
        slack.emplace_back(d-p);
    }
    fclose(file);
}

#include <limits>
#include <algorithm>

int findMin(const vector<int>& nums, int endIndex) {
    if (endIndex >= nums.size())
        throw runtime_error("Invalid endIndex");

    int minValue = numeric_limits<int>::max();
    for (int i = 0; i <= endIndex; i++) {
        if (nums[i] < minValue)
            minValue = nums[i];
    }
    return minValue;
}

int findMax(const vector<int>& nums, int endIndex) {
    if (endIndex >= nums.size())
        throw runtime_error("Invalid endIndex");

    int maxValue = numeric_limits<int>::min();
    for (int i = 0; i <= endIndex; i++) {
        if (nums[i] > maxValue)
            maxValue = nums[i];
    }
    return maxValue;
}

int findMinIndexed(const std::vector<int>& arr, const std::vector<int>& indices) {
    int minVal = std::numeric_limits<int>::max();

    for (int index : indices) {
        if (arr[index] < minVal) {
            minVal = arr[index];
        }
    }

    return minVal;
}


int findMaxIndexed(const std::vector<int>& arr, const std::vector<int>& indices) {
    int maxVal = std::numeric_limits<int>::min();

    for (int index : indices) {
        if (arr[index] > maxVal) {
            maxVal = arr[index];
        }
    }

    return maxVal;
}

int main(int argc, char** argv) {
    if (argc < 3)
        cout << "Need 2 arguments: ./program <input path> <output path>\n";

    load(argv[1]);

    vector<pair<int,int>> tasks;
    for (int i = 0; i < slack.size(); ++i) {
        tasks.emplace_back(i, slack[i]);
    }

    sort(tasks.begin(), tasks.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    vector<int> scheduled(0);
    vector<int> unscheduled;
    for (int i = 0; i < cnt; ++i) {
        unscheduled.emplace_back(tasks[i].first);
    }
    bratley_branchAndBound(scheduled, unscheduled, 0);

    vector<int> output(cnt, 0);

    if (!best.empty()) {
        int currentScheduleTime = 0;
        for (int i : best) {
            auto scheduledTime = max(currentScheduleTime, release[i]);
            output[i] = scheduledTime;
            currentScheduleTime = scheduledTime + duration[i];
        }
    } else {
        cout << "No solution found\n";
        output = {-1};
    }

    FILE *file = fopen(argv[2], "w+");

    if (file == nullptr) {
        cout << "Could not create file\n";
        return -1;
    }

    for (auto e : output) {
        fprintf(file, "%i\n", e);
    }

    return 0;
}

bool bratley_branchAndBound(const vector<int>& scheduled, vector<int> unscheduled, int currentScheduleTime) {
    // Missed deadline: Check if unassigned tasks would miss their deadlines when assigned
    // to the current schedule. If that is the case, prune this node.
    for (int j : unscheduled) {
        auto maxTime = max(currentScheduleTime, release[j]);
        if (maxTime + duration[j] > deadline[j]) {
            return false;
        }
    }

//    We can calculate lover bound (LB) of the current
//    solution and prune this node if LB ≥ UB.
    if (unscheduled.empty()) {
        if (upperBound[0] == -1 || currentScheduleTime < upperBound[0]) {
            upperBound[0] = currentScheduleTime;
            best = scheduled;
            return false;
        }
    }
    else {
        int minRelease = INT_MAX;
        int sumDuration = 0;
        for (int j : unscheduled) {
            minRelease = min(minRelease, release[j]);
            sumDuration += duration[j];
        }
        int lowerBound = max(currentScheduleTime, minRelease) + sumDuration;
        if (upperBound[0] == -1) {
            int upperBound = findMaxIndexed(deadline, unscheduled);
            if (lowerBound > upperBound) {
                return false;
            }
        } else {
            if (lowerBound >= upperBound[0]) {
                return false;
            }
        }
    }

    bool has_solution = false;

    if (currentScheduleTime <= findMinIndexed(release, unscheduled)) {
        best.insert(best.end(), unscheduled.begin(), unscheduled.end());
        has_solution = true;
    }

    for (int i = 0; i < unscheduled.size(); ++i) {
        vector<int> scheduledCopy = scheduled;
        vector<int> unscheduledCopy = unscheduled;
        scheduledCopy.emplace_back(unscheduled[i]);
        unscheduledCopy.erase(unscheduledCopy.begin() + i);
        int nextScheduleTime = max(currentScheduleTime, release[unscheduled[i]]) + duration[unscheduled[i]];
        bool isFeasible = bratley_branchAndBound(scheduledCopy, unscheduledCopy, nextScheduleTime);
        if (isFeasible) {
            return true;
        }
    }

    return has_solution;
}
