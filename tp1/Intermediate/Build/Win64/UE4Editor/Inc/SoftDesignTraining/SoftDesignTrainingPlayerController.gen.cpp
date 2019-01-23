// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "SoftDesignTraining.h"
#include "SoftDesignTrainingPlayerController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSoftDesignTrainingPlayerController() {}
// Cross Module References
	SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingPlayerController_NoRegister();
	SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// End Cross Module References
	void ASoftDesignTrainingPlayerController::StaticRegisterNativesASoftDesignTrainingPlayerController()
	{
	}
	UClass* Z_Construct_UClass_ASoftDesignTrainingPlayerController_NoRegister()
	{
		return ASoftDesignTrainingPlayerController::StaticClass();
	}
	UClass* Z_Construct_UClass_ASoftDesignTrainingPlayerController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_APlayerController,
				(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Collision Rendering Utilities|Transformation" },
				{ "IncludePath", "SoftDesignTrainingPlayerController.h" },
				{ "ModuleRelativePath", "SoftDesignTrainingPlayerController.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<ASoftDesignTrainingPlayerController>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&ASoftDesignTrainingPlayerController::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00800284u,
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
	IMPLEMENT_CLASS(ASoftDesignTrainingPlayerController, 1182536885);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASoftDesignTrainingPlayerController(Z_Construct_UClass_ASoftDesignTrainingPlayerController, &ASoftDesignTrainingPlayerController::StaticClass, TEXT("/Script/SoftDesignTraining"), TEXT("ASoftDesignTrainingPlayerController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASoftDesignTrainingPlayerController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
