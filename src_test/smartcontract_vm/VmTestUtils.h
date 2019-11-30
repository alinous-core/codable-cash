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

class VmTestUtils {
public:
	VmTestUtils(const wchar_t* seg, const File* projectFolder);
	virtual ~VmTestUtils();

	void loadAllFiles();
	void scanFiles(File* folder, SmartContract* sc);
	void addCompilantUnit(File* file, SmartContract* sc);

	void setMain(const wchar_t* pkg, const wchar_t* clazz, const wchar_t* method) noexcept;
	bool analyze();
	bool createInstance();

	VirtualMachine* vm;
	SmartContract* sc;
private:
	File* folder;
};

} /* namespace alinous */

#endif /* SMARTCONTRACT_VM_VMTESTUTILS_H_ */