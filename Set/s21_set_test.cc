#include "s21_set.h"

#include <gtest/gtest.h>

#include <set>
#include <string>

TEST(SetConstructorTest, EmptySet) {
  s21::Set<int> mySet;
  std::set<int> stdSet;
  EXPECT_EQ(mySet.size(), stdSet.size());
  EXPECT_TRUE(mySet.empty());
}

TEST(SetConstructorTest, EmptySet2) {
  s21::Set<std::string> mySet;
  std::set<std::string> stdSet;
  EXPECT_EQ(mySet.size(), stdSet.size());
  EXPECT_TRUE(mySet.empty());
}

TEST(SetConstructorTest, NonEmptySet) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};
  EXPECT_EQ(mySet.size(), stdSet.size());
  EXPECT_FALSE(mySet.empty());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), stdSet.begin()));
}

TEST(SetConstructorTest, NonEmptySet2) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  std::set<std::string> stdSet = {"1", "2", "3"};
  EXPECT_EQ(mySet.size(), stdSet.size());
  EXPECT_FALSE(mySet.empty());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), stdSet.begin()));
}

TEST(SetConstructorTest, EmptySet3) {
  s21::Set<int> my_set;
  std::set<int> stl_set;

  ASSERT_EQ(my_set.size(), stl_set.size());
}

TEST(SetConstructorTest, CopyConstructor) {
  s21::Set<int> mySet = {1, 2, 3};
  s21::Set<int> secSet(mySet);
  EXPECT_EQ(mySet.size(), secSet.size());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), secSet.begin()));
}

TEST(SetConstructorTest, CopyConstructor2) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  s21::Set<std::string> secSet(mySet);
  EXPECT_EQ(mySet.size(), secSet.size());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), secSet.begin()));
}

TEST(SetConstructorTest, MoveConstructor) {
  s21::Set<int> mySet = {1, 2, 3};
  s21::Set<int> movedSet(std::move(mySet));
  std::set<int> stdSet = {1, 2, 3};
  EXPECT_TRUE(mySet.empty());
  EXPECT_EQ(movedSet.size(), stdSet.size());
  EXPECT_TRUE(std::equal(movedSet.begin(), movedSet.end(), stdSet.begin()));
}

TEST(SetConstructorTest, MoveConstructor2) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  s21::Set<std::string> movedSet(std::move(mySet));
  std::set<std::string> stdSet = {"1", "2", "3"};
  EXPECT_TRUE(mySet.empty());
  EXPECT_EQ(movedSet.size(), stdSet.size());
  EXPECT_TRUE(std::equal(movedSet.begin(), movedSet.end(), stdSet.begin()));
}

TEST(SetAssignementTest, CopyAssignement) {
  s21::Set<int> mySet = {1, 2, 3};
  s21::Set<int> secSet = mySet;
  EXPECT_EQ(mySet.size(), secSet.size());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), secSet.begin()));
}

TEST(SetAssignementTest, CopyAssignement2) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  s21::Set<std::string> secSet = mySet;
  EXPECT_EQ(mySet.size(), secSet.size());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), secSet.begin()));
}

TEST(SetAssignementTest, MoveAssignement) {
  s21::Set<int> mySet = {1, 2, 3};
  s21::Set<int> movedSet = std::move(mySet);
  std::set<int> stdSet = {1, 2, 3};
  EXPECT_TRUE(mySet.empty());
  EXPECT_EQ(movedSet.size(), stdSet.size());
  EXPECT_TRUE(std::equal(movedSet.begin(), movedSet.end(), stdSet.begin()));
}

TEST(SetAssignementTest, MoveAssignement2) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  s21::Set<std::string> movedSet = std::move(mySet);
  std::set<std::string> stdSet = {"1", "2", "3"};
  EXPECT_TRUE(mySet.empty());
  EXPECT_EQ(movedSet.size(), stdSet.size());
  EXPECT_TRUE(std::equal(movedSet.begin(), movedSet.end(), stdSet.begin()));
}

TEST(SetIteratorTest, BeginTest) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};
  EXPECT_EQ(*mySet.begin(), *stdSet.begin());
}

