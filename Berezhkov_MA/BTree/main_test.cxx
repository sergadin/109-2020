#include <any>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "btree.hxx"
#include "keyval.hxx"
#include "parser.hxx"

#include "testing.hxx"

auto test_btree(testing::context& t) -> void {
  t.describe("- btree");

  btree::tree<int> bt;

  for (int i = 100; i < 1000; i++) {
    bt.insert(i);
  }

  for (int i = 0; i < 100; i++) {
    auto x = bt.lookup(i);
    if (x != std::nullopt) {
      t.diag("lookup should not return values that were not inserted");
      t.fail();
    }
  }
  for (int i = 100; i < 1000; i++) {
    auto x = bt.lookup(i);
    if (x == std::nullopt) {
      t.diag("lookup should return values that were inserted");
      t.fail();
    }
  }

  for (int i = 100; i < 1000; i++) {
    bt.insert(i);
  }
  for (int i = 100; i < 1000; i++) {
    auto x = bt.lookup(i);
    if (x == std::nullopt) {
      t.diag("lookup should return values that were inserted multiple times");
      t.fail();
    }
  }
}

auto test_keyval(testing::context& t) -> void {
  t.describe("- keyval");

  auto kv = keyval::make_btree_store();

  auto kvget = [&](const std::string& k) -> std::optional<int> {
    auto opt = kv->get(k);
    if (opt == std::nullopt) {
      return std::nullopt;
    }
    if (auto x = std::any_cast<int>(&*opt)) {
      return *x;
    }
    return std::nullopt;
  };

  if (kvget("a") != std::nullopt) {
    t.diag("get should not return values from empty keyval store");
    t.fail();
    return;
  }

  kv->put("a", 1337);

  if (kvget("a") != 1337) {
    t.diag("get should return the value put in keyval store");
    t.fail();
  }

  kv->put("a", 7331);

  if (kvget("a") != 7331) {
    t.diag(
        "put should replace the value if it already exists in the keyval "
        "store");
    t.fail();
  }
}

auto test_parser(testing::context& t) -> void {
  t.describe("- parser");

  auto eval = [](const std::string& s) -> std::unique_ptr<keyval::store> {
    std::stringstream ss(s);
    auto kv = keyval::make_btree_store();
    if (!parser::eval(ss, *kv)) {
      return nullptr;
    }
    return kv;
  };

  for (const auto& in : std::vector<std::string>{
           "",
           " \t\n\r",
       }) {
    if (eval(in) == nullptr) {
      t.diag("should accept empty input");
      t.fail();
    }
  }

  for (const auto& in : std::vector<std::string>{
           "x = 0",      "x = 1",         "x = +1",        "x = -1",
           "x = 1e1",    "x = 1.",        "x = 1.0",       "x = 1.0e1",
           "x = 1.0e+1", "x = 1.0e-1",    "x = 1.0e-1",    "x = \"\"",
           "x = \"z\"",  "x = \"z\\\\\"", "x = \"z\\\"\"", "x = ||",
           "x = | 1 |",  "x = | 1 2 |",   "x = |1-1|",     "x = |1+1|",
       }) {
    if (eval(in) == nullptr) {
      t.diag("should accept simple assignments");
      t.fail();
    }
  }

  for (const auto& in : std::vector<std::string>{
           "x\n=\n1",
           "x\n=\n|\n1\n2\n3\n|\n",
       }) {
    if (eval(in) == nullptr) {
      t.diag("should accept multiline assignments");
      t.fail();
    }
  }

  for (const auto& in : std::vector<std::string>{
           "x",
           "\nx\n",
           "=",
           "x =",
           "x = 1e",
           "x = 1.1e",
           "x = 0-0",
           "x = 0+0",
           "x = \"",
           "x = \"\\",
           "x = \"\\\"",
           "x = |",
           "x = -",
           "x = +",
       }) {
    if (eval(in) != nullptr) {
      t.diag("should reject incomplete statements");
      t.fail();
    }
  }

  for (const auto& in : std::vector<std::string>{
           "x = z",
           "x = | z |",
           "x = 01",
           "x = +01",
           "x = -01",
           "x = 123e-2",
           "x = \"\\x\"",
       }) {
    if (eval(in) != nullptr) {
      t.diag("should reject invalid input");
      t.fail();
    }
  }

  for (const auto& in : std::vector<std::string>{
           "#",
           "#hello",
           "# hello",
           "# hello\n",
           "x = 1 # hello",
           "x = 1# hello",
           "#hello\nx=1\n#world",
       }) {
    if (eval(in) == nullptr) {
      t.diag("should accept comments");
      t.fail();
    }
  }
}

auto main() -> int {
  return testing::run_suite({
      test_btree,
      test_keyval,
      test_parser,
  });
}
