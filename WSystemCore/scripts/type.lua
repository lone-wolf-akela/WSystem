--- @class TiirCommander
TiirCommander = {}

--- @class TiirStatusEffectHandle
TiirStatusEffectHandle = {}

--- @class TiirModifierHandle
TiirModifierHandle = {}

--- @class SquadronTactics
--- @field Aggressive SquadronTactics
--- @field Defensive SquadronTactics
--- @field Passive SquadronTactics
SquadronTactics = {}

--- @class SquadronStance
--- @field Aggressive SquadronStance
--- @field Evasive SquadronStance
--- @field Neutral SquadronStance
SquadronStance = {}

--- @class AutoLaunchSetting
--- @field Launch AutoLaunchSetting
--- @field StayDockedUpToLimit AutoLaunchSetting
--- @field StayDockedAlways AutoLaunchSetting
AutoLaunchSetting = {}

--- @class RetaliationSetting
--- @field Enemies RetaliationSetting
--- @field AttackersOfFriends RetaliationSetting
--- @field AttackersOfUs RetaliationSetting
--- @field None RetaliationSetting
RetaliationSetting = {}

--- @class SobPropertyType
--- @field HealthMax SobPropertyType
--- @field HealthRegenerateDelay SobPropertyType
--- @field HealthRegeneratePerSecond SobPropertyType
--- @field HealthMaxRegeneratePerSecond SobPropertyType
--- @field HealthTransientRegeneratePerSecond SobPropertyType
--- @field ShieldBulletMax SobPropertyType
--- @field ShieldBulletRechargeRate SobPropertyType
--- @field ShieldEmpMax SobPropertyType
--- @field ShieldEmpRechargeRate SobPropertyType
--- @field DamageMitigation SobPropertyType
--- @field DamageRateDustCloud SobPropertyType
--- @field DamageRateNebula SobPropertyType
--- @field MainEngineAccel SobPropertyType
--- @field MainEngineBrake SobPropertyType
--- @field MainEngineMaxSpeed SobPropertyType
--- @field MainEngineMaxSpeedWithFormation SobPropertyType
--- @field RotationAccel SobPropertyType
--- @field RotationBrake SobPropertyType
--- @field RotationMaxSpeed SobPropertyType
--- @field ThrusterAccel SobPropertyType
--- @field ThrusterBrake SobPropertyType
--- @field ThrusterMaxSpeed SobPropertyType
--- @field PrimarySensorRange SobPropertyType
--- @field SecondarySensorRange SobPropertyType
--- @field CloakDetectionLevel SobPropertyType
--- @field VisualRange SobPropertyType
--- @field RetaliationRange SobPropertyType
--- @field RetaliationDistanceFromGoal SobPropertyType
--- @field LeashingRange SobPropertyType
SobPropertyType = {}

--- @class MultiplierType
--- @field Unknown MultiplierType
--- @field MaxHealth MultiplierType
--- @field Speed MultiplierType
--- @field BuildSpeed MultiplierType
--- @field ShipHoldRepairSpeed MultiplierType
--- @field HealthRegenerationRate MultiplierType
--- @field WeaponAccuracy MultiplierType
--- @field WeaponDamage MultiplierType
--- @field ShieldRegenerationRate MultiplierType
--- @field MaxShield MultiplierType
--- @field HyperspaceRecoveryTime MultiplierType
--- @field HyperspaceTime MultiplierType
--- @field HyperspaceCost MultiplierType
--- @field HyperspaceAbortDamage MultiplierType
--- @field Capture MultiplierType
--- @field SensorDistortion MultiplierType
--- @field VisualDistortion MultiplierType
--- @field CloakingTime MultiplierType
--- @field CloakingStrength MultiplierType
--- @field CloakDetection MultiplierType
--- @field MaxSpeed MultiplierType
--- @field VisualRange MultiplierType
--- @field PrimarySensorsRange MultiplierType
--- @field SecondarySensorsRange MultiplierType
--- @field DustCloudSensitivity MultiplierType
--- @field NebulaSensitivity MultiplierType
--- @field ResourceCollectionRate MultiplierType
--- @field ResourceDropOffRate MultiplierType
--- @field ResourceCapacity MultiplierType
--- @field DefenseFieldTime MultiplierType
--- @field CustomCommandTime MultiplierType
--- @field Rotation MultiplierType
--- @field RotationAccel MultiplierType
--- @field RotationBrake MultiplierType
--- @field Thruster MultiplierType
--- @field ThrusterAccel MultiplierType
--- @field ThrusterBrake MultiplierType
--- @field EngineAccel MultiplierType
--- @field EngineBrake MultiplierType
--- @field WeaponCone MultiplierType
--- @field BulletSpeed MultiplierType
--- @field TurretSpeed MultiplierType
--- @field DamageApplied MultiplierType
--- @field AccuracyApplied MultiplierType
--- @field FlightPerf MultiplierType
--- @field ExpireTime MultiplierType
--- @field FireRate MultiplierType
--- @field NavTrench MultiplierType
--- @field ResearchSpeed MultiplierType
--- @field Armour MultiplierType
--- @field WeaponRange MultiplierType
--- @field WeaponRadius MultiplierType
--- @field MaxSpeedWithFormation MultiplierType
MultiplierType = {}

