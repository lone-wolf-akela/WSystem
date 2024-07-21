function WSys_RegisterCustomCode()
  WSys.CustomCode:Register("SA_F01_Probe", "Probe_OnCreate", "Probe_OnUpdate", "Probe_OnDestroy", 2 * 20)
  WSys.CustomCode:Register("SA_F01_Frigate01", "Ion_OnCreate", "Ion_OnUpdate", "Ion_OnDestroy", 5 * 20)
  -- CustomCode can also be registered for non ship entities!
  -- If you do not need any of the 3 callbacks, you can pass an empty string.
  -- The first trigger of the on_update function will happen after 20 seconds (400 ticks) after they're born.
  WSys.CustomCode:Register("Resource_Asteroid_large_Visible", "", "Resource_OnUpdate", "Resource_OnDestroy", 20 * 20)
end

--- @param entity_id integer
function Resource_OnUpdate(entity_id)
  -- kill all large RUs after 20 seconds
  WSys.Entity:MakeDead(entity_id, false, true, true, true)
end

--- @param entity_id integer
function Resource_OnDestroy(entity_id)
  print(string.format("resource %d destroyed\n", entity_id))
end

--- @param entity_id integer
function Ion_OnCreate(entity_id)
  print(string.format("ion frigate %d created\n", entity_id))
end

--- @param entity_id integer
function Ion_OnDestroy(entity_id)
  print(string.format("ion frigate %d destroyed\n", entity_id))
end

--- @param entity_id integer
function Ion_OnUpdate(entity_id)
  local stance = WSys.Entity:GetStance(entity_id)
  local formation = WSys.Entity:GetFormation(entity_id)
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
  print(string.format("ion frigate %d @ stance `%s`(%d) @ formation `%s`\n", entity_id, stance_str, stance, formation))
end

--- @param entity_id integer
function Probe_OnCreate(entity_id)
  print(string.format("probe %d created\n", entity_id))
end

--- @param entity_id integer
function Probe_OnDestroy(entity_id)
  print(string.format("probe %d destroyed\n", entity_id))
end

Probe_HyperspaceDest = {
  { 0, 0,     0 },
  { 0, 10000, 0 },
  { 0, 0,     10000 }
}

--- @param entity_id integer
function Probe_OnUpdate(entity_id)
  LastProbeJumpTarget = LastProbeJumpTarget or {}
  LastProbeJumpTarget[entity_id] = LastProbeJumpTarget[entity_id] or -1
  LastProbeJumpTarget[entity_id] = (LastProbeJumpTarget[entity_id] + 1) % 3
  local dest = Probe_HyperspaceDest[LastProbeJumpTarget[entity_id] + 1]

  -- print(string.format("probe %d jump to (%f, %f, %f)\n", entity_id, dest[1], dest[2], dest[3]))
  WSys.Entity:Teleport(
    entity_id,
    0, 0, 0, 0,                -- rotate
    dest[1], dest[2], dest[3], -- xyz
    1, 1, 1,                   -- scale
    false                      -- teleport_ships_in_parade
  )
end
