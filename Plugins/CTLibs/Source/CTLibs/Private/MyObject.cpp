// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject.h"

void UMyObject::CallableFunc() {

}

void UMyObject::CallableFuncWithParams(const FString& str)
{
}

int32 UMyObject::CallableFuncWithParamsAndRet(const FString& str)
{
	return int32();
}

void UMyObject::NativeFunc_Implementation() {
}

void UMyObject::GetObjects(const UClass* inCls, TArray<UObject*>& outObj) {
	GetObjectsOfClass(inCls, outObj);

	for (auto obj : outObj) {
		UE_LOG(LogTemp, Log, TEXT("obj: %s"), *(obj->GetName()));
	}
}

void UMyObject::GetObjectClassName(const UObject* object)
{
	UClass* cls = object->GetClass();
	FName clsName = cls->GetFName();
	UE_LOG(LogTemp, Log, TEXT("%s"), *(clsName.ToString()));
}

void UMyObject::IterateFields(const UObject* object)
{
	//for (TFieldIterator<FProperty> i(object->GetClass()); i; ++i) {
	//	FProperty* prop = *i;
	//	
	//	FString fieldname;
	//	prop->GetName(fieldname);
	//	

	//	UE_LOG(LogTemp, Log, TEXT("%s"), *fieldname);
	//}

	UClass* cls = object->GetClass();
	for (FProperty* prop = cls->PropertyLink; prop; prop = prop->PropertyLinkNext) {
		FString propName = prop->GetName();
		FString propType = prop->GetCPPType();

		//UE_LOG(LogTemp, Log, TEXT("%s : %s"), *propType, *propType);

		// 把属性转为字符串属性， FStrProperty: Describes a dynamic string variable.
		if (propType == "FString" && propName == "Name") {
			FStrProperty* strProp = CastField<FStrProperty>(prop);
			//FStrProperty::TCppType
			
			// 获取提供的“容器”中属性值的指针。(FProperty 拥有对应类型中改属性的偏移, 通过 对象 + 偏移 的方式获取属性)
			const void* addr = strProp->ContainerPtrToValuePtr<void>(object);
			// 获取属性值
			FString propValue = strProp->GetPropertyValue(addr);
			UE_LOG(LogTemp, Log, TEXT("%s : %s, value: %s"), *propType, *propName, *propValue);

			// 设置属性值
			strProp->SetPropertyValue(const_cast<void*>(addr), "World!");
			propValue = strProp->GetPropertyValue(addr);
			UE_LOG(LogTemp, Log, TEXT("after set value: %s"), *propValue);
		}
	}
}

void UMyObject::IterateFunctions(const UObject* object)
{
	for (TFieldIterator<UFunction> iter(object->GetClass()); iter; ++iter) {
		UFunction* func = *iter;

		FString funcName = func->GetName();

		if (funcName == "HelloWorld") {
			UE_LOG(LogTemp, Log, TEXT("func name: %s"), *funcName);

			for (TFieldIterator<FProperty> iterParam(func); iterParam; ++iterParam) {
				FProperty* param = *iterParam;

				FString paramType = param->GetCPPType();
				FString paramName = param->GetName();

				UE_LOG(LogTemp, Log, TEXT("param type: %s, param name: %s"), *paramType, *paramName);
			}
		}
	}
	
}

void UMyObject::GetParentClass(const UObject* object)
{
	UClass* parentCls = object->GetClass()->GetSuperClass();

	FString parentClsName = parentCls->GetName();
	UE_LOG(LogTemp, Log, TEXT("parentCls name: %s"), *parentClsName);
}

void UMyObject::Obj1IsChildOfObj2(const UObject* object1, const UObject* object2)
{
	UClass* cls1 = object1->GetClass();
	UClass* cls2 = object2->GetClass();

	if (cls1->IsChildOf(cls2)) {
		UE_LOG(LogTemp, Log, TEXT("object1 is object2's child"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("object1 is not object2's child"));
	}
}

void UMyObject::GetChildrenClass(const UObject* object)
{
	UClass* cls = object->GetClass();

	TArray<UClass*> childrenCls;
	GetDerivedClasses(cls, childrenCls, false);
	
	for (auto childCls : childrenCls) {
		UE_LOG(LogTemp, Log, TEXT("child : %s"), *(childCls->GetName()));
	}
}

void UMyObject::CallObjectFuncHello(UObject* object)
{
	UClass* cls = object->GetClass();
	UFunction* func = cls->FindFunctionByName(FName("HelloWorld"));

	//参数与函数参数, 返回值严格一致
	//注意字节对齐(可以使用 链表?), 下面的示例中没有处理字节对齐的情况
	//蓝图中浮点数位 8 字节, 即 double
	struct params {
		//params
		double f;
		int32 i;

		//return value
		int32 ri;
		bool rb;
	} p;

	p.f = 10.24;
	p.i = 1024;

	uint8* pointerToParams = (uint8*)(&p);
	uint8* pointerToResult = (uint8*)(&p.ri);

	//调用 _alloca 分配一个栈内存, 用于存储 params
	void* paramPropBuffer = (uint8*)FMemory_Alloca(func->ParmsSize);
	FMemory::Memzero(paramPropBuffer, func->ParmsSize);

	//设置 paramPropBuffer 中的值
	for (TFieldIterator<FProperty> iterParam(func); iterParam; ++iterParam) {
		void* addr = iterParam->ContainerPtrToValuePtr<void>(paramPropBuffer);

		//设置返回值这段可以不写
		if (iterParam->PropertyFlags & CPF_OutParm) {
			int32 pSize = iterParam->GetSize();
			iterParam->CopyCompleteValue(addr, pointerToResult);
			UE_LOG(LogTemp, Log, TEXT("%d"), pSize);
			pointerToResult += pSize;
		}

		else if (iterParam->PropertyFlags & CPF_Parm) {
			int32 pSize = iterParam->GetSize();
			iterParam->CopyCompleteValue(addr, pointerToParams);
			UE_LOG(LogTemp, Log, TEXT("%d"), pSize);
			pointerToParams += pSize;
		}
	}

	//反射调用函数
	object->ProcessEvent(func, paramPropBuffer);

	pointerToResult = (uint8*)(&p.ri);

	for (TFieldIterator<FProperty> iterResult(func); iterResult; ++iterResult) {
		void* addr = iterResult->ContainerPtrToValuePtr<void>(paramPropBuffer);
		if (iterResult->PropertyFlags & CPF_OutParm) {
			iterResult->CopyCompleteValue(pointerToResult, addr);
			pointerToResult += iterResult->GetSize();
		}
	}

	UE_LOG(LogTemp, Log, TEXT("result: ri : %d, rb : %d"), p.ri, p.rb);
}