--- @class AbilityType
--- @field None AbilityType
--- @field Move AbilityType
--- @field Attack AbilityType
--- @field Guard AbilityType
--- @field Repair AbilityType
--- @field RepairOverseer AbilityType
--- @field Cloak AbilityType
--- @field Resource AbilityType
--- @field Harvest AbilityType
--- @field Mine AbilityType
--- @field SalvageCapture AbilityType
--- @field SalvageCaptureOverseer AbilityType
--- @field Salvage AbilityType
--- @field SalvageOverseer AbilityType
--- @field Dock AbilityType
--- @field AcceptDocking AbilityType
--- @field Builder AbilityType
--- @field Stop AbilityType
--- @field Hyperspace AbilityType
--- @field Parade AbilityType
--- @field FormHyperspaceGate AbilityType
--- @field HyperspaceViaGate AbilityType
--- @field SensorPing AbilityType
--- @field Retire AbilityType
--- @field DefenseField AbilityType
--- @field DefenseFieldShield AbilityType
--- @field HyperspaceInhibitor AbilityType
--- @field Scuttle AbilityType
--- @field UseSpecialWeaponsInNormalAttack AbilityType
--- @field Steering AbilityType
--- @field Targeting AbilityType
--- @field Sensors AbilityType
--- @field Lights AbilityType
--- @field Custom AbilityType
--- @field Kamikaze AbilityType
--- @field DeployTurret AbilityType
--- @field DeployCounterMeasureFog AbilityType
--- @field ToggleAlternativeShipOrientation AbilityType
--- @field Maneuver AbilityType
--- @field BoostAllies AbilityType
--- @field BoostArmor AbilityType
--- @field BoostProduction AbilityType
--- @field BoostSpeed AbilityType
--- @field BoostWeaponDamage AbilityType
--- @field BoostWeaponRange AbilityType
--- @field BoostWeaponRateOfFire AbilityType
--- @field SpecialAttackTripleShot AbilityType
--- @field SpecialAttackMissileVolley AbilityType
--- @field SpecialAttackMegaBeam AbilityType
--- @field SpecialAttackClusterMissile AbilityType
--- @field SpecialAttackCruiseMissile AbilityType
--- @field SpecialAttackCannonVolley AbilityType
--- @field SpecialAttackFusionRound AbilityType
--- @field SpecialAttackNuke AbilityType
--- @field SelfRepair AbilityType
AbilityType = {}

--- @class InfluenceType
--- @field Unknown InfluenceType
--- @field ThisShipOnly InfluenceType
--- @field AllShipsWithinRadius InfluenceType
--- @field OwnShipsWithinRadius InfluenceType
--- @field EnemyShipsWithinRadius InfluenceType
--- @field AllShipsWithinRadiusExcludingThisShip InfluenceType
--- @field OwnShipsWithinRadiusExcludingThisShip InfluenceType
--- @field EnemyShipsWithinRadiusIncludingSleeping InfluenceType
InfluenceType = {}

--- @class ActivityRelation
--- @field Unknown ActivityRelation
--- @field None ActivityRelation
--- @field Linear ActivityRelation
ActivityRelation = {}

--- @class ParadeMode
--- @field Normal ParadeMode
--- @field InstantWithHyperspace ParadeMode
--- @field Instant ParadeMode
ParadeMode = {}

--- @class ScriptRuleManagerType
ScriptRuleManagerType = {}

--- @param name string
function ScriptRuleManagerType:Add(name) end

--- @param name string
--- @param interval integer @ in ticks
function ScriptRuleManagerType:AddInterval(name, interval) end

--- Add a rule that does not repeat
--- @param name string
--- @param interval integer @ in ticks
function ScriptRuleManagerType:AddIntervalOneTime(name, interval) end

--- @param name string
--- @param param string
function ScriptRuleManagerType:AddParam(name, param) end

--- @param name string
--- @param param string
--- @param interval integer @ in ticks
function ScriptRuleManagerType:AddParamInterval(name, param, interval) end

--- Add a rule that does not repeat
--- @param name string
--- @param param string
--- @param interval integer @ in ticks
function ScriptRuleManagerType:AddParamIntervalOneTime(name, param, interval) end

--- @param name string
function ScriptRuleManagerType:Remove(name) end

--- @param name string
--- @param param string
function ScriptRuleManagerType:RemoveParam(name, param) end

--- @param name string
--- @return boolean
function ScriptRuleManagerType:Exists(name) return false end

--- @param name string
--- @param param string
--- @return boolean
function ScriptRuleManagerType:ParamExists(name, param) return false end

--- @class SobGroupManagerType
SobGroupManagerType = {}

--- @param name string
--- @return boolean @ true if the group was created, false if it already exists
function SobGroupManagerType:CreateOrClear(name) return false end

--- @param name string
--- @return boolean @ true if the group was created, false if it already exists
function SobGroupManagerType:CreateIfNotExists(name) return false end

--- @param name string
--- @return boolean
function SobGroupManagerType:IsExists(name) return false end

--- @param name string
--- @return boolean
function SobGroupManagerType:IsEmptyOrNotExists(name) return false end

--- @param name string
--- @return boolean @ true if the group was deleted, false if it did not exist
function SobGroupManagerType:Delete(name) return false end

--- @param group string
--- @param owning_player integer
--- @param include_docked boolean
--- @param include_in_hyperspace boolean
--- @param include_dead boolean
--- @return integer
function SobGroupManagerType:FillGroupFromPlayer(group, owning_player, include_docked, include_in_hyperspace,
                                                 include_dead)
    return 0
end

