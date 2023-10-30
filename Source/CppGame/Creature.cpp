// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "CratureAnim.h"
#include "MyActorComponent.h"


ACreature::ACreature()
{
	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorComponent"));
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();

	CreatureAnimInstance = Cast<UCratureAnim>(GetMesh()->GetAnimInstance());
	CreatureAnimInstance->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackMontageEnded);
}

float ACreature::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	MyActorComponent->OnDamaged(Damage);
	return Damage;
}

void ACreature::Attack()
{
	if (IsAttacking)
	{
		return;
	}

	if (IsValid(CreatureAnimInstance))
	{
		CreatureAnimInstance->PlayAttackMontage();
		IsAttacking = true;
	}
}

void ACreature::OnHit()
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
}

void ACreature::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}
