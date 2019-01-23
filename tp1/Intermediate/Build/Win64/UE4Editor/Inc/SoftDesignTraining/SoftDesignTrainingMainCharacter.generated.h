// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef SOFTDESIGNTRAINING_SoftDesignTrainingMainCharacter_generated_h
#error "SoftDesignTrainingMainCharacter.generated.h already included, missing '#pragma once' in SoftDesignTrainingMainCharacter.h"
#endif
#define SOFTDESIGNTRAINING_SoftDesignTrainingMainCharacter_generated_h

#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnBeginOverlap) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComponent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_OtherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnBeginOverlap(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComponent,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	}


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnBeginOverlap) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComponent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_OtherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnBeginOverlap(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComponent,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	}


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASoftDesignTrainingMainCharacter(); \
	friend SOFTDESIGNTRAINING_API class UClass* Z_Construct_UClass_ASoftDesignTrainingMainCharacter(); \
public: \
	DECLARE_CLASS(ASoftDesignTrainingMainCharacter, ASoftDesignTrainingCharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SoftDesignTraining"), NO_API) \
	DECLARE_SERIALIZER(ASoftDesignTrainingMainCharacter) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_INCLASS \
private: \
	static void StaticRegisterNativesASoftDesignTrainingMainCharacter(); \
	friend SOFTDESIGNTRAINING_API class UClass* Z_Construct_UClass_ASoftDesignTrainingMainCharacter(); \
public: \
	DECLARE_CLASS(ASoftDesignTrainingMainCharacter, ASoftDesignTrainingCharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SoftDesignTraining"), NO_API) \
	DECLARE_SERIALIZER(ASoftDesignTrainingMainCharacter) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASoftDesignTrainingMainCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASoftDesignTrainingMainCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASoftDesignTrainingMainCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASoftDesignTrainingMainCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASoftDesignTrainingMainCharacter(ASoftDesignTrainingMainCharacter&&); \
	NO_API ASoftDesignTrainingMainCharacter(const ASoftDesignTrainingMainCharacter&); \
public:


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASoftDesignTrainingMainCharacter(ASoftDesignTrainingMainCharacter&&); \
	NO_API ASoftDesignTrainingMainCharacter(const ASoftDesignTrainingMainCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASoftDesignTrainingMainCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASoftDesignTrainingMainCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASoftDesignTrainingMainCharacter)


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__m_TopDownCameraComponent() { return STRUCT_OFFSET(ASoftDesignTrainingMainCharacter, m_TopDownCameraComponent); } \
	FORCEINLINE static uint32 __PPO__m_CameraBoom() { return STRUCT_OFFSET(ASoftDesignTrainingMainCharacter, m_CameraBoom); } \
	FORCEINLINE static uint32 __PPO__m_PowerUpDuration() { return STRUCT_OFFSET(ASoftDesignTrainingMainCharacter, m_PowerUpDuration); } \
	FORCEINLINE static uint32 __PPO__m_PoweredUpMaterial() { return STRUCT_OFFSET(ASoftDesignTrainingMainCharacter, m_PoweredUpMaterial); }


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_12_PROLOG
#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_PRIVATE_PROPERTY_OFFSET \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_RPC_WRAPPERS \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_INCLASS \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_PRIVATE_PROPERTY_OFFSET \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_INCLASS_NO_PURE_DECLS \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