--- @param group string
--- @param dest_rotation_w number
--- @param dest_rotation_x number
--- @param dest_rotation_y number
--- @param dest_rotation_z number
--- @param dest_position_x number
--- @param dest_position_y number
--- @param dest_position_z number
--- @param scale_x number
--- @param scale_y number
--- @param scale_z number
--- @param skip_placement_logic boolean
function SobGroupManagerType:HyperspaceToDestination(group, dest_rotation_w, dest_rotation_x, dest_rotation_y,
                                                     dest_rotation_z, dest_position_x, dest_position_y, dest_position_z,
                                                     scale_x, scale_y, scale_z, skip_placement_logic)
end

--- @param group string
--- @param dest_rotation_w number
--- @param dest_rotation_x number
--- @param dest_rotation_y number
--- @param dest_rotation_z number
--- @param dest_position_x number
--- @param dest_position_y number
--- @param dest_position_z number
--- @param scale_x number
--- @param scale_y number
--- @param scale_z number
--- @param skip_placement_logic boolean
function SobGroupManagerType:Teleport(group, dest_rotation_w, dest_rotation_x, dest_rotation_y, dest_rotation_z,
                                      dest_position_x, dest_position_y, dest_position_z, scale_x, scale_y, scale_z,
                                      skip_placement_logic)
end

--- @param group string
--- @param source_group string
--- @param desired_types string[]
--- @return integer
function SobGroupManagerType:FillGroupFromFilteredType(group, source_group, desired_types) return 0 end

--- @param group string
--- @return integer
function SobGroupManagerType:GroupCount(group) return 0 end

--- @param group string
--- @param damage_absolute number
function SobGroupManagerType:TakeDamageAbsolute(group, damage_absolute) end

--- @param group string
--- @param damage_percentage number
function SobGroupManagerType:TakeDamage(group, damage_percentage) end

--- @param group string
function SobGroupManagerType:Stop(group) end

--- @param group string
--- @param x number
--- @param y number
--- @param z number
function SobGroupManagerType:SetVelocity(group, x, y, z) end

--- @param group string
--- @param instantaneous boolean
function SobGroupManagerType:UndeployTurret(group, instantaneous) end

--- @param group string
function SobGroupManagerType:ToggleAlternativeShipOrientation(group) end

--- @param group string
--- @param rotation_w number
--- @param rotation_x number
--- @param rotation_y number
--- @param rotation_z number
--- @param translation_x number
--- @param translation_y number
--- @param translation_z number
--- @param scale_x number
--- @param scale_y number
--- @param scale_z number
--- @param skip_placement_logic boolean
function SobGroupManagerType:Spawn(group, rotation_w, rotation_x, rotation_y, rotation_z, translation_x, translation_y,
                                   translation_z, scale_x, scale_y, scale_z, skip_placement_logic)
end

--- @param group string
--- @param rotation_w number
--- @param rotation_x number
--- @param rotation_y number
--- @param rotation_z number
--- @param translation_x number
--- @param translation_y number
--- @param translation_z number
--- @param scale_x number
--- @param scale_y number
--- @param scale_z number
function SobGroupManagerType:SetTransform(group, rotation_w, rotation_x, rotation_y, rotation_z, translation_x,
                                          translation_y, translation_z, scale_x, scale_y, scale_z)
end

--- @param group string
--- @param tactics SquadronTactics
function SobGroupManagerType:SetTactics(group, tactics) end

--- @param group string
--- @param formation string
function SobGroupManagerType:SetStrikeGroupFormation(group, formation) end

--- @param group string
--- @param stance SquadronStance
function SobGroupManagerType:SetStance(group, stance) end

--- @param group string
--- @param pitch number
--- @param yaw number
--- @param roll number
function SobGroupManagerType:SetRotation(group, pitch, yaw, roll) end

--- @param group string
--- @param enabled boolean
function SobGroupManagerType:SetNoRetaliate(group, enabled) end

--- @param group string
--- @param x number
--- @param y number
--- @param z number
function SobGroupManagerType:SetLocation(group, x, y, z) end

--- @param group string
--- @param enabled boolean
function SobGroupManagerType:SetInvincible(group, enabled) end

--- @param group string
--- @param enabled boolean
function SobGroupManagerType:SetIgnoreForPersistentFleet(group, enabled) end

--- @param group string
--- @param enabled boolean
function SobGroupManagerType:SetIgnoreDamage(group, enabled) end

--- @param group string
--- @param health_percentage number
function SobGroupManagerType:SetHealth(group, health_percentage) end

--- @param group string
--- @param enabled boolean
function SobGroupManagerType:SetGhost(group, enabled) end

--- @param group string
--- @param enabled boolean
function SobGroupManagerType:SetCloaking(group, enabled) end

--- @param group string
--- @param auto_launch_setting AutoLaunchSetting
function SobGroupManagerType:SetAutoLaunch(group, auto_launch_setting) end

--- @param group string
function SobGroupManagerType:Scuttle(group) end

--- @param group string
--- @param targets string
function SobGroupManagerType:SalvageCapture(group, targets) end

--- @param group string
--- @param revealed boolean
function SobGroupManagerType:RevealInFow(group, revealed) end

--- @param group string
function SobGroupManagerType:Retire(group) end

--- @param group string
--- @param target_group string
function SobGroupManagerType:Repair(group, target_group) end

--- @param handles TiirStatusEffectHandle[]
function SobGroupManagerType:RemoveStatusEffectsByHandles(handles) end

