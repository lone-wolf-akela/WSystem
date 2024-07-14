#pragma once

#include <cstdint>

#include <ThirdParty/UnrealContainers/UnrealContainers.h>

struct TiirResearch
{
	std::uint32_t ResearchID;
};

struct TiirCommander
{
	std::int32_t Index;
};

struct TiirEntity 
{
    std::uint64_t EntityID;
};

struct TiirEntityGroup 
{
    UC::TSet<TiirEntity> Entities;
};


struct TiirModifierHandle 
{
    TiirEntity Owner;
    std::int32_t Modifier;
};

enum class SquadronStance : std::uint8_t 
{
    Aggressive,
    Evasive,
    Neutral,
};

enum class SquadronTactics : std::uint8_t 
{
    Aggressive,
    Defensive,
    Passive,
};

enum class AutoLaunchSetting : std::uint8_t 
{
    Launch,
    StayDockedUpToLimit,
    StayDockedAlways,
};

struct TiirStatusEffectHandle
{
    TiirEntity Owner;
    std::uint32_t StatusEffectID;
};

enum class RetaliationSetting : std::uint8_t 
{
    Enemies,
    AttackersOfFriends,
    AttackersOfUs,
    None,
};

enum class SobPropertyType : std::uint8_t 
{
    HealthMax,
    HealthRegenerateDelay,
    HealthRegeneratePerSecond,
    HealthMaxRegeneratePerSecond,
    HealthTransientRegeneratePerSecond,
    ShieldBulletMax,
    ShieldBulletRechargeRate,
    ShieldEmpMax,
    ShieldEmpRechargeRate,
    DamageMitigation,
    DamageRateDustCloud,
    DamageRateNebula,
    MainEngineAccel,
    MainEngineBrake,
    MainEngineMaxSpeed,
    MainEngineMaxSpeedWithFormation,
    RotationAccel,
    RotationBrake,
    RotationMaxSpeed,
    ThrusterAccel,
    ThrusterBrake,
    ThrusterMaxSpeed,
    PrimarySensorRange,
    SecondarySensorRange,
    CloakDetectionLevel,
    VisualRange,
    RetaliationRange,
    RetaliationDistanceFromGoal,
    LeashingRange,
};

enum class MultiplierType : std::uint8_t 
{
    Unknown,
    MaxHealth,
    Speed,
    BuildSpeed,
    ShipHoldRepairSpeed,
    HealthRegenerationRate,
    WeaponAccuracy,
    WeaponDamage,
    ShieldRegenerationRate,
    MaxShield,
    HyperspaceRecoveryTime,
    HyperspaceTime,
    HyperspaceCost,
    HyperspaceAbortDamage,
    Capture,
    SensorDistortion,
    VisualDistortion,
    CloakingTime,
    CloakingStrength,
    CloakDetection,
    MaxSpeed,
    VisualRange,
    PrimarySensorsRange,
    SecondarySensorsRange,
    DustCloudSensitivity,
    NebulaSensitivity,
    ResourceCollectionRate,
    ResourceDropOffRate,
    ResourceCapacity,
    DefenseFieldTime,
    CustomCommandTime,
    Rotation,
    RotationAccel,
    RotationBrake,
    Thruster,
    ThrusterAccel,
    ThrusterBrake,
    EngineAccel,
    EngineBrake,
    WeaponCone,
    BulletSpeed,
    TurretSpeed,
    DamageApplied,
    AccuracyApplied,
    FlightPerf,
    ExpireTime,
    FireRate,
    NavTrench,
    ResearchSpeed,
    Armour,
    WeaponRange,
    WeaponRadius,
    MaxSpeedWithFormation,
};

enum class AbilityType : std::uint8_t
{
    None,
    Move,
    Attack,
    Guard,
    Repair,
    RepairOverseer,
    Cloak,
    Resource,
    Harvest,
    Mine,
    SalvageCapture,
    SalvageCaptureOverseer,
    Salvage,
    SalvageOverseer,
    Dock,
    AcceptDocking,
    Builder,
    Stop,
    Hyperspace,
    Parade,
    FormHyperspaceGate,
    HyperspaceViaGate,
    SensorPing,
    Retire,
    DefenseField,
    DefenseFieldShield,
    HyperspaceInhibitor,
    Scuttle,
    UseSpecialWeaponsInNormalAttack,
    Steering,
    Targeting,
    Sensors,
    Lights,
    Custom,
    Kamikaze,
    DeployTurret,
    DeployCounterMeasureFog,
    ToggleAlternativeShipOrientation,
    Maneuver,
    BoostAllies,
    BoostArmor,
    BoostProduction,
    BoostSpeed,
    BoostWeaponDamage,
    BoostWeaponRange,
    BoostWeaponRateOfFire,
    SpecialAttackTripleShot,
    SpecialAttackMissileVolley,
    SpecialAttackMegaBeam,
    SpecialAttackClusterMissile,
    SpecialAttackCruiseMissile,
    SpecialAttackCannonVolley,
    SpecialAttackFusionRound,
    SpecialAttackNuke,
    SelfRepair,
};

enum class InfluenceType : std::uint8_t 
{
    Unknown,
    ThisShipOnly,
    AllShipsWithinRadius,
    OwnShipsWithinRadius,
    EnemyShipsWithinRadius,
    AllShipsWithinRadiusExcludingThisShip,
    OwnShipsWithinRadiusExcludingThisShip,
    EnemyShipsWithinRadiusIncludingSleeping,
};

enum class ActivityRelation : std::uint8_t 
{
    Unknown,
    None,
    Linear,
};

struct EntityDeathModifiers 
{
    std::uint8_t Instant : 1;
    std::uint8_t NoAoeDamage : 1;
    std::uint8_t NoDebris : 1;
    std::uint8_t NoZombie : 1;
};

enum class ParadeMode : std::uint8_t 
{
    Normal,
    InstantWithHyperspace,
    Instant,
};

enum class TiirGroupCountFilter : std::uint8_t
{
    All = 0b0000,
    Awake = 0b0001,
    Docked = 0b0010,
    InHyperspace = 0b0100,
    InCombat = 0b1000,
};

/*
struct RAVENSIMULATION_API FTiirGroupQuery {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ETiirGroupCountFilter StateFilter;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UEntityStaticData*> TypeFilter;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTiirCommander> OwnerFilter;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<ESobType> SobTypeFilter;

    FTiirGroupQuery();
};
*/