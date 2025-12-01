// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NetworkAgent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeNetworkAgent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetworkAgent();
NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetworkAgent_NoRegister();
UPackage* Z_Construct_UPackage__Script_NetSimProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ANetworkAgent Function GetCurrentAlgorithmState **************************
struct Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics
{
	struct NetworkAgent_eventGetCurrentAlgorithmState_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Network Status" },
		{ "ModuleRelativePath", "Public/NetworkAgent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkAgent_eventGetCurrentAlgorithmState_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ANetworkAgent, nullptr, "GetCurrentAlgorithmState", Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::PropPointers), sizeof(Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::NetworkAgent_eventGetCurrentAlgorithmState_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::Function_MetaDataParams), Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::NetworkAgent_eventGetCurrentAlgorithmState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ANetworkAgent::execGetCurrentAlgorithmState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetCurrentAlgorithmState();
	P_NATIVE_END;
}
// ********** End Class ANetworkAgent Function GetCurrentAlgorithmState ****************************

// ********** Begin Class ANetworkAgent ************************************************************
void ANetworkAgent::StaticRegisterNativesANetworkAgent()
{
	UClass* Class = ANetworkAgent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetCurrentAlgorithmState", &ANetworkAgent::execGetCurrentAlgorithmState },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ANetworkAgent;
UClass* ANetworkAgent::GetPrivateStaticClass()
{
	using TClass = ANetworkAgent;
	if (!Z_Registration_Info_UClass_ANetworkAgent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("NetworkAgent"),
			Z_Registration_Info_UClass_ANetworkAgent.InnerSingleton,
			StaticRegisterNativesANetworkAgent,
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
	return Z_Registration_Info_UClass_ANetworkAgent.InnerSingleton;
}
UClass* Z_Construct_UClass_ANetworkAgent_NoRegister()
{
	return ANetworkAgent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ANetworkAgent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "NetworkAgent.h" },
		{ "ModuleRelativePath", "Public/NetworkAgent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsEnablePrediction_MetaData[] = {
		{ "Category", "Network Simulation" },
		{ "ModuleRelativePath", "Public/NetworkAgent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bIsEnablePrediction_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsEnablePrediction;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ANetworkAgent_GetCurrentAlgorithmState, "GetCurrentAlgorithmState" }, // 1035889407
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANetworkAgent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
void Z_Construct_UClass_ANetworkAgent_Statics::NewProp_bIsEnablePrediction_SetBit(void* Obj)
{
	((ANetworkAgent*)Obj)->bIsEnablePrediction = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ANetworkAgent_Statics::NewProp_bIsEnablePrediction = { "bIsEnablePrediction", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ANetworkAgent), &Z_Construct_UClass_ANetworkAgent_Statics::NewProp_bIsEnablePrediction_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsEnablePrediction_MetaData), NewProp_bIsEnablePrediction_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANetworkAgent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetworkAgent_Statics::NewProp_bIsEnablePrediction,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkAgent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ANetworkAgent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_NetSimProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkAgent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ANetworkAgent_Statics::ClassParams = {
	&ANetworkAgent::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ANetworkAgent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkAgent_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkAgent_Statics::Class_MetaDataParams), Z_Construct_UClass_ANetworkAgent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ANetworkAgent()
{
	if (!Z_Registration_Info_UClass_ANetworkAgent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANetworkAgent.OuterSingleton, Z_Construct_UClass_ANetworkAgent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ANetworkAgent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ANetworkAgent);
ANetworkAgent::~ANetworkAgent() {}
// ********** End Class ANetworkAgent **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h__Script_NetSimProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANetworkAgent, ANetworkAgent::StaticClass, TEXT("ANetworkAgent"), &Z_Registration_Info_UClass_ANetworkAgent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANetworkAgent), 3252213018U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h__Script_NetSimProject_3320632135(TEXT("/Script/NetSimProject"),
	Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h__Script_NetSimProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h__Script_NetSimProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