--- @param group string
--- @param status string
function SobGroupManagerType:RemoveStatusEffect(group, status) end

--- @param group string
function SobGroupManagerType:RemoveObtainableArtifactFromShips(group) end

--- @param group string
--- @param parade_around_entity_id integer
--- @param parade_mode ParadeMode
function SobGroupManagerType:ParadeAround(group, parade_around_entity_id, parade_mode) end

--- @param group string
--- @param retaliation_setting RetaliationSetting
function SobGroupManagerType:OverrideRetaliationSetting(group, retaliation_setting) end

--- @param group string
--- @param dest_x number
--- @param dest_y number
--- @param dest_z number
--- @param attack_move boolean
function SobGroupManagerType:MoveTo(group, dest_x, dest_y, dest_z, attack_move) end

--- @param group string
--- @param locations number[] @ {x1, y1, z1, x2, y2, z2, ...}
--- @param attack_move boolean
function SobGroupManagerType:MovePingPong(group, locations, attack_move) end

--- @param group string
--- @param path number[] @ {x1, y1, z1, x2, y2, z2, ...}
--- @param loop boolean
--- @param attack_move boolean
function SobGroupManagerType:MoveAlong(group, path, loop, attack_move) end

--- @param group string
--- @param instant boolean
--- @param no_aoe_damage boolean
--- @param no_debris boolean
--- @param no_zombie boolean
function SobGroupManagerType:MakeDead(group, instant, no_aoe_damage, no_debris, no_zombie) end

--- @param group string
function SobGroupManagerType:LaunchSelf(group) end

--- @param group string
function SobGroupManagerType:LaunchAll(group) end

--- @param group string
--- @param latch_target_group string
function SobGroupManagerType:LatchInstantly(group, latch_target_group) end

--- @param group string
--- @param by_damage boolean
function SobGroupManagerType:KillUnit(group, by_damage) end

--- @param group string
--- @param target_player integer
--- @return boolean
function SobGroupManagerType:IsWithinPlayerSensorRange(group, target_player) return false end

--- @param group string
--- @return boolean
function SobGroupManagerType:IsInHyperspace(group) return false end

--- @param group string
--- @param require_everyone boolean
--- @return boolean
function SobGroupManagerType:IsGroupInCombat(group, require_everyone) return false end

--- @param group string
--- @return boolean
function SobGroupManagerType:IsDeSpawned(group) return false end

--- @param group string
--- @param require_all boolean
--- @return boolean
function SobGroupManagerType:IsCloaking(group, require_all) return false end

--- @param group string
--- @param dest_rotation_w number
--- @param dest_rotation_x number
--- @param dest_rotation_y number
--- @param dest_rotation_z number
--- @param dest_position_x number
--- @param dest_position_y number
--- @param dest_position_z number
--- @param scale_x number
--- @param scale_y number
--- @param scale_z number
--- @param skip_placement_logic boolean
function SobGroupManagerType:HyperspaceExit(group, dest_rotation_w, dest_rotation_x, dest_rotation_y, dest_rotation_z,
                                            dest_position_x, dest_position_y, dest_position_z, scale_x, scale_y, scale_z,
                                            skip_placement_logic)
end

--- @param group string
function SobGroupManagerType:HyperspaceEnter(group) end

--- @param group string
--- @param status_effect string
--- @param check_for_all boolean
--- @return boolean
function SobGroupManagerType:HasStatusEffect(group, status_effect, check_for_all) return false end

--- @param group string
--- @param targets string
function SobGroupManagerType:Guard(group, targets) end

--- @param group string
--- @param entity_id integer
--- @return integer
function SobGroupManagerType:GroupRemoveEntity(group, entity_id) return 0 end

--- @param group string
--- @param source_group string
--- @return integer
function SobGroupManagerType:GroupRemove(group, source_group) return 0 end

--- @param group string
--- @return integer
function SobGroupManagerType:GroupPurgeDead(group) return 0 end

--- @param group string
--- @return integer
function SobGroupManagerType:GroupPurgeAlive(group) return 0 end

--- @param group string
--- @return integer[] @ entity id list
function SobGroupManagerType:GroupMembers(group) return {} end

--- @param group string
--- @param awake boolean
--- @param docked boolean
--- @param in_hyperspace boolean
--- @param in_combat boolean
--- @return integer
function SobGroupManagerType:GroupCountFiltered(group, awake, docked, in_hyperspace, in_combat) return 0 end

--- @param group string
function SobGroupManagerType:GroupClear(group) end

--- @param group string
--- @param entity_id integer
--- @return integer
function SobGroupManagerType:GroupAddEntity(group, entity_id) return 0 end

--- @param group string
--- @param source_group string
--- @return integer
function SobGroupManagerType:GroupAdd(group, source_group) return 0 end

--- @param group string
--- @return number, number, number @ x, y, z
function SobGroupManagerType:GetPosition(group) return 0, 0, 0 end

--- @param group string
--- @return number, number, number @ pitch, yaw, roll
function SobGroupManagerType:GetOrientation(group) return 0, 0, 0 end

--- @param group string
--- @return string
function SobGroupManagerType:GenerateDebugString(group) return "" end

--- @param group string
--- @param targets string
function SobGroupManagerType:GatherResource(group, targets) end

