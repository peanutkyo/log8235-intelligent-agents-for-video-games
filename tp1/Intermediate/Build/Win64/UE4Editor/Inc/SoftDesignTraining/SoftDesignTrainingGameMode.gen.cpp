// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "SoftDesignTraining.h"
#include "SoftDesignTrainingGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSoftDesignTrainingGameMode() {}
// Cross Module References
	SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingGameMode_NoRegister();
	SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// End Cross Module References
	void ASoftDesignTrainingGameMode::StaticRegisterNativesASoftDesignTrainingGameMode()
	{
	}
	UClass* Z_Construct_UClass_ASoftDesignTrainingGameMode_NoRegister()
	{
		return ASoftDesignTrainingGameMode::StaticClass();
	}
	UClass* Z_Construct_UClass_ASoftDesignTrainingGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AGameMode,
				(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
				{ "IncludePath", "SoftDesignTrainingGameMode.h" },
				{ "ModuleRelativePath", "SoftDesignTrainingGameMode.h" },
				{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<ASoftDesignTrainingGameMode>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&ASoftDesignTrainingGameMode::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x0088028Cu,
				nullptr, 0,
				nullptr, 0,
				"Game",
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASoftDesignTrainingGameMode, 689979211);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASoftDesignTrainingGameMode(Z_Construct_UClass_ASoftDesignTrainingGameMode, &ASoftDesignTrainingGameMode::StaticClass, TEXT("/Script/SoftDesignTraining"), TEXT("ASoftDesignTrainingGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASoftDesignTrainingGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