TEST(SetIteratorTest, BeginTest2) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  std::set<std::string> stdSet = {"1", "2", "3"};
  EXPECT_EQ(*mySet.begin(), *stdSet.begin());
}

TEST(SetIteratorTest, BeginTest3) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};
  auto it = mySet.cbegin();
  ++it;
  auto std_it = stdSet.cbegin();
  ++std_it;
  EXPECT_EQ(*it, *std_it);
}

TEST(SetIteratorTest, BeginTest4) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  std::set<std::string> stdSet = {"1", "2", "3"};
  auto it = mySet.cbegin();
  ++it;
  auto std_it = stdSet.cbegin();
  ++std_it;
  EXPECT_EQ(*it, *std_it);
}

TEST(SetIteratorTest, CBeginTest) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};
  EXPECT_EQ(*mySet.cbegin(), *stdSet.cbegin());
}

TEST(SetIteratorTest, CBeginTest2) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  std::set<std::string> stdSet = {"1", "2", "3"};
  EXPECT_EQ(*mySet.cbegin(), *stdSet.cbegin());
}

TEST(SetIteratorTest, CBeginTest3) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};
  auto it = mySet.cbegin();
  ++it;
  auto std_it = stdSet.cbegin();
  ++std_it;
  EXPECT_EQ(*it, *std_it);
}

TEST(SetIteratorTest, CBeginTest4) {
  s21::Set<std::string> mySet = {"1", "2", "3"};
  std::set<std::string> stdSet = {"1", "2", "3"};
  auto it = mySet.cbegin();
  ++it;
  auto std_it = stdSet.cbegin();
  ++std_it;
  EXPECT_EQ(*it, *std_it);
}

TEST(SetIteratorTest, MutabilityTest) {
  s21::Set<int> mySet = {1, 2, 3};
  auto it = mySet.begin();

  *it = 10;            // Modify the element through iterator
  EXPECT_EQ(*it, 10);  // Verify the modification

  // Ensure container remains unchanged
  EXPECT_EQ(*mySet.begin(), 10);
}

TEST(SetIteratorTest, ComparisonTest) {
  s21::Set<int> mySet = {1, 2, 3};
  auto beginIter = mySet.begin();
  auto cbeginIter = mySet.cbegin();

  EXPECT_NE(beginIter, mySet.end());
  EXPECT_NE(cbeginIter, mySet.cend());
}

// Iterator Category Test
TEST(SetIteratorTest, IteratorCategoryTest) {
  s21::Set<int> mySet = {1, 2, 3};

  // Ensure iterator category is correct
  ASSERT_TRUE((std::is_same<decltype(mySet.begin())::iterator_category,
                            std::bidirectional_iterator_tag>::value));
}

TEST(SetIteratorTest, RangeBasedForLoopTest) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};

  std::vector<int> myVec;
  std::vector<int> stdVec;

  for (auto it = mySet.begin(); it != mySet.end(); ++it) myVec.push_back(*it);

  for (auto it = stdSet.begin(); it != stdSet.end(); ++it)
    stdVec.push_back(*it);

  EXPECT_EQ(myVec, stdVec);
}

TEST(SetCapacityTest, EmptySet) {
  s21::Set<int> mySet;
  EXPECT_TRUE(mySet.empty());
}

// Test case to check if empty() returns false for a non-empty set
TEST(SetCapacityTest, NonEmptySet) {
  s21::Set<int> mySet = {1, 2, 3};
  EXPECT_FALSE(mySet.empty());
}

// Test case to check if empty() returns true for an empty set after elements
// are removed
TEST(SetCapacityTest, EmptyAfterClear) {
  s21::Set<int> mySet = {1, 2, 3};
  mySet.clear();
  EXPECT_TRUE(mySet.empty());
}

TEST(SetCapacityTest, NonEmptyAfterErase) {
  s21::Set<int> mySet = {1, 2, 3};
  mySet.erase(1);
  EXPECT_FALSE(mySet.empty());
}

TEST(SetCapacityTest, SizeEmptySet) {
  s21::Set<int> mySet;
  EXPECT_EQ(mySet.size(), 0u);
}

TEST(SetCapacityTest, SizeNonEmptySet) {
  s21::Set<int> mySet = {1, 2, 3};
  EXPECT_EQ(mySet.size(), 3u);
}

