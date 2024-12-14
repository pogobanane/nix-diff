// #include "nix_api_expr_internal.h"
#include "eval-gc.hh"
#include "eval.hh"
#include "flake/flake.hh"
#include "flake/settings.hh"
#include "globals.hh"
#include "store-api.hh"
#include "util.hh"
#include "plugin.hh"
#include "fetch-settings.hh"
#include "src/diff.cc"
#include <fstream>
#include <iostream>
// #include <nix_api_util.h>
// #include <nix_api_expr.h>
// #include <nix_api_value.h>
#include <stdlib.h>
#include <string.h>
#include <boost/json/src.hpp>

// NOTE: This example lacks all error handling. Production code must check for
// errors, as some return values will be undefined.

void my_get_string_cb(const char * start, unsigned int n, void * user_data)
{
    *((char **) user_data) = strdup(start);
}

boost::json::value &foo(boost::json::value &json) {
    auto j1 = json.as_object().at("key");
    std::cout << j1 << std::endl;
    // auto j2 = json.as_object().at("key2");
    // std::cout << j2 << std::endl;
    return j1;
}

int main()
{
    boost::json::value json;
    json = {};
    json.at_pointer("").emplace_object();
    std::cerr << json << std::endl;

    // json.as_object().at("key") = {};
    json.as_object().emplace("ke/y", nullptr);
    json.as_object().at("ke/y").emplace_object();
    json.at_pointer("/ke~1y").as_object().emplace("key2", nullptr);
    json.as_object().emplace("kex", nullptr);
    json.at_pointer("/kex").emplace_array();
    std::cerr << json << std::endl;
    json.at_pointer("/kex").as_array().push_back(nullptr);
    std::cerr << json << std::endl;
    json.at_pointer("/kex/0").emplace_object();
    // json.as_object().at("key").as_object().emplace("key2", boost::json::object());
    std::cerr << json << std::endl;
    // json.as_object().at("key").emplace_object();
    // // foo(json).emplace_object();
    // foo(json).as_object().emplace("key3", nullptr);
    // std::cout << json << std::endl;

    // nix_libexpr_init(NULL);
    nix::initLibUtil(); // throws
    nix::initLibStore(); // throws
    nix::initGC(); // throws
    nix::initPlugins(); // throws


    // Store * store = nix_store_open(NULL, "dummy://", NULL);
    nix::Store::Params params_map;
    // std::string uri = "dummy://";
    std::string uri = "/tmp/debug-store";
    nix::ref<nix::Store> store = nix::openStore(uri, params_map);



    // EvalState * state = nix_state_create(NULL, NULL, store); // empty search path (NIX_PATH)
    auto fetchSettings = nix::fetchers::Settings{};

    nix::flake::Settings flakeSettings;
    nix::flake::initLib(flakeSettings);

    bool readOnly = false;
    nix::EvalSettings settings = nix::EvalSettings{readOnly, {}};
    nix::EvalState state = nix::EvalState({}, store, fetchSettings, settings);



    // Value * value = nix_alloc_value(NULL, state);
    nix::Value * value = state.allocValue();
    // // nix_printer nix_printer = nix_printer(std::cout);

    std::ifstream ifs("dump-config.nix");
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    // // nix_expr_eval_from_string(NULL, state, "{ \"a\" = \"foo\"; }", ".", value);
    std::string expr = "{ \"a\" = \"foo\"; }";
    nix::Expr * parsedExpr = state.parseExprFromString(content, state.rootPath(nix::CanonPath(".")));

    auto diff = diff::Diff{};
    diff.diff(&state, parsedExpr);

    // nix_expr_eval_from_string(NULL, state, content.c_str(), ".", value);
    // nix_value_force(NULL, state, value);

    // printf("fine\n");

    // const char* typename_ = nix_get_typename(NULL, value);
    // printf("Type: %s\n", typename_);

    // // std::cout << "foo " <<  value->print(std::cout) << std::endl;


    // char * version;
    // nix_get_string(NULL, value, my_get_string_cb, &version);
    // printf("Nix version: %s\n", version);

    // free(version);
    // nix_gc_decref(NULL, value);
    // nix_state_free(state);
    // // nix_store_free(store);
    return 0;
}

