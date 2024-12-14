{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
  };

  outputs = { self, nixpkgs }: let
      pkgs  = nixpkgs.legacyPackages.x86_64-linux;
    in {

    devShells.x86_64-linux.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        just
        meson
        ninja
        nlohmann_json
        toml11
        cmake
        sqlite
        perlPackages.DBDSQLite
        perlPackages.DBI
        git
      ] ++ pkgs.nix.buildInputs
      ++ pkgs.nix.nativeBuildInputs;

      hardeningDisable = [ "all" ];
    };

    packages.x86_64-linux.hello = nixpkgs.legacyPackages.x86_64-linux.hello;

    packages.x86_64-linux.default = self.packages.x86_64-linux.hello;

    undocumented = (import ./dump-config.nix);

  };
}
