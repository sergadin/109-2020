#include <algorithm>
#include <cstddef>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <vector>

namespace deque {
const auto out_of_range = std::out_of_range("deque: index out of bounds");

template <typename T>
class deque {
 public:
  // size returns the number of elements in deque.
  auto size() -> std::size_t { return count; }

  // at accesses specified element with bounds checking.
  auto at(std::size_t pos) -> T& {
    if (pos < 0 || pos >= count) {
      throw out_of_range;
    }
    return buf.at(index_of(pos)).value();
  }
  // operator[] access specified element.
  auto operator[](std::size_t pos) -> T& { return *buf[index_of(pos)]; }

  // back returns the first element.
  auto front() -> T& {
    if (count <= 0) {
      throw out_of_range;
    }
    return buf.at(head).value();
  }
  // back returns the last element.
  auto back() -> T& {
    if (count <= 0) {
      throw out_of_range;
    }
    return buf.at(prev(tail)).value();
  }

  // push_front inserts an element to the beginning.
  auto push_front(const T& element) -> void {
    grow_if_full();
    head = prev(head);
    buf[head] = element;
    count++;
  }
  // push_back adds an element to the end.
  auto push_back(const T& element) -> void {
    grow_if_full();
    buf[tail] = element;
    tail = next(tail);
    count++;
  }

  // pop_front removes the first element.
  auto pop_front() -> void {
    if (count <= 0) {
      throw out_of_range;
    }
    buf[head].reset();
    head = next(head);
    count--;
    shrink_if_excess();
  }
  // pop_back removes the last element.
  auto pop_back() -> void {
    if (count <= 0) {
      throw out_of_range;
    }
    tail = prev(tail);
    buf[tail].reset();
    count--;
    shrink_if_excess();
  }

  // rotate rotates the deque n steps front-to-back.
  // If n is negative, rotates back-to-front.
  auto rotate(int n) -> void {
    if (count <= 1) {
      return;
    }
    if (n > 0) {
      n %= count;
    }
    if (n < 0) {
      n = -n;
      n %= count;
      n = -n;
    }
    if (n == 0) {
      return;
    }

    const auto& m = buf.size() - 1;

    if (head == tail) {
      head = (head + n) & m;
      tail = (tail + n) & m;
      return;
    }

    if (n < 0) {
      while (n < 0) {
        head = (head - 1) & m;
        tail = (tail - 1) & m;
        buf[head] = buf[tail];
        buf[tail].reset();
        n++;
      }
      return;
    }

    while (n > 0) {
      buf[tail] = buf[head];
      buf[head].reset();
      head = (head + 1) & m;
      tail = (tail + 1) & m;
      n--;
    }
  }

 private:
  static const std::size_t min_capacity = 1 << 4;

  // std_ncopy is like std::copy but returns the number of copied elements
  // instead of iterator.
  template <typename InputIt, typename OutputIt>
  static auto std_ncopy(InputIt first, InputIt last, OutputIt dst) ->
      typename std::iterator_traits<OutputIt>::difference_type {
    return std::distance(first, std::copy(first, last, dst));
  }

 private:
  std::vector<std::optional<T>> buf;
  std::size_t head = 0;
  std::size_t tail = 0;
  std::size_t count = 0;
  std::size_t min_cap = 0;

  auto index_of(std::size_t i) -> std::size_t {
    return (head + i) & (buf.size() - 1);
  }

  auto next(std::size_t i) -> std::size_t { return (i + 1) & (buf.size() - 1); }

  auto prev(std::size_t i) -> std::size_t { return (i - 1) & (buf.size() - 1); }

  auto grow_if_full() -> void {
    const auto& bufSize = buf.size();
    if (bufSize == 0) {
      if (min_cap == 0) {
        min_cap = min_capacity;
      }
      buf.resize(min_cap);
      return;
    }
    if (bufSize == count) {
      resize();
    }
  }

  auto shrink_if_excess() -> void {
    const auto& bufSize = buf.size();
    if (bufSize > min_cap && (count * 4) <= bufSize) {
      resize();
    }
  }

  auto resize() -> void {
    std::vector<std::optional<T>> newBuf(count * 2);

    if (tail > head) {
      std::copy(std::next(std::begin(buf), head),
                std::next(std::begin(buf), tail), std::begin(newBuf));
    } else {
      const auto& n = std_ncopy(std::next(std::begin(buf), head), std::end(buf),
                                std::begin(newBuf));
      std::copy(std::begin(buf), std::next(std::begin(buf), tail),
                std::next(std::begin(newBuf), n));
    }
    head = 0;
    tail = count;
    buf = newBuf;
  }
};
}  // namespace deque
