// Fill out your copyright notice in the Description page of Project Settings.


#include "LittleMagic.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ALittleMagic::ALittleMagic()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateAbstractDefaultSubobject<USphereComponent>("SphereComp");
	//以下注释为代码设置
	
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);//设置物体碰撞类型
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);//设置物体对碰撞通道的反应
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);//设置物体对某类物体的碰撞类型,overlap为重叠
	
	//下面一句为在UE编辑器中设置好配置文件之后在代码中调用
	//SphereComp->SetCollisionProfileName("Projectile");//设置碰撞配置文件名称
	RootComponent = SphereComp;

	EffectComp = CreateAbstractDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);


	MovementComp = CreateAbstractDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;


}

void ALittleMagic::Interact_Implementation()
{

}
/*
void ALittleMagic::DistoryMagic()
{

	CFValue = CurrentLocation - FirstLocation;
	float CFV = CFValue.Size();

	if (CFV == 500)
	{
		GetWorld()->DestroyActor(this);
	}

}

void ALittleMagic::Tick(float DeltaTime)
{
	CurrentLocation = GetActorLocation();
	DistoryMagic();
}

void ALittleMagic::BeginPlay()
{
	FirstLocation = GetActorLocation();
}
*/