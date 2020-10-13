/*
 * VmTestUtils.h
 *
 *  Created on: 2019/11/24
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_VM_VMTESTUTILS_H_
#define SMARTCONTRACT_VM_VMTESTUTILS_H_
#include <cstdlib>

#include "base/ArrayList.h"

#include "engine/compiler/CompileError.h"

#include "ext_binary/ExtExceptionObject.h"

#include "../test_utils/TestEnv.h"

namespace alinous {

class UnicodeString;
class File;
class SmartContract;
class VirtualMachine;
class VmClassInstance;
class ExtClassObject;
class AnalyzedType;
class ExtArrayObject;

class VmTestUtils {
public:
	VmTestUtils(const wchar_t* seg, const File* projectFolder);
	VmTestUtils(const wchar_t* seg, const File* projectFolder, TestEnv* env);
	virtual ~VmTestUtils();

private:
	void init(const wchar_t* seg, const File* projectFolder) noexcept;
	void initdb(const wchar_t* seg, const File* projectFolder, TestEnv* env);
public:
	bool loadAllFiles();
	void scanFiles(File* folder, SmartContract* sc);
	void addCompilantUnit(File* file, SmartContract* sc, File* base);

	void setMain(const wchar_t* pkg, const wchar_t* clazz, const wchar_t* method) noexcept;
	bool analyze();
	bool createInstance();
	ExtClassObject* getMainExtObject();

	bool hasAnalyzeError(int errorType);

	AnalyzedType* findClassDeclare(const wchar_t* classFqn);
	AnalyzedType* findClassDeclare(const UnicodeString* classFqn);

	static bool getBoolMemberValue(ExtClassObject* obj, const wchar_t* str);
	static int64_t getIntMemberValue(ExtClassObject* obj, const wchar_t* str);
	static int64_t getByteMemberValue(ExtClassObject* obj, const wchar_t* str);
	static int64_t getShortMemberValue(ExtClassObject* obj, const wchar_t* str);
	static int64_t getCharMemberValue(ExtClassObject* obj, const wchar_t* str);
	static int64_t getLongMemberValue(ExtClassObject* obj, const wchar_t* str);
	static const UnicodeString* getStringMemberValue(ExtClassObject* obj, const wchar_t* str);
	static ExtClassObject* getObjectValue(ExtClassObject* obj, const wchar_t* str);
	static ExtExceptionObject* getExtExceptionObject(ExtClassObject* obj, const wchar_t* str);

	static ExtArrayObject* getArrayMember(ExtClassObject* obj, const wchar_t* str);

	static int64_t getArrayInt(ExtArrayObject* array, int pos);

	VirtualMachine* vm;
	SmartContract* sc;
	VmClassInstance* mainInst;
	const ArrayList<CompileError>* compile_errors;

private:
	File* folder;

};

} /* namespace alinous */

#endif /* SMARTCONTRACT_VM_VMTESTUTILS_H_ */
