function Rule_OnInit()
  WSys.Rule:AddIntervalOneTime("FindPlayer0Scouts", 5 * 20)
  WSys.Rule:AddInterval("SpawnFighter", 10 * 20)
  WSys.Rule:AddIntervalOneTime("FindResource", 5 * 20)

  local tick = WSys.Universe:GameFrame()
  print(string.format("Rule_OnInit: tick = %d\n", tick))

  -- At tick 0, players are not yet initialized.
  -- So we need to wait a bit before we can fix the CPU player names.
  WSys.Rule:AddIntervalOneTime("FixCpuPlayerName", 1)

  WSys.Rule:AddIntervalOneTime("MotherShipAnimation", 2 * 20)
end

function MotherShipAnimation()
  WSys.SobGroup:CreateOrClear("player_0_allships")
  WSys.SobGroup:FillGroupFromPlayer("player_0_allships", 0, true, true, false)

  WSys.SobGroup:CreateOrClear("player_0_motherships")
  WSys.SobGroup:FillGroupFromFilteredType(
    "player_0_motherships", "player_0_allships", { "SA_F01_Mothership01_PVP" })
  local n = WSys.SobGroup:GroupCount("player_0_motherships")
  print("find " .. n .. " motherships.\n")

  local motherships = WSys.SobGroup:GroupMembers("player_0_motherships")
  local mothership = motherships[1]

  WSys.Entity:SetAnimationState(mothership, SobAnimationState.DockPathOpen, true)
end


function FindPlayer0Scouts()
  WSys.SobGroup:CreateOrClear("player_0_allships")
  WSys.SobGroup:FillGroupFromPlayer("player_0_allships", 0, true, true, false)

  WSys.SobGroup:CreateOrClear("player_0_scouts")
  WSys.SobGroup:FillGroupFromFilteredType(
    "player_0_scouts", "player_0_allships", { "SA_F01_Fighter01" })
  local n = WSys.SobGroup:GroupCount("player_0_scouts")
  print("find " .. n .. " scouts.\n")

  local scouts = WSys.SobGroup:GroupMembers("player_0_scouts")
  local is_member_1 = WSys.SobGroup:GroupContains("player_0_scouts", scouts[1])
  local is_member_2 = WSys.SobGroup:GroupContains("player_0_scouts", scouts[1] + 1)

  print(string.format("%d is member of player_0_scouts: %s\n", scouts[1], tostring(is_member_1)))
  print(string.format("%d is member of player_0_scouts: %s\n", scouts[1] + 1, tostring(is_member_2)))

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
  WSys.SobGroup:GroupPurgeDead("player_0_scouts")
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
end

function FixCpuPlayerName()
  local count = WSys.Player:PlayerCount()
  print(string.format("Found %d players.\n", count))
  for i = 0, count - 1 do
    local name = WSys.Player:GetPlayerName(i)
    local team = WSys.Player:GetPlayerTeamID(i)
    local is_human = WSys.Player:IsHuman(i)
    print(string.format("Player %d: name = %s, team = %d, is_human = %s\n", i, name, team, is_human))
    if not is_human then
      WSys.Player:SetPlayerName(i, string.format("CPU %d", i))
    end
  end
end