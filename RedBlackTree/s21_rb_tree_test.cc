#include "gtest/gtest.h"
#include "rb_tree.h"

// Test the default constructor
TEST(RedBlackTreeTest, DefaultConstructor) {
  s21::RedBlackTree<int, char> tree;
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0u);
}

// Test the initializer_list constructor with keys
TEST(RedBlackTreeTest, InitializerListConstructor_Keys) {
  s21::RedBlackTree<int, char> tree{1, 2, 3, 4, 5};
  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(), 5u);
}

// Test the initializer_list constructor with key-value pairs
TEST(RedBlackTreeTest, InitializerListConstructor_KeyValuePairs) {
  s21::RedBlackTree<int, char> tree = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(), 3u);
}

// Test copy constructor
TEST(RedBlackTreeTest, CopyConstructor) {
  s21::RedBlackTree<int, char> original_tree{1, 2, 3};
  s21::RedBlackTree<int, char> tree_copy(original_tree);
  EXPECT_EQ(original_tree.size(), tree_copy.size());
}

// Test move constructor
TEST(RedBlackTreeTest, MoveConstructor) {
  s21::RedBlackTree<int, char> original_tree{1, 2, 3};
  s21::RedBlackTree<int, char> tree_move(std::move(original_tree));
  EXPECT_EQ(original_tree.size(), 0u);
}

// Test copy assignment operator
TEST(RedBlackTreeTest, CopyAssignmentOperator) {
  s21::RedBlackTree<int, char> original_tree{1, 2, 3};
  s21::RedBlackTree<int, char> tree_copy = original_tree;
  EXPECT_EQ(original_tree.size(), tree_copy.size());
}

// Test move assignment operator
TEST(RedBlackTreeTest, MoveAssignmentOperator) {
  s21::RedBlackTree<int, char> original_tree{1, 2, 3};
  s21::RedBlackTree<int, char> tree_move;
  tree_move = std::move(original_tree);
  EXPECT_EQ(original_tree.size(), 0u);
}

// Test insert method
TEST(RedBlackTreeTest, Insert) {
  s21::RedBlackTree<int, char> tree;
  auto result = tree.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first.key(), 1);
}

// Test erase method
TEST(RedBlackTreeTest, Erase) {
  s21::RedBlackTree<int, char> tree{1, 2, 3};
  auto result = tree.erase(2);
  EXPECT_EQ(result, 1u);
}

// Test find method
TEST(RedBlackTreeTest, Find) {
  s21::RedBlackTree<int, char> tree{1, 2, 3};
  auto it = tree.find(2);
  EXPECT_NE(it, tree.end());
  EXPECT_EQ(it.key(), 2);
}

// Test contains method
TEST(RedBlackTreeTest, Contains) {
  s21::RedBlackTree<int, char> tree{1, 2, 3};
  EXPECT_TRUE(tree.contains(2));
  EXPECT_FALSE(tree.contains(4));
}

// Test clear method
TEST(RedBlackTreeTest, Clear) {
  s21::RedBlackTree<int, char> tree{1, 2, 3};
  tree.clear();
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0u);
}

TEST(RedBlackTreeTest, Swap) {
  s21::RedBlackTree<int, char> tree1{1, 2, 3};
  s21::RedBlackTree<int, char> tree2{4, 5, 6};
  tree1.swap(tree2);
  EXPECT_EQ(tree1.size(), 3u);
  EXPECT_EQ(tree2.size(), 3u);
}

TEST(RedBlackTreeTest, Merge) {
  s21::RedBlackTree<int, char> tree1{1, 2, 3};
  s21::RedBlackTree<int, char> tree2{4, 5, 6};
  tree1.merge(tree2);
  EXPECT_EQ(tree1.size(), 6u);
  EXPECT_TRUE(tree2.empty());
}

TEST(RedBlackTreeTest, Iterators) {
  s21::RedBlackTree<int, char> tree{1, 2, 3};
  auto it = tree.begin();
  EXPECT_EQ(it.key(), 1);
  ++it;
  EXPECT_EQ(it.key(), 2);
}

