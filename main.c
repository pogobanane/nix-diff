#include <nix_api_util.h>
#include <nix_api_expr.h>
#include <nix_api_value.h>
#include <stdio.h>
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
    nix_libexpr_init(NULL);

    Store * store = nix_store_open(NULL, "dummy://", NULL);
    EvalState * state = nix_state_create(NULL, NULL, store); // empty search path (NIX_PATH)
    Value * value = nix_alloc_value(NULL, state);

    nix_expr_eval_from_string(NULL, state, "builtins.nixVersion", ".", value);
    nix_value_force(NULL, state, value);

    char * version;
    nix_get_string(NULL, value, my_get_string_cb, &version);
    printf("Nix version: %s\n", version);

    free(version);
    nix_gc_decref(NULL, value);
    nix_state_free(state);
    nix_store_free(store);
    return 0;
}

