function FindPlayer0Scouts()
  WSys.SobGroup:CreateOrClear("player_0_allships")
  WSys.SobGroup:FillGroupFromPlayer("player_0_allships", 0, true, true, false)

  WSys.SobGroup:CreateOrClear("player_0_scouts")
  WSys.SobGroup:FillGroupFromFilteredType(
    "player_0_scouts", "player_0_allships", { "SA_F01_Fighter01" })
  local n = WSys.SobGroup:GroupCount("player_0_scouts")
  print("find " .. n .. " scouts.\n")

  WSys.Rule:AddInterval("JumpScouts", 5 * 20)
end

HyperspaceDest = {
  { 0, 0,     0 },
  { 0, 10000, 0 },
  { 0, 0,     10000 }
}

function JumpScouts()
  JumpTarget = JumpTarget or -1
  JumpTarget = (JumpTarget + 1) % 3
  local dest = HyperspaceDest[JumpTarget + 1]
  -- print("jump to [" .. JumpTarget .. "]: " .. dest[1] .. ", " .. dest[2] .. ", " .. dest[3] .. "\n")
  WSys.SobGroup:Teleport(
    "player_0_scouts",
    0, 0, 0, 0,                -- rotate
    dest[1], dest[2], dest[3], -- xyz
    1, 1, 1,                   -- scale
    false                      -- skip_placement_logic
  )
end

SpawnDest = {
  { 100000, 0,     0 },
  { 100000, 10000, 0 },
  { 100000, 0,     10000 }
}

function SpawnFighter()
  SpawnTarget = SpawnTarget or -1
  SpawnTarget = (SpawnTarget + 1) % 3
  local dest = SpawnDest[SpawnTarget + 1]

  WSys.SobGroup:CreateOrClear("create_fighter_group")
  WSys.SobGroup:CreateShipSimple(
    "create_fighter_group",
    dest[1], dest[2], dest[3],
    0, 0, 0,
    0,                       -- std::int32_t owning_player
    false,                   -- bool start_in_hyperspace
    false,                   -- bool skip_placement_logic,
    "SA_F01_Fighter02",      -- std::string_view ship_type,
    1,                       -- std::int32_t ship_count,
    SquadronStance.Aggressive, -- SquadronStance stance,
    false,                   -- bool use_retaliation_override,
    RetaliationSetting.None, -- RetaliationSetting retaliation_override,
    true                     -- bool do_not_retaliate_against_me
  )
  local n = WSys.SobGroup:GroupCount("create_fighter_group")
  -- print("find " .. n .. " fighters.\n")
end

function FindResource()
  WSys.SobGroup:CreateOrClear("all_nonship_entities")
  WSys.SobGroup:FillGroupAllAliveNonShipEntitiesInGame("all_nonship_entities")
  local n = WSys.SobGroup:GroupCount("all_nonship_entities")
  print("find " .. n .. " nonship entities.\n")

  local t = WSys.SobGroup:GroupMembers("all_nonship_entities")
  for i, entity in pairs(t) do
    if WSys.Entity:IsResource(entity) then
      print(string.format("entity [%d] = %s\n", i, WSys.Entity:GetEntityInternalName(entity)))
    end
  end

  -- WSys.SobGroup:MakeDead("all_nonship_entities", true, true, true, true)
end

function Rule_OnInit()
  WSys.Rule:AddIntervalOneTime("FindPlayer0Scouts", 5 * 20)
  WSys.Rule:AddInterval("SpawnFighter", 10 * 20)
  WSys.Rule:AddIntervalOneTime("FindResource", 5 * 20)

  local tick = WSys.Universe:GameFrame()
  print(string.format("Rule_OnInit: tick = %d\n", tick))
end
