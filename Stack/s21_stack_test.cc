#include "s21_stack.h"

#include <gtest/gtest.h>

#include <iostream>
#include <stack>

TEST(TestConstructor, ConstructorDefault) {
  s21::Stack<size_t> s;
  std::stack<size_t> o;
  ASSERT_EQ(s.size(), o.size());
}

TEST(TestConstructor, ConstructorInit) {
  s21::Stack<size_t> s = {1, 2, 3, 4, 5};
  ASSERT_EQ(s.top(), 5u);
  ASSERT_EQ(s.size(), 5u);
}

TEST(TestConstructor, ConstructorCopy) {
  s21::Stack<size_t> s = {1, 2, 3, 4, 5};
  s21::Stack<size_t> a(s);
  ASSERT_EQ(s.top(), a.top());
  ASSERT_EQ(s.size(), a.size());
}

TEST(TestConstructor, ConstructorMove) {
  std::stack<size_t> s1 = std::stack<size_t>({1, 2, 3, 4, 5});
  std::stack<size_t> a(std::move(s1));
  s21::Stack<size_t> s2 = {1, 2, 3, 4, 5};
  s21::Stack<size_t> b(std::move(s2));
  ASSERT_EQ(a.top(), b.top());
  ASSERT_EQ(a.size(), b.size());
}

TEST(TestConstructor, OperatorEqual) {
  s21::Stack<size_t> a1 = {1, 2, 3, 4, 5};
  s21::Stack<size_t> b1 = {1, 2, 3};
  std::stack<size_t> a2 = std::stack<size_t>({1, 2, 3, 4, 5});
  std::stack<size_t> b2 = std::stack<size_t>({1, 2, 3});
  b1 = std::move(a1);
  b2 = std::move(a2);
  ASSERT_EQ(b1.top(), b2.top());
  ASSERT_EQ(b1.size(), b2.size());
  ASSERT_EQ(a1.size(), a2.size());
}

TEST(TestConstructor, OperatorEqualSecond) {
  s21::Stack<size_t> a1 = {1, 2, 3};
  s21::Stack<size_t> b1 = {1, 2, 3, 4, 5};
  std::stack<size_t> a2 = std::stack<size_t>({1, 2, 3});
  std::stack<size_t> b2 = std::stack<size_t>({1, 2, 3, 4, 5});
  b1 = std::move(a1);
  b2 = std::move(a2);
  ASSERT_EQ(b1.top(), b2.top());
  ASSERT_EQ(b1.size(), b2.size());
  ASSERT_EQ(a1.size(), a2.size());
}

TEST(TestConstructor, OperatorEqualThird) {
  s21::Stack<size_t> a1 = {1, 2, 3, 4, 5};
  s21::Stack<size_t> b1 = {2, 5};
  a1 = b1;
  std::stack<size_t> a2 = std::stack<size_t>({1, 2, 3, 4, 5});
  std::stack<size_t> b2 = std::stack<size_t>({2, 5});
  a2 = b2;
  ASSERT_EQ(a1.top(), a2.top());
  ASSERT_EQ(a1.size(), a2.size());
}

TEST(TestConstructor, OperatorEqualFourth) {
  s21::Stack<size_t> a1 = {2, 5};
  s21::Stack<size_t> b1 = {1, 2, 3, 4, 5};
  a1 = b1;
  std::stack<size_t> a2 = std::stack<size_t>({2, 5});
  std::stack<size_t> b2 = std::stack<size_t>({1, 2, 3, 4, 5});
  a2 = b2;
  ASSERT_EQ(a1.top(), a2.top());
  ASSERT_EQ(a1.size(), a2.size());
}

TEST(TestConstructor, Push) {
  s21::Stack<size_t> a = {1, 2, 3, 4, 5};
  a.push(10);
  std::stack<size_t> b = std::stack<size_t>({1, 2, 3, 4, 5});
  b.push(10);
  ASSERT_EQ(a.top(), b.top());
  ASSERT_EQ(a.size(), b.size());
}

