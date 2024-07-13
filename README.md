# Wolf System

A Lua scripting system for Homeworld 3, built on the [RE-UE4SS](https://github.com/UE4SS-RE/RE-UE4SS/) platform. It aims to provide a scripting experience similar to Homeworld 2 and Homeworld Remastered.

## Major Features

### Currently Available:
- Unlock and lock research based on the player's ships.
  - Supports complex requirements, such as needing `any of` / `all of` / `none of` certain ship types, making it possible to bring back the detailed tech tree we are all familiar with. 

### Planned:
- Advanced tech tree management:
  - Keep specific units docked or latched to production ships to emulate ship subsystems.
  - Control production per ship, allowing carriers to build specific units only if they have the necessary production modules.
- Advanced production line control:
  - Limit the number of units each production ship can build simultaneously.
- Complete Lua system to control ships' and players' behavior:
  - Includes `SobGroup_*`, `Player_*`, `Volume_*`, and `Universe_*` functions.
  - Features a `Rule_Init()` entry point.
  - Supports `Rule_Add()` and `Rule_AddInterval()`.
  - Enables custom code per ship, with function calls on ship creation, destruction, and existence.
  - Additional features for building special ship abilities, similar to the [XSystem](https://github.com/lone-wolf-akela/XSystem/).

## Current Limitations

- AI players may not follow the tech tree defined by WSystem and could build locked units without meeting the requirements.
- When a build option changes from unlocked to locked (e.g., if the player loses their "production module ship"), ongoing build tasks are not canceled.

## How to Use

Download the latest version from the [Releases](https://github.com/lone-wolf-akela/WSystem/releases) page and follow the instructions provided there.

## How to Build

To build from source, first clone the repository:

```
git clone --recursive https://github.com/lone-wolf-akela/WSystem/
```

Then, follow the UE4SS guide for [Creating a C++ Mod](https://github.com/UE4SS-RE/RE-UE4SS/blob/e4a1d607fb39fc164b7bd71a09b09d1040d0b2d3/docs/guides/creating-a-c%2B%2B-mod.md).

## License

This project is licensed under the Apache License, Version 2.0. 

### What You Can Do:
- **Use**: You are free to use this software for any purpose.
- **Modify**: You can modify the source code to suit your needs.
- **Distribute**: You can distribute the original or modified versions of the software.
- **Sublicense**: You can grant others the right to use the software under this license.
- **Patent Rights**: You are granted a license to any patents that cover the software.

### What You Cannot Do:
- **Trademark Use**: You cannot use the project's name, logos, or trademarks without permission.
- **Liability**: The software is provided "as is", without warranty of any kind. The authors are not liable for any damages or issues that arise from using the software.
- **Endorsement**: You cannot imply that your modified version is endorsed by the original authors.

For more details, you can read the full text of the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0).

