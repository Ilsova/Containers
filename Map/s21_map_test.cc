#include "s21_map.h"

#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <string>

TEST(TestMapMapConstructor, DefaultConstructor) {
  s21::Map<int, int> m;
  std::map<int, int> m2;
  ASSERT_EQ(m.size(), m2.size());
}

TEST(MapConstructorTest, InitializerListConstructor) {
  // Test case with integer keys and string values
  s21::Map<int, std::string> intStrMap = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(intStrMap.size(), 3u);
  EXPECT_EQ(intStrMap.at(1), "one");
  EXPECT_EQ(intStrMap.at(2), "two");
  EXPECT_EQ(intStrMap.at(3), "three");

  // Test case with string keys and integer values
  s21::Map<std::string, int> strIntMap = {{"one", 1}, {"two", 2}, {"three", 3}};

  EXPECT_EQ(strIntMap.size(), 3u);
  EXPECT_EQ(strIntMap.at("one"), 1);
  EXPECT_EQ(strIntMap.at("two"), 2);
  EXPECT_EQ(strIntMap.at("three"), 3);
}

TEST(MapAccessorTest, AccessExistingKey) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(myMap[1], "one");
}

TEST(MapAccessorTest, AccessNonExistingKey) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(myMap[4], "");
}

TEST(MapAccessorTest, ModifyExistingKey) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  myMap[1] = "ONE";
  EXPECT_EQ(myMap[1], "ONE");
}

TEST(MapAccessorTest, AddNewKey) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  myMap[4] = "four";
  EXPECT_EQ(myMap[4], "four");
}

TEST(MapAccessorTest, DefaultValueForNewKey) {
  s21::Map<int, std::string> myMap;
  EXPECT_EQ(myMap[1], "");
}

TEST(MapModifierTest, InsertExistingKey) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto result = myMap.insert({2, "new_two"});
  EXPECT_EQ(result.second, false);
  EXPECT_EQ(myMap.at(2), "two");
}

TEST(MapModifierTest, InsertNewKey) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto result = myMap.insert({4, "four"});
  EXPECT_EQ(result.second, true);
  EXPECT_EQ(myMap.at(4), "four");
  EXPECT_EQ(myMap.size(), 4u);
}

TEST(MapModifierTest, InsertOrAssignExistingKey) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto result = myMap.insert_or_assign(2, "new_two");
  EXPECT_EQ(result.second, false);
  EXPECT_EQ(myMap.at(2), "new_two");
}

TEST(MapModifierTest, InsertOrAssignNewKey) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto result = myMap.insert_or_assign(4, "four");
  EXPECT_EQ(result.second, true);
  EXPECT_EQ(myMap[4], "four");
  EXPECT_EQ(myMap.size(), 4u);
}

TEST(SwapTest, SwapMaps) {
  s21::Map<int, std::string> myMap1 = {{1, "one"}, {2, "two"}};
  s21::Map<int, std::string> myMap2 = {{3, "three"}, {4, "four"}};

  auto size1_before = myMap1.size();
  auto size2_before = myMap2.size();

  myMap1.swap(myMap2);

  EXPECT_EQ(myMap1.size(), size2_before);
  EXPECT_EQ(myMap2.size(), size1_before);
}

TEST(MergeTest, MergeMaps) {
  s21::Map<int, std::string> myMap1 = {{1, "one"}, {2, "two"}};
  s21::Map<int, std::string> myMap2 = {{3, "three"}, {4, "four"}};

  auto size1_before = myMap1.size();
  auto size2_before = myMap2.size();

  myMap1.merge(myMap2);

  EXPECT_EQ(myMap1.size(), size1_before + size2_before);
  EXPECT_EQ(myMap2.size(), 0u);
}

TEST(MoveAssignmentTest, MoveAssignmentOperator) {
  s21::Map<int, std::string> originalMap = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  std::size_t originalSize = originalMap.size();

  s21::Map<int, std::string> movedMap;
  movedMap = std::move(originalMap);

  EXPECT_EQ(movedMap.size(), originalSize);
  EXPECT_EQ(originalMap.size(), 0u);
  EXPECT_EQ(movedMap.at(1), "one");
  EXPECT_EQ(movedMap.at(2), "two");
  EXPECT_EQ(movedMap.at(3), "three");
}

