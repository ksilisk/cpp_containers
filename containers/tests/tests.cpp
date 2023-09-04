#include "tests.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <type_traits>
#include <vector>

using namespace s21;

TEST(VECTOR_CONSTRUCTOR_TESTS, DEFAULT_CONSTRUCTOR_TEST) {
  vector<int> vec;
  EXPECT_EQ(vec.size(), static_cast<size_t>(0));
  EXPECT_EQ(vec.capacity(), DEFAULT_CAPACITY * FACTOR);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, CONSTRUCTOR_WITH_SIZE) {
  vector<int> vec2(50);

  EXPECT_EQ(vec2.size(), static_cast<size_t>(0));
  EXPECT_EQ(vec2.capacity(), 50 * FACTOR);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, CONSTRUCT_WITH_FILL_ELEMENTS) {
  vector<int> vec2(50, 50);

  EXPECT_EQ(vec2.size(), static_cast<size_t>(50));
  EXPECT_EQ(vec2.capacity(), 50 * FACTOR);
  EXPECT_EQ(vec2.at(45), 50);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, INITIALIZER_CONSTRUCTOR) {
  vector<int> vec = {1, 2, 3, 4};
  std::vector<int> vec2 = {1, 2, 3, 4};

  EXPECT_EQ(vec.size(), static_cast<size_t>(4));
  EXPECT_EQ(vec.capacity(), 4 * FACTOR);

  auto res1 = std::equal(vec.begin(), vec.end(), vec2.begin());
  ASSERT_EQ(res1, true);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, ITERATOR_CONSTRUCTOR) {
  vector<int> vec = {1, 2, 3, 4, 5};

  vector vec3(vec.begin(), vec.end());

  EXPECT_EQ(vec3.size(), static_cast<size_t>(5));
  EXPECT_EQ(vec3.capacity(), static_cast<size_t>(10));
}

TEST(VECTOR_CONSTRUCTOR_TESTS, COPY_CONSTRUCTOR_AND_OPERATOR) {
  ::Test l(43);
  vector<::Test> test{::Test(1), l};
  decltype(test) test2;

  test2 = test;

  ASSERT_EQ(test[0].a, 1);
  ASSERT_EQ(test[1].a, 43);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, MOVE_CONSTRUCTOR_AND_OPERATOR) {
  vector<int> test(vector<int>(10, 5));

  test = vector(vector({1, 2, 3, 4, 5}));

  ASSERT_EQ(test[4], 5);
}

TEST(VECTOR_FUNCTION_TESTS, INDEX_OPERATOR_TEST) {
  vector<int> vec = {1, 2, 3, 4, 5, 6};

  EXPECT_THROW(vec[75], std::out_of_range);
  ASSERT_EQ(vec[4], 5);
}

TEST(VECTOR_FUNCTION_TESTS, METHOD_AT_TEST) {
  vector<int> vec = {1, 2, 3, 4, 5, 6};

  EXPECT_THROW(vec.at(75), std::out_of_range);
  ASSERT_EQ(vec.at(3), 4);
}

TEST(VECTOR_FUNCTION_TESTS, METHOD_FILL_TEST) {
  vector<int> vec(10);
  vec.fill(3);

  std::for_each(vec.begin(), vec.end(), [](auto elem) { ASSERT_EQ(elem, 3); });
}

TEST(VECTOR_FUNCTION_TESTS, METHOD_CLEAR_TEST) {
  vector<::Test> vec;
  vec.push_back(::Test(4));
  vec.push_back(::Test(6));
  vec.clear();

  ASSERT_EQ(vec.size(), static_cast<size_t>(0));
}

