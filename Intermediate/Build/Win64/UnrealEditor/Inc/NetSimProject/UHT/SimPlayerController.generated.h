// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SimPlayerController.h"

#ifdef NETSIMPROJECT_SimPlayerController_generated_h
#error "SimPlayerController.generated.h already included, missing '#pragma once' in SimPlayerController.h"
#endif
#define NETSIMPROJECT_SimPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASimPlayerController *****************************************************
NETSIMPROJECT_API UClass* Z_Construct_UClass_ASimPlayerController_NoRegister();

#define FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASimPlayerController(); \
	friend struct Z_Construct_UClass_ASimPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend NETSIMPROJECT_API UClass* Z_Construct_UClass_ASimPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ASimPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/NetSimProject"), Z_Construct_UClass_ASimPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ASimPlayerController)


#define FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASimPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASimPlayerController(ASimPlayerController&&) = delete; \
	ASimPlayerController(const ASimPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASimPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASimPlayerController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASimPlayerController) \
	NO_API virtual ~ASimPlayerController();


#define FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h_12_PROLOG
#define FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h_15_INCLASS_NO_PURE_DECLS \
	FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASimPlayerController;

// ********** End Class ASimPlayerController *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
