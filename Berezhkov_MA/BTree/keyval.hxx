#pragma once
#include <any>
#include <memory>
#include <optional>
#include <string>

namespace keyval {
class store {
 public:
  virtual auto put(const std::string& k, const std::any& v) -> void = 0;
  virtual auto get(const std::string& k) -> std::optional<std::any> = 0;
  virtual ~store(){};
};

auto make_btree_store() -> std::unique_ptr<store>;
}  // namespace keyval
