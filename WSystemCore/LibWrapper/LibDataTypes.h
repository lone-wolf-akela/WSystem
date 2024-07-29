#pragma once
#include <pch.h>

#include <DataWrapper/EnumDef.h>

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

    friend std::uint32_t GetTypeHash(const TiirEntity& Entity)
    {
        return RC::Unreal::GetTypeHash(Entity.EntityID);
    }
    friend std::strong_ordering operator<=>(const TiirEntity& lhs, const TiirEntity& rhs) = default;
};

struct TiirEntityGroup 
{
	RC::Unreal::TSet<TiirEntity> Entities;
};

struct TiirModifierHandle 
{
    TiirEntity Owner;
    std::int32_t Modifier;
};

struct TiirStatusEffectHandle
{
    TiirEntity Owner;
    std::uint32_t StatusEffectID;
};

struct EntityDeathModifiers 
{
    std::uint8_t Instant : 1;
    std::uint8_t NoAoeDamage : 1;
    std::uint8_t NoDebris : 1;
    std::uint8_t NoZombie : 1;
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