TEST(SetCapacityTest, SizeZeroAfterClear) {
  s21::Set<int> mySet = {1, 2, 3};
  mySet.clear();
  EXPECT_EQ(mySet.size(), 0u);
}

TEST(SetCapacityTest, SizeAfterErase) {
  s21::Set<int> mySet = {1, 2, 3};
  mySet.erase(1);
  EXPECT_EQ(mySet.size(), 2u);
}

TEST(SetCapacityTest, MaxSize) {
  s21::Set<int> mySet;
  std::set<int> std_set;
  EXPECT_EQ(mySet.max_size(), std_set.max_size());
}

// Test case to check if clear() empties the set for integer elements
TEST(SetModifiersTest, ClearIntegerSet) {
  s21::Set<int> myIntSet = {1, 2, 3, 4, 5};
  myIntSet.clear();
  EXPECT_TRUE(myIntSet.empty());
}

// Test case to check if clear() empties the set for string elements
TEST(SetModifiersTest, ClearStringSet) {
  s21::Set<std::string> myStrSet = {"apple", "banana", "orange"};
  myStrSet.clear();
  EXPECT_TRUE(myStrSet.empty());
}

// Test case to check if clear() has no effect on an already empty set for
// integer elements
TEST(SetModifiersTest, ClearEmptyIntegerSet) {
  s21::Set<int> myIntSet;
  myIntSet.clear();
  EXPECT_TRUE(myIntSet.empty());
}

// Test case to check if clear() has no effect on an already empty set for
// string elements
TEST(SetModifiersTest, ClearEmptyStringSet) {
  s21::Set<std::string> myStrSet;
  myStrSet.clear();
  EXPECT_TRUE(myStrSet.empty());
}

// Test case to check if clear() resets the size to 0 for integer elements
TEST(SetModifiersTest, ClearResetsSizeIntegerSet) {
  s21::Set<int> myIntSet = {1, 2, 3, 4, 5};
  myIntSet.clear();
  EXPECT_EQ(myIntSet.size(), 0u);
}

// Test case to check if clear() resets the size to 0 for string elements
TEST(SetModifiersTest, ClearResetsSizeStringSet) {
  s21::Set<std::string> myStrSet = {"apple", "banana", "orange"};
  myStrSet.clear();
  EXPECT_EQ(myStrSet.size(), 0u);
}

// Test case to check insertion of unique integer elements
TEST(SetModifiersTest, InsertUniqueInteger) {
  s21::Set<int> myIntSet;
  std::pair<typename s21::Set<int>::iterator, bool> result = myIntSet.insert(5);
  auto it = result.first;
  bool success = result.second;
  EXPECT_TRUE(success);
  EXPECT_EQ(*it, 5);
}

// check if insert() returns the correct iterator after insertion for integer
// elements
TEST(SetModifiersTest, InsertReturnIteratorInteger) {
  s21::Set<int> myIntSet = {1, 2, 3};
  std::pair<typename s21::Set<int>::iterator, bool> result = myIntSet.insert(5);
  auto it = result.first;
  EXPECT_EQ(*it, 5);
}

TEST(SetModifiersTest, InsertNoModificationInteger) {
  s21::Set<int> myIntSet = {1, 2, 3};
  std::pair<typename s21::Set<int>::iterator, bool> result = myIntSet.insert(2);
  bool success = result.second;
  EXPECT_FALSE(success);
  EXPECT_EQ(myIntSet.size(), 3u);
}

