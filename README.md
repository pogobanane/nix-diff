# nix-diff

Status: prototype

Nix-diff allows you to compare nix expressions (e.g. NixOS configs).

Nix-diff takes an expression from `expression.nix` which can load a NixOS config from a flake.
It writes the config as json to stdout.
Dump the json for different configs and compare them, e.g., with `vimdiff` to find the differences.


## Considerations

Is it bijective/complete?
No.
Nix expressions may contain unbounded lists which we just attempt to ignore.
Additionally, some data-types like functions cannot be represented in json and are stripped as well.

## Build

```console
nix develop ./subprojects/nix_subproject/#
meson build
meson compile -C build
```
