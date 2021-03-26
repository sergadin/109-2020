#include <any>
#include <cctype>
#include <istream>
#include <stdexcept>
#include <string>
#include <vector>

#include "keyval.hxx"

namespace parser {
auto eof(std::istream& r) -> bool {
  r.peek();
  return r.eof();
}

auto skip_spaces(std::istream& r) -> bool {
  while (!eof(r) && std::isspace(r.peek())) {
    r.get();
  }
  return !eof(r);
}

auto skip_comment(std::istream& r) -> bool {
  if (eof(r) || r.peek() != '#') {
    return false;
  }
  while (!eof(r) && r.peek() != '\n') {
    r.get();
  }
  return true;
}

auto skip_equals(std::istream& r) -> bool {
  if (eof(r) || r.peek() != '=') {
    return false;
  }
  r.get();
  return true;
}

auto parse_key(std::istream& r, std::string& key) -> bool {
  if (eof(r) || !std::isalpha(r.peek())) {
    return false;
  }
  key += r.get();
  while (!eof(r) && std::isalnum(r.peek())) {
    key += r.get();
  }
  return true;
}

auto parse_value_number(std::istream& r, std::any& val) -> bool {
  std::string integer = "";
  std::string fraction = "";
  std::string exponent = "";

  switch (auto c = r.peek()) {
    case '+':
      r.get();
      if (eof(r)) {
        return false;
      }
      break;
    case '-':
      integer += r.get();
      if (eof(r)) {
        return false;
      }
      break;
    default:
      if (!std::isdigit(c)) {
        return false;
      }
  }
  if (!eof(r) && r.peek() == '0') {
    auto zero = r.get();
    if (!eof(r) && std::isdigit(r.peek())) {
      return false;
    }
    integer += zero;
  }
  while (!eof(r) && std::isdigit(r.peek())) {
    integer += r.get();
  }

  if (!eof(r) && r.peek() == '.') {
    r.get();
    while (!eof(r) && std::isdigit(r.peek())) {
      fraction += r.get();
    }
    if (fraction == "") {
      fraction = "0";
    }
  }

  if (!eof(r) && r.peek() == 'e') {
    r.get();
    if (eof(r)) {
      return false;
    }
    auto c = r.peek();
    switch (c) {
      case '+':
        r.get();
        break;
      case '-':
        exponent += r.get();
        break;
      default:
        if (!std::isdigit(c)) {
          return false;
        }
    }
    while (!eof(r) && std::isdigit(r.peek())) {
      exponent += r.get();
    }
  }

  if (fraction != "") {
    std::string number = integer + "." + fraction;
    if (exponent != "") {
      number += "e" + exponent;
    }
    try {
      val = std::stod(number);
    } catch (const std::out_of_range&) {
      return false;
    }
  } else if (exponent != "") {
    std::string number = integer;
    int exp;
    try {
      exp = std::stoi(exponent);
    } catch (const std::out_of_range&) {
      return false;
    }
    if (exp > 0) {
      number += std::string(exp, '0');
    }
    while (exp < 0 && number.back() == '0') {
      number.pop_back();
      exp++;
    }
    if (exp < 0) {
      return false;
    }
    try {
      val = std::stoi(number);
    } catch (const std::out_of_range&) {
      return false;
    }
  } else {
    try {
      val = std::stoi(integer);
    } catch (const std::out_of_range&) {
      return false;
    }
  }
  return true;
}

auto parse_value_array(std::istream& r, std::any& val) -> bool {
  bool fp = false;
  std::vector<int> vi;
  std::vector<double> vd;

  auto b = r.get();
  skip_spaces(r);
  while (!eof(r) && r.peek() != b) {
    std::any x;
    if (!parse_value_number(r, x)) {
      return false;
    }
    if (auto xd = std::any_cast<double>(&x)) {
      if (!fp) {
        for (const auto& xi : vi) {
          vd.push_back(static_cast<double>(xi));
        }
        fp = true;
      }
      vd.push_back(*xd);
    } else if (auto xi = std::any_cast<int>(&x)) {
      if (!fp) {
        vi.push_back(*xi);
      } else {
        vd.push_back(static_cast<double>(*xi));
      }
    } else {
      return false;
    }
    skip_spaces(r);
  }
  if (eof(r) || r.get() != b) {
    return false;
  }

  if (!fp) {
    val = vi;
  } else {
    val = vd;
  }
  return true;
}

auto parse_value_string(std::istream& r, std::any& val) -> bool {
  auto q = r.get();
  std::string s = "";
  while (!eof(r) && r.peek() != q) {
    auto c = r.get();
    if (c == '\\') {
      if (eof(r)) {
        return false;
      }
      auto cc = r.peek();
      if (cc == q || cc == '\\') {
        s += r.get();
        continue;
      } else {
        return false;
      }
    }
    s += c;
  }
  if (eof(r) || r.get() != q) {
    return false;
  }
  val = s;
  return true;
}

auto parse_value(std::istream& r, std::any& val) -> bool {
  if (eof(r)) {
    return false;
  }
  auto c = r.peek();
  switch (c) {
    case '"':
      return parse_value_string(r, val);
    case '|':
      return parse_value_array(r, val);
    case '-':
    case '+':
      return parse_value_number(r, val);
  }
  if (std::isdigit(c)) {
    return parse_value_number(r, val);
  }
  return false;
}

auto eval(std::istream& r, keyval::store& kv) -> bool {
  while (!eof(r)) {
    std::string key = "";
    std::any val = std::nullopt;

    if (!skip_spaces(r)) {
      return true;
    }
    if (skip_comment(r)) {
      continue;
    }

    if (!parse_key(r, key)) {
      return false;
    }
    if (!skip_spaces(r)) {
      return false;
    }
    if (!skip_equals(r)) {
      return false;
    }
    if (!skip_spaces(r)) {
      return false;
    }
    if (!parse_value(r, val)) {
      return false;
    }

    kv.put(key, val);
  }
  return true;
}
}  // namespace parser