TEST(SetModifiersTest, InsertUniqueInteger2) {
  s21::Set<int> myIntSet = {1, 2, 5};
  std::pair<typename s21::Set<int>::iterator, bool> result = myIntSet.insert(3);
  auto it = result.first;
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(SetModifiersTest, InsertUniqueString) {
  s21::Set<std::string> myStringSet;
  std::pair<typename s21::Set<std::string>::iterator, bool> result =
      myStringSet.insert("hello");
  auto it = result.first;
  bool success = result.second;
  EXPECT_TRUE(success);
  EXPECT_EQ(*it, "hello");
}

TEST(SetModifiersTest, InsertReturnIteratorString) {
  s21::Set<std::string> myStringSet = {"apple", "banana", "orange"};
  std::pair<typename s21::Set<std::string>::iterator, bool> result =
      myStringSet.insert("kiwi");
  auto it = result.first;
  EXPECT_EQ(*it, "kiwi");
}

TEST(SetModifiersTest, InsertNoModificationString) {
  s21::Set<std::string> myStringSet = {"apple", "banana", "orange"};
  std::pair<typename s21::Set<std::string>::iterator, bool> result =
      myStringSet.insert("banana");
  bool success = result.second;
  EXPECT_FALSE(success);
}

TEST(SetModifiersTest, InsertUniqueString2) {
  s21::Set<std::string> myStringSet = {"apple", "banana", "orange"};
  std::pair<typename s21::Set<std::string>::iterator, bool> result =
      myStringSet.insert("grape");
  auto it = result.first;
  ++it;
  EXPECT_EQ(*it, "orange");
}

TEST(SetModifiersTest, InsertRandomOrder) {
  s21::Set<int> myIntSet;
  std::vector<int> elements = {5, 2, 8, 3, 1};
  for (int elem : elements) {
    myIntSet.insert(elem);
  }
  EXPECT_EQ(myIntSet.size(), elements.size());
  for (int elem : elements) {
    EXPECT_TRUE(myIntSet.find(elem) != myIntSet.end());
  }
}

TEST(SetModifiersTest, InsertLargeNumberOfElements) {
  s21::Set<int> myIntSet;
  const unsigned int numElements = 1000;
  for (unsigned int i = 0; i < numElements; ++i) {
    myIntSet.insert(i);
  }
  EXPECT_EQ(myIntSet.size(), numElements);
  for (unsigned int i = 0; i < numElements; ++i) {
    EXPECT_TRUE(myIntSet.find(i) != myIntSet.end());
  }
}

TEST(SetModifiersTest, EraseExistingElement) {
  s21::Set<int> mySet = {1, 2, 3};
  auto it = mySet.find(2);
  mySet.erase(it);
  EXPECT_EQ(mySet.size(), 2u);
}

TEST(SetModifiersTest, EraseNonExistingElement) {
  s21::Set<int> mySet = {1, 2, 3};
  auto it = mySet.find(4);
  mySet.erase(it);
  EXPECT_EQ(mySet.size(), 3u);
}

TEST(SetModifiersTest, EraseInvalidIterator) {
  s21::Set<int> myIntSet = {1, 2, 3, 4};

  auto it = myIntSet.end();  // Invalid iterator
  myIntSet.erase(it);

  EXPECT_EQ(myIntSet.size(), 4u);  // Size should remain unchanged
}

TEST(SetModifiersTest, EraseString) {
  s21::Set<std::string> myStrSet = {"apple", "banana", "orange"};

  auto it = myStrSet.find("banana");
  myStrSet.erase(it);

  EXPECT_EQ(myStrSet.size(), 2u);
}

TEST(SetModifiersTest, SwapInteger) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2 = {4, 5};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), 2u);
  EXPECT_EQ(set2.size(), 3u);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(5));
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
}

TEST(SetModifiersTest, SwapString) {
  s21::Set<std::string> set1 = {"apple", "banana"};
  s21::Set<std::string> set2 = {"kiwi", "grape", "pear"};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), 3u);
  EXPECT_EQ(set2.size(), 2u);
  EXPECT_TRUE(set1.contains("kiwi"));
  EXPECT_TRUE(set1.contains("grape"));
  EXPECT_TRUE(set1.contains("pear"));
  EXPECT_TRUE(set2.contains("apple"));
  EXPECT_TRUE(set2.contains("banana"));
}

TEST(SetModifiersTest, MergeInteger) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2 = {4, 5};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), 5u);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(5));
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
}

TEST(SetModifiersTest, MergeIntEmpty) {
  s21::Set<int> set1;
  s21::Set<int> set2 = {4, 5};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), 2u);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(5));
  EXPECT_EQ(set2.size(), 0u);
}