--- @param group string
--- @param weapon_type string
--- @param all_sources_fire boolean
--- @param fire_from_socket string
--- @param muzzle_offset_x number
--- @param muzzle_offset_y number
--- @param muzzle_offset_z number
--- @return boolean
function SobGroupManagerType:FireAtNoTarget(group, weapon_type, all_sources_fire, fire_from_socket, muzzle_offset_x,
                                            muzzle_offset_y, muzzle_offset_z)
    return false
end

--- @param group string
--- @param target_group string
--- @param weapon_type string
--- @param all_sources_fire boolean
--- @param fire_at_all_targets boolean
--- @param fire_from_socket string
--- @param muzzle_offset_x number
--- @param muzzle_offset_y number
--- @param muzzle_offset_z number
--- @return boolean
function SobGroupManagerType:FireAt(group, target_group, weapon_type, all_sources_fire, fire_at_all_targets,
                                    fire_from_socket, muzzle_offset_x, muzzle_offset_y, muzzle_offset_z)
    return false
end

--- @param group string
--- @param source_group string
--- @param owning_player TiirCommander
--- @return integer
function SobGroupManagerType:FillGroupIncludingPlayer(group, source_group, owning_player) return 0 end

--- @param group string
--- @param owning_player integer
--- @param include_dead boolean
--- @return integer
function SobGroupManagerType:FillGroupFromPlayerMothershipList(group, owning_player, include_dead) return 0 end

--- @param group string
--- @param source_group string
--- @param desired_types string[]
--- @return integer
function SobGroupManagerType:FillGroupFromFilteredFamily(group, source_group, desired_types) return 0 end

--- @param group string
--- @param source_group string
--- @param location_x number
--- @param location_y number
--- @param location_z number
--- @param distance_x number
--- @param distance_y number
--- @param distance_z number
--- @return integer
function SobGroupManagerType:FillGroupByProximityToLocation(group, source_group, location_x, location_y, location_z,
                                                            distance_x, distance_y, distance_z)
    return 0
end

--- @param group string
--- @param source_group string
--- @param near_group string
--- @param distance_x number
--- @param distance_y number
--- @param distance_z number
--- @return integer
function SobGroupManagerType:FillGroupByProximityToGroup(group, source_group, near_group, distance_x, distance_y,
                                                         distance_z)
    return 0
end

--- @param group string
--- @param dock_target_entity_group string
function SobGroupManagerType:DockInstantly(group, dock_target_entity_group) end

--- @param group string
--- @param dock_target_entity_group string
--- @param stay_docked boolean
--- @param dock_only boolean
function SobGroupManagerType:Dock(group, dock_target_entity_group, stay_docked, dock_only) end

--- @param group string
function SobGroupManagerType:DisbandStrikeGroup(group) end

--- @param group string
--- @param ignore_active_commands boolean
function SobGroupManagerType:Despawn(group, ignore_active_commands) end

--- @param group string
--- @param position_x number
--- @param position_y number
--- @param position_z number
--- @param pitch number
--- @param yaw number
--- @param roll number
--- @param instantaneous boolean
function SobGroupManagerType:DeployTurretAtPositionAndOrientation(group, position_x, position_y, position_z, pitch, yaw,
                                                                  roll, instantaneous)
end

--- @param group string
--- @param position_x number
--- @param position_y number
--- @param position_z number
--- @param normal_x number
--- @param normal_y number
--- @param normal_z number
--- @param instantaneous boolean
function SobGroupManagerType:DeployTurretAtPositionAndNormal(group, position_x, position_y, position_z, normal_x,
                                                             normal_y, normal_z, instantaneous)
end

--- @param group string
--- @param instantaneous boolean
function SobGroupManagerType:DeployTurret(group, instantaneous) end

--- @param group string
function SobGroupManagerType:CustomCommand(group) end

--- @param group string
--- @param filter_types string[]
--- @return integer
function SobGroupManagerType:CountShipTypePresentInGroup(group, filter_types) return 0 end

--- @param group string
--- @param filter_families string[]
--- @return integer
function SobGroupManagerType:CountAttackFamilyPresentInGroup(group, filter_families) return 0 end

--- @param group string
function SobGroupManagerType:ClearStatusEffects(group) end

--- @param group string
function SobGroupManagerType:ClearRetaliationSetting(group) end

--- @param group string
--- @param target_player integer
function SobGroupManagerType:ChangeOwner(group, target_player) end

--- @param group string
--- @param new_commander TiirCommander
function SobGroupManagerType:ChangeCommander(group, new_commander) end

--- @param group string
--- @param bind_target_entity_group string
function SobGroupManagerType:BindInstantly(group, bind_target_entity_group) end

--- @param group string
--- @param target_player integer
--- @param can_attack_cloaked_units boolean
function SobGroupManagerType:AttackPlayer(group, target_player, can_attack_cloaked_units) end

--- @param group string
--- @param target_group string
--- @param maintain_guard boolean
--- @param can_attack_cloaked_units boolean
function SobGroupManagerType:Attack(group, target_group, maintain_guard, can_attack_cloaked_units) end

--- @param group string
--- @param status string
--- @return TiirStatusEffectHandle[]
function SobGroupManagerType:AddStatusEffect(group, status) return {} end

--- @param group string
--- @param artifact_static_data string
function SobGroupManagerType:AddObtainableArtifactToShips(group, artifact_static_data) end

