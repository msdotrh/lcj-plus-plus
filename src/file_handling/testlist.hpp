#ifndef TESTLIST_H
#define TESTLIST_H
#include <toml++/toml.hpp>
#pragma once

#include "testcase.hpp"
#include <set>

struct TestCaseList {
  std::set<TestCase> testcase_set;

  void Add(TestCase& ts) {
    testcase_set.insert(ts);
  }
};

#endif