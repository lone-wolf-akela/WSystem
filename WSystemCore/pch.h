#pragma once

#include <sol/sol.hpp>
#undef check

#include <memory>
#include <optional>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <compare>
#include <utility>
#include <source_location>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <format>
#include <string_view>
#include <optional>
#include <tuple>
#include <stdexcept>
#include <ranges>
#include <functional>
#include <type_traits>

#include <magic_enum_all.hpp>
#include <boost/nowide/convert.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>

#include <UnrealContainers/UnrealContainers.h>

#include <Mod/CppUserModBase.hpp>

#include <Unreal/AGameModeBase.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/World.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/FProperty.hpp>
#include <Unreal/UClass.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/Transform.hpp>
#include <Unreal/Rotator.hpp>
#include <Unreal/FOutputDevice.hpp>
#include <Unreal/Core/Containers/Set.hpp>
#include <Unreal/Core/Containers/Map.hpp>
#include <Unreal/Property/FMulticastDelegateProperty.hpp>

#include <LuaMadeSimple/LuaMadeSimple.hpp>

#include <DynamicOutput/Output.hpp>
