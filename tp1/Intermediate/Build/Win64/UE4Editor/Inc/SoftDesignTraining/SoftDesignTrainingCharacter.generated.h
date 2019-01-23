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
#ifdef SOFTDESIGNTRAINING_SoftDesignTrainingCharacter_generated_h
#error "SoftDesignTrainingCharacter.generated.h already included, missing '#pragma once' in SoftDesignTrainingCharacter.h"
#endif
#define SOFTDESIGNTRAINING_SoftDesignTrainingCharacter_generated_h

#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_RPC_WRAPPERS \
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


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
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


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASoftDesignTrainingCharacter(); \
	friend SOFTDESIGNTRAINING_API class UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter(); \
public: \
	DECLARE_CLASS(ASoftDesignTrainingCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SoftDesignTraining"), NO_API) \
	DECLARE_SERIALIZER(ASoftDesignTrainingCharacter) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_INCLASS \
private: \
	static void StaticRegisterNativesASoftDesignTrainingCharacter(); \
	friend SOFTDESIGNTRAINING_API class UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter(); \
public: \
	DECLARE_CLASS(ASoftDesignTrainingCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SoftDesignTraining"), NO_API) \
	DECLARE_SERIALIZER(ASoftDesignTrainingCharacter) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASoftDesignTrainingCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASoftDesignTrainingCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASoftDesignTrainingCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASoftDesignTrainingCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASoftDesignTrainingCharacter(ASoftDesignTrainingCharacter&&); \
	NO_API ASoftDesignTrainingCharacter(const ASoftDesignTrainingCharacter&); \
public:


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASoftDesignTrainingCharacter(ASoftDesignTrainingCharacter&&); \
	NO_API ASoftDesignTrainingCharacter(const ASoftDesignTrainingCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASoftDesignTrainingCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASoftDesignTrainingCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASoftDesignTrainingCharacter)


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_PRIVATE_PROPERTY_OFFSET
#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_7_PROLOG
#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_PRIVATE_PROPERTY_OFFSET \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_RPC_WRAPPERS \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_INCLASS \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_PRIVATE_PROPERTY_OFFSET \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_INCLASS_NO_PURE_DECLS \
	softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID softdesigntraining_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