--- @param group string
--- @param x number
--- @param y number
--- @param z number
--- @param pitch number
--- @param yaw number
--- @param roll number
--- @param owning_player integer
--- @param start_in_hyperspace boolean
--- @param skip_placement_logic boolean
--- @param ship_type string
--- @param ship_count integer
--- @param stance SquadronStance
--- @param use_retaliation_override boolean
--- @param retaliation_override RetaliationSetting
--- @param do_not_retaliate_against_me boolean
function SobGroupManagerType:CreateShipSimple(group, x, y, z, pitch, yaw, roll, owning_player, start_in_hyperspace,
                                              skip_placement_logic, ship_type, ship_count, stance,
                                              use_retaliation_override, retaliation_override, do_not_retaliate_against_me)
end

--- @param group string
function SobGroupManagerType:FillGroupAllEntitiesInGame(group) end

--- @param group string
function SobGroupManagerType:FillGroupAllShipsInGame(group) end

--- @param group string
function SobGroupManagerType:FillGroupAllNonShipEntitiesInGame(group) end

--- @param group string
function SobGroupManagerType:FillGroupAllAliveShipsInGame(group) end

--- @param group string
function SobGroupManagerType:FillGroupAllAliveEntitiesInGame(group) end

--- @param group string
function SobGroupManagerType:FillGroupAllAliveNonShipEntitiesInGame(group) end

--- @class CustomCodeManagerType
CustomCodeManagerType = {}

--- @param unit_type string
--- @param on_create string
--- @param on_update string
--- @param on_destroy string
--- @param update_interval integer @ in ticks
function CustomCodeManagerType:Register(unit_type, on_create, on_update, on_destroy, update_interval) end

--- @class EntityLibInterface
EntityLibInterface = {}

--- @param entity_id integer
--- @param instantaneous boolean
function EntityLibInterface:UndeployTurret(entity_id, instantaneous) end

--- @param entity_id integer
--- @param dest_rotation_w number
--- @param dest_rotation_x number
--- @param dest_rotation_y number
--- @param dest_rotation_z number
--- @param dest_position_x number
--- @param dest_position_y number
--- @param dest_position_z number
--- @param scale_x number
--- @param scale_y number
--- @param scale_z number
--- @param teleport_ships_in_parade boolean
function EntityLibInterface:Teleport(entity_id, dest_rotation_w, dest_rotation_x, dest_rotation_y, dest_rotation_z,
                                     dest_position_x, dest_position_y, dest_position_z, scale_x, scale_y, scale_z,
                                     teleport_ships_in_parade)
end

--- @param entity_id integer
--- @param x number
--- @param y number
--- @param z number
function EntityLibInterface:SetVelocity(entity_id, x, y, z) end

--- @param entity_id integer
--- @param rotation_w number
--- @param rotation_x number
--- @param rotation_y number
--- @param rotation_z number
--- @param position_x number
--- @param position_y number
--- @param position_z number
--- @param scale_x number
--- @param scale_y number
--- @param scale_z number
function EntityLibInterface:SetTransform(entity_id, rotation_w, rotation_x, rotation_y, rotation_z, position_x,
                                         position_y, position_z, scale_x, scale_y, scale_z)
end

--- @param entity_id integer
--- @param tactics SquadronTactics
function EntityLibInterface:SetTactics(entity_id, tactics) end

--- @param entity_id integer
--- @param stance SquadronStance
function EntityLibInterface:SetStance(entity_id, stance) end

--- @param entity_id integer
--- @param pitch number
--- @param yaw number
--- @param roll number
function EntityLibInterface:SetRotation(entity_id, pitch, yaw, roll) end

--- @param entity_id integer
--- @param enabled boolean
function EntityLibInterface:SetNoRetaliate(entity_id, enabled) end

--- @param entity_id integer
--- @param key string
--- @param value integer
function EntityLibInterface:SetMetaDataValue(entity_id, key, value) end

--- @param entity_id integer
--- @param x number
--- @param y number
--- @param z number
function EntityLibInterface:SetLocation(entity_id, x, y, z) end

--- @param entity_id integer
--- @param enabled boolean
function EntityLibInterface:SetInvincible(entity_id, enabled) end

--- @param entity_id integer
--- @param enabled boolean
function EntityLibInterface:SetIgnoreForPersistentFleet(entity_id, enabled) end

--- @param entity_id integer
--- @param enabled boolean
function EntityLibInterface:SetIgnoreDamage(entity_id, enabled) end

--- @param entity_id integer
--- @param enabled boolean
function EntityLibInterface:SetGhost(entity_id, enabled) end

--- @param entity_id integer
--- @param enabled boolean
function EntityLibInterface:SetCloaking(entity_id, enabled) end

--- @param entity_id integer
--- @param auto_launch_setting AutoLaunchSetting
function EntityLibInterface:SetAutoLaunch(entity_id, auto_launch_setting) end

--- @param entity_id integer
--- @param x number
--- @param y number
--- @param z number
function EntityLibInterface:SetAngularVelocity(entity_id, x, y, z) end

--- @param entity_id integer
function EntityLibInterface:Scuttle(entity_id) end

--- @param entity_id integer
--- @param target_group string
function EntityLibInterface:SalvageCapture(entity_id, target_group) end

--- @param entity_id integer
--- @param revealed boolean
function EntityLibInterface:RevealInFow(entity_id, revealed) end

--- @param entity_id integer
--- @param target_id integer
function EntityLibInterface:RetireTo(entity_id, target_id) end

--- @param entity_id integer
function EntityLibInterface:Retire(entity_id) end

--- @param entity_id integer
--- @param target_group string
function EntityLibInterface:Repair(entity_id, target_group) end

