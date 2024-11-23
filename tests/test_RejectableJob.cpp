#include <gtest/gtest.h>
#include "../src/utils/model/RejectableJob.cpp"

TEST(RejectableJobTest, constructor) {
    RejectableJob rj(1, 2, 3, 4);
    EXPECT_EQ(rj.id, 1);
    EXPECT_EQ(rj.processing_time, 2);
    EXPECT_EQ(rj.due_to, 3);
    EXPECT_EQ(rj.rejection_cost, 4);
}

TEST(RejectableJobTest, costOfJobWithFreeRegection) {
    RejectableJob rj(1, 2, 3, 0);
    auto const & testCases = std::vector<std::pair<int, int>>{
        // {start, expected}
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},
        {4, 0}
    };
    for(auto const & [start, expected] : testCases) {
        EXPECT_EQ(rj.cost(start), expected) << "expected " << expected << ", got " << rj.cost(start) << " for start=" << start << " and job=" << rj;
    }
}
TEST(RejectableJobTest, costOfJobWithExpensiveRegection) {
    RejectableJob rj(1, 2, 3, 999);
    auto const & testCases = std::vector<std::pair<int, int>>{
        // {start, expected}
        {0, 2},
        {1, 2},
        {2, 1},
        {3, 0},
        {4, 0}
    };
    for(auto const & [start, expected] : testCases) {
        EXPECT_EQ(rj.cost(start), expected) << "expected " << expected << ", got " << rj.cost(start) << " for start=" << start << " and job=" << rj;
    }
}
TEST(RejectableJobTest, costOfJobWithCheapRegection) {
    RejectableJob rj(1, 2, 3, 1);
    auto const & testCases = std::vector<std::pair<int, int>>{
        // {start, expected}
        {0, 1},
        {1, 1},
        {2, 1},
        {3, 0},
        {4, 0}
    };
    for(auto const & [start, expected] : testCases) {
        EXPECT_EQ(rj.cost(start), expected) << "expected " << expected << ", got " << rj.cost(start) << " for start=" << start << " and job=" << rj;
    }
}

TEST(RejectableJobTest, display) {
    RejectableJob rj(1, 2, 3, 4);
    testing::internal::CaptureStdout();
    rj.display();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(id=1 p=2, d=3, r=4)");
}