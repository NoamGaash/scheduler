#include <gtest/gtest.h>
#include "../src/utils/model/Job.cpp"

TEST(JobTest, constractor) {
    Job j(1, 2, 3);
    EXPECT_EQ(j.id, 1);
    EXPECT_EQ(j.processing_time, 2);
    EXPECT_EQ(j.due_to, 3);
}

TEST(JobTest, cost) {
    Job j(1, 2, 3);
    auto const & testCases = std::vector<std::pair<int, int>>{
        {0, 2},
        {1, 2},
        {2, 1},
        {3, 0},
        {4, 0}
    };
    for(auto const & [start, expected] : testCases) {
        EXPECT_EQ(j.cost(start), expected) << "expected " << expected << ", got " << j.cost(start) << " for start=" << start << " and job=" << j;
    }
}

TEST(JobTest, display) {
    Job j(1, 2, 3);
    testing::internal::CaptureStdout();
    j.display();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(id=1 p=2, d=3)");
}