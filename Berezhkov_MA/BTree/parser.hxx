#include <istream>

#include "keyval.hxx"

namespace parser {
auto eval(std::istream& r, keyval::store& kv) -> bool;
}