--- @param entity_id integer
function EntityLibInterface:RemoveObtainableArtifactFromShip(entity_id) end

--- @param entity_id integer
--- @param retaliation_setting RetaliationSetting
function EntityLibInterface:OverrideRetaliationSetting(entity_id, retaliation_setting) end

--- @param entity_id integer
--- @param locations number[] @ {x1, y1, z1, x2, y2, z2, ...}
--- @param attack_move boolean
function EntityLibInterface:MovePingPong(entity_id, locations, attack_move) end

--- @param entity_id integer
--- @param path number[] @ {x1, y1, z1, x2, y2, z2, ...}
--- @param loop boolean
--- @param attack_move boolean
function EntityLibInterface:MoveAlong(entity_id, path, loop, attack_move) end

--- @param entity_id integer
--- @param instant boolean
--- @param no_aoe_damage boolean
--- @param no_debris boolean
--- @param no_zombie boolean
function EntityLibInterface:MakeDead(entity_id, instant, no_aoe_damage, no_debris, no_zombie) end

--- @param entity_id integer
function EntityLibInterface:LaunchSelf(entity_id) end

--- @param entity_id integer
function EntityLibInterface:LaunchAll(entity_id) end

--- @param entity_id integer
--- @param latch_target_entity integer
function EntityLibInterface:LatchInstantly(entity_id, latch_target_entity) end