TEST(RedBlackTreeTest, Empty) {
  s21::RedBlackTree<int, char> empty_tree;
  s21::RedBlackTree<int, char> non_empty_tree{1, 2, 3};
  EXPECT_TRUE(empty_tree.empty());
  EXPECT_FALSE(non_empty_tree.empty());
}

TEST(RedBlackTreeTest, CopyAssignmentOperator2) {
  s21::RedBlackTree<int, char> original_tree{1, 2, 3};
  s21::RedBlackTree<int, char> tree_copy;
  tree_copy = original_tree;

  EXPECT_EQ(original_tree.size(), tree_copy.size());
  EXPECT_TRUE(std::equal(original_tree.begin(), original_tree.end(),
                         tree_copy.begin()));

  original_tree.insert(4);
  EXPECT_NE(original_tree.size(), tree_copy.size());
}

TEST(RedBlackTreeTest, EraseFromNonEmptyTree) {
  s21::RedBlackTree<int, char> tree{1, 2, 3};
  auto it = tree.find(2);
  ASSERT_NE(it, tree.end());
  tree.erase(it);
  EXPECT_EQ(tree.size(), 2u);
  EXPECT_FALSE(tree.contains(2));
}

TEST(RedBlackTreeTest, EraseLastElement) {
  s21::RedBlackTree<int, char> tree{1};
  auto it = tree.begin();
  tree.erase(it);
  EXPECT_EQ(tree.size(), 0u);
  EXPECT_TRUE(tree.empty());
}

TEST(RedBlackTreeTest, EraseFirstElement) {
  s21::RedBlackTree<int, char> tree{1, 2, 3};
  auto it = tree.begin();
  tree.erase(it);
  EXPECT_EQ(tree.size(), 2u);
  EXPECT_FALSE(tree.contains(1));
}

TEST(RedBlackTreeTest, EraseAndCheckStructure) {
  s21::RedBlackTree<int, char> tree{1, 2, 3};
  auto it = tree.find(2);
  tree.erase(it);
}

TEST(RedBlackTreeTest, EraseMultipleAndCheckStructure) {
  s21::RedBlackTree<int, char> tree{1, 2, 3, 4, 5};
  tree.erase(tree.begin());
  tree.erase(--tree.end());
}

TEST(RedBlackTreeTest, Erase_BalancedNodeRightRed) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({12, 'F'});
  tree.insert({18, 'G'});

  auto it = tree.find(5);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(5));
}

TEST(RedBlackTreeTest, Erase_UnbalancedNodeLeftRed) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({12, 'F'});
  tree.insert({18, 'G'});
  tree.insert({7, 'H'});

  auto it = tree.find(5);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 7u);
  EXPECT_FALSE(tree.contains(5));
}

TEST(RedBlackTreeTest, Erase_UnbalancedRightChildRed) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({12, 'F'});
  tree.insert({18, 'G'});
  tree.insert({7, 'H'});

  auto erasedNode = tree.erase(5);

  EXPECT_EQ(tree.size(), 7u);
  EXPECT_EQ(erasedNode, 1u);
}

TEST(RedBlackTreeTest, Erase_BalancedRightChildToRed2) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({12, 'F'});
  tree.insert({18, 'G'});

  auto erasedNode = tree.erase(3);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_EQ(erasedNode, 1u);
}

TEST(RedBlackTreeTest, Merge_MoveAssignment) {
  s21::RedBlackTree<int, char> tree1{1, 2, 3};
  s21::RedBlackTree<int, char> tree2{4, 5, 6};

  tree1.merge(tree2);

  EXPECT_EQ(tree1.size(), 6u);
  EXPECT_TRUE(tree2.empty());
}

