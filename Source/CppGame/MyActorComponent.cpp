// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "MyGameInstance.h" // GameInstace 사용하기 위해
#include "Kismet/GameplayStatics.h" // UGameplayStatics  사용하기 위해

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true; // InitializeComponet 호출 허락
	Level = 1;

	// ...
}


void UMyActorComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevel(Level);
}

// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyActorComponent::SetLevel(int32 _Level)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto CharacterData = MyGameInstance->GetCharacterData(_Level);	 
		if (CharacterData)
		{
			Level = CharacterData->Level;
			MaxHp = CharacterData->MaxHp;
			Hp = MaxHp;

			UE_LOG(LogTemp, Warning, TEXT("HP : %d"), Hp);
			UE_LOG(LogTemp, Warning, TEXT("Level : %d"), Level);
		}
	}
}

void UMyActorComponent::OnDamaged(float DamageAmount)
{

	Hp -= DamageAmount;
	if (Hp < 0)
	{
		Hp = 0;
	}

	UE_LOG(LogTemp, Warning, TEXT("HP : %d"), Hp);
}


