function WSys_RegisterCustomCode()
  WSys.CustomCode:Register("SA_F01_Probe", "Probe_OnCreate", "Probe_OnUpdate", "Probe_OnDestroy", 2 * 20)
  WSys.CustomCode:Register("SA_F01_Frigate01", "Ion_OnCreate", "Ion_OnUpdate", "Ion_OnDestroy", 5 * 20)
end

function Ion_OnCreate(ShipID)
  print(string.format("ion frigate %d created\n", ShipID))
end

function Ion_OnDestroy(ShipID)
  print(string.format("ion frigate %d destroyed\n", ShipID))
end

function Ion_OnUpdate(ShipID)
  local stance = WSys.Entity:GetStance(ShipID)
  local formation = WSys.Entity:GetFormation(ShipID)
  local stance_str
  if stance == SquadronStance.Aggressive then
    stance_str = "Aggressive"
  elseif stance == SquadronStance.Evasive then
    stance_str = "Evasive"
  elseif stance == SquadronStance.Neutral then
    stance_str = "Neutral"
  else
    stance_str = "Unknown"
  end
  print(string.format("ion frigate %d @ stance `%s`(%d) @ formation `%s`\n", ShipID, stance_str, stance, formation))
end

function Probe_OnCreate(ShipID)
  print(string.format("probe %d created\n", ShipID))
end

function Probe_OnDestroy(ShipID)
  print(string.format("probe %d destroyed\n", ShipID))
end

Probe_HyperspaceDest = {
  { 0, 0,     0 },
  { 0, 10000, 0 },
  { 0, 0,     10000 }
}

function Probe_OnUpdate(ShipID)
  LastProbeJumpTarget = LastProbeJumpTarget or {}
  LastProbeJumpTarget[ShipID] = LastProbeJumpTarget[ShipID] or -1
  LastProbeJumpTarget[ShipID] = (LastProbeJumpTarget[ShipID] + 1) % 3
  local dest = Probe_HyperspaceDest[LastProbeJumpTarget[ShipID] + 1]

  print(string.format("probe %d jump to (%f, %f, %f)\n", ShipID, dest[1], dest[2], dest[3]))
  WSys.Entity:Teleport(
    ShipID,
    0, 0, 0, 0,                -- rotate
    dest[1], dest[2], dest[3], -- xyz
    1, 1, 1,                   -- scale
    false                      -- teleport_ships_in_parade
  )
end