TEST(MapConstructor, Default) {
  s21::Map<std::string, int> s;
  std::map<std::string, int> b;

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(MapIterator,
     initializer_List_operator_dereferencing_plusplus_minusminus_begin_end) {
  s21::Map<int, std::string> s = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};

  std::map<int, std::string> b = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};

  auto si = s.begin();
  auto bi = b.begin();
  for (; si != s.end() && bi != b.end(); ++si, ++bi) {
    EXPECT_EQ((*si).first, (*bi).first);
    EXPECT_EQ((*si).second, (*bi).second);
  }

  si = s.end();
  bi = b.end();
  -- --si;
  -- --bi;
  EXPECT_EQ((*si).first, (*bi).first);
  EXPECT_EQ((*si).second, (*bi).second);

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(MapConstructors, Copy) {
  s21::Map<int, std::string> s_tree = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
  s21::Map<int, std::string> &cp_s_tree(s_tree);

  std::map<int, std::string> o_tree = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
  std::map<int, std::string> cp_o_tree = o_tree;

  auto si = cp_s_tree.begin();
  auto oi = cp_o_tree.begin();
  for (; si != cp_s_tree.end() && oi != cp_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(cp_s_tree.size(), cp_o_tree.size());
  EXPECT_EQ(cp_s_tree.empty(), cp_o_tree.empty());
}

TEST(MapConstructors, Move) {
  s21::Map<int, std::string> s_tree = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
  s21::Map<int, std::string> mv_s_tree = std::move(s_tree);

  std::map<int, std::string> o_tree = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
  std::map<int, std::string> mv_o_tree = std::move(o_tree);

  auto si = mv_s_tree.begin();
  auto oi = mv_o_tree.begin();
  for (; si != mv_s_tree.end() && oi != mv_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(mv_s_tree.size(), mv_o_tree.size());
  EXPECT_EQ(mv_s_tree.empty(), mv_o_tree.empty());

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(MapConstructors, Operator_equal) {
  s21::Map<int, int> m1 = {{10, 1}, {20, 2}, {30, 3}, {40, 4},
                           {50, 5}, {60, 6}, {70, 7}};

  s21::Map<int, int> &m2 = m1;

  auto e = m1.end();
  --e;
  auto i = m1.end();
  do {
    ++i;
    EXPECT_EQ((*i).first, (*i).first);
    EXPECT_EQ((*i).second, (*i).second);
  } while (i != e);

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(Modifier, Erase) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();

  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  auto s_it = s_tree.end();
  auto o_it = o_tree.end();
  --s_it;
  --o_it;

  s_tree.erase(s_it);
  o_tree.erase(o_it);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  si = s_tree.begin();
  oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
}

TEST(MapElementAccess, At) {
  s21::Map<std::string, int> m1 = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(0, m1.at("zero"));
  EXPECT_EQ(5, m1.at("five"));
  EXPECT_EQ(8, m1.at("eight"));
  EXPECT_EQ(9, m1.at("nine"));

  // EXPECT_ANY_THROW(m1.at("SSD"));
}

TEST(MapElementAccess, Brackets) {
  s21::Map<std::string, std::string> s_tree = {
      {"CPU", "Intel"}, {"GPU", "Nvidia"}, {"RAM", "64GB"}};

  std::map<std::string, std::string> o_tree = {
      {"CPU", "Intel"}, {"GPU", "Nvidia"}, {"RAM", "64GB"}};

  EXPECT_EQ(s_tree["CPU"], o_tree["CPU"]);
  EXPECT_EQ(s_tree["GPU"], o_tree["GPU"]);
  EXPECT_EQ(s_tree["RAM"], o_tree["RAM"]);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  EXPECT_EQ(s_tree["SSD"], o_tree["SSD"]);
}

TEST(MapLookup, Contains) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.contains("zero"), true);
  EXPECT_EQ(s_tree.contains("seven"), true);
  EXPECT_EQ(s_tree.contains("seventy"), false);
}

TEST(MapModifiers, InsertPair) {
  s21::Map<std::string, int> s_tree
      // ;
      = {{"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
         {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> o_tree
      // ;
      = {{"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
         {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  s_tree.clear();
  o_tree.clear();

  auto s_pr = s_tree.insert({"one", 0});
  auto o_pr = o_tree.insert({"one", 0});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"ten", 10});
  o_pr = o_tree.insert({"ten", 10});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"twelve", 20});
  o_pr = o_tree.insert({"twelve", 20});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"thirty", 30});
  o_pr = o_tree.insert({"thirty", 30});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(MapModifiers, InsertObjects) {
  s21::Map<std::string, int> s_tree;
  std::map<std::string, int> o_tree;

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  s_tree.clear();
  o_tree.clear();

  auto s_pr = s_tree.insert("ten", 10);
  auto o_pr = o_tree.insert({"ten", 10});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert("twelve", 20);
  o_pr = o_tree.insert({"twelve", 20});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert("thirty", 30);
  o_pr = o_tree.insert({"thirty", 30});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(MapModifiers, InsertOrAssign) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto s_pr = s_tree.insert_or_assign("ten", 10);
  auto o_pr = o_tree.insert_or_assign("ten", 10);
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert_or_assign("zero", -1);
  o_pr = o_tree.insert_or_assign("zero", -1);
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert_or_assign("seven", 777);
  o_pr = o_tree.insert_or_assign("seven", 777);
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(Modifiers, Swap) {
  s21::Map<std::string, int> f_s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  s21::Map<std::string, int> s_s_tree = {
      {"ten", 10},   {"twenty", 20}, {"thirty", 30}, {"fourty", 40},
      {"fifty", 50}, {"sixty", 60},  {"seventy", 70}};

  std::map<std::string, int> f_o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> s_o_tree = {
      {"ten", 10},   {"twenty", 20}, {"thirty", 30}, {"fourty", 40},
      {"fifty", 50}, {"sixty", 60},  {"seventy", 70}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  f_s_tree.swap(s_s_tree);
  f_o_tree.swap(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
}

TEST(Modifiers, Merge) {
  s21::Map<int, std::string> m1a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::Map<int, std::string> m1b{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  s21::Map<int, std::string> u1;

  std::map<int, std::string> m2a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  std::map<int, std::string> m2b{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  std::map<int, std::string> u2;
  u1.merge(m1a);
  u2.merge(m2a);

  auto i1 = u1.begin();
  auto i2 = u2.begin();
  for (; i1 != u1.end() && i2 != u2.end(); ++i1, ++i2) {
    EXPECT_EQ((*i1).first, (*i2).first);
    EXPECT_EQ((*i1).second, (*i2).second);
  }

  s21::Map<std::string, int> f_s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  s21::Map<std::string, int> s_s_tree = {
      {"ten", 10},   {"twenty", 20}, {"thirty", 30}, {"fourty", 40},
      {"fifty", 50}, {"sixty", 60},  {"seventy", 70}};

  std::map<std::string, int> f_o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> s_o_tree = {
      {"ten", 10},   {"twenty", 20}, {"thirty", 30}, {"fourty", 40},
      {"fifty", 50}, {"sixty", 60},  {"seventy", 70}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  f_s_tree.merge(s_s_tree);
  f_o_tree.merge(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
}

TEST(MapModifiers, Emplace) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto v = s_tree.emplace(std::pair<std::string, int>{"eleven", 11},
                          std::pair<std::string, int>{"twelve", 12},
                          std::pair<std::string, int>{"nine", 13},
                          std::pair<std::string, int>{"thirteen", 13});

  auto p1 = o_tree.emplace("eleven", 11);
  auto p2 = o_tree.emplace("twelve", 12);
  auto p3 = o_tree.emplace("nine", 13);
  auto p4 = o_tree.emplace("thirteen", 13);

  EXPECT_EQ((*(v[0].first)).first, (*(p1.first)).first);
  EXPECT_EQ((*(v[0].first)).second, (*(p1.first)).second);
  EXPECT_EQ(v[0].second, p1.second);

  EXPECT_EQ((*(v[1].first)).first, (*(p2.first)).first);
  EXPECT_EQ((*(v[1].first)).second, (*(p2.first)).second);
  EXPECT_EQ(v[1].second, p2.second);

  EXPECT_EQ((*(v[2].first)).first, (*(p3.first)).first);
  EXPECT_EQ((*(v[2].first)).second, (*(p3.first)).second);
  EXPECT_EQ(v[2].second, p3.second);

  EXPECT_EQ((*(v[3].first)).first, (*(p4.first)).first);
  EXPECT_EQ((*(v[3].first)).second, (*(p4.first)).second);
  EXPECT_EQ(v[3].second, p4.second);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
}

TEST(SetConstructor, Default) {
  s21::Set<std::string> s;
  std::set<std::string> b;

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(SetIterator,
     initializer_List_operator_dereferencing_plusplus_minusminus_begin_end) {
  s21::Set<int> s = {10, 20, 30, 40, 50, 60, 70};

  std::set<int> b = {10, 20, 30, 40, 50, 60, 70};

  auto si = s.begin();
  auto bi = b.begin();
  for (; si != s.end() && bi != b.end(); ++si, ++bi) {
    EXPECT_EQ((*si), (*bi));
  }

  si = s.end();
  bi = b.end();
  -- --si;
  -- --bi;
  EXPECT_EQ((*si), (*bi));

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(SetConstructors, Copy) {
  s21::Set<int> s_tree = {10, 20, 30, 40, 50, 60, 70};

  s21::Set<int> &cp_s_tree(s_tree);

  std::set<int> o_tree = {10, 20, 30, 40, 50, 60, 70};
  std::set<int> cp_o_tree = o_tree;

  auto si = cp_s_tree.begin();
  auto oi = cp_o_tree.begin();
  for (; si != cp_s_tree.end() && oi != cp_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  EXPECT_EQ(cp_s_tree.size(), cp_o_tree.size());
  EXPECT_EQ(cp_s_tree.empty(), cp_o_tree.empty());
}

TEST(SetConstructors, Move) {
  s21::Set<int> s_tree = {10, 20, 30, 40, 50, 60, 70};
  s21::Set<int> mv_s_tree = std::move(s_tree);

  std::set<int> o_tree = {10, 20, 30, 40, 50, 60, 70};
  std::set<int> mv_o_tree = std::move(o_tree);

  auto si = mv_s_tree.begin();
  auto oi = mv_o_tree.begin();
  for (; si != mv_s_tree.end() && oi != mv_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  EXPECT_EQ(mv_s_tree.size(), mv_o_tree.size());
  EXPECT_EQ(mv_s_tree.empty(), mv_o_tree.empty());

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(SetConstructors, Operator_equal) {
  s21::Set<int> m1 = {10, 20, 30, 40, 50, 60, 70};

  s21::Set<int> &m2 = m1;

  auto e = m1.end();
  --e;
  auto i = m1.end();
  do {
    ++i;
    EXPECT_EQ((*i), (*i));
  } while (i != e);

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(Moifier, Erase) {
  s21::Set<std::string> s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  std::set<std::string> o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  auto s_it = s_tree.end();
  auto o_it = o_tree.end();
  --s_it;
  --o_it;

  s_tree.erase(s_it);
  o_tree.erase(o_it);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  si = s_tree.begin();
  oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(SetLookup, Find) {
  s21::Set<std::string> s1 = {{"zero"},  {"one"},  {"two"}, {"three"},
                              {"four"},  {"five"}, {"six"}, {"seven"},
                              {"eight"}, {"nine"}};

  std::set<std::string> s2 = {{"zero"},  {"one"},  {"two"}, {"three"},
                              {"four"},  {"five"}, {"six"}, {"seven"},
                              {"eight"}, {"nine"}};

  EXPECT_EQ(*s1.find("zero"), *s2.find("zero"));
  EXPECT_EQ(*s1.find("seven"), *s2.find("seven"));
}

TEST(SetLookup, Contains) {
  s21::Set<std::string> s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.contains("zero"), true);
  EXPECT_EQ(s_tree.contains("seven"), true);
  EXPECT_EQ(s_tree.contains("seventy"), false);
}

TEST(SetModifiers, Insert) {
  s21::Set<std::string> s_tree
      // ;
      = {{"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
         {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::set<std::string> o_tree
      // ;
      = {{"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
         {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  s_tree.clear();
  o_tree.clear();

  auto s_pr = s_tree.insert({"one"});
  auto o_pr = o_tree.insert("one");
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"ten", 10});
  o_pr = o_tree.insert({"ten", 10});
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"twelve", 20});
  o_pr = o_tree.insert({"twelve", 20});
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"thirty", 30});
  o_pr = o_tree.insert({"thirty", 30});
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(Modifies, Swap) {
  s21::Set<std::string> f_s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  s21::Set<std::string> s_s_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                    {"fourty"}, {"fifty"},  {"sixty"},
                                    {"seventy"}};

  std::set<std::string> f_o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  std::set<std::string> s_o_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                    {"fourty"}, {"fifty"},  {"sixty"},
                                    {"seventy"}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  f_s_tree.swap(s_s_tree);
  f_o_tree.swap(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(Moifier, Merge) {
  s21::Set<std::string> f_s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  s21::Set<std::string> s_s_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                    {"fourty"}, {"fifty"},  {"sixty"},
                                    {"seventy"}};

  std::set<std::string> f_o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  std::set<std::string> s_o_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                    {"fourty"}, {"fifty"},  {"sixty"},
                                    {"seventy"}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  f_s_tree.merge(s_s_tree);
  f_o_tree.merge(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(SetModifiers, Emplace) {
  s21::Set<std::string> s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  std::set<std::string> o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto v = s_tree.emplace("eleven", "twelve", "nine", "thirteen");

  auto p0 = o_tree.emplace("eleven");
  auto p1 = o_tree.emplace("twelve");
  auto p2 = o_tree.emplace("nine");
  auto p3 = o_tree.emplace("thirteen");

  EXPECT_EQ((*(v[0].first)), (*(p0.first)));
  EXPECT_EQ(v[0].second, p0.second);

  EXPECT_EQ((*(v[1].first)), (*(p1.first)));
  EXPECT_EQ(v[1].second, p1.second);

  EXPECT_EQ((*(v[2].first)), (*(p2.first)));
  EXPECT_EQ(v[2].second, p2.second);

  EXPECT_EQ((*(v[3].first)), (*(p3.first)));
  EXPECT_EQ(v[3].second, p3.second);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(Test_1, constructor_int) {
  s21::stack<int> my_stack = {1, 2};
  std::stack<int> orig_stack;
  orig_stack.push(1);
  orig_stack.push(2);
  EXPECT_EQ(my_stack.top(), orig_stack.top());
}

TEST(Test_1, constructor_float) {
  s21::stack<float> my_stack = {1.5, 2.5};
  std::stack<float> orig_stack;
  orig_stack.push(1.5);
  orig_stack.push(2.5);
  EXPECT_EQ(my_stack.top(), orig_stack.top());
}

TEST(Test_2, copy_arr) {
  s21::stack<float> my_stack = {1.5, 2.5};
  s21::stack<float> copy_stack(my_stack);
  EXPECT_EQ(my_stack.top(), copy_stack.top());
}

TEST(Test_2, copy_operator) {
  s21::stack<int> my_stack = {1, 4, 6, 3, 7};
  s21::stack<int> copy_stack = my_stack;
  EXPECT_EQ(my_stack.top(), copy_stack.top());
}

TEST(Test_3, move_arr) {
  s21::stack<int> my_stack = {1, 4, 6, 3, 7};
  s21::stack<int> move_stack = std::move(my_stack);
  EXPECT_EQ(7, move_stack.top());
}

TEST(Test_4, push) {
  s21::stack<int> my_stack = {1, 4, 6, 3, 7};
  EXPECT_EQ(7, my_stack.top());
  my_stack.push(10);
  EXPECT_EQ(10, my_stack.top());
}

TEST(Test_5, pop) {
  s21::stack<int> my_stack = {1, 4, 6, 3, 7};
  EXPECT_EQ(7, my_stack.top());
  my_stack.pop();
  EXPECT_EQ(3, my_stack.top());
}

TEST(Test_6, empty) {
  s21::stack<int> my_stack = {1, 4, 6, 3, 7};
  s21::stack<int> empty_stack;
  EXPECT_TRUE(empty_stack.empty());
  EXPECT_FALSE(my_stack.empty());
}

TEST(Test_7, size) {
  s21::stack<int> my_stack = {1, 4, 6, 3, 7};
  EXPECT_EQ(my_stack.size(), static_cast<size_t>(5));
  my_stack.push(3);
  EXPECT_EQ(my_stack.size(), static_cast<size_t>(6));
}

TEST(Test_8, swap) {
  s21::stack<int> stack1 = {1, 1, 1, 1, 1};
  s21::stack<int> stack2 = {2, 2, 2, 2, 2};
  EXPECT_EQ(stack2.top(), 2);
  EXPECT_EQ(stack1.top(), 1);
  stack1.swap(stack2);
  EXPECT_EQ(stack1.top(), 2);
  EXPECT_EQ(stack2.top(), 1);
}

TEST(Test_9, full_pop) {
  s21::stack<int> stack1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(stack1.empty());
  const int const_size = stack1.size();
  for (auto i = 0; i < const_size; i++) {
    stack1.pop();
  }
  EXPECT_TRUE(stack1.empty());
}

TEST(Test_10, fill_stack) {
  s21::stack<int> stack1;
  EXPECT_TRUE(stack1.empty());
  for (auto i = 1; i <= 5; i++) {
    stack1.push(i);
  }
  EXPECT_EQ(stack1.top(), 5);
  EXPECT_FALSE(stack1.empty());
}

TEST(Test_12, constructor_int) {
  s21::queue<int> my_queue = {1, 2};
  std::queue<int> or_queue;
  or_queue.push(1);
  or_queue.push(2);
  EXPECT_EQ(my_queue.front(), or_queue.front());
}

TEST(Test_12, constructor_float) {
  s21::queue<float> my_queue = {1.5, 2.5};
  std::queue<float> or_queue;
  or_queue.push(1.5);
  or_queue.push(2.5);
  EXPECT_EQ(my_queue.front(), or_queue.front());
  EXPECT_EQ(my_queue.back(), or_queue.back());
}

TEST(Test_22, copy_arr) {
  s21::queue<float> my_queue = {1.5, 2.5};
  s21::queue<float> copy_queue(my_queue);
  EXPECT_EQ(my_queue.front(), copy_queue.front());
  EXPECT_EQ(my_queue.back(), copy_queue.back());
}

TEST(Test_22, copy_operator) {
  s21::queue<int> my_queue = {1, 4, 6, 3, 7};
  s21::queue<int> copy_queue = my_queue;
  EXPECT_EQ(my_queue.front(), copy_queue.front());
  EXPECT_EQ(my_queue.back(), copy_queue.back());
}

TEST(Test_32, move_arr) {
  s21::queue<int> my_queue = {1, 4, 6, 3, 7};
  s21::queue<int> move_queue = std::move(my_queue);
  EXPECT_EQ(1, move_queue.front());
  EXPECT_EQ(7, move_queue.back());
}

TEST(Test_42, push) {
  s21::queue<int> my_queue = {1, 4, 6, 3, 7};
  my_queue.push(10);
  EXPECT_EQ(10, my_queue.back());
}

TEST(Test_52, pop) {
  s21::queue<int> my_queue = {1, 4, 6, 3, 7};
  my_queue.pop();
  EXPECT_EQ(4, my_queue.front());
}

TEST(Test_62, empty) {
  s21::queue<int> my_queue = {1, 4, 6, 3, 7};
  s21::queue<int> empty_queue;
  EXPECT_TRUE(empty_queue.empty());
  EXPECT_FALSE(my_queue.empty());
}

TEST(Test_72, size) {
  s21::queue<int> my_queue = {1, 4, 6, 3, 7};
  EXPECT_EQ(my_queue.size(), static_cast<size_t>(5));
}

TEST(Test_82, swap) {
  s21::queue<int> queue1 = {1, 1, 1, 1, 1};
  s21::queue<int> queue2 = {2, 2, 2, 2, 2};
  EXPECT_EQ(queue2.front(), 2);
  EXPECT_EQ(queue1.front(), 1);
  queue1.swap(queue2);
  EXPECT_EQ(queue1.front(), 2);
  EXPECT_EQ(queue2.front(), 1);
}

TEST(Test_29, full_pop) {
  s21::queue<int> queue1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(queue1.empty());
  const int const_size = queue1.size();
  for (auto i = 0; i < const_size; i++) {
    queue1.pop();
  }
  EXPECT_TRUE(queue1.empty());
}

TEST(Test_120, fill_queue) {
  s21::queue<int> queue1;
  EXPECT_TRUE(queue1.empty());
  for (auto i = 1; i <= 5; i++) {
    queue1.push(i);
  }
  EXPECT_EQ(queue1.front(), 1);
  EXPECT_EQ(queue1.back(), 5);
  EXPECT_FALSE(queue1.empty());
}

TEST(Constructor, Default) {
  s21::List<double> l;
  EXPECT_EQ(static_cast<size_t>(0), l.size());
}

TEST(List_element, front) {
  std::list<double> l1 = {1.366, 2, 3};
  s21::List<double> l2 = {1.366, 2, 3};
  EXPECT_EQ(l1.front(), l2.front());
}

TEST(List_modifier, empty) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  // EXPECT_EQ(l1.empty(), l2.empty());
}

TEST(List_iterator, Begin) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  EXPECT_EQ(*iter1, *iter2);
}

int main(int argc, char **argv) {
  static_assert(std::is_same_v<vector<int>::const_pointer, const int *>,
                "Pointer(const) types are not equal.");
  static_assert(std::is_same_v<vector<int>::pointer, int *>,
                "Pointer types are not equal.");
  static_assert(std::is_same_v<vector<int>::iterator::meta_reference, int &>,
                "References types are not equal.");
  static_assert(
      std::is_same_v<vector<int>::const_iterator::meta_reference, const int &>,
      "References(const) types are not equal.");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
