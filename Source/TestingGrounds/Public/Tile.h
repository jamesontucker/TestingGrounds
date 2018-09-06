// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Placement")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);
	
	UFUNCTION(BlueprintCallable, Category = "Placement")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500);
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

private:

	void PositionNavMeshBoundsVolume();

//	TArray<FSpawnPosition> RandomSpawnPositions(int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);
	
	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition SpawnPosition);
	
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);
	
	bool CanSpawnAtLocation(FVector Location, float Radius);
	
	UActorPool* Pool;
	
	AActor* NavMeshBoundsVolume;
};