TEST(RedBlackTreeTest, Merge_MoveAssignment2) {
  s21::RedBlackTree<int, char> tree1{1, 2, 3};
  s21::RedBlackTree<int, char> tree2{4, 5, 6};

  tree1.merge(tree2);

  EXPECT_EQ(tree1.size(), 6u);
  EXPECT_TRUE(tree2.empty());

  for (const auto& element : {4, 5, 6}) {
    EXPECT_TRUE(tree1.contains(element));
  }
}

TEST(RedBlackTreeTest, TreeIteratorStepBackward) {
  s21::RedBlackTree<int, char> tree{3, 1, 5, 2, 4};
  auto it = tree.find(4);
  --it;
  EXPECT_EQ(it.key(), 3);
}

TEST(RedBlackTreeTest, Erase_BalancedNodeRightRed_DifferentData) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({20, 'A'});
  tree.insert({10, 'B'});
  tree.insert({25, 'C'});
  tree.insert({5, 'D'});
  tree.insert({15, 'E'});
  tree.insert({22, 'F'});
  tree.insert({30, 'G'});

  auto it = tree.find(10);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(10));
}

TEST(RedBlackTreeTest, Erase_BalancedNodeTwoRedChildren) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({12, 'F'});
  tree.insert({18, 'G'});

  auto it = tree.find(5);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(5));
}

TEST(RedBlackTreeTest, Erase_BalancedRoot) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});

  auto it = tree.find(10);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 2u);
  EXPECT_FALSE(tree.contains(10));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedChild) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});

  auto it = tree.find(5);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 4u);
  EXPECT_FALSE(tree.contains(5));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedSibling) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});

  auto it = tree.find(5);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 5u);
  EXPECT_FALSE(tree.contains(5));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedSibling_LeftChildRed) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});

  auto it = tree.find(5);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(5));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedSibling_RightChildRed) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({20, 'G'});

  auto it = tree.find(5);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(5));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedSibling_BothChildrenBlack) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({20, 'G'});

  auto it = tree.find(3);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(3));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedSibling_RightChildBlack) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({20, 'G'});

  auto it = tree.find(18);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(18));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedSibling_LeftChildBlack) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({20, 'G'});

  auto it = tree.find(8);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(8));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedSibling_BothChildrenRed) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({20, 'G'});

  auto it = tree.find(15);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(15));
}

TEST(RedBlackTreeTest, Erase_BalancedBlackNodeRedSibling_RightChildRed2) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});

  auto it = tree.find(8);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 5u);
  EXPECT_FALSE(tree.contains(8));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_RightChildBlack_LeftChildRed) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});

  auto it = tree.find(8);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(8));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_RightChildBlack_LeftChildBlack) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});

  auto it = tree.find(8);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 5u);
  EXPECT_FALSE(tree.contains(8));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_LeftChildBlack_RightChildRed) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});

  auto it = tree.find(8);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 6u);
  EXPECT_FALSE(tree.contains(8));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_LeftChildBlack_RightChildRed9) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});
  tree.insert({20, 'H'});
  tree.insert({17, 'I'});

  auto it = tree.find(5);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 8u);
  EXPECT_FALSE(tree.contains(5));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_LeftChildBlack_RightChildRed7) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});
  tree.insert({20, 'H'});
  tree.insert({13, 'J'});
  tree.insert({2, 'K'});
  tree.insert({7, 'L'});
  tree.insert({21, 'M'});

  auto it = tree.find(3);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 11u);
  EXPECT_FALSE(tree.contains(3));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_LeftChildBlack_RightChildRed6) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});
  tree.insert({20, 'H'});
  tree.insert({13, 'J'});
  tree.insert({2, 'K'});
  tree.insert({7, 'L'});
  tree.insert({21, 'M'});
  tree.insert({19, 'N'});

  auto it = tree.find(21);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 12u);
  EXPECT_FALSE(tree.contains(21));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_LeftChildBlack_RightChildRed5) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});
  tree.insert({20, 'H'});
  tree.insert({13, 'J'});
  tree.insert({2, 'K'});
  tree.insert({7, 'L'});
  tree.insert({21, 'M'});
  tree.insert({19, 'N'});
  tree.insert({9, 'O'});
  tree.insert({11, 'P'});
  tree.insert({14, 'Q'});
  tree.insert({16, 'R'});

  auto it = tree.find(20);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 16u);
  EXPECT_FALSE(tree.contains(20));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_LeftChildBlack_RightChildRed4) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});
  tree.insert({20, 'H'});
  tree.insert({13, 'J'});
  tree.insert({2, 'K'});
  tree.insert({7, 'L'});
  tree.insert({21, 'M'});
  tree.insert({19, 'N'});
  tree.insert({9, 'O'});
  tree.insert({11, 'P'});
  tree.insert({14, 'Q'});
  tree.insert({16, 'R'});
  tree.insert({1, 'S'});

  auto it = tree.find(2);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 17u);
  EXPECT_FALSE(tree.contains(2));
}