TEST(TestConstructor, Pop) {
  s21::Stack<size_t> a = {1, 2, 3, 4, 5};
  a.pop();
  std::stack<size_t> b = std::stack<size_t>({1, 2, 3, 4, 5});
  b.pop();
  ASSERT_EQ(a.top(), b.top());
  ASSERT_EQ(a.size(), b.size());
}

TEST(TestConstructor, Empty) {
  s21::Stack<size_t> a;
  std::stack<size_t> b;
  ASSERT_EQ(a.empty(), b.empty());
  a = {1, 2, 3, 4, 5};
  b = std::stack<size_t>({1, 2, 3, 4, 5});
  ASSERT_EQ(a.empty(), b.empty());
}

TEST(TestConstructor, Swap) {
  s21::Stack<size_t> a1 = {1, 2, 3};
  s21::Stack<size_t> b1 = {1, 2, 3, 4, 5};
  std::stack<size_t> a2 = std::stack<size_t>({1, 2, 3});
  std::stack<size_t> b2 = std::stack<size_t>({1, 2, 3, 4, 5});
  a1.swap(b1);
  a2.swap(b2);
  ASSERT_EQ(a1.size(), a2.size());
  ASSERT_EQ(b1.size(), b2.size());
  ASSERT_EQ(a1.top(), a2.top());
  ASSERT_EQ(b1.top(), b2.top());
}

TEST(TestConstructor, Size) {
  s21::Stack<size_t> a = {1, 2, 3, 4, 5};
  std::stack<size_t> b = std::stack<size_t>({1, 2, 3, 4, 5});
  ASSERT_EQ(a.size(), b.size());
}

TEST(TestConstructor, Top) {
  s21::Stack<size_t> a = {1, 2, 3, 4, 5};
  std::stack<size_t> b = std::stack<size_t>({1, 2, 3, 4, 5});
  ASSERT_EQ(a.top(), b.top());
}

TEST(TestStack, IsEmptyInitially) {
  s21::Stack<int, s21::Vector<int>> stack;
  ASSERT_TRUE(stack.empty());
  ASSERT_EQ(stack.size(), 0u);
}

TEST(TestStack, PushIncreasesSize) {
  s21::Stack<int, s21::Vector<int>> stack;
  stack.push(1);
  ASSERT_FALSE(stack.empty());
  ASSERT_EQ(stack.size(), 1u);
}

TEST(TestStack, PopDecreasesSize) {
  s21::Stack<int, s21::Vector<int>> stack;
  stack.push(1);
  stack.push(2);
  stack.pop();
  ASSERT_EQ(stack.size(), 1u);
}

TEST(TestStack, TopReturnsLastPushedElement) {
  s21::Stack<int, s21::Vector<int>> stack;
  stack.push(1);
  stack.push(2);
  ASSERT_EQ(stack.top(), 2);
}

TEST(TestStack, PopRemovesTopElement) {
  s21::Stack<int, s21::Vector<int>> stack;
  stack.push(1);
  stack.push(2);
  stack.pop();
  ASSERT_EQ(stack.top(), 1);
}

TEST(TestStackSwap, SwapStacksWithVector) {
  s21::Stack<int, s21::Vector<int>> stack1;
  s21::Stack<int, s21::Vector<int>> stack2;

  stack1.push(1);
  stack1.push(2);
  stack2.push(3);
  stack2.push(4);

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 2u);
  EXPECT_EQ(stack2.size(), 2u);
  EXPECT_EQ(stack1.top(), 4);
  EXPECT_EQ(stack2.top(), 2);
}

TEST(TestStackMoveAssignment, MoveAssignmentWithVector) {
  s21::Stack<int, s21::Vector<int>> stack1;
  s21::Stack<int, s21::Vector<int>> stack2;

  stack1.push(1);
  stack1.push(2);
  stack2.push(3);
  stack2.push(4);

  stack1 = std::move(stack2);

  EXPECT_EQ(stack1.size(), 2u);
  EXPECT_EQ(stack2.size(), 0u);
  EXPECT_EQ(stack1.top(), 4);
}

