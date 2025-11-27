// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetSimProject_init() {}
	NETSIMPROJECT_API UFunction* Z_Construct_UDelegateFunction_NetSimProject_OnEnemyDied__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_NetSimProject;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_NetSimProject()
	{
		if (!Z_Registration_Info_UPackage__Script_NetSimProject.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_NetSimProject_OnEnemyDied__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/NetSimProject",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x652A52EB,
				0x2D2FB7D0,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_NetSimProject.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_NetSimProject.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_NetSimProject(Z_Construct_UPackage__Script_NetSimProject, TEXT("/Script/NetSimProject"), Z_Registration_Info_UPackage__Script_NetSimProject, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x652A52EB, 0x2D2FB7D0));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
