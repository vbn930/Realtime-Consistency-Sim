// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimPlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSimPlayerController() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
NETSIMPROJECT_API UClass* Z_Construct_UClass_ASimPlayerController();
NETSIMPROJECT_API UClass* Z_Construct_UClass_ASimPlayerController_NoRegister();
UPackage* Z_Construct_UPackage__Script_NetSimProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASimPlayerController *****************************************************
void ASimPlayerController::StaticRegisterNativesASimPlayerController()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASimPlayerController;
UClass* ASimPlayerController::GetPrivateStaticClass()
{
	using TClass = ASimPlayerController;
	if (!Z_Registration_Info_UClass_ASimPlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SimPlayerController"),
			Z_Registration_Info_UClass_ASimPlayerController.InnerSingleton,
			StaticRegisterNativesASimPlayerController,
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
	return Z_Registration_Info_UClass_ASimPlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_ASimPlayerController_NoRegister()
{
	return ASimPlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASimPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "SimPlayerController.h" },
		{ "ModuleRelativePath", "Public/SimPlayerController.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASimPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ASimPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_NetSimProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASimPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASimPlayerController_Statics::ClassParams = {
	&ASimPlayerController::StaticClass,
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
	0x009003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASimPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_ASimPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASimPlayerController()
{
	if (!Z_Registration_Info_UClass_ASimPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASimPlayerController.OuterSingleton, Z_Construct_UClass_ASimPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASimPlayerController.OuterSingleton;
}
ASimPlayerController::ASimPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASimPlayerController);
ASimPlayerController::~ASimPlayerController() {}
// ********** End Class ASimPlayerController *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h__Script_NetSimProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASimPlayerController, ASimPlayerController::StaticClass, TEXT("ASimPlayerController"), &Z_Registration_Info_UClass_ASimPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASimPlayerController), 489416289U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h__Script_NetSimProject_369494468(TEXT("/Script/NetSimProject"),
	Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h__Script_NetSimProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_NetSimProject_Source_NetSimProject_Public_SimPlayerController_h__Script_NetSimProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
