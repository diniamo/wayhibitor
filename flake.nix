{
  description = "Manual Wayland idle inhibitor written in C";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    systems.url = "github:nix-systems/default";
  };

  outputs = {
    nixpkgs,
    systems,
    self,
    ...
  }: let
    eachSystem = callback: nixpkgs.lib.genAttrs (import systems) (system: callback nixpkgs.legacyPackages.${system});
  in {
    devShells = eachSystem (pkgs: {
      default = with pkgs; mkShell {
        packages = [
          wayland
        ];
      };
    });

    packages = eachSystem (pkgs: let
      package = pkgs.callPackage ./package.nix {
        commit = self.shortRev or "dirty";
      };
    in {
      default = package;
      wayhibitor = package;
    });
  };
}
