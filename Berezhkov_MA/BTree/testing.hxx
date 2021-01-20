#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace testing {
template <typename E>
auto throws(std::function<auto()->void> f) -> bool {
  try {
    f();
  } catch (const E&) {
    return true;
  }
  return false;
}

// context holds test results.
struct context {
 public:
  // context returns a new test context for nth test.
  context(int n = 0) : n(n){};

  // pass marks the test as passed.
  auto pass() -> void;
  // fail marks the test as failed.
  auto fail() -> void;
  // skip marks the test as skipped with optional message.
  auto skip(const std::string& message = "") -> void;
  // todo marks the test as to-be-done with optional message.
  auto todo(const std::string& message = "") -> void;
  // diag adds the diagnostics message for this test.
  auto diag(const std::string& message) -> void;
  // describe sets a description for the test.
  auto describe(const std::string& desc) -> void;

  // write_to writes TAP protocol test log to w stream.
  auto write_to(std::ostream& w) -> bool;

 private:
  bool ok = true;
  int n = 0;
  std::string description;
  std::string directive;
  std::string reason;
  std::vector<std::string> messages;
};

// check is a test case. Results are reported via test context.
using check = std::function<auto(context&)->void>;

// run_suite runs checks in a test suite and dumps TAP protocol test log to w
// stream. The checks are not guaranteed to start or complete in the iteration
// order.
auto run_suite(const std::vector<check>& suite, std::ostream& w = std::cout)
    -> int;
}  // namespace testing
