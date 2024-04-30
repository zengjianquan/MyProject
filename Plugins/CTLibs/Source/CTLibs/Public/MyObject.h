// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CTLIBS_API UMyObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	float Score;

public:
	//查看 .gen.cpp, 如何定义蓝图函数
	UFUNCTION(BlueprintCallable, Category = "Hello")
	void CallableFunc();    //C++实现，蓝图调用

	UFUNCTION(BlueprintCallable, Category = "Hello")
	void CallableFuncWithParams(const FString& str);    //C++实现，蓝图调用

	UFUNCTION(BlueprintCallable, Category = "Hello")
	int32 CallableFuncWithParamsAndRet(const FString& str);    //C++实现，蓝图调用

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Hello")
	void NativeFunc();  //C++实现默认版本，蓝图可重载实现
	void NativeFunc_Implementation();	//实现

	UFUNCTION(BlueprintImplementableEvent, Category = "Hello")
	void ImplementableFunc();   //C++不实现，蓝图实现


public:
	//反射
	UFUNCTION(BlueprintCallable, Category = "Hello")
	void GetObjects(const UClass* inCls, TArray<UObject*>& outObj);

	UFUNCTION(BlueprintCallable, Category = "Hello")
	void GetObjectClassName(const UObject* object);

	UFUNCTION(BlueprintCallable, Category = "Hello")
	void IterateFields(const UObject* object);

	UFUNCTION(BlueprintCallable, Category = "Hello")
	void IterateFunctions(const UObject* object);

	UFUNCTION(BlueprintCallable, Category = "Hello")
	void GetParentClass(const UObject* object);

	UFUNCTION(BlueprintCallable, Category = "Hello")
	void Obj1IsChildOfObj2(const UObject* object1, const UObject* object2);

	UFUNCTION(BlueprintCallable, Category = "Hello")
	void GetChildrenClass(const UObject* object);

	UFUNCTION(BlueprintCallable, Category = "Hello")
	void CallObjectFuncHello(UObject* object);
};
