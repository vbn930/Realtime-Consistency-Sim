// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetSimProjectPlayerController.h"

#ifdef NETSIMPROJECT_NetSimProjectPlayerController_generated_h
#error "NetSimProjectPlayerController.generated.h already included, missing '#pragma once' in NetSimProjectPlayerController.h"
#endif
#define NETSIMPROJECT_NetSimProjectPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ANetSimProjectPlayerController *******************************************
NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetSimProjectPlayerController_NoRegister();

#define FID_NetSimProject_Source_NetSimProject_NetSimProjectPlayerController_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANetSimProjectPlayerController(); \
	friend struct Z_Construct_UClass_ANetSimProjectPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetSimProjectPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ANetSimProjectPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/NetSimProject"), Z_Construct_UClass_ANetSimProjectPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ANetSimProjectPlayerController)


#define FID_NetSimProject_Source_NetSimProject_NetSimProjectPlayerController_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ANetSimProjectPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANetSimProjectPlayerController(ANetSimProjectPlayerController&&) = delete; \
	ANetSimProjectPlayerController(const ANetSimProjectPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANetSimProjectPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANetSimProjectPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ANetSimProjectPlayerController) \
	NO_API virtual ~ANetSimProjectPlayerController();


#define FID_NetSimProject_Source_NetSimProject_NetSimProjectPlayerController_h_16_PROLOG
#define FID_NetSimProject_Source_NetSimProject_NetSimProjectPlayerController_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_NetSimProject_Source_NetSimProject_NetSimProjectPlayerController_h_19_INCLASS_NO_PURE_DECLS \
	FID_NetSimProject_Source_NetSimProject_NetSimProjectPlayerController_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANetSimProjectPlayerController;

// ********** End Class ANetSimProjectPlayerController *********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NetSimProject_Source_NetSimProject_NetSimProjectPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
