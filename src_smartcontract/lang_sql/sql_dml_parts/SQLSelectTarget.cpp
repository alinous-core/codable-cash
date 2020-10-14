/*
 * SQLSelectTarget.cpp
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLSelectTarget.h"
#include "base/UnicodeString.h"
#include "lang_sql/sql/AbstractSQLExpression.h"

#include "scan_select/scan_planner/base/TablesHolder.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_columns/AllScanColumns.h"
#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"

using namespace codablecash;

namespace alinous {

SQLSelectTarget::SQLSelectTarget() : AbstractSQLPart(CodeElement::SQL_PART_SELECT_TARGET) {
	this->wildcard = false;
	this->exp = nullptr;
	this->asName = nullptr;
}

SQLSelectTarget::~SQLSelectTarget() {
	delete this->exp;
	delete this->asName;
}

void SQLSelectTarget::setWildcard(bool wildcard) noexcept {
	this->wildcard = wildcard;
}

void SQLSelectTarget::setExpression(AbstractSQLExpression* exp) noexcept {
	if(exp->getKind() == CodeElement::SQL_EXP_WILDCARD){
		setWildcard(true);
	}

	this->exp = exp;
}

void SQLSelectTarget::setAsName(UnicodeString* asName) noexcept {
	this->asName = asName;
}

void SQLSelectTarget::preAnalyze(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->setParent(this);
		this->exp->preAnalyze(actx);
	}
}

void SQLSelectTarget::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->analyzeTypeRef(actx);
	}
}

void SQLSelectTarget::analyze(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->analyze(actx);
	}
}

void SQLSelectTarget::init(VirtualMachine* vm) {
	if(this->exp != nullptr){
		this->exp->init(vm);
	}
}

AbstractVmInstance* SQLSelectTarget::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	if(this->wildcard){
		AllScanColumns* col = new AllScanColumns();
		colHolder->push(col);

		return nullptr;
	}

	this->exp->onSelectTarget(vm);

	return nullptr;
}

int SQLSelectTarget::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint8_t);
	total += sizeof(uint8_t);
	if(this->exp != nullptr && !this->wildcard){
		total += this->exp->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->asName != nullptr){
		total += stringSize(this->asName);
	}

	return total;
}

void SQLSelectTarget::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_PART_SELECT_TARGET);

	out->put(this->wildcard ? 1 : 0);
	out->put((this->exp != nullptr  && !this->wildcard) ? 1 : 0);
	if(this->exp != nullptr && !this->wildcard){
		this->exp->toBinary(out);
	}

	out->put(this->asName != nullptr ? 1 : 0);
	if(this->asName != nullptr){
		putString(out, this->asName);
	}
}

void SQLSelectTarget::fromBinary(ByteBuffer* in) {
	int8_t bl = in->get();
	this->wildcard = (bl == 1);

	bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkIsSQLExp(element);
		this->exp = dynamic_cast<AbstractSQLExpression*>(element);

		checkNotNull(this->exp);
	}

	bl = in->get();
	if(bl == 1){
		this->asName = getString(in);
	}
}

} /* namespace alinous */
