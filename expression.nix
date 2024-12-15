let
  currentHostname = builtins.head (builtins.match "([a-zA-Z0-9]+)\n" (builtins.readFile "/etc/hostname"));
  flakeUrl = (toString /home/peter/dev/dotfiles);
  flake = (builtins.getFlake flakeUrl);
  hostConfig = flake.nixosConfigurations.${currentHostname}.config;
in
  hostConfig
