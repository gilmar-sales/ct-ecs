//
// Created by gilmar on 12/21/21.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "core/sparse_set.hpp"

class SparseSetMock : public SparseSet<unsigned> {
public:
    SparseSetMock() {
        ON_CALL(*this, dense_sort).WillByDefault([this](){
            return this->SparseSet<unsigned>::dense_sort();
        });
    }

    MOCK_METHOD(void, dense_sort, (), (override));
};

class SparseSetSpec : public ::testing::Test {
protected:
    void SetUp() override {
        set = new SparseSetMock();
    }

    void TearDown() override {
        delete set;
    }

    SparseSetMock *set = nullptr;
};

TEST_F(SparseSetSpec, SparseSetShouldInsertElements) {
    unsigned numbers[] = {10, 200, 30, 40};

    for (auto num: numbers) {
        set->insert(num);
    }

    unsigned numbers_count = sizeof(numbers) / sizeof(numbers[0]);

    ASSERT_EQ(numbers_count, set->size());

    for (auto num: numbers) {
        ASSERT_TRUE(set->contains(num));
    }
}

TEST_F(SparseSetSpec, SparseSetShouldBeEmptyWhenInsertingAndRemovingTheSameElements) {
    unsigned numbers[] = {10, 200, 30, 40, 65, 80};

    for (auto num: numbers) {
        set->insert(num);
    }

    for (auto num: numbers) {
        set->remove(num);
    }

    ASSERT_EQ(set->size(), 0);
}


TEST_F(SparseSetSpec, SparseSetShouldNotContainRemovedElements) {
    unsigned numbers_to_insert[] = {10, 200, 30, 40, 65, 80};
    unsigned numbers_to_remove[] = {10, 200, 30};

    for (auto num: numbers_to_insert) {
        set->insert(num);
    }

    for (auto num: numbers_to_remove) {
        set->remove(num);
    }

    for (auto num: numbers_to_remove) {
        ASSERT_FALSE(set->contains(num));
    }

    ASSERT_TRUE(set->size() == 3);
}

TEST_F(SparseSetSpec, SparseSetShouldNotContainRemovedElementsAndContainTheRest) {
    unsigned numbers_to_insert[] = {10, 200, 30, 40, 65, 80};
    unsigned numbers_to_remove[] = {10, 200, 30};
    unsigned numbers_to_remain[] = {40, 65, 80};

    for (auto num: numbers_to_insert) {
        set->insert(num);
    }

    for (auto num: numbers_to_remove) {
        set->remove(num);
    }

    for (auto num: numbers_to_remove) {
        ASSERT_FALSE(set->contains(num));
    }

    for (auto num: numbers_to_remain) {
        ASSERT_TRUE(set->contains(num));
    }

    ASSERT_TRUE(set->size() == 3);
}

TEST_F(SparseSetSpec, SparseSetShouldSortTheFirstTimeAfterInitialization) {
    using testing::Exactly;
    SparseSetMock setMock = SparseSetMock();
    unsigned numbers[] = {10, 200, 30, 40, 65, 80};
    for (auto num: numbers) {
        setMock.insert(num);
    }

    EXPECT_CALL(setMock, dense_sort()).Times(1);

    setMock.sort();

    for (int i = 1; i < setMock.size(); i++) {
        ASSERT_LT(setMock[i - 1], setMock[i]);
    }

    for (auto num: numbers) {
        ASSERT_TRUE(setMock.contains(num));
    }

    ASSERT_TRUE(setMock.size() == 6);
}

TEST_F(SparseSetSpec, SparseSetShouldSortAutomaticallyOnlyWhenNeeded) {
    unsigned numbers[] = {100, 25, 90, 80, 1000, 900, 872, 646, 853, 217, 981};
    set->resize(11000);

    for (auto number : numbers) {
        set->insert(number);
    }

    EXPECT_CALL(*set, dense_sort()).Times(1);

    set->sort();
    set->sort();

    EXPECT_CALL(*set, dense_sort()).Times(1);
    set->insert(123);
    set->sort();
    set->sort();

    unsigned numbers_count = sizeof(numbers) / sizeof(numbers[0]) + 1;

    ASSERT_EQ(numbers_count, set->size());
    ASSERT_TRUE(set->contains(123));
}