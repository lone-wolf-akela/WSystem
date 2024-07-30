#pragma once
#include <pch.h>

enum class ETurretDeploymentState : std::uint8_t
{
    None,
    Failed,
    MovingToTarget,
    PreparingToDeploy,
    Deploying,
    Deployed,
    Undeploying,
    Undeployed,
};

enum class EDockingStage : std::uint8_t
{
    OrderGiven,
    FindBestDockShip,
    FlyToDockShip,
    FindBestPathOnShip,
    RegisterForQueue,
    FlyToBehindQueue,
    Queue,
    BookPath,
    FlyToDockPathStartPoint,
    OpenDoor,
    DockFormations,
    PutSquadronInShip,
    Docked,
    UnInitialized,
};

enum class EHyperspaceStatus : std::uint8_t
{
    Entering,
    EnteringGate,
    Exiting,
    Interrupted,
    GateFormed,
    EnteredInhibitorVolume,
    NotEnoughCash,
    EnteringEffect,
    ExitingEffect,
};

enum class ESobAnimationState : std::uint8_t
{
    Normal,
    Open,
    Closed,
    CodeRed,
    CodeGreen,
    ResourceStart,
    ResourceDo,
    ResourceEnd,
    RepairStart,
    RepairDo,
    RepairEnd,
    DockPathOpen,
    DockPathOpen1,
    DockPathOpen2,
    DockPathOpen3,
    DockPathOpen4,
    DockPathOpen5,
    DockPathClosed,
    DockPathClosed1,
    DockPathClosed2,
    DockPathClosed3,
    DockPathClosed4,
    DockPathClosed5,
    Launched,
    Docked,
    DefenseFieldActivate,
    DefenseFieldDeActivate,
    CloakFieldActivate,
    CloakFieldDeactivate,
    HyperspaceGateActivate,
    HyperspaceGateDeActivate,
    DoingFlightManeuver,
    CaptureActive,
    CaptureInActive,
    CustomCommandActivate,
    CustomCommandDeActivate,
    MagneticFieldActivate,
    MagneticFieldDeActivate,
    NIS00,
    NIS01,
    NIS02,
    NumberStates,
    NoState,
};

enum class UCommandType : std::uint8_t
{
    UCommand_Idle,
    UCommand_Move,
    UCommand_Attack,
    UCommand_BlindFire,
    UCommand_Build,
    UCommand_Dock,
    UCommand_Resource,
    UCommand_Launch,
    UCommand_WaypointMove,
    UCommand_Parade,
    UCommand_Guard,
    UCommand_SalvageCaptureOverseer,
    UCommand_SalvageCapture,
    UCommand_Hyperspace,
    UCommand_MoveToSob,
    UCommand_FormHyperspaceGate,
    UCommand_HyperspaceViaGate,
    UCommand_RepairOverseer,
    UCommand_Repair,
    UCommand_Retire,
    UCommand_Despawn,
    UCommand_LayMines,
    UCommand_DeployTurret,
    UCommand_DeployCounterMeasureFog,
    UCommand_AttackMove,
    UCommand_RallyParade,
    UCommand_Rotate,
    UCommand_Harvest,
    UCommand_Scuttle,
    UCommand_BoostAllies,
    UCommand_BoostArmor,
    UCommand_BoostProduction,
    UCommand_BoostSpeed,
    UCommand_BoostWeaponDamage,
    UCommand_BoostWeaponRange,
    UCommand_BoostWeaponRateOfFire,
    UCommand_SpecialAttackTripleShot,
    UCommand_SpecialAttackMissileVolley,
    UCommand_SpecialAttackMegaBeam,
    UCommand_SpecialAttackClusterMissile,
    UCommand_SpecialAttackCruiseMissile,
    UCommand_SpecialAttackCannonVolley,
    UCommand_SpecialAttackFusionRound,
    UCommand_SpecialAttackNuke,
    UCommand_Maneuver,
    UCommand_Custom,
    UCommand_SelfRepair,
};

enum class ESquadronStance : std::uint8_t
{
    Aggressive,
    Evasive,
    Neutral,
};

enum class ESquadronTactics : std::uint8_t
{
    Aggressive,
    Defensive,
    Passive,
};

enum class EAutoLaunchSetting : std::uint8_t
{
    Launch,
    StayDockedUpToLimit,
    StayDockedAlways,
};

enum class ERetaliationSetting : std::uint8_t
{
    Enemies,
    AttackersOfFriends,
    AttackersOfUs,
    None,
};

enum class ESobPropertyType : std::uint8_t
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

enum class EMultiplierType : std::uint8_t
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

enum class EAbilityType : std::uint8_t
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

enum class EInfluenceType : std::uint8_t
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

enum class EActivityRelation : std::uint8_t
{
    Unknown,
    None,
    Linear,
};

enum class EParadeMode : std::uint8_t
{
    Normal,
    InstantWithHyperspace,
    Instant,
};

enum class ETiirGroupCountFilter : std::uint8_t
{
    All = 0b0000,
    Awake = 0b0001,
    Docked = 0b0010,
    InHyperspace = 0b0100,
    InCombat = 0b1000,
};

enum class EBuildCancelType : std::uint8_t
{
    Job,
    Family,
    All,
};

enum class EBuildPauseType : std::uint8_t
{
    Job,
    Family,
    Queue,
    All,
};

enum class EUpgradeType : std::uint8_t
{
    Modifier,
    Ability,
    None,
};

enum class ELobbyState : std::int8_t
{
    Invalid = -1,
    Setup = 0,
    PreLobby = 1,
    Lobby = 2,
    LoadSaveGame = 3,
    LoadReplay = 4,
    InitScenario = 5,
    InGame = 6,
    PostGame = 7,
};

enum class EResearchState : std::int8_t
{
    Restricted,
    Locked,
    Pending,
    InProgress,
    Done,
};

enum class EResearchEvent : std::uint8_t
{
    ResearchStart,
    ResearchCancel,
    ResearchComplete,
    ResearchNoRU,
    ResearchAvailable,
    InstaResearchComplete,
    ResearchInProgress,
    ResearchRestricted,
    ResearchUnrestricted,
    ResearchPaused,
    ResearchUnpaused,
    _ResearchEventNum,
};