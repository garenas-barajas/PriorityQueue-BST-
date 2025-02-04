#include "prqueue.h"

#include "gtest/gtest.h"

using namespace std;

TEST(EmptyTest, Test)
{
    prqueue<int> pq;
}

// Test constructor, size, and enqueue
TEST(EnqueueTestInt, Test)
{
    prqueue<int> pq;
    // Test size, and pointers
    EXPECT_EQ(pq.size(), 0);

    pq.enqueue(1, 1);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);

    // Test size
    EXPECT_EQ(pq.size(), 3);
}

// Test copy constructor

// Test assignment operator

// Test clear
TEST(ClearTest, Test)
{
    prqueue<int> pq;
    // Test on empty queue
    pq.clear();
    EXPECT_EQ(pq.size(), 0);

    pq.enqueue(4, 4);
    pq.enqueue(5, 5);
    pq.enqueue(6, 6);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);
    pq.enqueue(1, 1);

    // Test clear
    pq.clear();
    EXPECT_EQ(pq.size(), 0);
    EXPECT_EQ(pq.peek(), 0);

    // Test adding to queue after clear
    pq.enqueue(4, 4);
    pq.enqueue(5, 5);
    pq.enqueue(6, 6);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);
    pq.enqueue(1, 1);

    EXPECT_EQ(pq.size(), 6);
    EXPECT_EQ(pq.peek(), 1);
}

// Test clear on large queue
TEST(ClearTestLarge, Test)
{
    prqueue<int> pq;
    for (int i = 0; i < 1000; i++)
    {
        pq.enqueue(i, i);
    }

    // Test clear
    pq.clear();
    EXPECT_EQ(pq.size(), 0);
}

// Test dequeue
TEST(DequeueTest, Test)
{
    prqueue<int> pq;
    pq.enqueue(1, 1);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);

    // Test size
    ASSERT_EQ(pq.size(), 3);

    // Test dequeue and size
    EXPECT_EQ(pq.dequeue(), 1);
    EXPECT_EQ(pq.size(), 2);
    EXPECT_EQ(pq.dequeue(), 2);
    EXPECT_EQ(pq.size(), 1);
    EXPECT_EQ(pq.dequeue(), 3);

    // Test on empty queue
    EXPECT_EQ(pq.dequeue(), 0);
    EXPECT_EQ(pq.size(), 0);
}

// Test 2 dequeue
TEST(DequeueTest2, Test)
{
    prqueue<int> pq;
    pq.enqueue(4, 4);
    pq.enqueue(5, 5);
    pq.enqueue(6, 6);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);
    pq.enqueue(1, 1);

    // Test size after dequeue
    ASSERT_EQ(pq.size(), 6);
    EXPECT_EQ(pq.dequeue(), 1);
    EXPECT_EQ(pq.size(), 5);
    EXPECT_EQ(pq.dequeue(), 2);
    EXPECT_EQ(pq.size(), 4);
    EXPECT_EQ(pq.dequeue(), 3);
    EXPECT_EQ(pq.size(), 3);
    EXPECT_EQ(pq.dequeue(), 4);
    EXPECT_EQ(pq.size(), 2);
    EXPECT_EQ(pq.dequeue(), 5);
    EXPECT_EQ(pq.size(), 1);
    EXPECT_EQ(pq.dequeue(), 6);
    EXPECT_EQ(pq.size(), 0);
}

// Test peek
TEST(PeekTest, Test)
{
    prqueue<int> pq;

    // Test on empty queue
    EXPECT_EQ(pq.peek(), 0);

    pq.enqueue(1, 1);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);

    // Test peek
    EXPECT_EQ(pq.peek(), 1);
}

// Test begin

// Test next

// Test as_string with int
TEST(AsStringTestint, Test)
{
    prqueue<int> pq;
    pq.enqueue(1, 1);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);

    string prString = "1 value: 1\n2 value: 2\n3 value: 3\n";

    // Test as_string
    EXPECT_EQ(pq.as_string(), prString);
}

// Test as_string with string
TEST(AsStringTestString, Test)
{
    prqueue<string> pq;
    pq.enqueue("a", 1);
    pq.enqueue("b", 2);
    pq.enqueue("c", 3);

    string prString = "1 value: a\n2 value: b\n3 value: c\n";

    // Test as_string
    EXPECT_EQ(pq.as_string(), prString);
}

// test cases involving duplicates
// Each node now has its own linked list of duplicates
// new pointers now include head and next for each node

// Test begin and next with 7 priorities and 21 nodes
TEST(BeginNextTestDupe, Test)
{
    prqueue<int> pq;
    pq.enqueue(7, 5);
    pq.enqueue(1, 6);
    pq.enqueue(5, 1);
    pq.enqueue(6, 2);
    pq.enqueue(3, 7);
    pq.enqueue(6, 1);
    pq.enqueue(2, 4);
    pq.enqueue(4, 3);
    pq.enqueue(1, 5);
    pq.enqueue(2, 2);
    pq.enqueue(1, 3);
    pq.enqueue(4, 7);
    pq.enqueue(4, 4);
    pq.enqueue(2, 3);
    pq.enqueue(1, 4);
    pq.enqueue(3, 5);
    pq.enqueue(2, 6);
    pq.enqueue(3, 6);
    pq.enqueue(5, 7);
    pq.enqueue(7, 1);
    pq.enqueue(4, 2);

    // Expected values
    vector<int> expectedValues = {5, 6, 7, 6, 2, 4, 4, 1, 2, 2, 4, 1, 7, 1, 3, 1, 2, 3, 3, 4, 5};
    vector<int> expectedPriorities = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7};

    pq.begin();

    int value;
    int priority;
    int index = 0;

    // Test next using while loop
    while (pq.next(value, priority))
    {
        ASSERT_EQ(value, expectedValues[index]);
        ASSERT_EQ(priority, expectedPriorities[index]);
        ++index;
    }

    // Test size
    EXPECT_EQ(index, expectedValues.size());
}