TEST(SetModifiersTest, MergeString) {
  s21::Set<std::string> set1 = {"apple", "banana"};
  s21::Set<std::string> set2 = {"kiwi", "grape", "pear"};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), 5u);
  EXPECT_EQ(set2.size(), 0u);
  EXPECT_TRUE(set1.contains("kiwi"));
  EXPECT_TRUE(set1.contains("grape"));
  EXPECT_TRUE(set1.contains("pear"));
  EXPECT_TRUE(set1.contains("apple"));
  EXPECT_TRUE(set1.contains("banana"));
}

TEST(SetModifiersTest, MergeStrEmpty) {
  s21::Set<std::string> set1 = {"apple", "banana"};
  s21::Set<std::string> set2;

  set1.merge(set2);

  EXPECT_EQ(set1.size(), 2u);
  EXPECT_EQ(set2.size(), 0u);
  EXPECT_TRUE(set1.contains("apple"));
  EXPECT_TRUE(set1.contains("banana"));
}

TEST(SetLookupTest, ExistingKeyInt) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  auto it = mySet.find(3);
  ASSERT_NE(it, mySet.end());
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(SetLookupTest, NonExistingKeyInt) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  auto it = mySet.find(6);
  EXPECT_EQ(it, mySet.end());
}

TEST(SetLookupTest, ExistingKeyString) {
  s21::Set<std::string> mySet = {"apple", "banana", "orange"};
  auto it = mySet.find("banana");
  ASSERT_NE(it, mySet.end());
  EXPECT_EQ(*it, "banana");
  ++it;
  EXPECT_EQ(*it, "orange");
}

TEST(SetLookupTest, NonExistingKeyString) {
  s21::Set<std::string> mySet = {"apple", "banana", "orange"};
  auto it = mySet.find("grape");
  EXPECT_EQ(it, mySet.end());
}

TEST(SetLookupTest, EmptySet) {
  s21::Set<int> mySet;
  auto it = mySet.find(1);
  EXPECT_EQ(it, mySet.end());
}

TEST(SetLookupTest, KeyAtBeginning) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  auto it = mySet.find(1);
  ASSERT_NE(it, mySet.end());
  EXPECT_EQ(*it, 1);
}

TEST(SetLookupTest, KeyAtEnd) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  auto it = mySet.find(5);
  ASSERT_NE(it, mySet.end());
  EXPECT_EQ(*it, 5);
}

TEST(SetLookupTest, KeyInMiddle) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  auto it = mySet.find(3);
  ASSERT_NE(it, mySet.end());
  EXPECT_EQ(*it, 3);
}

TEST(SetLookupTest, ExistingKeyInt1) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  EXPECT_TRUE(mySet.contains(3));
}

TEST(SetLookupTest, NonExistingKeyInt1) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  EXPECT_FALSE(mySet.contains(6));
}

TEST(SetLookupTest, ExistingKeyString1) {
  s21::Set<std::string> mySet = {"apple", "banana", "orange"};
  EXPECT_TRUE(mySet.contains("banana"));
}

TEST(SetLookupTest, NonExistingKeyString1) {
  s21::Set<std::string> mySet = {"apple", "banana", "orange"};
  EXPECT_FALSE(mySet.contains("grape"));
}

TEST(SetLookupTest, EmptySet1) {
  s21::Set<int> mySet;
  EXPECT_FALSE(mySet.contains(1));
}

TEST(SetLookupTest, KeyAtBeginning1) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  EXPECT_TRUE(mySet.contains(1));
}

TEST(SetLookupTest, KeyAtEnd1) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  EXPECT_TRUE(mySet.contains(5));
}

TEST(SetLookupTest, KeyInMiddle1) {
  s21::Set<int> mySet = {1, 2, 3, 4, 5};
  EXPECT_TRUE(mySet.contains(3));
}

TEST(SetTest, InsertAndSize) {
  s21::Set<int> mySet;
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);

  EXPECT_EQ(mySet.size(), 3u);
}

TEST(SetTest, RemoveAndSize) {
  s21::Set<int> mySet = {1, 2, 3};

  mySet.erase(2);

  EXPECT_EQ(mySet.size(), 2u);
  EXPECT_EQ(mySet.contains(2), false);
}

