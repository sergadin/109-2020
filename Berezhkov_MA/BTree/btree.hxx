#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

namespace btree {

[[maybe_unused]] const std::size_t range_min = 2;
const std::size_t range_max = 5;

template <typename T>
class tree;

template <typename T>
class node {
 public:
  node(node<T>* p) : parent(p), size(0) {}

  auto insert(T key) -> void;
  auto lookup(T key) -> std::optional<T>;

 private:
  static auto split(node<T>* old_node) -> void;

  auto add(T key, std::unique_ptr<node<T>>& other) -> void;
  auto is_leaf() -> bool;
  auto find_pos(const T& key) -> std::size_t;
  auto place_key(const T& key, const std::size_t pos) -> void;

  node<T>* parent;
  std::size_t size;
  T keys[range_max];
  std::unique_ptr<node<T>> children[range_max + 1];

  friend class tree<T>;
};

template <typename T>
class tree {
 public:
  tree() : root(std::unique_ptr<node<T>>(new node<T>(nullptr))) {}

  auto insert(T key) -> void;
  auto lookup(T key) -> std::optional<T>;

 private:
  auto reroot() -> void;

  std::unique_ptr<node<T>> root;
};

template <typename T>
auto node<T>::is_leaf() -> bool {
  for (auto i = 0ul, end = size; i != end; ++i) {
    if ((bool)children[i])
      return false;
  }
  return true;
}

template <typename T>
auto node<T>::find_pos(const T& key) -> std::size_t {
  int lo = -1;
  int hi = size;
  while (lo + 1 < hi) {
    auto mid = (lo + hi) / 2;
    if (keys[mid] == key) {
      return mid;
    } else if (keys[mid] < key) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  return hi;
}

template <typename T>
auto node<T>::place_key(const T& key, const std::size_t pos) -> void {
  if (pos < size && keys[pos] == key) {
    keys[pos] = key;
    return;
  }

  for (auto i = size; i > pos; --i) {
    keys[i] = keys[i - 1];
    children[i + 1] = std::move(children[i]);
  }

  keys[pos] = key;
  ++size;
}

template <typename T>
auto node<T>::insert(T key) -> void {
  if (!is_leaf()) {
    auto key_pos = find_pos(key);
    if (key_pos < size && keys[key_pos] == key) {
      keys[key_pos] = key;
      return;
    }
    if (!children[key_pos])
      children[key_pos] = std::unique_ptr<node<T>>(new node<T>(this));
    else if (children[key_pos]->size == range_max) {
      split(children[key_pos].get());
      key_pos = find_pos(key);
    }
    children[key_pos]->insert(key);
    return;
  }
  place_key(key, find_pos(key));
}

template <typename T>
auto node<T>::lookup(T key) -> std::optional<T> {
  if (size == 0) {
    return std::nullopt;
  }
  auto pos = find_pos(key);
  if (pos < size && keys[pos] == key) {
    return keys[pos];
  }
  if (is_leaf()) {
    return std::nullopt;
  }
  return children[pos]->lookup(key);
}

template <typename T>
auto node<T>::add(T key, std::unique_ptr<node<T>>& other) -> void {
  const auto pos = find_pos(key);
  place_key(key, pos);
  children[pos + 1] = std::move(other);
  children[pos + 1]->parent = this;
}

template <typename T>
auto node<T>::split(node<T>* old_node) -> void {
  std::unique_ptr<node<T>> new_node(new node<T>(old_node->parent));
  node<T>* new_node_raw = new_node.get();

  const std::size_t median = range_max / 2;
  const T median_key = old_node->keys[median];

  if ((bool)old_node->children[median + 1]) {
    new_node->children[0] = std::move(old_node->children[median + 1]);
    new_node->children[0]->parent = new_node_raw;
  }
  for (std::size_t i = median + 1, new_node_i = 0, end = range_max; i != end;
       ++i, ++new_node_i) {
    new_node->keys[new_node_i] = old_node->keys[i];
    if (old_node->children[i + 1]) {
      new_node->children[new_node_i + 1] = std::move(old_node->children[i + 1]);
      new_node->children[new_node_i + 1]->parent = new_node.get();
    }
    ++new_node->size;
    --old_node->size;
  }
  --old_node->size;

  old_node->parent->add(median_key, new_node);
}

template <typename T>
auto tree<T>::reroot() -> void {
  auto new_root = std::unique_ptr<node<T>>(new node<T>(nullptr));
  auto old_root_raw = root.get();
  root->parent = new_root.get();
  new_root->children[0] = std::move(root);
  new_root->children[0]->parent = new_root.get();
  root = std::move(new_root);
  node<T>::split(old_root_raw);
}

template <typename T>
auto tree<T>::insert(T key) -> void {
  if (root->size == range_max) {
    reroot();
  }
  root->insert(key);
}

template <typename T>
auto tree<T>::lookup(T key) -> std::optional<T> {
  return root->lookup(key);
}
}  // namespace btree
