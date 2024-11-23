#include <gtest/gtest.h>
#include "../src/utils/model/RejectableJobCollection.h"

TEST(RejectableJobCollectionTest, ConstructorWithData) {
    std::vector<std::vector<int>> data = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };
    RejectableJobCollection collection(data);

    ASSERT_EQ(collection.jobs.size(), 2);
    EXPECT_EQ(collection.jobs[0].id, 1);
    EXPECT_EQ(collection.jobs[0].processing_time, 2);
    EXPECT_EQ(collection.jobs[0].due_to, 3);
    EXPECT_EQ(collection.jobs[0].rejection_cost, 4);

    EXPECT_EQ(collection.jobs[1].id, 5);
    EXPECT_EQ(collection.jobs[1].processing_time, 6);
    EXPECT_EQ(collection.jobs[1].due_to, 7);
    EXPECT_EQ(collection.jobs[1].rejection_cost, 8);
}

TEST(RejectableJobCollectionTest, ConstructorWithRandomData) {
    int njobs = 5;
    int p_max = 10;
    float alpha = 0.5;
    float beta = 0.5;
    RejectableJobCollection collection(njobs, p_max, alpha, beta);

    ASSERT_EQ(collection.jobs.size(), njobs);
    int total_processing_time = collection.P();
    for (const auto &job : collection.jobs) {
        EXPECT_GT(job.processing_time, 0);
        EXPECT_LE(job.processing_time, p_max);
        EXPECT_GT(job.due_to, 0);
        EXPECT_LE(job.due_to, static_cast<int>(alpha * total_processing_time + 1));
        EXPECT_GT(job.rejection_cost, 0);
        EXPECT_LE(job.rejection_cost, static_cast<int>(beta * total_processing_time + 1));
        total_processing_time += job.processing_time;
    }
}

TEST(RejectableJobCollectionTest, RandomConstructorDistinctProcessingTimes) {
    int njobs = 5;
    int p_max = 10;
    float alpha = 0.5;
    float beta = 0.5;
    RejectableJobCollection collection(njobs, p_max, alpha, beta);
    int distinct_processing_times = 0;

    for (int i = 0; i < njobs; ++i) {
        for (int j = i + 1; j < njobs; ++j) {
            if (collection.jobs[i].processing_time != collection.jobs[j].processing_time) {
                ++distinct_processing_times;
            }
        }
    }
    // statistical test
    EXPECT_GT(distinct_processing_times, njobs / 2);
}

TEST(RejectableJobCollectionTest, P) {
    std::vector<std::vector<int>> data = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };
    RejectableJobCollection collection(data);

    EXPECT_EQ(collection.P(), 2 + 6);
}

TEST(RejectableJobCollectionTest, R) {
    std::vector<std::vector<int>> data = {
        {1, 2, 3, 2},
        {5, 6, 7, 3}
    };
    RejectableJobCollection collection(data);

    EXPECT_EQ(collection.R(), 2 + 3);
}

TEST(RejectableJobCollectionTest, RGreaterThanP) {
    std::vector<std::vector<int>> data = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };
    RejectableJobCollection collection(data);

    EXPECT_EQ(collection.R(), 2 + 6);
}

TEST(RejectableJobCollectionTest, SortByDescendingDueTo) {
    std::vector<std::vector<int>> data = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {3, 4, 5, 6}
    };
    RejectableJobCollection collection(data);

    collection.sort_by_descending_due_to();

    EXPECT_EQ(collection.jobs[0].id, 5);
    EXPECT_EQ(collection.jobs[1].id, 3);
    EXPECT_EQ(collection.jobs[2].id, 1);
}

TEST(RejectableJobCollectionTest, SortByAscendingDueTo) {
    std::vector<std::vector<int>> data = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {3, 4, 5, 6}
    };
    RejectableJobCollection collection(data);

    collection.sort_by_ascending_due_to();

    EXPECT_EQ(collection.jobs[0].id, 1);
    EXPECT_EQ(collection.jobs[1].id, 3);
    EXPECT_EQ(collection.jobs[2].id, 5);
}


