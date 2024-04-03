// Fill out your copyright notice in the Description page of Project Settings.


#include "LittleMagic.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ALittleMagic::ALittleMagic()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateAbstractDefaultSubobject<USphereComponent>("SphereComp");
	//����ע��Ϊ��������
	
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);//����������ײ����
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);//�����������ײͨ���ķ�Ӧ
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);//���������ĳ���������ײ����,overlapΪ�ص�
	
	//����һ��Ϊ��UE�༭�������ú������ļ�֮���ڴ����е���
	//SphereComp->SetCollisionProfileName("Projectile");//������ײ�����ļ�����
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