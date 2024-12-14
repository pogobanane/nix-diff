// #include "nix_api_expr_internal.h"
#include "eval-gc.hh"
#include "eval.hh"
#include "globals.hh"
#include "store-api.hh"
#include "util.hh"
#include "fetch-settings.hh"
#include "src/diff.cc"
#include <fstream>
#include <iostream>
// #include <nix_api_util.h>
// #include <nix_api_expr.h>
// #include <nix_api_value.h>
#include <stdlib.h>
#include <string.h>

// NOTE: This example lacks all error handling. Production code must check for
// errors, as some return values will be undefined.

void my_get_string_cb(const char * start, unsigned int n, void * user_data)
{
    *((char **) user_data) = strdup(start);
}

int main()
{
    // nix_libexpr_init(NULL);
    nix::initLibUtil(); // throws
    nix::initLibStore(); // throws
    nix::initGC(); // throws


    // Store * store = nix_store_open(NULL, "dummy://", NULL);
    nix::Store::Params params_map;
    std::string uri = "dummy://";
    nix::ref<nix::Store> store = nix::openStore(uri, params_map);



    // EvalState * state = nix_state_create(NULL, NULL, store); // empty search path (NIX_PATH)
    auto fetchSettings = nix::fetchers::Settings{};
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

