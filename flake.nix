{
  description = "Bitcoinkernel Club - Learn libbitcoinkernel";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    nix-bitcoinkernel.url = "github:yuvicc/nix-bitcoinkernel";
  };

  outputs = { self, nixpkgs, flake-utils, nix-bitcoinkernel }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        bitcoinkernel = nix-bitcoinkernel.packages.${system}.default;
      in
      {
        devShells = {
          # Default shell with everything
          default = pkgs.mkShell {
            buildInputs = [
              bitcoinkernel
              pkgs.clang
              pkgs.gnumake
              pkgs.gdb
              pkgs.ccls
            ];

            shellHook = ''
              echo "=========================================="
              echo "  Bitcoinkernel Club - Bitshala"
              echo "=========================================="
              echo ""
              echo "Available sessions:"
              echo "  nix develop .#session1"
              echo "  ...end"
              echo ""
              echo "Or cd into sessions/sessionX and run: nix develop"
              echo ""
            '';
          };

          # Session 1: Introduction & C API basics
          session1 = pkgs.mkShell {
            buildInputs = [
              bitcoinkernel
              pkgs.clang
              pkgs.gnumake
              pkgs.gdb
            ];

            shellHook = ''
              echo "=========================================="
              echo "  Session 1: Introduction to Bitcoinkernel"
              echo "  & C API Basics"
              echo "=========================================="
              echo ""
              echo "Objectives:"
              echo "  - Understand the libbitcoinkernel C API"
              echo "  - Validate a script (non-contextual)"
              echo ""
              echo "Getting started:"
              echo "  cd sessions/session1"
              echo "  make        # compile"
              echo "  make run    # run"
              echo ""
              echo "Edit src/main.c and complete the TODOs!"
              echo ""
              cd sessions/session1 2>/dev/null || true
            '';
          };

          # Session 2: Hands on with Bitcoinkernel API
          session2 = pkgs.mkShell {
            buildInputs = [
              bitcoinkernel
              pkgs.clang
              pkgs.gnumake
              pkgs.gdb
            ];

            shellHook = ''
              echo "=========================================="
              echo "  Session 2: Handson with Bitcoinkernel API"
              echo "=========================================="
              echo ""
              echo "Objectives:"
              echo "  - Understand the libbitcoinkernel C API"
              echo "  - Validate & process a block (contextual)"
              echo ""
              echo "  make        # compile"
              echo "  make run    # run"
              echo ""
              echo ""
              cd sessions/session2 2>/dev/null || true
            '';
          };

          # Session 3
        };
      }
    );
}