// Тест проверки на пустоту
TEST(SetTest, Empty) {
  s21::Set<int> mySet;
  EXPECT_TRUE(mySet.empty());

  mySet.insert(42);
  EXPECT_FALSE(mySet.empty());

  mySet.clear();
  EXPECT_TRUE(mySet.empty());
}

// Тест отчистки
TEST(SetTest, Clear) {
  s21::Set<int> mySet = {1, 2, 3};

  mySet.clear();
  EXPECT_TRUE(mySet.empty());
  EXPECT_EQ(mySet.size(), 0u);
}

// Тест метода проверки на содержание
TEST(SetTest, Contains) {
  s21::Set<int> mySet = {1, 2, 3};

  EXPECT_TRUE(mySet.contains(2));
  EXPECT_FALSE(mySet.contains(4));
}

// Тест методов итератора: конец/начало/итерации
TEST(SetTest, BeginEnd) {
  s21::Set<int> mySet = {1, 2, 3};

  auto it = mySet.begin();
  EXPECT_EQ(it.key(), 1);

  ++it;
  EXPECT_EQ(it.key(), 2);

  ++it;
  EXPECT_EQ(it.key(), 3);
}

// Тест для сравнения s21::Set и std::set
TEST(SetComparisonTest, SameElements) {
  s21::Set<int> mySet = {1, 2, 3};

  std::set<int> stdSet = {1, 2, 3};

  // Сравниваем размеры
  EXPECT_EQ(mySet.size(), stdSet.size());
}

TEST(SetComparisonTest, Insertion) {
  s21::Set<int> mySet;
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);

  std::set<int> stdSet;
  stdSet.insert(1);
  stdSet.insert(2);
  stdSet.insert(3);

  EXPECT_EQ(mySet.size(), stdSet.size());
  auto it1 = mySet.begin();
  auto it2 = stdSet.begin();
  for (; it1 != mySet.end() && it2 != stdSet.end(); ++it1, ++it2) {
    EXPECT_EQ(it1.key(), *it2);
  }
  EXPECT_EQ(it1, mySet.end());
  EXPECT_EQ(it2, stdSet.end());
}

// Тест для сравнения метода contains
TEST(SetComparisonTest, Contains) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};

  // Сравнение метода contains
  EXPECT_EQ(mySet.contains(2), stdSet.count(2) > 0);
}

TEST(SetComparisonTest, Merge) {
  s21::Set<int> mySet = {1, 2, 3};
  s21::Set<int> otherSet = {3, 4, 5};
  mySet.merge(otherSet);

  std::set<int> stdSet = {1, 2, 3};
  std::set<int> otherStdSet = {3, 4, 5};
  stdSet.insert(otherStdSet.begin(), otherStdSet.end());

  EXPECT_EQ(mySet.size(), stdSet.size());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), stdSet.begin()));
}

// Тест для сравнения метода swap
TEST(SetComparisonTest, Swap) {
  s21::Set<int> mySet = {1, 2, 3};
  s21::Set<int> emptySet;

  std::set<int> stdSet = {1, 2, 3};
  std::set<int> emptyStdSet;

  mySet.swap(emptySet);
  stdSet.swap(emptyStdSet);

  EXPECT_TRUE(mySet.empty());
  EXPECT_FALSE(emptySet.empty());
  EXPECT_TRUE(stdSet.empty());
  EXPECT_FALSE(emptyStdSet.empty());
}

// Тест для сравнения метода erase
TEST(SetComparisonTest, Erase) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};

  mySet.erase(2);
  stdSet.erase(2);

  EXPECT_EQ(mySet.size(), stdSet.size());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), stdSet.begin()));
}

// Тест для сравнения метода insert
TEST(SetComparisonTest, Insert) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};

  mySet.insert(4);
  stdSet.insert(4);

  EXPECT_EQ(mySet.size(), stdSet.size());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), stdSet.begin()));
}

TEST(SetComparisonTest, Insert2) {
  s21::Set<int> mySet = {1, 2, 3};
  std::set<int> stdSet = {1, 2, 3};

  mySet.insert(3);
  stdSet.insert(3);

  EXPECT_EQ(mySet.size(), stdSet.size());
  EXPECT_TRUE(std::equal(mySet.begin(), mySet.end(), stdSet.begin()));
}
