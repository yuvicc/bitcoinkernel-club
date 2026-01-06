# Bitcoinkernel Club

Welcome to the **Bitcoinkernel Club** hosted by [Bitshala](https://bitshala.org)!

This club focuses on understanding and contributing to [libbitcoinkernel](https://github.com/orgs/bitcoin/projects/3/views/1) — the project extracting Bitcoin Core's consensus engine into a reusable C library.

# What the heck is Bitcoinkernel (or libbitcoinkernel), and why is there a requirement for it?

If you are familiar with Bitcoin nodes (if not, you can learn more about them [here](https://learnmeabitcoin.com/beginners/guide/node/)), you'll know that Bitcoin Core is actually a reference implementation for Bitcoin nodes. You can use Bitcoin Core to interact with the Bitcoin network. There are other implementations as well, such as BTCD, libbitcoin, etc.

So what do you think is the most important aspect that keeps everyone in agreement on a Bitcoin network? If your guess is some code or an algorithm running inside the Bitcoin nodes (Bitcoin Core, BTCD, libbitcoin, etc.), then you are correct. This is simply known as **Validation Logic** or the **Consensus Engine**. This logic validates blocks and transactions, which is what matters to most of us. We want at least the client (Bitcoin Core, BTCD, etc.) to validate blocks and transactions correctly.

When Satoshi wrote the first reference implementation after the white paper (i.e., Bitcoin Core), he wrote all the validation logic, P2P, wallet, and everything in C++. After the reference implementation came alternate clients such as BTCD, libbitcoin, etc., which have their own Consensus Engine/Validation Logic written from scratch. This means we could have consensus bugs. Why? Because different programming languages have different quirks, and that is a problem. This means we can have differences in the consensus engines of different clients.

As of 2025, 98%+ of nodes are running Bitcoin Core, or basically running the Bitcoin Core consensus engine. We have also seen that BTCD/libbitcoin had previously known consensus bugs, which have been fixed now, but there might be more we don't know about. So the problem is: **if Consensus Engines differ, we will have a network split**. This keeps Bitcoin developers up at night. Having a uniform consensus engine could solve this ambiguity.

This is where the **Bitcoinkernel** project comes into the picture. The Bitcoinkernel project aims to extract the consensus engine and expose it as a reusable library so that other clients can use it and experiment with their projects while staying within the Bitcoin network. This project provides safe and easy experimentation for developers.

As of January 2026, the first step towards a reusable API was provided by PR [#30595](https://github.com/bitcoin/bitcoin/pull/30595), which has been merged into Bitcoin Core.

Since the library is provided via a C API, we will also discuss why C has been used for the API. To ease the use of the library in popular programming languages, different language bindings are available. Currently, we have:

## Getting Started

We use Nix to ensure everyone has a consistent development environment with pre-compiled Bitcoin Core and libbitcoinkernel.

### 1. Install [Nix](https://nixos.org/download) 
```bash
sh <(curl --proto '=https' --tlsv1.2 -L https://nixos.org/nix/install) --daemon
```

### 2. Clone this repo
```bash
git clone https://github.com/bitshala/bitcoinkernel-club.git
cd bitcoinkernel-club
```

### 3. Enter a session shell
```bash
# For session 1
nix develop .#session1
```

### 4. Complete the exercises
```bash
cd sessions/session1
make
make run
```

Edit `src/main.c` and complete the TODOs!


## Club Overview

- **When:** Every Thursday at 19:00 IST / 13:30 UTC
- **Starting:** January 8th, 2026
- **Duration:** 12 sessions
- **Where:** [Bitshala Discord](https://discord.gg/bitshala)

## What We'll Cover

- Understanding the C API and its design principles
- Memory management in the kernel library
- Chainstate, blocks, and transaction validation APIs
- Building simple Rust and C++ bindings from scratch
- Reviewing open PRs related to the kernel project

## Sessions

| Session | Date | Topic | Discussion | Recording |
|---------|------|-------|------------|-----------|
| 1 | Jan 8, 2026 | Introduction to Bitcoinkernel & C API basics | [Link](https://github.com/yuvicc/bitcoinkernel-club/issues/1) | [YouTube(TBA)]() |
| 2 | Jan 15, 2026 | Memory management & Logging API | [Link(TBA)]() | [YouTube(TBA)]() |
| 3 | Jan 22, 2026 | Chainstate API | [Link(TBA)]() | [YouTube(TBA)]() |
| 4 | Jan 29, 2026 | Blocks API | [Link(TBA)]() | [YouTube(TBA)]() |
| 5 | TBD | BlockTree API | [Link(TBA)]() | [YouTube(TBA)]() |
| 6 | TBD | Transaction & Script validation | [Link(TBA)]() | [YouTube(TBA)]() |
| 7 | TBD | Completing & testing our bindings | [Link(TBA)]() | [YouTube(TBA)]() |
| 8 | TBD | Java, Go & Python bindings | [Link(TBA)]() | [YouTube(TBA)]() |
| 9 | TBD | PR Review: #33856 & #33822 | [Link(TBA)]() | [YouTube(TBA)]() |
| 10 | TBD | PR Review: #33796 | [Link(TBA)]() | [YouTube(TBA)]() |
| 11 | TBD | PR Review: #33908 | [Link(TBA)]() | [YouTube(TBA)]() |
| 12 | TBD | TBD | [Link(TBA)]() | [YouTube(TBA)]() |

## Key Resources

### PRs We'll Review
- [#30595](https://github.com/bitcoin/bitcoin/pull/30595) - First step towards reusable kernel API (merged)
- [#33856](https://github.com/bitcoin/bitcoin/pull/33856)
- [#33822](https://github.com/bitcoin/bitcoin/pull/33822)
- [#33796](https://github.com/bitcoin/bitcoin/pull/33796)
- [#33908](https://github.com/bitcoin/bitcoin/pull/33908)
- And many more.

### Language Bindings
- **Rust:** [rust-bitcoinkernel](https://github.com/TheCharlatan/rust-bitcoinkernel)
- **Python:** [py-bitcoinkernel](https://github.com/stickies-v/py-bitcoinkernel)
- **Go:** [go-bitcoinkernel](https://github.com/stringintech/go-bitcoinkernel)
- **Java/JDK:** [bitcoinkernel-jdk](https://github.com/yuvicc/bitcoinkernel-jdk)
- **.NET:** [BitcoinKernel.NET](https://github.com/janb84/BitcoinKernel.NET)

### Further Reading
- [Bitcoin Kernel Project Tracking Issue](https://github.com/bitcoin/bitcoin/issues/27587)
- [Learn Me a Bitcoin - Nodes](https://learnmeabitcoin.com/beginners/guide/node/)

## Prerequisites

Just some basics of Bitcoin and programming languages. We'll be covering everything from scratch!

## How to Participate

1. Join the [Bitshala Discord](https://discord.gg/atjEPVTdsQ).
2. Each review topic is detailed in an [Issue](https://github.com/yuvicc/bitcoinkernel-club) - use the comments to post questions and discuss the PR.
3. Come prepared by reading the linked materials
4. Join the live session every Thursday at 19:00 IST / 13:30 UTC

## Contributing

Found something to improve? Feel free to open an issue or submit a PR!

## License

This repository is for educational purposes. All content is provided under [MIT License](LICENSE).

---

**Hosted by [Bitshala](https://bitshala.org)** | Follow us on [X/Twitter](https://x.com/bitshala_org)
