// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0

    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    ASSERT_EQ(collection->size(), 1);

    // is the collection still empty?
    // if not empty, what must the size be?
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    ASSERT_EQ(collection->size(), 0);
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterOrEqualToSize) {
    //Checks vector is of size 0, than compares max size
    ASSERT_EQ(collection->size(), 0);
    ASSERT_GE(collection->max_size(), collection->size());
    
    //Adds 1 value, Checks vector is of size 1, than compares max size
    add_entries(1);
    ASSERT_EQ(collection->size(), 1);
    ASSERT_GE(collection->max_size(), collection->size());
    
    //Adds 4 values, Checks vector is of size 5, than compares max size
    add_entries(4);
    ASSERT_EQ(collection->size(), 5);
    ASSERT_GE(collection->max_size(), collection->size());
    
    //Adds 5 values, Checks vector is of size 10, than compares max size
    add_entries(5);
    ASSERT_EQ(collection->size(), 10);
    ASSERT_GE(collection->max_size(), collection->size());

}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterOrEqualToSize) {
    //Checks vector is of size 0, than compares capacity
    ASSERT_EQ(collection->size(), 0);
    ASSERT_GE(collection->capacity(), collection->size());

    //Adds 1 value, Checks vector is of size 1, than compares capacity
    add_entries(1);
    ASSERT_EQ(collection->size(), 1);
    ASSERT_GE(collection->capacity(), collection->size());

    //Adds 4 values, Checks vector is of size 5, than compares capacity
    add_entries(4);
    ASSERT_EQ(collection->size(), 5);
    ASSERT_GE(collection->capacity(), collection->size());

    //Adds 5 values, Checks vector is of size 10, than compares capacity
    add_entries(5);
    ASSERT_EQ(collection->size(), 10);
    ASSERT_GE(collection->capacity(), collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeBecomesLargerCollection) {
    //Easily Set/Check Resize value, must be larger than 0 to test properly
    const int RESIZE_VALUE = 10;
    
    //Checks that initial size is 0, then after resize value equals new larger value
    ASSERT_EQ(collection->size(), 0);
    collection->resize(RESIZE_VALUE);
    ASSERT_EQ(collection->size(), RESIZE_VALUE);

    //Alternatively this could be used to test as well
    int oldSize = collection->size();
    collection->resize(oldSize + RESIZE_VALUE);
    ASSERT_GT(collection->size(), oldSize);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeBecomesSmallerCollection) {
    //Easily Set/Check Resize value
    const int RESIZE_VALUE = 5;

    //Add 2x Resize Value entries to collection
    add_entries(RESIZE_VALUE * 2);
    //Checks to ensure that size is GT Resize Value 
    ASSERT_GT(collection->size(), RESIZE_VALUE);

    //Record old size, Resize collection to size - Resize value
    int oldSize = collection->size();
    collection->resize(oldSize - RESIZE_VALUE);
    ASSERT_LT(collection->size(), oldSize);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeToZero) {
    //Set size to a larger than 0 size
    const int RESIZE_VALUE = 10; 

    //Add entries and ensure size is correct
    add_entries(RESIZE_VALUE);
    ASSERT_EQ(collection->size(), RESIZE_VALUE);

    //Resize to 0 and ensure size is 0, not null
    collection->resize(0);
    ASSERT_EQ(collection->size(), 0);
    ASSERT_NE(collection.get(), nullptr);


}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection) {
    //Ensure that collection is created, add 10 values than, check if erased with clear()
    const int RESIZE_VALUE = 10;
    ASSERT_NE(collection.get(), nullptr);
    add_entries(RESIZE_VALUE);

    //Check collection is of size RESIZE VALUE and not 0 than clear and check collection is empty
    ASSERT_EQ(collection->size(), RESIZE_VALUE);
    ASSERT_NE(collection->size(), 0);
    collection->clear();
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseCollectionWorks) {
    //Ensure that collection is created, add 10 values than, check if erase works
    const int RESIZE_VALUE = 10;
    add_entries(RESIZE_VALUE);

    //Check collection is of size RESIZE VALUE and not 0 than clear and check collection is empty
    ASSERT_EQ(collection->size(), RESIZE_VALUE);
    ASSERT_NE(collection->size(), 0);
    
    collection->erase(collection->begin(), collection->end());
    ASSERT_EQ(collection->size(), 0);
}
// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReservesMoreCapacityNotSize) {
    //Const values for testing capacity and Size before and after reserve
    const int CAPACITY_VALUE = collection->capacity();
    const int INCREASE_CAPACITY_VALUE = 10;
    const int INITIAL_SIZE = collection->size();

    //Increases Capacity 
    collection->reserve(CAPACITY_VALUE + INCREASE_CAPACITY_VALUE);

    //Checks that capacity has been increased from initial value
    ASSERT_GT(collection->capacity(), CAPACITY_VALUE);
    //Checks that size has not changed since initial value
    ASSERT_EQ(collection->size(), INITIAL_SIZE);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, ProperExceptionThrownOutOfRange) {
    //Resize value should be over 0 to test
    const int RESIZE_VALUE = 10;
    add_entries(RESIZE_VALUE);

    EXPECT_EQ(collection->size(), RESIZE_VALUE); //Expect is used here as if this fails it should not critically damage the testing, this is for reassurance

    //Checks to ensure proper exception is thrown in out of bounds indexing
    ASSERT_THROW(collection->at(RESIZE_VALUE * 2), std::out_of_range);

}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

//Positive test to change value at index and test to ensure value is changed
TEST_F(CollectionTest, ChangeValueAtIndex) {
    //Resize value should be over 0 and divisable by 2
    const int RESIZE_VALUE = 10;
    const int INDEX_LOCATION = RESIZE_VALUE / 2;
    const int INTENDED_VALUE = 14; //Placed in index
    
    //Resize vector than change value at index to INTENDED VALUE
    collection->resize(RESIZE_VALUE);
    EXPECT_NE(collection->at(INDEX_LOCATION), INTENDED_VALUE);//Could detect false positive if values are initialized to INTENDED_VALUE or are assigned earlier
    //Making it important to check and notify tester
    collection->at(INDEX_LOCATION) = INTENDED_VALUE;

    //Assert that value at index location is now INTENDED value
    ASSERT_EQ(collection->at(INDEX_LOCATION), INTENDED_VALUE);

}

//Tests to ensure exception is thrown when the vector is resized to a negative value
TEST_F(CollectionTest, NegativeSizeException) {

    //Tests to make sure an exception is thrown when collection is resized to negative value
    const int RESIZE_VALUE = -2;
    ASSERT_ANY_THROW(collection->resize(RESIZE_VALUE)); //Catches any exception thrown by this attempted resize.
    ASSERT_EQ(collection->size(), 0); //Ensure the vector did not get resized. (Not needed for test but good to check test failed successfully.)

}