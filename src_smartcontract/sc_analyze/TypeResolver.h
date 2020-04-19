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
	static const UnicodeString DOT;

	static const UnicodeString BOOLEAN;
	static const UnicodeString BYTE;
	static const UnicodeString CHAR;
	static const UnicodeString SHORT;
	static const UnicodeString INT;
	static const UnicodeString LONG;
	static const UnicodeString STRING;


	explicit TypeResolver(AnalyzeContext* ctx);
	virtual ~TypeResolver();

	AnalyzedType* getClassType(CodeElement* element) const;
	AnalyzedType* resolveType(CodeElement* element, AbstractType* type) const;
	AnalyzedType* findClassType(const CodeElement* element, const UnicodeString* name) const;

	AnalyzedType* findBaseType(const UnicodeString* name) const;
	AnalyzedType* findClassType(const UnicodeString* packageName, const UnicodeString* name) const;

	static bool isFqn(const UnicodeString* name) noexcept;
	static UnicodeString* getPackageName(const UnicodeString* name) noexcept;
	static UnicodeString* getClassName(const UnicodeString* name) noexcept;

private:
	AnalyzedType* resolveType(CodeElement* element, ObjectType* type) const;

	AnalyzedType* findFromImports(const UnicodeString* name, ImportsDeclare* imports) const;


#ifdef __DEBUG__
public:
	AnalyzedType* testFindClassType(const UnicodeString* packageName, const UnicodeString* name) const;
	AnalyzedType* testResolveType(CodeElement* element, ObjectType* type) const;
#endif

private:
	AnalyzeContext* const ctx;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_TYPERESOLVER_H_ */
