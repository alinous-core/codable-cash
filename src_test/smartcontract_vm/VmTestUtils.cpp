/*
 * VmTestUtils.cpp
 *
 *  Created on: 2019/11/24
 *      Author: iizuka
 */

#include "VmTestUtils.h"

#include "base/UnicodeString.h"

#include "sc/SmartContract.h"
#include "vm/VirtualMachine.h"

#include "base/StackRelease.h"
#include "base_io/File.h"
#include "base_io_stream/FileInputStream.h"

namespace alinous {

VmTestUtils::VmTestUtils(const wchar_t* seg, const File* projectFolder) {
	this->folder = projectFolder->get(seg);
	this->vm = new VirtualMachine(1024*1024);
	this->sc = nullptr;
}

VmTestUtils::~VmTestUtils() {
	vm->destroy();
	delete this->vm;
	delete this->folder;
	this->sc = nullptr;
}

void VmTestUtils::loadAllFiles() {
	SmartContract* sc = new SmartContract();

	scanFiles(this->folder, sc);

	this->sc = sc;
	this->vm->loadSmartContract(sc);
}

void VmTestUtils::scanFiles(File* folder, SmartContract* sc) {
	ArrayList<UnicodeString>* filesList = folder->list(); __STP(filesList);
	filesList->setDeleteOnExit();

	int maxLoop = filesList->size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* path = filesList->get(i);

		File* f = folder->get(path); __STP(f);
		if(f->isDirectory()){
			scanFiles(f, sc);
		}
		else{
			addCompilantUnit(f, sc);
		}
	}
}

void VmTestUtils::addCompilantUnit(File* file, SmartContract* sc) {
	int length = file->length();
	FileInputStream stream(file);

	sc->addCompilationUnit(&stream, length);
}

void VmTestUtils::setMain(const wchar_t* pkg, const wchar_t* clazz,	const wchar_t* method) noexcept {
	UnicodeString mainPackage(pkg);
	UnicodeString mainClass(clazz);
	UnicodeString mainMethod(method);
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);
}

} /* namespace alinous */
