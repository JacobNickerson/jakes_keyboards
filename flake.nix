{
  description = "QMK dev environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = with pkgs; [
        qmk
        dfu-util
        avrdude
        gcc-arm-embedded
        pkgsCross.avr.buildPackages.gcc
        pkgsCross.avr.buildPackages.binutils
        git
        python3
        python3Packages.pip
      ];

      shellHook = ''
        echo "QMK devshell ready"
      '';
    };
  };
}