TEST(TestStackCopyAssignment, CopyAssignmentWithVector) {
  s21::Stack<int, s21::Vector<int>> stack1;
  s21::Stack<int, s21::Vector<int>> stack2;

  stack1.push(1);
  stack1.push(2);
  stack2.push(3);
  stack2.push(4);

  stack1 = stack2;

  EXPECT_EQ(stack1.size(), 2u);
  EXPECT_EQ(stack2.size(), 2u);
  EXPECT_EQ(stack1.top(), 4);
}

TEST(TestStackConstructor, DefaultConstructor) {
  s21::Stack<int, s21::Vector<int>> stack;
  EXPECT_EQ(stack.size(), 0u);
  EXPECT_TRUE(stack.empty());
}

TEST(TestStackConstructor, InitializerListConstructor) {
  s21::Stack<int, s21::Vector<int>> stack = {1, 2, 3, 4, 5};
  EXPECT_EQ(stack.size(), 5u);
  EXPECT_EQ(stack.top(), 5);
}

TEST(TestStackConstructor, CopyConstructor) {
  s21::Stack<int, s21::Vector<int>> original = {1, 2, 3};
  s21::Stack<int, s21::Vector<int>> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.top(), original.top());
}

TEST(TestStackConstructor, MoveConstructor) {
  s21::Stack<int, s21::Vector<int>> original = {1, 2, 3};
  s21::Stack<int, s21::Vector<int>> moved(std::move(original));

  EXPECT_EQ(moved.size(), 3u);
  EXPECT_EQ(moved.top(), 3);
  EXPECT_EQ(original.size(), 0u);
}

TEST(TestStackDestructor, Destructor) {
  s21::Stack<int, s21::Vector<int>>* stack =
      new s21::Stack<int, s21::Vector<int>>{1, 2, 3};
  delete stack;
  EXPECT_TRUE(true);
}

TEST(TestStackMoveAssignment, MoveAssignment) {
  s21::Stack<int, s21::Vector<int>> original = {1, 2, 3};
  s21::Stack<int, s21::Vector<int>> stack;
  stack = std::move(original);

  EXPECT_EQ(stack.size(), 3u);
  EXPECT_EQ(stack.top(), 3);
  EXPECT_EQ(original.size(), 0u);
}

TEST(TestStackCopyAssignment, CopyAssignment) {
  s21::Stack<int, s21::Vector<int>> original = {1, 2, 3};
  s21::Stack<int, s21::Vector<int>> stack;
  stack = original;

  EXPECT_EQ(stack.size(), original.size());
  EXPECT_EQ(stack.top(), original.top());
}

TEST(TestStackString, IsEmptyInitially) {
  s21::Stack<std::string, s21::Vector<std::string>> stack;
  ASSERT_TRUE(stack.empty());
  ASSERT_EQ(stack.size(), 0u);
}

TEST(TestStackString, PushIncreasesSize) {
  s21::Stack<std::string, s21::Vector<std::string>> stack;
  stack.push("One");
  ASSERT_FALSE(stack.empty());
  ASSERT_EQ(stack.size(), 1u);
}

TEST(TestStackString, PopDecreasesSize) {
  s21::Stack<std::string, s21::Vector<std::string>> stack;
  stack.push("One");
  stack.push("Two");
  stack.pop();
  ASSERT_EQ(stack.size(), 1u);
}

TEST(TestStackString, TopReturnsLastPushedElement) {
  s21::Stack<std::string, s21::Vector<std::string>> stack;
  stack.push("One");
  stack.push("Two");
  ASSERT_EQ(stack.top(), "Two");
}

TEST(TestStackString, PopRemovesTopElement) {
  s21::Stack<std::string, s21::Vector<std::string>> stack;
  stack.push("One");
  stack.push("Two");
  stack.pop();
  ASSERT_EQ(stack.top(), "One");
}

