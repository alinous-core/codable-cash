/*
 * CdbTableColumn.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "table/CdbTableColumn.h"

#include "engine/CdbOid.h"

#include "base/UnicodeString.h"

#include "transaction/SchemaObjectIdPublisher.h"

#include "base_io/ByteBuffer.h"

#include "transaction_scan_result/ScanResultFieldMetadata.h"

#include "schema/ColumnModifyContext.h"

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

#include "sql_ddl/DdlColumnDescriptor.h"
#include "sql_ddl/ColumnTypeDescriptor.h"

namespace codablecash {



CdbTableColumn::CdbTableColumn(const CdbTableColumn& inst) {
	this->oid = new CdbOid(*inst.oid);
	this->name = new UnicodeString(inst.name);
	this->type = inst.type;
	this->length = inst.length;
	this->notnull = inst.notnull;
	this->unique = inst.unique;
	if(inst.defaultValue != nullptr){
		this->defaultValue = new UnicodeString(inst.defaultValue);
	}else{
		this->defaultValue = nullptr;
	}
	this->position = inst.position;
}


CdbTableColumn::CdbTableColumn(uint64_t oid) {
	this->oid = new CdbOid(oid);
	this->name = nullptr;
	this->type = 0;
	this->length = 0;
	this->notnull = false;
	this->unique = false;
	this->defaultValue = nullptr;
	this->position = 0;
}

CdbTableColumn::~CdbTableColumn() {
	delete this->oid;
	delete this->name;
	delete this->defaultValue;
}

const CdbOid* CdbTableColumn::getOid() const noexcept {
	return this->oid;
}

void CdbTableColumn::setName(const UnicodeString* name) noexcept {
	this->name = new UnicodeString(name);
}

const UnicodeString* CdbTableColumn::getName() const noexcept {
	return this->name;
}

void CdbTableColumn::setType(uint8_t type, int length) noexcept {
	this->type = type;
	this->length = length;
}

void CdbTableColumn::setAttributes(bool notnull, bool unique) noexcept {
	this->notnull = notnull;
	this->unique = unique;
}

void CdbTableColumn::setDefaultValue(const UnicodeString* defaultValue) noexcept {
	delete this->defaultValue;

	if(defaultValue != nullptr){
		this->defaultValue = new UnicodeString(defaultValue);
	}
	else{
		this->defaultValue = nullptr;
	}
}

void CdbTableColumn::assignNewOid(SchemaObjectIdPublisher* publisher) {
	uint64_t oid = publisher->newOid();
	setOid(oid);
}

void CdbTableColumn::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}


int CdbTableColumn::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint8_t);
	total += sizeof(uint64_t); // oid

	total += stringSize(this->name);

	total += sizeof(uint8_t);//uint8_t type;
	total += sizeof(uint32_t);//int length;
	total += sizeof(uint8_t);//bool notnull;
	total += sizeof(uint8_t);//bool unique;

	bool bl = this->defaultValue != nullptr;
	total += sizeof(uint8_t);
	if(bl){
		total += stringSize(this->defaultValue);
	}
	//UnicodeString* defaultValue;

	return total;
}

void CdbTableColumn::toBinary(ByteBuffer* out) const {
	checkNotNull(this->name);

	out->put(CdbTableColumn::CDB_OBJ_TYPE);
	out->putLong(this->oid->getOidValue());

	putString(out, this->name);

	out->put(this->type);
	out->putInt(this->length);
	out->put(this->notnull);
	out->put(this->unique);

	bool bl = this->defaultValue != nullptr;
	out->put(bl ? 1 : 0);
	if(bl){
		putString(out, this->defaultValue);
	}
}

void CdbTableColumn::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	this->type = in->get();
	this->length = in->getInt();
	this->notnull = in->get() > 0;
	this->unique = in->get() > 0;

	bool bl = in->get() > 0;
	if(bl){
		this->defaultValue = getString(in);
	}
}

int CdbTableColumn::getPosition() const noexcept {
	return this->position;
}

void CdbTableColumn::setPosition(int position) noexcept {
	this->position = position;
}

ScanResultFieldMetadata* CdbTableColumn::getFieldMetadata(const CdbTable* table) const noexcept {
	ScanResultFieldMetadata* fld = new ScanResultFieldMetadata(table, this);

	return fld;
}

ColumnModifyContext* CdbTableColumn::createModifyContextwithChange(const AlterModifyCommand* cmd, const UnicodeString* defaultStr){
	return createModifyContextwithChange(cmd, defaultStr, true);
}

ColumnModifyContext* CdbTableColumn::createModifyContextwithChange(const AlterModifyCommand* cmd, const UnicodeString* defaultStr, bool update) {
	ColumnModifyContext* ctx = new ColumnModifyContext();
	const DdlColumnDescriptor* newdesc = cmd->getColumnDescriptor();

	bool nextUnique = newdesc->isUnique();
	if(nextUnique != this->unique){
		if(nextUnique){
			ctx->setUniqueChange(ColumnModifyContext::UniqueChage::TO_UNIQUE);
		}
		else {
			ctx->setUniqueChange(ColumnModifyContext::UniqueChage::TO_NOT_UNIQUE);
		}

		if(update){
			this->unique = nextUnique;
		}
	}
	ctx->setUnique(nextUnique);

	bool nextNotnull = newdesc->isNotNull();
	if(nextNotnull != this->notnull){
		if(nextNotnull){
			ctx->setNotNullChange(ColumnModifyContext::NotNullChage::TO_NOT_NULL);
		}
		else {
			ctx->setNotNullChange(ColumnModifyContext::NotNullChage::RELEASE_NOT_NULL);
		}

		if(update){
			this->notnull = nextNotnull;
		}
	}
	ctx->setNotNull(nextNotnull);

	ColumnTypeDescriptor* typeDesc = newdesc->getColumnTypeDescriptor();
	uint8_t cdbType = typeDesc->toCdbValueType();
	int64_t length = cmd->getLengthValue();

	if(this->type != cdbType || this->length != length){
		ctx->setTypeChanged(true);
		ctx->setCdbType(cdbType);
		ctx->setLength(length);

		if(update){
			this->type = cdbType;
			this->length = length;
		}
	}
	else{
		ctx->setCdbType(this->type);
		ctx->setLength(this->length);
	}

	if((this->defaultValue != nullptr && defaultStr == nullptr) ||
			(this->defaultValue == nullptr && defaultStr != nullptr) ||
			!this->defaultValue->equals(defaultStr)){
		ctx->setDefaultChanged(true);
		ctx->setDefaultValue(defaultStr);


		if(update){
			setDefaultValue(defaultStr);
		}
	}
	else{
		ctx->setDefaultValue(this->defaultValue);
	}

	return ctx;
}

} /* namespace codablecash */