TEST(RedBlackTreeTest,
     Erase_BalancedBlackNodeRedSibling_LeftChildBlack_RightChildRed3) {
  s21::RedBlackTree<int, char> tree;
  tree.insert({10, 'A'});
  tree.insert({5, 'B'});
  tree.insert({15, 'C'});
  tree.insert({3, 'D'});
  tree.insert({8, 'E'});
  tree.insert({18, 'F'});
  tree.insert({12, 'G'});
  tree.insert({20, 'H'});
  tree.insert({13, 'J'});
  tree.insert({2, 'K'});
  tree.insert({7, 'L'});
  tree.insert({21, 'M'});
  tree.insert({19, 'N'});
  tree.insert({9, 'O'});
  tree.insert({11, 'P'});
  tree.insert({14, 'Q'});
  tree.insert({16, 'R'});
  tree.insert({1, 'S'});

  auto it = tree.find(20);
  ASSERT_NE(it, tree.end());
  tree.erase(it);

  EXPECT_EQ(tree.size(), 17u);
  EXPECT_FALSE(tree.contains(20));
}

TEST(RedBlackTreeTest, IteratorTest) {
  s21::RedBlackTree<int, char> tree{1, 2, 3, 7, 78, 4, 9, 0};
  auto it = tree.begin();
  ++it;
  --it;
  EXPECT_EQ(*it, 0);
}

TEST(RedBlackTreeTest, MaxTest) {
  s21::RedBlackTree<int, char> tree{1, 2, 3, 7, 78, 4, 9, 0};
  auto it = tree.max();
  EXPECT_EQ(*it, 78);
}

TEST(RedBlackTreeTest, AdvanceTest) {
  s21::RedBlackTree<int, char> tree{1, 2, 3, 7, 78, 4, 9, 0};
  auto it = tree.root();
  std::advance(it, 4);
  EXPECT_EQ(*it, 9);
  std::advance(it, -3);
  EXPECT_EQ(*it, 3);
}

TEST(RedBlackTreeTest, DeletionTest) {
  s21::RedBlackTree<int, char> tree{12, 8, 15, 5, 9, 13, 19, 10, 23};
  tree.erase(8);
  EXPECT_FALSE(tree.contains(8));
}

TEST(RedBlackTreeTest, DeletionTest2) {
  s21::RedBlackTree<int, char> tree{50, 25, 80, 5,  35, 60, 90,
                                    45, 56, 65, 95, 63, 58, 54};
  tree.erase(58);
  EXPECT_FALSE(tree.contains(58));
}

TEST(RedBlackTreeTest, InsertionTest) {
  s21::RedBlackTree<int, char> tree{1, 2, 3, 7, 78, 4, 9, 0};
  auto res = tree.insert(1);
  EXPECT_EQ(tree.end(), res.first);
  EXPECT_FALSE(res.second);
}

TEST(RedBlackTreeTest, MergeTest) {
  s21::RedBlackTree<int, char> tree{1, 2, 3, 7, 78, 4, 9, 0};
  s21::RedBlackTree<int, char> tree2{12, 8, 15, 5, 9, 13, 19, 10, 23};
  tree.merge(tree2);
  EXPECT_EQ(tree.size(), 16u);
}