TEST(CopyAssignmentTest, CopyAssignmentOperator) {
  s21::Map<int, std::string> originalMap = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  std::size_t originalSize = originalMap.size();
  s21::Map<int, std::string> copiedMap;
  copiedMap = originalMap;

  EXPECT_EQ(copiedMap.size(), originalSize);
  EXPECT_EQ(copiedMap.at(1), "one");
  EXPECT_EQ(copiedMap.at(2), "two");
  EXPECT_EQ(copiedMap.at(3), "three");
  EXPECT_EQ(originalMap.size(), originalSize);
  EXPECT_EQ(originalMap.at(1), "one");
  EXPECT_EQ(originalMap.at(2), "two");
  EXPECT_EQ(originalMap.at(3), "three");
}

TEST(IteratorTest, BeginMethod) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = myMap.begin();
  EXPECT_EQ(it.node()->key_, 1);
  EXPECT_EQ(it.node()->value_, "one");
}

TEST(IteratorTest, CBeginMethod) {
  const s21::Map<int, std::string> myMap = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  auto it = myMap.cbegin();
  EXPECT_EQ(it.node()->key_, 1);
  EXPECT_EQ(it.node()->value_, "one");
}

TEST(IteratorTest, CEndMethod) {
  const s21::Map<int, std::string> myMap = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  auto it = myMap.cend();
  EXPECT_EQ(it, myMap.cend());
}

TEST(MapAtTest, ThrowExceptionForMissingKey) {
  s21::Map<int, std::string> myMap;
  myMap.insert({1, "one"});
  myMap.insert({2, "two"});
  myMap.insert({3, "three"});

  EXPECT_THROW(myMap.at(4), std::out_of_range);
  EXPECT_THROW(myMap.at(0), std::out_of_range);
}

TEST(MapTest, Contains) {
  s21::Map<int, std::string> Map;

  Map.insert({1, "One"});
  Map.insert({2, "Two"});
  Map.insert({3, "Three"});

  EXPECT_TRUE(Map.contains(1));
  EXPECT_TRUE(Map.contains(2));
  EXPECT_TRUE(Map.contains(3));

  EXPECT_FALSE(Map.contains(0));
  EXPECT_FALSE(Map.contains(4));
}

TEST(CapacityTest, EmptyMap) {
  s21::Map<int, std::string> myMap;
  EXPECT_TRUE(myMap.empty());
}

TEST(CapacityTest, NonEmptyMap) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_FALSE(myMap.empty());
}

TEST(CapacityTest, EmptyAfterClear) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  myMap.~Map();
  EXPECT_TRUE(myMap.empty());
}

TEST(CapacityTest, NonEmptyAfterErase) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = myMap.begin();
  myMap.erase(it);
  EXPECT_FALSE(myMap.empty());
}

TEST(CapacityTest, NonEmptyAfterErase2) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = myMap.begin();
  ++it;
  myMap.erase(it);
  EXPECT_FALSE(myMap.empty());
}

TEST(CapacityTest, NonEmptyAfterErase3) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = myMap.begin();
  ++it;
  ++it;
  myMap.erase(it);
  EXPECT_FALSE(myMap.empty());
}

TEST(CapacityTest, NonEmptyAfterErase4) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = myMap.begin();
  ++it;
  ++it;
  ++it;
  myMap.erase(it);
  EXPECT_FALSE(myMap.empty());
}

TEST(MapComparisonTest, Erase) {
  s21::Map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::Map<int, std::string> myMap2 = {{1, "one"}, {2, "two"}, {3, "three"}};

  auto it = myMap.begin();
  ++it;

  auto it2 = myMap2.begin();
  ++it2;

  myMap.erase(it);
  myMap2.erase(it2);

  EXPECT_EQ(myMap.size(), myMap2.size());
  EXPECT_TRUE(std::equal(myMap.begin(), myMap.end(), myMap2.begin()));
}

TEST(MapInsertTest, InsertKeyValue) {
  s21::Map<int, std::string> myMap;

  auto result1 = myMap.insert(1, "one");
  auto result2 = myMap.insert(2, "two");
  auto result3 = myMap.insert(3, "three");

  EXPECT_TRUE(result1.second);
  EXPECT_TRUE(result2.second);
  EXPECT_TRUE(result3.second);

  EXPECT_EQ(myMap.at(1), "one");
  EXPECT_EQ(myMap.at(2), "two");
  EXPECT_EQ(myMap.at(3), "three");

  auto result4 = myMap.insert(2, "duplicate");

  EXPECT_FALSE(result4.second);

  EXPECT_EQ(myMap.at(2), "two");
}
