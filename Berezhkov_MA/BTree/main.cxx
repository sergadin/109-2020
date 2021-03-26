#include <any>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <numeric>
#include <optional>
#include <string>
#include <typeinfo>
#include <vector>

#include "keyval.hxx"
#include "parser.hxx"

auto describe_type(const std::type_info& ti) -> std::string {
  if (ti == typeid(int)) {
    return "int";
  }
  if (ti == typeid(double)) {
    return "float";
  }
  if (ti == typeid(std::string)) {
    return "string";
  }
  if (ti == typeid(std::vector<int>)) {
    return "ints";
  }
  if (ti == typeid(std::vector<double>)) {
    return "floats";
  }
  return "";
}

auto describe_any(const std::any& x) -> std::string {
  if (x.type() == typeid(int)) {
    return std::to_string(std::any_cast<int>(x));
  }
  if (x.type() == typeid(double)) {
    return std::to_string(std::any_cast<double>(x));
  }
  if (x.type() == typeid(std::string)) {
    return std::any_cast<std::string>(x);
  }
  if (x.type() == typeid(std::vector<int>)) {
    auto v = std::any_cast<std::vector<int>>(x);
    return std::accumulate(v.begin(), v.end(), std::string("|"),
                           [](const std::string& a, int b) {
                             return a + " " + std::to_string(b);
                           }) +
           " |";
  }
  if (x.type() == typeid(std::vector<double>)) {
    auto v = std::any_cast<std::vector<double>>(x);
    return std::accumulate(v.begin(), v.end(), std::string("|"),
                           [](const std::string& a, double b) {
                             return a + " " + std::to_string(b);
                           }) +
           " |";
  }
  return "<unknown>";
}

auto usage(std::string argv0) -> void {
  std::cerr << "usage: " << argv0
            << " [<options>] [--] key[:type] [key[:type] ...]" << std::endl;
  std::cerr << "options:" << std::endl;
  std::cerr << "\t-h" << std::endl;
  std::cerr << "\t-f <filename>" << std::endl;
  std::cerr << "types:" << std::endl;
  std::cerr << "\tint" << std::endl;
  std::cerr << "\tfloat" << std::endl;
  std::cerr << "\tstring" << std::endl;
  std::cerr << "\tints" << std::endl;
  std::cerr << "\tfloats" << std::endl;
}

auto main(int argc, char** argv) -> int {
  auto kv = keyval::make_btree_store();

  if (argc <= 1) {
    if (argc <= 0) {
      std::exit(1);
    }
    usage(argv[0]);
    std::exit(1);
  }

  int nfiles = 0;

  int i = 1;
  for (; i < argc; i++) {
    std::string arg(argv[i]);
    if (arg == "/f" || arg == "-f") {
      i++;
      if (i >= argc) {
        std::cerr << "expected file path" << std::endl;
        std::exit(1);
      }
      std::string filename(argv[i]);
      std::ifstream in(filename);
      if (!parser::eval(in, *kv)) {
        std::cerr << filename << ": oops, parse error" << std::endl;
        std::exit(1);
      }
      nfiles++;
      continue;
    } else if (arg == "/h" || arg == "-h") {
      usage(argv[0]);
      std::exit(0);
    } else if (arg == "--") {
      break;
    } else if (arg.starts_with('-') || arg.starts_with('/')) {
      std::cerr << "unknown argument: " << arg << std::endl;
      std::exit(1);
    } else {
      break;
    }
  }
  if (i >= argc) {
    std::cerr << "missing key query" << std::endl;
    std::exit(1);
  }
  if (nfiles <= 0) {
    if (!parser::eval(std::cin, *kv)) {
      std::cerr << "<stdin>: oops, parse error" << std::endl;
      std::exit(1);
    }
  }

  bool err = false;
  for (; i < argc; i++) {
    std::string arg(argv[i]);

    std::string key = arg;
    std::string typ = "";
    bool typecheck = false;

    auto pos = arg.find(':');
    if (pos != std::string::npos) {
      key = arg.substr(0, pos);
      typ = arg.substr(pos + 1);
      typecheck = true;
    }
    if (typ != "") {
      if (typ != "string" && typ != "int" && typ != "float" && typ != "ints" &&
          typ != "floats") {
        std::cerr << "unknown type: " << typ << std::endl;
        err = true;
        continue;
      }
    }

    auto x = kv->get(key);
    if (x == std::nullopt) {
      std::cerr << "value not found" << std::endl;
      err = true;
      continue;
    }

    auto xtyp = describe_type(x->type());
    auto desc = describe_any(*x);

    // Quick and dirty workaround for our dumb parser / type system.
    if (xtyp == "ints" && typ == "floats" &&
        std::any_cast<std::vector<int>>(*x).size() == 0) {
      typecheck = false;
    }

    if (typecheck && typ != xtyp) {
      std::cerr << key << ": expected type " << typ << ", but got " << xtyp
                << " (" << desc << ")" << std::endl;
      err = true;
      continue;
    }

    std::cout << key << " = " << desc << std::endl;
  }
  if (err) {
    std::exit(1);
  }
}
