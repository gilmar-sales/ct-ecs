//
// Created by gilmar on 12/21/21.
//
//
// Created by gilmar on 12/21/21.
//
#include "gtest/gtest.h"
#include "core/sparse_set.hpp"

class SparseSetSpec : public ::testing::Test {
protected:
    virtual void SetUp() {
        set = new ecs::sparse_set<unsigned>();
    }

    virtual void TearDown() {
        delete set;
    }

    ecs::sparse_set<unsigned> *set;
};

TEST_F(SparseSetSpec, SparseSetShouldInsertElements)
{
    unsigned numbers[] = {10,200,30,40};

    for (auto num : numbers)
    {
        set->insert(num);
    }

    for (auto num : numbers)
    {
        ASSERT_TRUE(set->contains(num));
    }
}

TEST_F(SparseSetSpec, SparseSetShouldBeEmptyWhenInsertingAndRemovingTheSameElements)
{
    unsigned numbers[] = {10,200,30,40, 65, 80};

    for (auto num : numbers)
    {
        set->insert(num);
    }

    for (auto num : numbers)
    {
        set->remove(num);
    }

    ASSERT_EQ(set->size(), 0);
}


TEST_F(SparseSetSpec, SparseSetShouldNotContainRemovedElements)
{
    unsigned numbers_to_insert[] = {10, 200, 30, 40, 65, 80};
    unsigned numbers_to_remove[] = {10, 200, 30};

    for (auto num : numbers_to_insert)
    {
        set->insert(num);
    }

    for (auto num : numbers_to_remove)
    {
        set->remove(num);
    }

    for (auto num : numbers_to_remove)
    {
        ASSERT_FALSE(set->contains(num));
    }

    ASSERT_TRUE(set->size() == 3);
}

TEST_F(SparseSetSpec, SparseSetShouldNotContainRemovedElementsAndContainTheRest)
{
    unsigned numbers_to_insert[] = {10, 200, 30, 40, 65, 80};
    unsigned numbers_to_remove[] = {10, 200, 30};
    unsigned numbers_to_remain[] = {40, 65, 80};

    for (auto num : numbers_to_insert)
    {
        set->insert(num);
    }

    for (auto num : numbers_to_remove)
    {
        set->remove(num);
    }

    for (auto num : numbers_to_remove)
    {
        ASSERT_FALSE(set->contains(num));
    }

    for (auto num : numbers_to_remain)
    {
        ASSERT_TRUE(set->contains(num));
    }

    ASSERT_TRUE(set->size() == 3);
}

TEST_F(SparseSetSpec, SparseSetShouldSortWithoutRemoveAnyElement)
{
    unsigned numbers[] = {10, 200, 30, 40, 65, 80};
    for (auto num : numbers)
    {
        set->insert(num);
    }

    set->sort();

    for (int i = 1; i < set->size(); i++)
    {
        ASSERT_LT((*set)[i-1], (*set)[i]);
    }

    for (auto num : numbers)
    {
        ASSERT_TRUE(set->contains(num));
    }

    ASSERT_TRUE(set->size() == 6);
}