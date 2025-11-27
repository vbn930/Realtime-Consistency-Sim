// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NetSimProjectGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeNetSimProjectGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetSimProjectGameMode();
NETSIMPROJECT_API UClass* Z_Construct_UClass_ANetSimProjectGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_NetSimProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ANetSimProjectGameMode ***************************************************
void ANetSimProjectGameMode::StaticRegisterNativesANetSimProjectGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ANetSimProjectGameMode;
UClass* ANetSimProjectGameMode::GetPrivateStaticClass()
{
	using TClass = ANetSimProjectGameMode;
	if (!Z_Registration_Info_UClass_ANetSimProjectGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("NetSimProjectGameMode"),
			Z_Registration_Info_UClass_ANetSimProjectGameMode.InnerSingleton,
			StaticRegisterNativesANetSimProjectGameMode,
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
	return Z_Registration_Info_UClass_ANetSimProjectGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_ANetSimProjectGameMode_NoRegister()
{
	return ANetSimProjectGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ANetSimProjectGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a third person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "NetSimProjectGameMode.h" },
		{ "ModuleRelativePath", "NetSimProjectGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a third person game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANetSimProjectGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ANetSimProjectGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_NetSimProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetSimProjectGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ANetSimProjectGameMode_Statics::ClassParams = {
	&ANetSimProjectGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008003ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANetSimProjectGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ANetSimProjectGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ANetSimProjectGameMode()
{
	if (!Z_Registration_Info_UClass_ANetSimProjectGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANetSimProjectGameMode.OuterSingleton, Z_Construct_UClass_ANetSimProjectGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ANetSimProjectGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ANetSimProjectGameMode);
ANetSimProjectGameMode::~ANetSimProjectGameMode() {}
// ********** End Class ANetSimProjectGameMode *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h__Script_NetSimProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANetSimProjectGameMode, ANetSimProjectGameMode::StaticClass, TEXT("ANetSimProjectGameMode"), &Z_Registration_Info_UClass_ANetSimProjectGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANetSimProjectGameMode), 1954315655U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h__Script_NetSimProject_2543571012(TEXT("/Script/NetSimProject"),
	Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h__Script_NetSimProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_NetSimProjectGameMode_h__Script_NetSimProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
