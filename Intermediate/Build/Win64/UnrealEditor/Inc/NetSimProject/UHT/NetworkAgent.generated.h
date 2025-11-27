// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetworkAgent.h"

#ifdef NETSIMPROJECT_NetworkAgent_generated_h
#error "NetworkAgent.generated.h already included, missing '#pragma once' in NetworkAgent.h"
#endif
#define NETSIMPROJECT_NetworkAgent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ANetworkAgent ************************************************************
NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetworkAgent_NoRegister();

#define FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANetworkAgent(); \
	friend struct Z_Construct_UClass_ANetworkAgent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetworkAgent_NoRegister(); \
public: \
	DECLARE_CLASS2(ANetworkAgent, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/NetSimProject"), Z_Construct_UClass_ANetworkAgent_NoRegister) \
	DECLARE_SERIALIZER(ANetworkAgent)


#define FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h_13_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANetworkAgent(ANetworkAgent&&) = delete; \
	ANetworkAgent(const ANetworkAgent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANetworkAgent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANetworkAgent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ANetworkAgent) \
	NO_API virtual ~ANetworkAgent();


#define FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h_10_PROLOG
#define FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h_13_INCLASS_NO_PURE_DECLS \
	FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANetworkAgent;

// ********** End Class ANetworkAgent **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
