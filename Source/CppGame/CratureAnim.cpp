// Fill out your copyright notice in the Description page of Project Settings.


#include "CratureAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCratureAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Creature = Cast<ACharacter>(Pawn);

		if (IsValid(Creature))
		{
			CharacterMovement = Creature->GetCharacterMovement();
		}
	}
}

void UCratureAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Creature))
	{
		Velocity = CharacterMovement->Velocity;
		FRotator Rotation = Creature->GetActorRotation();
		FVector UnrotateVector = Rotation.UnrotateVector(Velocity);
		Vertical = UnrotateVector.X;
		Horizontal = UnrotateVector.Y;
		Speed = Velocity.Size2D();

		//auto Acceleration = CharacterMovement->GetCurrentAcceleration();
		//ShouldMove = Speed > 3.f && Acceleration != FVector::Zero();
		ShouldMove = Speed > 3.f;
		IsFalling = CharacterMovement->IsFalling();
	}


}

void UCratureAnim::PlayAttackMontage()
{
	if (IsValid(AttackMontage))
	{
		if (!Montage_IsPlaying(AttackMontage))
		{
			Montage_Play(AttackMontage);
		}
	}
}

void UCratureAnim::AnimNotify_Hit()
{	
	OnAttackHit.Broadcast();
}
