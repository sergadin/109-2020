#include <any>
#include <memory>
#include <optional>
#include <string>

#include "btree.hxx"
#include "keyval.hxx"

namespace keyval {
class key_pair : public std::string {
 public:
  std::any value;

  key_pair() = default;

  key_pair(const std::string& k) : std::string(k) {}
  key_pair(const std::string& k, const std::any& v)
      : std::string(k), value(v) {}
};

class btree_store : public store {
 public:
  btree_store() = default;

  auto put(const std::string& k, const std::any& v) -> void {
    tree.insert(key_pair(k, v));
  }
  auto get(const std::string& k) -> std::optional<std::any> {
    auto pair = tree.lookup(key_pair(k));
    if (pair == std::nullopt) {
      return std::nullopt;
    }
    return pair->value;
  }

 private:
  btree::tree<key_pair> tree;
};

auto make_btree_store() -> std::unique_ptr<store> {
  return std::make_unique<btree_store>();
}
}  // namespace keyval
