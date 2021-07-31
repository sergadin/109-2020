#include <algorithm>
#include <exception>
#include <execution>
#include <mutex>
#include <numeric>
#include <ostream>
#include <string>
#include <vector>

#include "testing.hxx"

namespace testing {
auto context::describe(const std::string& desc) -> void {
  description = desc;
}

auto context::pass() -> void {
  ok = true;
  directive = "";
  reason = "";
}

auto context::fail() -> void {
  ok = false;
  directive = "";
  reason = "";
}

auto context::skip(const std::string& message) -> void {
  ok = true;
  directive = "skip";
  reason = message;
}

auto context::todo(const std::string& message) -> void {
  ok = false;
  directive = "TODO";
  reason = message;
}

auto context::diag(const std::string& message) -> void {
  messages.push_back(message);
}

auto context::write_to(std::ostream& w) -> bool {
  if (ok) {
    w << "ok";
  } else {
    w << "not ok";
  }
  if (n > 0) {
    w << " " << n;
  }
  if (!description.empty()) {
    w << " " << description;
  }
  if (!directive.empty()) {
    w << " # " << directive;
    if (!reason.empty()) {
      w << " " << reason;
    }
  }
  w << std::endl;
  for (const auto& m : messages) {
    if (!m.empty()) {
      w << "# " << m << std::endl;
    } else {
      w << "#" << std::endl;
    }
  }
  return ok;
}

auto run_suite(const std::vector<check>& suite, std::ostream& w) -> int {
  const auto& n = suite.size();

  // See https://testanything.org
  w << "TAP version 13" << std::endl;
  w << "1.." << n << std::endl;

  std::vector<int> iota(n);
  std::iota(std::begin(iota), std::end(iota), 0);

  bool ok = true;
  std::mutex m;
  std::for_each(std::execution::par, std::begin(iota), std::end(iota),
                [&](auto&& i) {
                  context t(i + 1);
                  const auto& run_check = suite[i];
                  try {
                    run_check(t);
                  } catch (const std::exception& err) {
                    t.diag(std::string(err.what()));
                    t.fail();
                  }

                  std::lock_guard<std::mutex> guard(m);
                  if (!t.write_to(w)) {
                    ok = false;
                  };
                });
  if (!ok) {
    return 1;
  } else {
    return 0;
  }
}
}  // namespace testing