TEST(TestStackStringSwap, SwapStacksWithVector) {
  s21::Stack<std::string, s21::Vector<std::string>> stack1;
  s21::Stack<std::string, s21::Vector<std::string>> stack2;

  stack1.push("One");
  stack1.push("Two");
  stack2.push("Three");
  stack2.push("Four");

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 2u);
  EXPECT_EQ(stack2.size(), 2u);
  EXPECT_EQ(stack1.top(), "Four");
  EXPECT_EQ(stack2.top(), "Two");
}

TEST(TestStackStringMoveAssignment, MoveAssignmentWithVector) {
  s21::Stack<std::string, s21::Vector<std::string>> stack1;
  s21::Stack<std::string, s21::Vector<std::string>> stack2;

  stack1.push("One");
  stack1.push("Two");
  stack2.push("Three");
  stack2.push("Four");

  stack1 = std::move(stack2);

  EXPECT_EQ(stack1.size(), 2u);
  EXPECT_EQ(stack2.size(), 0u);
  EXPECT_EQ(stack1.top(), "Four");
}

TEST(TestStackStringCopyAssignment, CopyAssignmentWithVector) {
  s21::Stack<std::string, s21::Vector<std::string>> stack1;
  s21::Stack<std::string, s21::Vector<std::string>> stack2;

  stack1.push("One");
  stack1.push("Two");
  stack2.push("Three");
  stack2.push("Four");

  stack1 = stack2;

  EXPECT_EQ(stack1.size(), 2u);
  EXPECT_EQ(stack2.size(), 2u);
  EXPECT_EQ(stack1.top(), "Four");
}

TEST(TestStackStringConstructor, DefaultConstructor) {
  s21::Stack<std::string, s21::Vector<std::string>> stack;
  EXPECT_EQ(stack.size(), 0u);
  EXPECT_TRUE(stack.empty());
}

TEST(TestStackStringConstructor, InitializerListConstructor) {
  s21::Stack<std::string, s21::Vector<std::string>> stack = {
      "One", "Two", "Three", "Four", "Five"};
  EXPECT_EQ(stack.size(), 5u);
  EXPECT_EQ(stack.top(), "Five");
}

TEST(TestStackStringConstructor, CopyConstructor) {
  s21::Stack<std::string, s21::Vector<std::string>> original = {"One", "Two",
                                                                "Three"};
  s21::Stack<std::string, s21::Vector<std::string>> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.top(), original.top());
}

TEST(TestStackStringConstructor, MoveConstructor) {
  s21::Stack<std::string, s21::Vector<std::string>> original = {"One", "Two",
                                                                "Three"};
  s21::Stack<std::string, s21::Vector<std::string>> moved(std::move(original));

  EXPECT_EQ(moved.size(), 3u);
  EXPECT_EQ(moved.top(), "Three");
  EXPECT_EQ(original.size(), 0u);
}

TEST(TestStackStringDestructor, Destructor) {
  s21::Stack<std::string, s21::Vector<std::string>>* stack =
      new s21::Stack<std::string, s21::Vector<std::string>>{"One", "Two",
                                                            "Three"};
  delete stack;
  EXPECT_TRUE(true);
}

TEST(TestStackStringMoveAssignment, MoveAssignment) {
  s21::Stack<std::string, s21::Vector<std::string>> original = {"One", "Two",
                                                                "Three"};
  s21::Stack<std::string, s21::Vector<std::string>> stack;
  stack = std::move(original);

  EXPECT_EQ(stack.size(), 3u);
  EXPECT_EQ(stack.top(), "Three");
  EXPECT_EQ(original.size(), 0u);
}

TEST(TestStackStringCopyAssignment, CopyAssignment) {
  s21::Stack<std::string, s21::Vector<std::string>> original = {"One", "Two",
                                                                "Three"};
  s21::Stack<std::string, s21::Vector<std::string>> stack;
  stack = original;

  EXPECT_EQ(stack.size(), original.size());
  EXPECT_EQ(stack.top(), original.top());
}
