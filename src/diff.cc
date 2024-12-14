
#include "eval.hh"
#include "value.hh"
#include <cstdio>
#include <boost/json/src.hpp>

namespace diff {

typedef std::vector<nix::Symbol> AttrPath;

class Diff {

private:
  boost::json::value json;
  nix::EvalState *state;

  std::set<nix::Value*> visited;

  std::string json_path(const AttrPath *path) {
    std::stringstream ret("");
    for(auto symbol: *path) {
      auto name = this->state->symbols[symbol].c_str();
      ret << "/" << name;
    }
    return ret.str();
  }
public:

  void diff(nix::EvalState *state, nix::Expr *expr) {
    this->state = state;
    this->json = {};

    nix::Value * value = this->state->allocValue();
    this->state->eval(expr, *value);
    auto path = new AttrPath();
    this->diff_value(value, path);
    delete path;

    std::cout << json << std::endl;
  }

  void diff_value(nix::Value *value, const AttrPath *path) {
    this->state->forceValue(*value, nix::noPos);

    std::cerr << " > ";
    for(auto name : *path) {
      std::cerr << this->state->symbols[name].c_str() << " > ";
    }
    value->print(*this->state, std::cerr);
    std::cerr << std::endl;

    switch(value->type()) {
      case nix::ValueType::nAttrs:
        diff_attrset(value, path);
        break;
      default:
        std::cerr << "unknown type: " << nix::showType(*value) << std::endl;
    }
  }

  void diff_attrset(nix::Value *value, const AttrPath *path) {
    // boost::json::object json_attrset;
    // this->json_object(&json_attrset, path);
    auto json_path = this->json_path(path);

    // nix::PosIdx last_index;
    for (auto attr : *value->attrs()) {
      // assert(last_index < attr.pos);
      // last_index = attr.pos;
      auto name = this->state->symbols[attr.name].c_str();
      // json[name] = nullptr;
      // auto json_path = std::format("/{}", name);
      // auto json_path = std::format("/{}", "name");
      // this->json.at_pointer("/") = boost::json::object {};

      // this->json.as_object().emplace(name, "value");
      // json_attrset.emplace(name, "value");
      this->json.at_pointer(json_path).as_object().emplace(name, boost::json::object {});
      // std::cout << json_attrset << std::endl;
      // auto object = this->json.at_pointer("/").as_object();
      // auto object = this->json.as_object();
      // object[name] = boost::json::object {};
      // std::cout << json << std::endl;

      auto next_path = new AttrPath(*path);
      next_path->push_back(attr.name);
      this->diff_value(attr.value, next_path);
      delete next_path;
    }
  }
};

}

