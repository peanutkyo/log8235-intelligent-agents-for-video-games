// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "SoftDesignTraining.h"
#include "SDTCollectible.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSDTCollectible() {}
// Cross Module References
	SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASDTCollectible_NoRegister();
	SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASDTCollectible();
	ENGINE_API UClass* Z_Construct_UClass_AStaticMeshActor();
	UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// End Cross Module References
	void ASDTCollectible::StaticRegisterNativesASDTCollectible()
	{
	}
	UClass* Z_Construct_UClass_ASDTCollectible_NoRegister()
	{
		return ASDTCollectible::StaticClass();
	}
	UClass* Z_Construct_UClass_ASDTCollectible()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AStaticMeshActor,
				(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Input" },
				{ "IncludePath", "SDTCollectible.h" },
				{ "ModuleRelativePath", "SDTCollectible.h" },
				{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_m_CollectCooldownDuration_MetaData[] = {
				{ "Category", "AI" },
				{ "ModuleRelativePath", "SDTCollectible.h" },
			};
#endif
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_m_CollectCooldownDuration = { UE4CodeGen_Private::EPropertyClass::Float, "m_CollectCooldownDuration", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(ASDTCollectible, m_CollectCooldownDuration), METADATA_PARAMS(NewProp_m_CollectCooldownDuration_MetaData, ARRAY_COUNT(NewProp_m_CollectCooldownDuration_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_m_CollectCooldownDuration,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<ASDTCollectible>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&ASDTCollectible::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				nullptr, 0,
				PropPointers, ARRAY_COUNT(PropPointers),
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASDTCollectible, 3617608217);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASDTCollectible(Z_Construct_UClass_ASDTCollectible, &ASDTCollectible::StaticClass, TEXT("/Script/SoftDesignTraining"), TEXT("ASDTCollectible"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASDTCollectible);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
