/*
 * TestExecutor.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "test_utils/TestExecutor.h"
#include "test_utils/TestGroup.h"
#include "test_utils/TestParams.h"
#include "test_utils/TestSummary.h"
#include "base/UnicodeString.h"

#include "osenv/funcs.h"

#include "base_io/File.h"
#include "base_io_stream/FileOutputStream.h"
#include "base_io_stream/exceptions.h"

#include "base_io_stream/OutputStreamWriter.h"
namespace alinous {

TestExecutor::TestExecutor() {
	this->groups = new HashMap<UnicodeString, TestGroup>();
	this->initialized = false;
}

TestExecutor* TestExecutor::get() noexcept {
	static TestExecutor testExecInst;

	return &testExecInst;
}

TestExecutor::~TestExecutor() {
	delete this->groups;
}

void TestExecutor::addGroup(UnicodeString* name, TestGroup* group) noexcept {
	this->groups->put(name, group);
}

int TestExecutor::execute(int ac, char** av) noexcept {
	if(!this->initialized){
		init(av[0]);
	}

	TestParams params;
	try{
		params.init(ac, av);
	}catch(TestParamsException* ex){
		printf("Wrong parameter...\n");
		return -1;
	}

	printf("Start Testing...\n");
	uint64_t start, end;

	start = Os::getMicroSec();
	execTest(&params);
	end = Os::getMicroSec();

	TestSummary summary;
	summaryTest(&summary);

	if(!params.isV()){
		printf("\n");
	}
	printf("Testing Summary\n");
	summary.echoSummary();

	double milli = ((double)end-(double)start) / (double)1000;
	printf("Testing Duration : %.3lf ms\n", milli);

	exporJUnitXML();

	int exitValue = summary.isSuccess() ? 0 : -1;

	return exitValue;
}



void TestExecutor::execTest(TestParams* params) noexcept {
	auto* it = this->groups->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestGroup* grp = this->groups->get(key);

		if(params->skipGroup(grp->getName())){
			continue;
		}

		if(params->isV()){
			UnicodeString* str = grp->getName();
			assert(str != nullptr);
			const wchar_t* wstr = str->towString();
			assert(wstr != nullptr);

			printf("Testing Test Group : %ls\n", wstr);
		}

		grp->execute(params);
	}
	delete it;
}

void TestExecutor::init(const char* prog) noexcept {
	auto* it = this->groups->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestGroup* grp = this->groups->get(key);
		grp->init(prog);
	}
	delete it;
}

void TestExecutor::exporJUnitXML() const {
	UnicodeString path(L"junit.xml");
	File file(&path);

	FileOutputStream* stream = nullptr;
	OutputStreamWriter* writer = nullptr;
	try{
		stream = new FileOutputStream(&file);
		stream->open(false);

		writer = new OutputStreamWriter(stream);

		writer->write(L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
		writer->write(L"<testsuite name=\"CPP Program Test All\">\n");

		auto* it = this->groups->keySet()->iterator();
		while(it->hasNext()){
			const UnicodeString* key = it->next();
			TestGroup* grp = this->groups->get(key);

			grp->exportJUnitXML(writer);
		}
		delete it;

		writer->write(L"</testsuite>\n");

		writer->close();
	}
	catch(Exception* exp){
		delete exp;
	}

	delete writer;
	delete stream;
}

void TestExecutor::summaryTest(TestSummary* summary) noexcept {
	auto* it = this->groups->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestGroup* grp = this->groups->get(key);

		grp->summaryTest(summary);
	}
	delete it;
}

} /* namespace alinous */