// Test begin and next without duplicates
TEST(BeginNextTest, Test)
{
    prqueue<int> pq;
    pq.enqueue(5, 2);
    pq.enqueue(6, 1);
    pq.enqueue(3, 3);

    // Excpeted values
    vector<int> expectedValues = {6, 5, 3};
    vector<int> expectedPriorities = {1, 2, 3};

    pq.begin();

    int value;
    int priority;
    int index = 0;

    // Test next using while loop
    while (pq.next(value, priority))
    {
        ASSERT_EQ(value, expectedValues[index]);
        ASSERT_EQ(priority, expectedPriorities[index]);
        ++index;
    }

    // Test size
    EXPECT_EQ(index, expectedValues.size());
}

// Test begin and next functions with dupicate priorities
TEST(BeginNextTestEmpty, Test)
{
    prqueue<int> pq;

    pq.begin();

    int value;
    int priority;

    // Ensure next returns false on empty queue
    EXPECT_EQ(pq.next(value, priority), false);
}

// Test operator= on empty bst
TEST(OperatorTestEmpty, Test)
{
    prqueue<int> pq;
    prqueue<int> pq2;
    pq2 = pq;

    // Test size
    EXPECT_EQ(pq2.size(), 0);
}

// Test operator= on regular bst
TEST(OperatorTest, Test)
{
    prqueue<int> pq;
    pq.enqueue(5, 2);
    pq.enqueue(6, 1);
    pq.enqueue(3, 3);

    prqueue<int> pq2;
    pq2 = pq;

    // Expected values
    vector<int> expectedValues = {6, 5, 3};
    vector<int> expectedPriorities = {1, 2, 3};

    pq2.begin();

    int value;
    int priority;
    int index = 0;

    // Test using while loop
    while (pq2.next(value, priority))
    {
        ASSERT_EQ(value, expectedValues[index]);
        ASSERT_EQ(priority, expectedPriorities[index]);
        index++;
    }

    // Test size
    EXPECT_EQ(index, expectedValues.size());
}

// Test operator= with duplicates
TEST(OperatorTestDupe, Test)
{
    prqueue<int> pq;

    pq.enqueue(7, 7);
    pq.enqueue(4, 4);
    pq.enqueue(1, 1);
    pq.enqueue(6, 6);
    pq.enqueue(5, 5);
    pq.enqueue(2, 1);
    pq.enqueue(5, 4);
    pq.enqueue(10, 10);
    pq.enqueue(11, 10);
    pq.enqueue(8, 8);
    pq.enqueue(9, 9);
    pq.enqueue(11, 11);
    pq.enqueue(12, 12);

    prqueue<int> pq2;
    pq2 = pq;

    // Expected values
    vector<int> expectedValues = {1, 2, 4, 5, 5, 6, 7, 8, 9, 10, 11, 11, 12};
    vector<int> expectedPriorities = {1, 1, 4, 4, 5, 6, 7, 8, 9, 10, 10, 11, 12};

    pq2.begin();

    int value;
    int priority;
    int index = 0;

    // Test using while loop
    while (pq2.next(value, priority))
    {
        ASSERT_EQ(value, expectedValues[index]);
        ASSERT_EQ(priority, expectedPriorities[index]);
        index++;
    }

    // Test size
    EXPECT_EQ(index, expectedValues.size());
}

// Test operator== on empty bst
TEST(OperatorEmptyTest, Test)
{
    prqueue<int> pq;
    prqueue<int> pq2;

    // Test operator==
    EXPECT_EQ(pq == pq2, true);
}

// Test operator== on regular bst
TEST(OperatorBSTTest, Test)
{
    prqueue<int> pq;
    pq.enqueue(5, 2);
    pq.enqueue(6, 1);
    pq.enqueue(3, 3);

    prqueue<int> pq2;
    pq2 = pq;

    // Test operator==
    EXPECT_EQ(pq2 == pq, true);
}

// Test operator== with duplicates
TEST(OperatorDupeTest, Test)
{
    prqueue<int> pq;
    pq.enqueue(5, 2);
    pq.enqueue(6, 1);
    pq.enqueue(4, 3);
    pq.enqueue(2, 2);
    pq.enqueue(7, 1);
    pq.enqueue(1, 3);

    prqueue<int> pq2;
    pq2 = pq;

    // Test operator==
    EXPECT_EQ(pq == pq2, true);
}

// Test operator== when they are not equal
TEST(OperatorNotEqualTest, Test)
{
    prqueue<int> pq;
    pq.enqueue(5, 2);
    pq.enqueue(6, 1);
    pq.enqueue(3, 3);

    prqueue<int> pq2;
    pq2.enqueue(5, 2);
    pq2.enqueue(6, 1);
    pq2.enqueue(4, 3);

    // Test operator==
    EXPECT_EQ(pq == pq2, false);
}