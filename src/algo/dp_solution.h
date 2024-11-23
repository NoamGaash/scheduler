#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include "../utils/model/JobCollection.h"
#include "../utils/model/RejectableJobCollection.h"

// Forward declaration of dp_solution with consistent signatures
int dp_solution(JobCollection &data, bool verbose = false, std::function<void(int **, std::vector<Job>, int)> backtrack = nullptr);
int dp_solution(RejectableJobCollection &data, bool verbose = false);
