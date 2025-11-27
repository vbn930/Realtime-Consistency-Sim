// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetSimProjectCharacter.h"

#ifdef NETSIMPROJECT_NetSimProjectCharacter_generated_h
#error "NetSimProjectCharacter.generated.h already included, missing '#pragma once' in NetSimProjectCharacter.h"
#endif
#define NETSIMPROJECT_NetSimProjectCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ANetSimProjectCharacter **************************************************
#define FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetSimProjectCharacter_NoRegister();

#define FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANetSimProjectCharacter(); \
	friend struct Z_Construct_UClass_ANetSimProjectCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetSimProjectCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ANetSimProjectCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/NetSimProject"), Z_Construct_UClass_ANetSimProjectCharacter_NoRegister) \
	DECLARE_SERIALIZER(ANetSimProjectCharacter)


#define FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANetSimProjectCharacter(ANetSimProjectCharacter&&) = delete; \
	ANetSimProjectCharacter(const ANetSimProjectCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANetSimProjectCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANetSimProjectCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ANetSimProjectCharacter) \
	NO_API virtual ~ANetSimProjectCharacter();


#define FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h_21_PROLOG
#define FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANetSimProjectCharacter;

// ********** End Class ANetSimProjectCharacter ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NetSimProject_Source_NetSimProject_NetSimProjectCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
