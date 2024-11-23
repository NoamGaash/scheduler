#include <gtest/gtest.h>
#include "../src/utils/model/JobCollection.cpp"

TEST(JobCollectionTest, ConstructorFromData) {
    std::vector<std::vector<int>> data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    JobCollection jc(data);

    ASSERT_EQ(jc.jobs.size(), 3);
    EXPECT_EQ(jc.jobs[0].id, 1);
    EXPECT_EQ(jc.jobs[0].processing_time, 2);
    EXPECT_EQ(jc.jobs[0].due_to, 3);
    EXPECT_EQ(jc.jobs[1].id, 4);
    EXPECT_EQ(jc.jobs[1].processing_time, 5);
    EXPECT_EQ(jc.jobs[1].due_to, 6);
    EXPECT_EQ(jc.jobs[2].id, 7);
    EXPECT_EQ(jc.jobs[2].processing_time, 8);
    EXPECT_EQ(jc.jobs[2].due_to, 9);
}

TEST(JobCollectionTest, ConstructorWithRandomJobs) {
    int njobs = 5;
    int p_max = 10;
    float alpha = 0.5;
    JobCollection jc(njobs, p_max, alpha);

    ASSERT_EQ(jc.jobs.size(), njobs);
    for (const auto &job : jc.jobs) {
        EXPECT_GT(job.processing_time, 0);
        EXPECT_LE(job.processing_time, p_max);
        EXPECT_GT(job.due_to, 0);
        EXPECT_LE(job.due_to, static_cast<int>(alpha * jc.P()));
    }
}

// we don't test RejectableJobCollection constructor right now

TEST(JobCollectionTest, TotalProcessingTime) {
    std::vector<std::vector<int>> data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    JobCollection jc(data);

    EXPECT_EQ(jc.P(), 15);
}

TEST(JobCollectionTest, SortByDescendingDueTo) {
    std::vector<std::vector<int>> data = {{1, 2, 10}, {4, 5, 6}, {7, 8, 11}};
    JobCollection jc(data);

    jc.sort_by_descending_due_to();

    EXPECT_EQ(jc.jobs[0].id, 7);
    EXPECT_EQ(jc.jobs[1].id, 1);
    EXPECT_EQ(jc.jobs[2].id, 4);
}

TEST(JobCollectionTest, SortByAscendingDueTo) {
    std::vector<std::vector<int>> data = {{1, 2, 10}, {4, 5, 6}, {7, 8, 11}};
    JobCollection jc(data);

    jc.sort_by_ascending_due_to();

    EXPECT_EQ(jc.jobs[0].id, 4);
    EXPECT_EQ(jc.jobs[1].id, 1);
    EXPECT_EQ(jc.jobs[2].id, 7);
}

TEST(JobCollectionTest, Display) {
    std::vector<std::vector<int>> data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    JobCollection jc(data);

    testing::internal::CaptureStdout();
    jc.display();
    std::string output = testing::internal::GetCapturedStdout();

    std::string expected_output = "Jobs: (id=1 p=2, d=3) (id=4 p=5, d=6) (id=7 p=8, d=9) ";
    EXPECT_EQ(output, expected_output);
}

TEST(JobCollectionTest, Cost) {
    std::vector<std::vector<int>> data = {{1, 2, 4}, {4, 5, 3}, {7, 8, 5}};
    JobCollection jc(data);

    EXPECT_EQ(jc.cost(jc.jobs), 3);
    jc.sort_by_descending_due_to();
    // the cost depends on the order of the jobs, because a job is early if it is processed before its due date
    EXPECT_EQ(jc.cost(jc.jobs), 5);
}

TEST(JobCollectionTest, OperatorOut) {
    std::vector<std::vector<int>> data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    JobCollection jc(data);

    testing::internal::CaptureStdout();
    std::cout << jc;
    std::string output = testing::internal::GetCapturedStdout();

    std::string expected_output = "Jobs: (id=1 p=2, d=3) (id=4 p=5, d=6) (id=7 p=8, d=9) ";
    EXPECT_EQ(output, expected_output);
}
