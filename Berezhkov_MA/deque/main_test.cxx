#include <any>
#include <string>

#include "deque.hxx"
#include "testing.hxx"

const int sentinel = 0xBADBEEF;

auto test_deque(testing::context& t) -> void {
  t.describe("- initialize deque");

  deque::deque<int> dq;

  if (dq.size() != 0) {
    t.diag("initial size must be zero");
    t.fail();
  }
}

auto test_deque_at(testing::context& t) -> void {
  t.describe("- random access of deque");

  deque::deque<int> dq;
  for (int i = 0; i < 1000; i++) {
    dq.push_back(i);
  }

  for (int i = 0; i < 1000; i++) {
    if (dq.at(i) != i || dq[i] != i) {
      t.diag("ith value must be i");
      t.fail();
      break;
    }
  }

  auto oob = testing::throws<const std::out_of_range&>([&]() -> void {
    dq.at(-2);
    dq.at(-1);
    dq.at(1000);
    dq.at(1001);

    deque::deque<std::any> dq_empty;
    dq_empty.at(-1);
    dq_empty.at(0);
    dq_empty.at(1);
  });
  if (!oob) {
    t.diag("index out of bounds must throw an exception");
    t.fail();
  }
}

auto test_deque_push_front(testing::context& t) -> void {
  t.describe("- push front to deque");

  deque::deque<int> dq;
  dq.push_front(sentinel);

  if (dq.size() != 1) {
    t.diag("deque must hold one element");
    t.fail();
  }

  if (dq.front() != sentinel) {
    t.diag("front element must be the pushed value");
    t.fail();
  }
}

auto test_deque_push_back(testing::context& t) -> void {
  t.describe("- push back to deque");

  deque::deque<int> dq;
  dq.push_back(sentinel);

  if (dq.size() != 1) {
    t.diag("deque must hold one element");
    t.fail();
  }

  if (dq.back() != sentinel) {
    t.diag("back element must be the pushed value");
    t.fail();
  }
}

auto test_deque_front_back(testing::context& t) -> void {
  t.describe("- front and back of deque");

  deque::deque<std::string> dq;
  dq.push_back("foo");
  dq.push_back("bar");
  dq.push_back("baz");

  if (dq.front() != "foo") {
    t.fail();
  }
  if (dq.back() != "baz") {
    t.fail();
  }
  dq.pop_front();

  if (dq.front() != "bar") {
    t.fail();
  }
  if (dq.back() != "baz") {
    t.fail();
  }
  dq.pop_back();

  if (dq.front() != "bar") {
    t.fail();
  }
  if (dq.back() != "bar") {
    t.fail();
  }
  if (dq.size() != 1) {
    t.fail();
  }

  auto oob = testing::throws<const std::out_of_range&>([&]() -> void {
    deque::deque<std::any> dq_empty;
    dq_empty.front();
    dq_empty.back();
  });
  if (!oob) {
    t.diag("front and back on empty deque must throw an exception");
    t.fail();
  }
}

auto test_deque_rotate(testing::context& t) -> void {
  t.describe("- rotate deque");

  deque::deque<int> dq;
  for (int i = 0; i < 1000; i++) {
    dq.push_back(i);
  }

  dq.rotate(dq.size());
  for (int i = 0; i < 1000; i++) {
    if (dq.at(i) != i) {
      t.diag("ith value must be i");
      t.fail();
      break;
    }
  }

  dq.rotate(100500);
  for (int i = 0; i < 1000; i++) {
    if (dq.at(i) != ((i + 500) % 1000)) {
      t.fail();
      break;
    }
  }

  dq.rotate(-100500);
  for (int i = 0; i < 1000; i++) {
    if (dq.at(i) != i) {
      t.fail();
      break;
    }
  }

  deque::deque<int> dq16;
  for (int i = 0; i < 16; i++) {
    dq16.push_back(i);
  }
  dq16.rotate(8);
  for (int i = 0; i < 16; i++) {
    if (dq16.at(i) != ((i + 8) % 16)) {
      t.fail();
      break;
    }
  }
}

auto test_deque_copy(testing::context& t) -> void {
  t.describe("- copy deque");

  deque::deque<int> dq1;
  for (int i = 0; i < 1000; i++) {
    dq1.push_back(i);
  }

  auto dq2 = dq1;
  for (int i = 0; i < 1000; i++) {
    dq2.at(i) += 1;
  }

  for (int i = 0; i < 1000; i++) {
    if (dq1.at(i) + 1 != dq2.at(i)) {
      t.fail();
      break;
    }
  }
}

auto main() -> int {
  return testing::run_suite({
      test_deque,
      test_deque_at,
      test_deque_push_front,
      test_deque_push_back,
      test_deque_front_back,
      test_deque_rotate,
      test_deque_copy,
  });
}
