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

#include "instance/VmClassInstance.h"

#include "ext_binary/AbstractExtObject.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "sc_analyze/AnalyzeContext.h"

#include "sc_analyze/TypeResolver.h"

#include "sc/CompilationUnit.h"

namespace alinous {

VmTestUtils::VmTestUtils(const wchar_t* seg, const File* projectFolder) {
	this->folder = projectFolder->get(seg);
	this->vm = new VirtualMachine(1024*1024);
	this->sc = nullptr;
	this->mainInst = nullptr;
}

VmTestUtils::~VmTestUtils() {
	vm->destroy();
	delete this->vm;
	delete this->folder;
	this->sc = nullptr;
	this->mainInst = nullptr;
}


bool VmTestUtils::analyze() {
	vm->analyze();
	return !vm->hasError();
}

bool VmTestUtils::createInstance() {
	this->mainInst = vm->createScInstance();
	ArrayList<AbstructProgramException>& exceptions = vm->getExceptions();

	return !vm->hasError() && exceptions.isEmpty();
}

bool VmTestUtils::loadAllFiles() {
	SmartContract* sc = new SmartContract();

	scanFiles(this->folder, sc);

	this->sc = sc;
	this->vm->loadSmartContract(sc);

	const ArrayList<CompileError>* list = this->sc->getCompileErrors();

	return list->isEmpty();
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
			addCompilantUnit(f, sc, folder);
		}
	}
}

void VmTestUtils::addCompilantUnit(File* file, SmartContract* sc, File* base) {
	int length = file->length();
	FileInputStream stream(file);

	sc->addCompilationUnit(&stream, length, base, file);
}

void VmTestUtils::setMain(const wchar_t* pkg, const wchar_t* clazz,	const wchar_t* method) noexcept {
	UnicodeString mainPackage(pkg);
	UnicodeString mainClass(clazz);
	UnicodeString mainMethod(method);
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);
}

ExtClassObject* VmTestUtils::getMainExtObject() {
	AnalyzeContext* actx = this->sc->getAnalyzeContext();
	VTableRegistory* reg = actx->getVtableRegistory();

	UnicodeString name(L"name");
	AbstractExtObject* extObj = this->mainInst->toClassExtObject(&name, reg);

	return dynamic_cast<ExtClassObject*>(extObj);
}

AnalyzedType* VmTestUtils::findClassDeclare(const wchar_t* classFqn) {
	UnicodeString strFqn(classFqn);

	return findClassDeclare(&strFqn);
}


AnalyzedType* VmTestUtils::findClassDeclare(const UnicodeString* classFqn) {
	CompilationUnit* unit = this->sc->getCompilationUnit(0);

	AnalyzeContext* actx = this->sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	return resolver->findClassType(unit, classFqn);
}

bool VmTestUtils::getBoolMemberValue(ExtClassObject* obj, const wchar_t* str) {
	UnicodeString strResult(str);
	ExtPrimitiveObject* oresult = obj->getExtPrimitiveObject(&strResult);
	return oresult->getBoolValue();
}

int64_t VmTestUtils::getIntMemberValue(ExtClassObject* obj,	const wchar_t* str) {
	UnicodeString strResult(str);
	ExtPrimitiveObject* oresult = obj->getExtPrimitiveObject(&strResult);
	return oresult->getIntValue();
}

} /* namespace alinous */
