
#include "eval.hh"
#include "value.hh"
#include <cstdio>
#include <boost/json/src.hpp>

namespace diff {

class Diff {
private:
  boost::json::object json;
  nix::EvalState *state;
public:
  void diff(nix::EvalState *state, nix::Value &value) {
    this->state = state;

    switch(value.type()) {
      case nix::ValueType::nAttrs:
        diff_attrset(value);
        break;
      default:
        std::cerr << "unknown type: " << nix::showType(value) << std::endl;
        return;
    }

    std::cout << json << std::endl;
  }

  void diff_attrset(nix::Value &value) {
    std::cerr << "diff attr" << std::endl;
    nix::PosIdx last_index;
    for (auto attr : *value.attrs()) {
      assert(last_index < attr.pos);
      last_index = attr.pos;
      auto name = this->state->symbols[attr.name].c_str();
      json[name] = nullptr;
    }
  }
};

}

