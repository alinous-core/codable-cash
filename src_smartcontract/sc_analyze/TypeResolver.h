/*
 * TypeResolver.h
 *
 *  Created on: 2019/06/23
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_TYPERESOLVER_H_
#define SC_ANALYZE_TYPERESOLVER_H_

#include "base/UnicodeString.h"

namespace alinous {

class AnalyzeContext;
class AnalyzedType;
class CodeElement;
class UnicodeString;
class CompilationUnit;
class ImportsDeclare;
class AbstractType;
class ObjectType;

class TypeResolver {
public:
	static UnicodeString DOT;

	explicit TypeResolver(AnalyzeContext* ctx);
	virtual ~TypeResolver();

	AnalyzedType* resolveType(CodeElement* element, AbstractType* type) const;

	AnalyzedType* findClassType(CodeElement* element, const UnicodeString* name) const;
	static bool isFqn(const UnicodeString* name) noexcept;
	static UnicodeString* getPackageName(const UnicodeString* name) noexcept;
	static UnicodeString* getClassName(const UnicodeString* name) noexcept;

private:
	AnalyzedType* resolveType(CodeElement* element, ObjectType* type) const;

	AnalyzedType* findFromImports(const UnicodeString* name, ImportsDeclare* imports) const;
	AnalyzedType* findClassType(const UnicodeString* packageName, const UnicodeString* name) const;

private:
	AnalyzeContext* const ctx;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_TYPERESOLVER_H_ */
