// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ANetworkManager.h"

#ifdef NETSIMPROJECT_ANetworkManager_generated_h
#error "ANetworkManager.generated.h already included, missing '#pragma once' in ANetworkManager.h"
#endif
#define NETSIMPROJECT_ANetworkManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AANetworkManager *********************************************************
#define FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsSocketEnabled); \
	DECLARE_FUNCTION(execSetAsClient); \
	DECLARE_FUNCTION(execSetAsServer);


NETSIMPROJECT_API UClass* Z_Construct_UClass_AANetworkManager_NoRegister();

#define FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAANetworkManager(); \
	friend struct Z_Construct_UClass_AANetworkManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend NETSIMPROJECT_API UClass* Z_Construct_UClass_AANetworkManager_NoRegister(); \
public: \
	DECLARE_CLASS2(AANetworkManager, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/NetSimProject"), Z_Construct_UClass_AANetworkManager_NoRegister) \
	DECLARE_SERIALIZER(AANetworkManager)


#define FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AANetworkManager(AANetworkManager&&) = delete; \
	AANetworkManager(const AANetworkManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AANetworkManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AANetworkManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AANetworkManager) \
	NO_API virtual ~AANetworkManager();


#define FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h_16_PROLOG
#define FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h_19_INCLASS_NO_PURE_DECLS \
	FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AANetworkManager;

// ********** End Class AANetworkManager ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
