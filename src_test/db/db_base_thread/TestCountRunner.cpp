/*
 * TestCountRunner.cpp
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#include "db/db_base_thread/TestCountRunner.h"

namespace alinous {

TestCountRunner::TestCountRunner() : AbstractThreadRunner() {
}

TestCountRunner::TestCountRunner(const UnicodeString* name) : AbstractThreadRunner(name) {

}

TestCountRunner::~TestCountRunner() {
}

void TestCountRunner::process() noexcept {

}

} /* namespace alinous */
