# moonflower ![License](https://img.shields.io/badge/License-GPLv2-blue.svg)
A fuse and GPIO dumper for the Switch, to be used with fusée gelée.

*NOTE: Your dump may contain sensitive info that you probably don't want to leak.*

## Usage

 1. Build `moonflower.bin`, or grab one from our [releases](https://github.com/moriczgergo/moonflower/releases).
 2. Run fusée gelée with `moonflower.bin` instead of `fusee.bin`.

## Changes

This section is required by the original license of Atmosphere, GPLv2.

 * This originates from [ktemkin's fork of Atmosphere](https://github.com/ktemkin/Atmosphere) (branch: poc_nvidia).
 * exosphere has been stripped out, only fusee remains.
 * main.c has been modified to print the fuse and GPIO data.
 * Makefile has been modified to only build moonflower.
 * .gitignore has been modified to apply to the new directory structure.
 * README.md has been modified.
 * `shutdown_using_pmic()` (src/main.c) is from [rajkosto's biskeydump](https://github.com/rajkosto/biskeydump).

## Responsibility

**Don't blame me if damage happens to your Switch.** (There shouldn't be any damage tho'.)

## Credits

 * rajkosto, for helping me out with GPIO stuff.
 * ktemkin, for making fusee gelee, and releasing a fusee payload POC.
 * SciresM, for making Atmosphère.
 * Everyone in the ReSwitched Discord. <3