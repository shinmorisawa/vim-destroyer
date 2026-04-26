{ pkgs ? import <nixpkgs> {} }:

let
  stdenv = pkgs.clangStdenv;
in 
pkgs.mkShell.override { inherit stdenv; } {
    nativeBuildInputs = with pkgs; [
        clang
        meson
        ninja
        pkg-config
        python3
    ];

    shellHook = ''
        export CC=clang
        export CXX=clang++
        echo "welcome to vim-destroyer env! run ./build.sh to build the final game"
    '';
}
