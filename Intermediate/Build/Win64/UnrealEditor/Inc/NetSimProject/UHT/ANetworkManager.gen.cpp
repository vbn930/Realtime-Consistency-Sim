// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ANetworkManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeANetworkManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
NETSIMPROJECT_API UClass* Z_Construct_UClass_AANetworkManager();
NETSIMPROJECT_API UClass* Z_Construct_UClass_AANetworkManager_NoRegister();
NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetworkAgent_NoRegister();
UPackage* Z_Construct_UPackage__Script_NetSimProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AANetworkManager Function IsSocketEnabled ********************************
struct Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics
{
	struct ANetworkManager_eventIsSocketEnabled_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Network Simulation" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((ANetworkManager_eventIsSocketEnabled_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ANetworkManager_eventIsSocketEnabled_Parms), &Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AANetworkManager, nullptr, "IsSocketEnabled", Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::PropPointers), sizeof(Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::ANetworkManager_eventIsSocketEnabled_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::Function_MetaDataParams), Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::ANetworkManager_eventIsSocketEnabled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AANetworkManager_IsSocketEnabled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AANetworkManager_IsSocketEnabled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AANetworkManager::execIsSocketEnabled)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsSocketEnabled();
	P_NATIVE_END;
}
// ********** End Class AANetworkManager Function IsSocketEnabled **********************************

// ********** Begin Class AANetworkManager Function SetAsClient ************************************
struct Z_Construct_UFunction_AANetworkManager_SetAsClient_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Network Simulation" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AANetworkManager_SetAsClient_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AANetworkManager, nullptr, "SetAsClient", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AANetworkManager_SetAsClient_Statics::Function_MetaDataParams), Z_Construct_UFunction_AANetworkManager_SetAsClient_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AANetworkManager_SetAsClient()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AANetworkManager_SetAsClient_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AANetworkManager::execSetAsClient)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetAsClient();
	P_NATIVE_END;
}
// ********** End Class AANetworkManager Function SetAsClient **************************************

// ********** Begin Class AANetworkManager Function SetAsServer ************************************
struct Z_Construct_UFunction_AANetworkManager_SetAsServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Network Simulation" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AANetworkManager_SetAsServer_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AANetworkManager, nullptr, "SetAsServer", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AANetworkManager_SetAsServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_AANetworkManager_SetAsServer_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AANetworkManager_SetAsServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AANetworkManager_SetAsServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AANetworkManager::execSetAsServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetAsServer();
	P_NATIVE_END;
}
// ********** End Class AANetworkManager Function SetAsServer **************************************

// ********** Begin Class AANetworkManager *********************************************************
void AANetworkManager::StaticRegisterNativesAANetworkManager()
{
	UClass* Class = AANetworkManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "IsSocketEnabled", &AANetworkManager::execIsSocketEnabled },
		{ "SetAsClient", &AANetworkManager::execSetAsClient },
		{ "SetAsServer", &AANetworkManager::execSetAsServer },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AANetworkManager;
UClass* AANetworkManager::GetPrivateStaticClass()
{
	using TClass = AANetworkManager;
	if (!Z_Registration_Info_UClass_AANetworkManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("ANetworkManager"),
			Z_Registration_Info_UClass_AANetworkManager.InnerSingleton,
			StaticRegisterNativesAANetworkManager,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AANetworkManager.InnerSingleton;
}
UClass* Z_Construct_UClass_AANetworkManager_NoRegister()
{
	return AANetworkManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AANetworkManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "ANetworkManager.h" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Agent_MetaData[] = {
		{ "Category", "Experiment" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimulatedLatency_MetaData[] = {
		{ "Category", "Network Simulation" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimulatedPacketLoss_MetaData[] = {
		{ "Category", "Network Simulation" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PathfindingRadius_MetaData[] = {
		{ "Category", "Network Simulation" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsServer_MetaData[] = {
		{ "Category", "Network Simulation" },
		{ "ModuleRelativePath", "Public/ANetworkManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Agent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SimulatedLatency;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SimulatedPacketLoss;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PathfindingRadius;
	static void NewProp_bIsServer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsServer;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AANetworkManager_IsSocketEnabled, "IsSocketEnabled" }, // 122641262
		{ &Z_Construct_UFunction_AANetworkManager_SetAsClient, "SetAsClient" }, // 2645776659
		{ &Z_Construct_UFunction_AANetworkManager_SetAsServer, "SetAsServer" }, // 834207612
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AANetworkManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AANetworkManager_Statics::NewProp_Agent = { "Agent", nullptr, (EPropertyFlags)0x0010000000000801, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AANetworkManager, Agent), Z_Construct_UClass_ANetworkAgent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Agent_MetaData), NewProp_Agent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AANetworkManager_Statics::NewProp_SimulatedLatency = { "SimulatedLatency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AANetworkManager, SimulatedLatency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimulatedLatency_MetaData), NewProp_SimulatedLatency_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AANetworkManager_Statics::NewProp_SimulatedPacketLoss = { "SimulatedPacketLoss", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AANetworkManager, SimulatedPacketLoss), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimulatedPacketLoss_MetaData), NewProp_SimulatedPacketLoss_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AANetworkManager_Statics::NewProp_PathfindingRadius = { "PathfindingRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AANetworkManager, PathfindingRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PathfindingRadius_MetaData), NewProp_PathfindingRadius_MetaData) };
void Z_Construct_UClass_AANetworkManager_Statics::NewProp_bIsServer_SetBit(void* Obj)
{
	((AANetworkManager*)Obj)->bIsServer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AANetworkManager_Statics::NewProp_bIsServer = { "bIsServer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AANetworkManager), &Z_Construct_UClass_AANetworkManager_Statics::NewProp_bIsServer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsServer_MetaData), NewProp_bIsServer_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AANetworkManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AANetworkManager_Statics::NewProp_Agent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AANetworkManager_Statics::NewProp_SimulatedLatency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AANetworkManager_Statics::NewProp_SimulatedPacketLoss,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AANetworkManager_Statics::NewProp_PathfindingRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AANetworkManager_Statics::NewProp_bIsServer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AANetworkManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AANetworkManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_NetSimProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AANetworkManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AANetworkManager_Statics::ClassParams = {
	&AANetworkManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AANetworkManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AANetworkManager_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AANetworkManager_Statics::Class_MetaDataParams), Z_Construct_UClass_AANetworkManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AANetworkManager()
{
	if (!Z_Registration_Info_UClass_AANetworkManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AANetworkManager.OuterSingleton, Z_Construct_UClass_AANetworkManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AANetworkManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AANetworkManager);
AANetworkManager::~AANetworkManager() {}
// ********** End Class AANetworkManager ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h__Script_NetSimProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AANetworkManager, AANetworkManager::StaticClass, TEXT("AANetworkManager"), &Z_Registration_Info_UClass_AANetworkManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AANetworkManager), 1097829137U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h__Script_NetSimProject_1011202253(TEXT("/Script/NetSimProject"),
	Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h__Script_NetSimProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_ANetworkManager_h__Script_NetSimProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
