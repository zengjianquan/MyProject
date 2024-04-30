// Copyright Epic Games, Inc. All Rights Reserved.

#include "CTLibs.h"
#include "Interfaces/IPluginManager.h"	//Projects

#define LOCTEXT_NAMESPACE "FCTLibsModule"

void FCTLibsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("CTLibs"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/CTLibs"), PluginShaderDir);	//RenderCore
}

void FCTLibsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FCTLibsModule::PostLoadCallback()
{
	//CTSceneViewExtension = FSceneViewExtensions::NewExtension<FCTSceneViewExtension>(FLinearColor::Red);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCTLibsModule, CTLibs)