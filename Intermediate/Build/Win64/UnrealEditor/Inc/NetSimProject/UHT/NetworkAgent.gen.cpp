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

// ********** Begin Class ANetworkAgent ************************************************************
void ANetworkAgent::StaticRegisterNativesANetworkAgent()
{
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
	nullptr,
	Z_Construct_UClass_ANetworkAgent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
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
		{ Z_Construct_UClass_ANetworkAgent, ANetworkAgent::StaticClass, TEXT("ANetworkAgent"), &Z_Registration_Info_UClass_ANetworkAgent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANetworkAgent), 1325097348U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h__Script_NetSimProject_999137443(TEXT("/Script/NetSimProject"),
	Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h__Script_NetSimProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_NetworkAgent_h__Script_NetSimProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
