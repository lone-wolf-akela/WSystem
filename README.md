# Wolf System

A Lua scripting system for Homeworld 3, built on the [RE-UE4SS](https://github.com/UE4SS-RE/RE-UE4SS/) platform. It aims to provide a scripting experience similar to Homeworld 2 and Homeworld Remastered.

## Major Features

### Currently Available:

#### - Research Module

Unlock and lock research based on complex preconditions determined by player-owned ships and unlocked research.

- Supports complex requirements, such as needing `any of` / `all of` / `none of` certain ship types and/or research, making it possible to bring back the detailed tech tree we are all familiar with.

#### - Rule Module

Just like Homeworld Remastered. You get the `Rule_OnInit()` entry point and an interface to schedule the execution of Lua functions at any time you want.

Including the following interface:

- `Rule:Add(name)`
- `Rule:AddInterval(name, interval)`
- `Rule:AddIntervalOneTime(name, interval)`
- `Rule:AddParam(name, param)`
- `Rule:AddParamInterval(name, param, interval)`
- `Rule:AddParamIntervalOneTime(name, param, interval)`
- `Rule:Remove(name)`
- `Rule:RemoveParam(name, param)`
- `Rule:Exists(name)`
- `Rule:ParamExists(name, param)`

#### - CustomCode Module

Execute Lua functions on entity creation, destruction, and during their existence. You can register CustomCode callbacks for any ships and even non-ship entities like RUs and missiles.

Using an interface familiar to Homeworld Remastered modders:

- `CustomCode:Register(unit_type, on_create, on_update, on_destroy, update_interval)`
- And define callbacks like this:
  - `SomeShip_OnCreate(entity_id)`
  - `SomeShip_OnUpdate(entity_id)`
  - `SomeShip_OnDestroy(entity_id)`

#### - Function Libraries

Including Lua bindings to various useful functions, divided into 4 libraries: `SobGroup`, `Entity`, `Player`, and `Universe`.

We currently have bindings for 214 functions, and the number is continuously rising.

### Planned:

- Advanced tech tree management:
  - Keep specific units docked or latched to production ships to emulate ship subsystems.
  - Control production per ship, allowing carriers to build specific units only if they have the necessary production modules.
- Advanced production line control:
  - Limit the number of units each production ship can build simultaneously.
- Complete Lua system to control ships' and players' behavior:
  - Provide more Lua function bindings.
  - Additional features for building special ship abilities, similar to the [XSystem](https://github.com/lone-wolf-akela/XSystem/).

## Current Limitations

- AI players may not understand the tech tree defined by WSystem.
- When a build option changes from unlocked to locked (e.g., if the player loses their "production module ship"), ongoing build tasks are not canceled.
- Not all functions in our function libraries have been tested. Some of them may not work, return wrong results, or even crash the game.

## How to Use

Download the latest version from the [Releases](https://github.com/lone-wolf-akela/WSystem/releases) page.

For mod developers, download the `-Dev` version; for players, download the `-Player` version. The dev version provides a debug console while the player version does not.

Unzip the file, and put the `dwmapi.dll` file and `ue4ss` folder in `Homeworld 3\Homeworld3\Binaries\Win64`.

Start a new game as Hiigaran Fleet; you should see the system has already begun to function. If you see things like your probes and scouts jumping everywhere, it means the installation is successful.

Now you can look at the Lua scripts in `ue4ss\Mods\WSystem\scripts`. You can edit the example codes in `research.lua`, `rule.lua`, and `custom_code.lua`. The `type.lua` file provides a full list of supported functions.

We recommend you use [VS Code](https://code.visualstudio.com/) with the [Lua Plugin by sumneko](https://marketplace.visualstudio.com/items?itemName=sumneko.lua) installed to edit these Lua scripts, as it provides full code completion and type-checking support.

## How to Build

- To build from source, first install [Vcpkg](https://github.com/microsoft/vcpkg).

- Then, download all the requested things in [RE-UE4SS build requirements](https://github.com/UE4SS-RE/RE-UE4SS/tree/e4a1d607fb39fc164b7bd71a09b09d1040d0b2d3?tab=readme-ov-file#build-requirements).

- And make sure you have access to the Unreal Engine source code GitHub repo:
  1. Make an Epic account and link it to your GitHub account.
  2. Check your email and accept the invitation to the @EpicGames GitHub organization for Unreal source access.
  3. Setup SSH keys on your GitHub account which will let git access the Unreal source you got access in previous steps.

- Now clone the repository:

  ```cmd
  git clone --recursive https://github.com/lone-wolf-akela/WSystem/
  ```

- Generating project files:

  ```cmd
  cd WSystem
  xmake project -k vsxmake2022
  ```

- Open the solution at `WSystem/vsxmake2022/WSystem.sln`; make sure that you're set to the `Game___Shipping__Win64` configuration unless you want to debug. Find the `WSystemCore` project in the solution explorer and right click it and hit `Build`.

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
