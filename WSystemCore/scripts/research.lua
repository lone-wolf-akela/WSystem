function WSys_SetupResearchConditions()
  -- Condition 1
  WSys:AddResearchCondition(
    -- Research for hgn interceptor
    "Skirmish_F01_Fighter02_Research", 
    -- Player can only build the interceptor if they have both a scout and a probe
    "SA_F01_Fighter01, SA_F01_Probe",  
    -- And they do not have an ion frigate
    "SA_F01_Frigate01",
    "",
    ""
  )

  -- WSys:AddResearchCondition can be called multiple times.
  -- Each call adds a new condition.
  -- Skirmish_F01_Fighter02_Research will be unlocked if either 
  -- Condition 1 or Condition 2 is met.
  -- In other words, multiple calls to AddResearchCondition create
  -- an "any of" condition group.

  -- Condition 2
  WSys:AddResearchCondition(
    "Skirmish_F01_Fighter02_Research", 
    -- Player can also build the interceptor if they have any assault frigates
    "SA_F01_Frigate02",  
    "",
    "",
    ""
  )

  -- Ion frigates require at least one scout to build
  WSys:AddResearchCondition(
    "Skirmish_F01_Frigate01_Research", 
    "SA_F01_Fighter01",  
    "",
    "",
    ""
  )

  -- Assault frigates
  WSys:AddResearchCondition(
    "Skirmish_F01_Frigate02_Research", 
    -- require at least one scout to build
    "SA_F01_Fighter01",  
    "",
    -- also requires that the player has unlocked scout speed boost ability
    "Skirmish_F01_Fighter01_BoostSpeedResearch",
    ""
  )
end