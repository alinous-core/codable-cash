/*
 * VmTestUtils.h
 *
 *  Created on: 2019/11/24
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_VM_VMTESTUTILS_H_
#define SMARTCONTRACT_VM_VMTESTUTILS_H_

namespace alinous {

class UnicodeString;
class File;
class SmartContract;
class VirtualMachine;
class VmClassInstance;
class ExtClassObject;
class AnalyzedType;

class VmTestUtils {
public:
	VmTestUtils(const wchar_t* seg, const File* projectFolder);
	virtual ~VmTestUtils();

	bool loadAllFiles();
	void scanFiles(File* folder, SmartContract* sc);
	void addCompilantUnit(File* file, SmartContract* sc, File* base);

	void setMain(const wchar_t* pkg, const wchar_t* clazz, const wchar_t* method) noexcept;
	bool analyze();
	bool createInstance();
	ExtClassObject* getMainExtObject();

	AnalyzedType* findClassDeclare(const UnicodeString* classFqn);

	VirtualMachine* vm;
	SmartContract* sc;
private:
	File* folder;
	VmClassInstance* mainInst;
};

} /* namespace alinous */

#endif /* SMARTCONTRACT_VM_VMTESTUTILS_H_ */
