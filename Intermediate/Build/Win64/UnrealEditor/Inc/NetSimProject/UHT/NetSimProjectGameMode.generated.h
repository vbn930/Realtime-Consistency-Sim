// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetSimProjectGameMode.h"

#ifdef NETSIMPROJECT_NetSimProjectGameMode_generated_h
#error "NetSimProjectGameMode.generated.h already included, missing '#pragma once' in NetSimProjectGameMode.h"
#endif
#define NETSIMPROJECT_NetSimProjectGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ANetSimProjectGameMode ***************************************************
NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetSimProjectGameMode_NoRegister();

#define FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANetSimProjectGameMode(); \
	friend struct Z_Construct_UClass_ANetSimProjectGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetSimProjectGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(ANetSimProjectGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/NetSimProject"), Z_Construct_UClass_ANetSimProjectGameMode_NoRegister) \
	DECLARE_SERIALIZER(ANetSimProjectGameMode)


#define FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANetSimProjectGameMode(ANetSimProjectGameMode&&) = delete; \
	ANetSimProjectGameMode(const ANetSimProjectGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANetSimProjectGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANetSimProjectGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ANetSimProjectGameMode) \
	NO_API virtual ~ANetSimProjectGameMode();


#define FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h_12_PROLOG
#define FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANetSimProjectGameMode;

// ********** End Class ANetSimProjectGameMode *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