--- @param entity_id integer
--- @param target_group string
function EntityLibInterface:Kamikaze(entity_id, target_group) end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsValid_OnPres(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsValid(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsInHyperspace(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsInCombat(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsCloaking(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsBeingCaptured(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsBeingAttacked(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsAttacking(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsAlive(entity_id) return false end

--- @param entity_id integer
--- @param target_group string
function EntityLibInterface:Guard(entity_id, target_group) end

--- @param entity_id integer
--- @return number
function EntityLibInterface:GetVisualRange(entity_id) return 0 end

--- @param entity_id integer
--- @return number
function EntityLibInterface:GetSecondarySensorRange(entity_id) return 0 end

--- @param entity_id integer
--- @return number
function EntityLibInterface:GetPrimarySensorRange(entity_id) return 0 end

--- @param entity_id integer
--- @return number, number, number @ x, y, z
function EntityLibInterface:GetPosition(entity_id) return 0, 0, 0 end

--- @param entity_id integer
--- @return TiirCommander
function EntityLibInterface:GetOwningPlayer(entity_id) return TiirCommander end

--- @param entity_id integer
--- @return number, number, number @ pitch, yaw, roll
function EntityLibInterface:GetOrientation(entity_id) return 0, 0, 0 end

--- @param entity_id integer
--- @return integer
function EntityLibInterface:GetNumberOfQueuedOrders(entity_id) return 0 end

--- @param entity_id integer
--- @param key string
--- @return boolean, number
function EntityLibInterface:GetMetaDataValue(entity_id, key) return false, 0 end

--- @param entity_id integer
--- @return number
function EntityLibInterface:GetHealthAbsolute(entity_id) return 0 end

--- @param entity_id integer
--- @return number
function EntityLibInterface:GetHealth(entity_id) return 0 end

--- @param entity_id integer
--- @return integer
function EntityLibInterface:GetBuildTime(entity_id) return 0 end

--- @param entity_id integer
--- @param target_group string
function EntityLibInterface:GatherResource(entity_id, target_group) end

--- @param entity_id integer
--- @return string
function EntityLibInterface:FindShipType(entity_id) return "" end

--- @param entity_id integer
--- @param dock_target_entity integer
function EntityLibInterface:DockInstantly(entity_id, dock_target_entity) end

--- @param entity_id integer
--- @param dock_target_entity integer
--- @param stay_docked boolean
--- @param dock_only boolean
function EntityLibInterface:Dock(entity_id, dock_target_entity, stay_docked, dock_only) end

--- @param entity_id integer
--- @param x number
--- @param y number
--- @param z number
--- @param pitch number
--- @param yaw number
--- @param roll number
--- @param instantaneous boolean
function EntityLibInterface:DeployTurretAtPositionAndOrientation(entity_id, x, y, z, pitch, yaw, roll, instantaneous) end

--- @param entity_id integer
--- @param position_x number
--- @param position_y number
--- @param position_z number
--- @param normal_x number
--- @param normal_y number
--- @param normal_z number
--- @param instantaneous boolean
function EntityLibInterface:DeployTurretAtPositionAndNormal(entity_id, position_x, position_y, position_z, normal_x,
                                                            normal_y, normal_z, instantaneous)
end

--- @param entity_id integer
--- @param instantaneous boolean
function EntityLibInterface:DeployTurret(entity_id, instantaneous) end

--- @param entity_id integer
--- @param target_group string
function EntityLibInterface:CustomCommand(entity_id, target_group) end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:ClearStatusEffects(entity_id) return false end

--- @param entity_id integer
function EntityLibInterface:ClearRetaliationSetting(entity_id) end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:ClearModifiers(entity_id) return false end

--- @param entity_id integer
--- @param target_player integer
function EntityLibInterface:ChangeOwner(entity_id, target_player) end

--- @param entity_id integer
--- @param new_commander TiirCommander
function EntityLibInterface:ChangeCommander(entity_id, new_commander) end

--- @param entity_id integer
--- @param bind_target_entity integer
function EntityLibInterface:BindInstantly(entity_id, bind_target_entity) end

--- @param entity_id integer
--- @param target_group string
function EntityLibInterface:Attack(entity_id, target_group) end

--- @param entity_id integer
--- @param property SobPropertyType
--- @param value number
--- @param influence_type InfluenceType
--- @param influence_radius number
--- @return TiirModifierHandle
function EntityLibInterface:AddOverrideModifier(entity_id, property, value, influence_type, influence_radius)
    return TiirModifierHandle
end

--- @param modifier TiirModifierHandle
--- @return boolean
function EntityLibInterface:RemoveModifier(modifier) return false end

--- @param entity_id integer
--- @param multiplier MultiplierType
--- @param multiplier_value number
--- @param influence_type InfluenceType
--- @param influence_radius number
--- @param multiplier_value_relation ActivityRelation
--- @param multiplier_interp_min_value number
--- @return TiirModifierHandle
function EntityLibInterface:AddMultiplierModifier(entity_id, multiplier, multiplier_value, influence_type,
                                                  influence_radius, multiplier_value_relation,
                                                  multiplier_interp_min_value)
    return TiirModifierHandle
end

--- @param entity_id integer
--- @param ability AbilityType
--- @param ability_state boolean
--- @param influence_type InfluenceType
--- @param influence_radius number
--- @return TiirModifierHandle
function EntityLibInterface:AddAbilityModifier(entity_id, ability, ability_state, influence_type, influence_radius)
    return TiirModifierHandle
end

--- @param handle TiirStatusEffectHandle
--- @return boolean
function EntityLibInterface:RemoveStatusEffectByHandle(handle) return false end

--- @param entity_id integer
--- @param status string
--- @return boolean
function EntityLibInterface:RemoveStatusEffect(entity_id, status) return false end

--- @param entity_id integer
--- @param status string
--- @return TiirStatusEffectHandle
function EntityLibInterface:AddStatusEffect(entity_id, status) return TiirStatusEffectHandle end

--- @param entity_id integer
--- @param artifact_static_data string
function EntityLibInterface:AddObtainableArtifactToShip(entity_id, artifact_static_data) end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsShip(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsMilitary(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsDamaged(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsAliveAndVisibleEntity(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:CanHeal(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:CanBeFocused(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsResource(entity_id) return false end

--- @param entity_id integer
--- @return boolean
function EntityLibInterface:IsMissile(entity_id) return false end

--- @param entity_id integer
--- @return string
function EntityLibInterface:GetEntityInternalName(entity_id) return "" end

--- @param entity_id integer
--- @return SquadronStance
function EntityLibInterface:GetStance(entity_id) return SquadronStance end

--- @param entity_id integer
--- @return string
function EntityLibInterface:GetFormation(entity_id) return "" end


--- @class PlayerLibInterface
PlayerLibInterface = {}

--- @param player_index integer
--- @param resource_unit_total integer
function PlayerLibInterface:SetResourceUnits(player_index, resource_unit_total) end

--- @param player_index integer
function PlayerLibInterface:ResetCommanderSupply(player_index) end

--- @param player_index integer
function PlayerLibInterface:PlayerKill(player_index) end

--- @param player_index integer
--- @return boolean
function PlayerLibInterface:PlayerIsAlive(player_index) return false end

--- @param player_index integer
--- @return boolean
function PlayerLibInterface:PlayerHasShipWithBuildQueue(player_index) return false end

--- @param player_index integer
--- @return boolean
function PlayerLibInterface:PlayerHasNonResourceShipWithBuildQueue(player_index) return false end

--- @param player_index integer
--- @return boolean
function PlayerLibInterface:PlayerHasMothership(player_index) return false end

--- @param output_group string
--- @param player_index integer
function PlayerLibInterface:PlayerEntityGroup(output_group, player_index) end

--- @return integer
function PlayerLibInterface:PlayerCount() return 0 end

--- @param player TiirCommander
--- @return boolean
function PlayerLibInterface:IsValid(player) return false end

--- @param player TiirCommander
--- @return boolean
function PlayerLibInterface:IsHuman(player) return false end

--- @param player TiirCommander
--- @return boolean
function PlayerLibInterface:IsEnvironment(player) return false end

--- @param player_index integer
--- @return integer
function PlayerLibInterface:GetResourceUnits(player_index) return 0 end

--- @param player TiirCommander
--- @return integer
function PlayerLibInterface:GetPlayerIndex(player) return 0 end

--- @param player_index integer
--- @return boolean, TiirCommander
function PlayerLibInterface:GetPlayerFromIndex(player_index) return false, TiirCommander end

--- @return TiirCommander
function PlayerLibInterface:GetEnvironmentPlayer() return TiirCommander end

--- @param player_index integer
--- @param resource_unit_count integer
function PlayerLibInterface:AddResourceUnits(player_index, resource_unit_count) end

--- @class WSysType
--- @field public Rule ScriptRuleManagerType
--- @field public SobGroup SobGroupManagerType
--- @field public CustomCode CustomCodeManagerType
--- @field public Entity EntityLibInterface
--- @field public Player PlayerLibInterface
WSysType = {}

--- @param target_research string
--- @param all_of_units string @ Comma separated list of unit types
--- @param none_of_units string @ Comma separated list of unit types
--- @param all_of_researches string @ Comma separated list of research types
--- @param none_of_researches string @ Comma separated list of research types
function WSysType:AddResearchCondition(target_research, all_of_units, none_of_units, all_of_researches,
                                       none_of_researches)
end

--- @type WSysType
WSys = WSysType()
