# :nut_and_bolt: nutsh

[![Build Status](https://img.shields.io/travis/com/remicmacs/nutsh/master.svg?style=for-the-badge&logo=travis)](https://travis-ci.com/remicmacs/nutsh) [![License CRAPL](https://img.shields.io/badge/License-CRAPL-1C1C1D.svg?style=for-the-badge&labelColor=B0AEAF)](CRAPL-LICENSE.txt) ![Code size](https://img.shields.io/github/languages/code-size/remicmacs/nutsh.svg?style=for-the-badge) [![GitHub release](https://img.shields.io/github/release/remicmacs/nutsh.svg?style=for-the-badge)](https://github.com/remicmacs/nutsh/releases/latest)

[![Built for Linux](https://img.shields.io/badge/Built%20for-Linux-C13D3B.svg?style=for-the-badge&labelColor=EA4761&logo=linux&logoColor=FFFFFF)](https://www.gnu.org/home.en.html) [![Built for MacOSX](https://img.shields.io/badge/Built%20for-MacOSX-C13D3B.svg?style=for-the-badge&labelColor=EA4761&logo=apple&logoColor=FFFFFF)](https://i.chzbgr.com/full/4378633984/h42BE4AB4/) [![Made with C++](https://img.shields.io/badge/Made%20with-C++-C1282D.svg?style=for-the-badge&labelColor=EF4041)](https://isocpp.org/) [![Works on my machine](https://img.shields.io/badge/Works-on%20my%20machine-5593C7.svg?style=for-the-badge&labelColor=A7BFC1)](https://i.redd.it/ygjaybp2l5c21.jpg)

Pronounced *« nutshell »* (/ˈnʌtʃel/)

<img align="right" src="logo.png" alt="drawing" width="128px"/>

- [:sparkles: Features](#sparkles-features)
- [:checkered_flag: Getting started](#checkeredflag-getting-started)
  - [:package: Build dependencies](#package-build-dependencies)
  - [:clown_face: `make` for dummies](#clownface-make-for-dummies)
  - [:penguin: Compilation on Debian systems](#penguin-compilation-on-debian-systems)
- [:gear: Builtin commands](#gear-builtin-commands)
- [:memo: Documentation](#memo-documentation)
- [:mailbox: Contact us](#mailbox-contact-us)
- [:interrobang: What the hell is this versioning scheme ?](#interrobang-what-the-hell-is-this-versioning-scheme)

[![Asciinema](res/asciinema.gif)](https://asciinema.org/a/RDZOFZoycUhqoW25VII5tl6AX)

## :sparkles: Features

nutsh is **barely usable** ! Enjoy using your system **the hard way** ! With nutsh, become a truly hardcore Linux guru ! After all if it's painless, is it really worth it ? (*hint*: it's not).

Here is some of the most notable features :

- Command history
- File autocompletion
- Command expansion
- Cool name
- Really fast (thanks to almost no unnecessary features)

## :checkered_flag: Getting started

A build script is [available for Arch Linux](https://github.com/rodolpheh/nutsh-pkgbuild/). For any other cases, please follow the instructions below.

### :package: Build dependencies

- `make`
- `g++`
- `readline`

### :clown_face: `make` for dummies

1. Clone the repo

   ```bash
   git clone https://github.com/remicmacs/nutsh.git
   ```

2. Get in the clone repo

    ```bash
    cd nutsh
    ```

3. Build the shell with `make`
4. *Voilà* !! :tada:

### :penguin: Compilation on Debian systems

On Debian and Ubuntu systems you can build the project like this :

1. Install needed software

   ```bash
   apt install libreadline-dev unzip build-essential
   ```

2. Dowload the source

   ```bash
   wget https://github.com/remicmacs/nutsh/archive/master.zip
   ```

3. Decompress and step into directory

   ```bash
   unzip master.zip
   cd nusth-master
   ```

4. Launch compilation with `make`

   ```bash
   make
   ```

5. That's it ! :tada:

## :gear: Builtin commands

Here is a list of shell builtin commands implemented in nutsh.

| Command name | Takes arguments    | Has options        | Status             |
| ------------ | ------------------ | ------------------ | ------------------ |
| `cd`         | :heavy_check_mark: | :x:                | :heavy_check_mark: |
| `pwd`        | :x:                | :x:                | :heavy_check_mark: |
| `exit`       | :x:                | :x:                | :heavy_check_mark: |
| `echo`       | :heavy_check_mark: | :x:                | :heavy_check_mark: |
| `type`       | :x:                | :x:                | :heavy_check_mark: |
| `export`     | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |

## :memo: Documentation

Some (very basic) documenation is provided. Most of it is inline in the source.

[Specifications](specifications.md) are provided. They are in French, as required by the assignment.
A lot of it is not yet implemented, but might be one day if we feel like it.

Anyone wanting to have a broader look at this project should build the docs with [doxygen](http://doxygen.nl/) and the provided configuration :

```bash
doxygen doxygenrc
```

HTML docs would then be accessible with `docs/html/index.html` being the entrypoint.

The documentation is far from perfect but it helps.

## :mailbox: Contact us

You can get in touch with the dev team in a really straightforward way :

1. Fork the repo
2. Obfuscate your message
3. Hide it in the source with steganography technics of your liking
4. Make a Pull Request
5. PR is ignored during an indefinitely long amount of time
6. Lose all hope
7. You don't want to get in touch anymore
8. Success : it was a school project anyways!

## :interrobang: What the hell is this versioning scheme ?

This is a new versioning scheme we invented that we're calling *revolver* (for *revolution* - *version*). It is based on [*calver*](http://calver.org/) but it uses the [Holocen calendar](https://en.wikipedia.org/wiki/Holocene_calendar) for the year and the [French Republican calendar](https://en.wikipedia.org/wiki/French_Republican_calendar) for the month and day. If you plan to release more than a version in a day, you can add a revision number by appending the current time in [decimal time](https://en.wikipedia.org/wiki/French_Republican_calendar).

As an example, this is the version of the first release :

```
12019.07.26-0870
──┬── ┌─ ┌─ ─┬──
  │   │  │   │
──┴─ ─┘ ─┘ ──┴───────────
2019-04-16T20:52:00+02:00
```

We can deduce the release date, in the standard ISO time:

|      Fragment       | Conversion                  |
| :-----------------: | :-------------------------- |
|      **12019**      | 12019 - 10000 = **2019 AD** |
| **07** (*Germinal*) | **04** (*April*)            |
|  **26** (*Lilas*)   | **16** (*Saint Paterne*)    |
|  **0870** (08h70)   | 8 * 2.4 = 19h 12min         |
|                     | 70 * 1.44 = 1h 40min        |
|                     | Total : **20h 52min**       |

Or in a simpler way : 12019.07.26-0870 = 2019-04-16T20:52:00+02:00.