function WSys_RegisterCustomCode()
  WSys.CustomCode:Register("SA_F01_Probe", "Probe_OnCreate", "Probe_OnUpdate", "Probe_OnDestroy", 2 * 20)
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
