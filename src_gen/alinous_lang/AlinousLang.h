#ifndef ALINOUSLANG_H
#define ALINOUSLANG_H
#include "JavaCC.h"
#include "CharStream.h"
#include "Token.h"
#include "TokenManager.h"
#include "sc/alinouslang.h"
#include "AlinousLangConstants.h"
#include "ErrorHandler.h"
namespace alinouslang {
  struct JJCalls {
    int        gen;
    int        arg;
    JJCalls*   next;
    Token*     first;
    ~JJCalls() { if (next) delete next; }
     JJCalls() { next = nullptr; arg = 0; gen = -1; first = nullptr; }
  };

class AlinousLang {
public:
CompilationUnit
               * compilationUnit();
ImportsDeclare              * importsDeclare();
ImportDeclare             * importDeclare();
PackageDeclare              * packageDeclare();
PackageNameDeclare                  * packageNameDeclare();
ClassDeclare            * classDeclare();
ClassExtends            * classExtends();
ClassImplements               * classImplements();
ClassName         * className();
ClassDeclareBlock                 * classDeclareBlock();
MethodDeclare             * methodDeclare(AccessControlDeclare* ctrl, bool _static, AbstractType* type, Token* identifier);
MemberVariableDeclare                     * memberVariableDeclare(AccessControlDeclare* ctrl, bool _static, AbstractType* type, Token* identifier);
AccessControlDeclare                    * accessControlDeclare();
ArgumentsListDeclare                    * argumentsListDeclare();
ArgumentDeclare               * argumentDeclare();
AbstractType            * typeDeclare();
ObjectType          * objectType();
BoolType        * boolType();
ByteType        * byteType();
CharType        * charType();
ShortType         * shortType();
IntType       * intType();
LongType        * longType();
StringType          * stringType();
VoidType        * voidType();
DomType       * domType();
AbstractStatement
                 * statement();
VariableDeclareStatement                        * variableDeclareStatement();
VariableDeclareStatement                        * __variableDeclareStatement();
AbstractStatement                 * substitutionStatement();
AbstractStatement                 * __substitutionStatement();
BlankStatement              * blankStatement();
StatementBlock              * statementBlock();
AbstractStatement
                 * ctrlStatement();
TryStatement            * tryStatement();
FinallyStatement                * finallyStatement();
CatchStatement              * catchStatement();
ThrowStatement              * throwStatement();
ForStatement            * forStatement();
AbstractStatement                 * forInnerStatement();
DoWhileStatement                * doWhileStatement();
WhileStatement              * whileStatement();
ReturnStatement               * returnStatement();
ContinueStatement                 * continueStatement();
BreakStatement              * breakStatement();
IfStatement           * ifStatement();
IfStatement           * elseifStatement();
AbstractExpression
                  * expression();
AbstractExpression                  * conditionalOrExpression();
AbstractExpression                  * conditionalAndExpression();
AbstractExpression                  * orExpression();
AbstractExpression                  * exclusiveOrExpression();
AbstractExpression                  * andExpression();
AbstractExpression                  * equalityExpression();
AbstractExpression                  * relationalExpression();
AbstractExpression                  * shiftExpression();
AbstractExpression                  * additiveExpression();
AbstractExpression                  * multiplicativeExpression();
AbstractExpression                  * negateExpression();
AbstractExpression                  * postIncrementExpression();
AbstractExpression                  * preIncrementExpression();
AbstractExpression                  * bitReverseExpression();
AbstractExpression                  * notExpression();
AbstractExpression                  * castExpression();
AbstractExpression                  * memberReferenceExpression();
AbstractExpression                  * arrayReferenceExpression();
AbstractExpression                  * functionCallExpression();
void functionCallExpressionArg(FunctionCallExpression* exp);
AbstractExpression                  * primitive();
AllocationExpression                    * allocationExpression();
ConstructorArray                * constructorArray();
ConstructorCall               * constructorCallExpression();
void constructorCallExpressionArg(ConstructorCall* exp);
ParenthesisExpression                     * parenthesisExpression();
VariableIdentifier                  * variableIdentifier();
Token     * identifierName();
VariableIdentifier                  * typeIdentifier();
AbstractExpression                  * literal();
NullLiteral           * nullLiteral();
NumberLiteral             * numberLiteral();
BooleanLiteral              * booleanLiteral();
LiteralExpression                 * literalExpression();
AbstractSQLStatement
                    * ddlStatement();
AlterTableStatement                   * alterTableStatement();
AbstractAlterDdlCommand                       * addAlterCommands();
AlterAddColumnCommand                     * alterAddColumnCommand();
AlterAddIndexCommand                    * alterAddIndexCommand();
CreateTableStatement                    * createTableStatement();
DdlColumnDescriptor                   * ddlColumnDescriptor();
ColumnTypeDescriptor                    * columnTypeDescriptor();
DropTableStatement                  * dropTableStatement();
AbstractSQLStatement
                    * sqlDmlStatement();
SelectStatement               * selectStatement();
SQLSelectTargetList                   * sqlSelectTargetList();
SQLSelectTarget               * sqlSelectTarget();
SQLGroupBy          * sqlGroupBy();
SQLHaving         * sqlHaving();
SQLOrderBy          * sqlOrderBy();
SQLLimitOffset              * sqlLimitOffset();
UpdateStatement               * updateStatement();
SQLSet      * sqlSet();
SQLSetPair          * sqlSetPair();
InsertStatement               * insertStatement();
SQLColumnsList              * sqlColumnsList();
DeleteStatement               * deleteStatement();
SQLWhere        * sqlWhere();
SQLFrom       * sqlFrom();
BeginStatement              * beginStatement();
CommitStatement               * commitStatement();
RollbackStatement                 * rollbackStatement();
AbstractSQLExpression
                     * sqlExpression();
AbstractSQLExpression                     * sqlOrExpression();
AbstractSQLExpression                     * sqlAndExpression();
AbstractSQLExpression                     * sqlNotExpression();
AbstractSQLExpression                     * sqlLikeExpression();
AbstractSQLExpression                     * sqlIsNullExpression();
AbstractSQLExpression                     * sqlBetweenExpression();
AbstractSQLExpression                     * sqlInExpression();
AbstractSQLExpression                     * sqlRelationalExpression();
AbstractSQLExpression                     * sqlEqualityExpression();
AbstractSQLExpression                     * sqlAdditiveExpression();
AbstractSQLExpression                     * sqlMultiplicativeExpression();
AbstractSQLExpression                     * sqlPrimitiveExpression();
SQLWildCard           * sqlWildCard();
SQLFunctionCall               * sqlFunctionCall();
void sqlFunctionCallArguments(SQLFunctionCall* exp);
SQLPlaceHolder              * sqlPlaceHolder();
SQLParenthesisExpression                        * sqlParenthesisExpression();
SQLLiteral          * sqlLiteral();
SQLBooleanLiteral                 * sqlBooleanLiteral();
SQLColumnIdentifier                   * sqlColumnIdentifier();
Token     * sqlIdentifierName();
SQLExpressionList
                 * sqlExpressionList();
AbstractJoinPart
                * tableList();
AbstractJoinPart                * join();
SQLJoinPart           * innerJoin();
SQLJoinPart           * leftJoin();
SQLJoinPart           * rightJoin();
SQLJoinPart           * crossJoin();
AbstractJoinPart                * joinTarget();
ParenthesisJoinPart                   * parenthesisJoinPart();
TableIdentifier               * tableIdentifier();
AbstractJsonExpression
                      * jsonElement();
JsonInitializerExpression                         * jsonInitializerExpression();
JsonArrayExpression                   * jsonArrayExpression();
JsonKeyValuePairExpression                          * jsonKeyValuePair();
 inline bool jj_2_1(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_1() || jj_done);
 { jj_save(0, xla); }
  }

 inline bool jj_2_2(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_2() || jj_done);
 { jj_save(1, xla); }
  }

 inline bool jj_2_3(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_3() || jj_done);
 { jj_save(2, xla); }
  }

 inline bool jj_2_4(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_4() || jj_done);
 { jj_save(3, xla); }
  }

 inline bool jj_2_5(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_5() || jj_done);
 { jj_save(4, xla); }
  }

 inline bool jj_2_6(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_6() || jj_done);
 { jj_save(5, xla); }
  }

 inline bool jj_2_7(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_7() || jj_done);
 { jj_save(6, xla); }
  }

 inline bool jj_2_8(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_8() || jj_done);
 { jj_save(7, xla); }
  }

 inline bool jj_2_9(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_9() || jj_done);
 { jj_save(8, xla); }
  }

 inline bool jj_2_10(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_10() || jj_done);
 { jj_save(9, xla); }
  }

 inline bool jj_2_11(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_11() || jj_done);
 { jj_save(10, xla); }
  }

 inline bool jj_2_12(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_12() || jj_done);
 { jj_save(11, xla); }
  }

 inline bool jj_2_13(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_13() || jj_done);
 { jj_save(12, xla); }
  }

 inline bool jj_2_14(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_14() || jj_done);
 { jj_save(13, xla); }
  }

 inline bool jj_2_15(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_15() || jj_done);
 { jj_save(14, xla); }
  }

 inline bool jj_2_16(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_16() || jj_done);
 { jj_save(15, xla); }
  }

 inline bool jj_2_17(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_17() || jj_done);
 { jj_save(16, xla); }
  }

 inline bool jj_2_18(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_18() || jj_done);
 { jj_save(17, xla); }
  }

 inline bool jj_2_19(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_19() || jj_done);
 { jj_save(18, xla); }
  }

 inline bool jj_2_20(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_20() || jj_done);
 { jj_save(19, xla); }
  }

 inline bool jj_2_21(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_21() || jj_done);
 { jj_save(20, xla); }
  }

 inline bool jj_2_22(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_22() || jj_done);
 { jj_save(21, xla); }
  }

 inline bool jj_2_23(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_23() || jj_done);
 { jj_save(22, xla); }
  }

 inline bool jj_2_24(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_24() || jj_done);
 { jj_save(23, xla); }
  }

 inline bool jj_3R_173()
 {
    if (jj_done) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3R_237()
 {
    if (jj_done) return true;
    if (jj_scan_token(INTEGER_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_195()
 {
    if (jj_done) return true;
    if (jj_scan_token(GEQ)) return true;
    return false;
  }

 inline bool jj_3R_135()
 {
    if (jj_done) return true;
    if (jj_3R_159()) return true;
    return false;
  }

 inline bool jj_3R_177()
 {
    if (jj_done) return true;
    if (jj_3R_183()) return true;
    return false;
  }

 inline bool jj_3R_153()
 {
    if (jj_done) return true;
    if (jj_scan_token(INSERT)) return true;
    if (jj_scan_token(INTO)) return true;
    return false;
  }

 inline bool jj_3R_142()
 {
    if (jj_done) return true;
    if (jj_scan_token(RETURN)) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_173()) jj_scanpos = xsp;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_64()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQL_NOT)) return true;
    return false;
  }

 inline bool jj_3R_194()
 {
    if (jj_done) return true;
    if (jj_scan_token(GT)) return true;
    return false;
  }

 inline bool jj_3R_235()
 {
    if (jj_done) return true;
    if (jj_scan_token(_NULL)) return true;
    return false;
  }

 inline bool jj_3R_48()
 {
    if (jj_done) return true;
    if (jj_3R_49()) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_213()
 {
    if (jj_done) return true;
    if (jj_scan_token(DOLLAR)) return true;
    return false;
  }

 inline bool jj_3R_186()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_194()) {
    jj_scanpos = xsp;
    if (jj_3R_195()) {
    jj_scanpos = xsp;
    if (jj_3R_196()) {
    jj_scanpos = xsp;
    if (jj_3R_197()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3R_234()
 {
    if (jj_done) return true;
    if (jj_3R_238()) return true;
    return false;
  }

 inline bool jj_3R_233()
 {
    if (jj_done) return true;
    if (jj_3R_237()) return true;
    return false;
  }

 inline bool jj_3R_232()
 {
    if (jj_done) return true;
    if (jj_3R_236()) return true;
    return false;
  }

 inline bool jj_3R_231()
 {
    if (jj_done) return true;
    if (jj_3R_235()) return true;
    return false;
  }

 inline bool jj_3R_178()
 {
    if (jj_done) return true;
    if (jj_3R_184()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_186()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3R_230()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_231()) {
    jj_scanpos = xsp;
    if (jj_3R_232()) {
    jj_scanpos = xsp;
    if (jj_3R_233()) {
    jj_scanpos = xsp;
    if (jj_3R_234()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3_12()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    if (jj_3R_44()) return true;
    if (jj_scan_token(R_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_169()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_12()) {
    jj_scanpos = xsp;
    if (jj_3R_177()) return true;
    }
    return false;
  }

 inline bool jj_3_22()
 {
    if (jj_done) return true;
    if (jj_scan_token(IS)) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_64()) jj_scanpos = xsp;
    if (jj_scan_token(_NULL)) return true;
    return false;
  }

 inline bool jj_3R_111()
 {
    if (jj_done) return true;
    if (jj_3R_135()) return true;
    return false;
  }

 inline bool jj_3R_143()
 {
    if (jj_done) return true;
    if (jj_scan_token(WHILE)) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_113()
 {
    if (jj_done) return true;
    if (jj_3R_44()) return true;
    if (jj_3R_87()) return true;
    return false;
  }

 inline bool jj_3R_251()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_scan_token(183)) {
    jj_scanpos = xsp;
    if (jj_scan_token(61)) {
    jj_scanpos = xsp;
    if (jj_scan_token(62)) {
    jj_scanpos = xsp;
    if (jj_scan_token(63)) {
    jj_scanpos = xsp;
    if (jj_scan_token(64)) {
    jj_scanpos = xsp;
    if (jj_scan_token(65)) {
    jj_scanpos = xsp;
    if (jj_scan_token(66)) {
    jj_scanpos = xsp;
    if (jj_scan_token(67)) return true;
    }
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_188()
 {
    if (jj_done) return true;
    if (jj_scan_token(CMP_NOTEQUALS)) return true;
    return false;
  }

 inline bool jj_3R_168()
 {
    if (jj_done) return true;
    if (jj_scan_token(NOT)) return true;
    return false;
  }

 inline bool jj_3R_187()
 {
    if (jj_done) return true;
    if (jj_scan_token(CMP_EQUALS)) return true;
    return false;
  }

 inline bool jj_3R_103()
 {
    if (jj_done) return true;
    if (jj_3R_113()) return true;
    return false;
  }

 inline bool jj_3R_164()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_168()) jj_scanpos = xsp;
    if (jj_3R_169()) return true;
    return false;
  }

 inline bool jj_3R_60()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_65()
 {
    if (jj_done) return true;
    if (jj_3R_87()) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_180()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_187()) {
    jj_scanpos = xsp;
    if (jj_3R_188()) return true;
    }
    return false;
  }

 inline bool jj_3R_46()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_scan_token(183)) {
    jj_scanpos = xsp;
    if (jj_scan_token(91)) {
    jj_scanpos = xsp;
    if (jj_scan_token(88)) {
    jj_scanpos = xsp;
    if (jj_scan_token(114)) {
    jj_scanpos = xsp;
    if (jj_scan_token(115)) {
    jj_scanpos = xsp;
    if (jj_scan_token(116)) {
    jj_scanpos = xsp;
    if (jj_scan_token(117)) {
    jj_scanpos = xsp;
    if (jj_scan_token(120)) {
    jj_scanpos = xsp;
    if (jj_scan_token(118)) {
    jj_scanpos = xsp;
    if (jj_scan_token(121)) {
    jj_scanpos = xsp;
    if (jj_scan_token(122)) {
    jj_scanpos = xsp;
    if (jj_scan_token(123)) {
    jj_scanpos = xsp;
    if (jj_scan_token(124)) {
    jj_scanpos = xsp;
    if (jj_scan_token(125)) {
    jj_scanpos = xsp;
    if (jj_scan_token(126)) {
    jj_scanpos = xsp;
    if (jj_scan_token(127)) {
    jj_scanpos = xsp;
    if (jj_scan_token(128)) {
    jj_scanpos = xsp;
    if (jj_scan_token(129)) {
    jj_scanpos = xsp;
    if (jj_scan_token(131)) {
    jj_scanpos = xsp;
    if (jj_scan_token(132)) {
    jj_scanpos = xsp;
    if (jj_scan_token(133)) {
    jj_scanpos = xsp;
    if (jj_scan_token(134)) {
    jj_scanpos = xsp;
    if (jj_scan_token(135)) {
    jj_scanpos = xsp;
    if (jj_scan_token(136)) {
    jj_scanpos = xsp;
    if (jj_scan_token(137)) {
    jj_scanpos = xsp;
    if (jj_scan_token(142)) {
    jj_scanpos = xsp;
    if (jj_scan_token(143)) {
    jj_scanpos = xsp;
    if (jj_scan_token(145)) {
    jj_scanpos = xsp;
    if (jj_scan_token(146)) {
    jj_scanpos = xsp;
    if (jj_scan_token(147)) {
    jj_scanpos = xsp;
    if (jj_scan_token(148)) {
    jj_scanpos = xsp;
    if (jj_scan_token(149)) {
    jj_scanpos = xsp;
    if (jj_scan_token(150)) {
    jj_scanpos = xsp;
    if (jj_scan_token(151)) {
    jj_scanpos = xsp;
    if (jj_scan_token(152)) {
    jj_scanpos = xsp;
    if (jj_scan_token(153)) {
    jj_scanpos = xsp;
    if (jj_scan_token(154)) {
    jj_scanpos = xsp;
    if (jj_scan_token(155)) {
    jj_scanpos = xsp;
    if (jj_scan_token(156)) {
    jj_scanpos = xsp;
    if (jj_scan_token(157)) {
    jj_scanpos = xsp;
    if (jj_scan_token(158)) {
    jj_scanpos = xsp;
    if (jj_scan_token(159)) {
    jj_scanpos = xsp;
    if (jj_scan_token(160)) return true;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_83()
 {
    if (jj_done) return true;
    if (jj_3R_107()) return true;
    return false;
  }

 inline bool jj_3R_82()
 {
    if (jj_done) return true;
    if (jj_3R_106()) return true;
    return false;
  }

 inline bool jj_3R_81()
 {
    if (jj_done) return true;
    if (jj_3R_105()) return true;
    return false;
  }

 inline bool jj_3R_80()
 {
    if (jj_done) return true;
    if (jj_3R_104()) return true;
    return false;
  }

 inline bool jj_3R_79()
 {
    if (jj_done) return true;
    if (jj_3R_103()) return true;
    return false;
  }

 inline bool jj_3_6()
 {
    if (jj_done) return true;
    if (jj_3R_48()) return true;
    return false;
  }

 inline bool jj_3R_170()
 {
    if (jj_done) return true;
    if (jj_3R_178()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_180()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3_5()
 {
    if (jj_done) return true;
    if (jj_3R_47()) return true;
    return false;
  }

 inline bool jj_3_21()
 {
    if (jj_done) return true;
    if (jj_scan_token(LIKE)) return true;
    if (jj_3R_63()) return true;
    return false;
  }

 inline bool jj_3R_144()
 {
    if (jj_done) return true;
    if (jj_scan_token(DO)) return true;
    if (jj_3R_51()) return true;
    return false;
  }

 inline bool jj_3R_89()
 {
    if (jj_done) return true;
    if (jj_3R_111()) return true;
    return false;
  }

 inline bool jj_3R_209()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASTERISK)) return true;
    return false;
  }

 inline bool jj_3R_87()
 {
    if (jj_done) return true;
    if (jj_3R_46()) return true;
    return false;
  }

 inline bool jj_3R_45()
 {
    if (jj_done) return true;
    if (jj_scan_token(STATIC)) return true;
    return false;
  }

 inline bool jj_3_2()
 {
    if (jj_done) return true;
    if (jj_3R_44()) return true;
    return false;
  }

 inline bool jj_3R_205()
 {
    if (jj_done) return true;
    if (jj_3R_213()) return true;
    return false;
  }

 inline bool jj_3R_163()
 {
    if (jj_done) return true;
    if (jj_scan_token(192)) return true;
    return false;
  }

 inline bool jj_3R_51()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_5()) {
    jj_scanpos = xsp;
    if (jj_3_6()) {
    jj_scanpos = xsp;
    if (jj_3R_79()) {
    jj_scanpos = xsp;
    if (jj_3R_80()) {
    jj_scanpos = xsp;
    if (jj_3R_81()) {
    jj_scanpos = xsp;
    if (jj_3R_82()) {
    jj_scanpos = xsp;
    if (jj_3R_83()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_204()
 {
    if (jj_done) return true;
    if (jj_3R_212()) return true;
    return false;
  }

 inline bool jj_3_23()
 {
    if (jj_done) return true;
    if (jj_3R_65()) return true;
    return false;
  }

 inline bool jj_3R_203()
 {
    if (jj_done) return true;
    if (jj_3R_211()) return true;
    return false;
  }

 inline bool jj_3R_202()
 {
    if (jj_done) return true;
    if (jj_3R_63()) return true;
    return false;
  }

 inline bool jj_3R_201()
 {
    if (jj_done) return true;
    if (jj_3R_210()) return true;
    return false;
  }

 inline bool jj_3R_200()
 {
    if (jj_done) return true;
    if (jj_3R_209()) return true;
    return false;
  }

 inline bool jj_3R_157()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_163()) jj_scanpos = xsp;
    if (jj_3R_164()) return true;
    return false;
  }

 inline bool jj_3_7()
 {
    if (jj_done) return true;
    if (jj_3R_49()) return true;
    return false;
  }

 inline bool jj_3R_172()
 {
    if (jj_done) return true;
    if (jj_scan_token(BIT_AND)) return true;
    return false;
  }

 inline bool jj_3R_154()
 {
    if (jj_done) return true;
    if (jj_scan_token(UPDATE)) return true;
    if (jj_3R_175()) return true;
    return false;
  }

 inline bool jj_3R_192()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_200()) {
    jj_scanpos = xsp;
    if (jj_3R_201()) {
    jj_scanpos = xsp;
    if (jj_3R_202()) {
    jj_scanpos = xsp;
    if (jj_3R_203()) {
    jj_scanpos = xsp;
    if (jj_3_23()) {
    jj_scanpos = xsp;
    if (jj_3R_204()) {
    jj_scanpos = xsp;
    if (jj_3R_205()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_88()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQL_NOT)) return true;
    return false;
  }

 inline bool jj_3R_228()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3R_101()
 {
    if (jj_done) return true;
    if (jj_scan_token(VAR)) return true;
    return false;
  }

 inline bool jj_3_3()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_45()) jj_scanpos = xsp;
    xsp = jj_scanpos;
    if (jj_3_2()) jj_scanpos = xsp;
    if (jj_3R_46()) return true;
    return false;
  }

 inline bool jj_3R_162()
 {
    if (jj_done) return true;
    if (jj_scan_token(PLUSPLUS)) return true;
    return false;
  }

 inline bool jj_3R_165()
 {
    if (jj_done) return true;
    if (jj_3R_170()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_172()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_62()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_88()) jj_scanpos = xsp;
    if (jj_3R_89()) return true;
    return false;
  }

 inline bool jj_3R_161()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUSMINUS)) return true;
    return false;
  }

 inline bool jj_3_18()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMA)) return true;
    if (jj_3R_60()) return true;
    return false;
  }

 inline bool jj_3R_100()
 {
    if (jj_done) return true;
    if (jj_scan_token(VOID)) return true;
    return false;
  }

 inline bool jj_3R_156()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_161()) {
    jj_scanpos = xsp;
    if (jj_3R_162()) return true;
    }
    return false;
  }

 inline bool jj_3R_167()
 {
    if (jj_done) return true;
    if (jj_scan_token(190)) return true;
    return false;
  }

 inline bool jj_3R_99()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING)) return true;
    return false;
  }

 inline bool jj_3R_133()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_156()) jj_scanpos = xsp;
    if (jj_3R_157()) return true;
    return false;
  }

 inline bool jj_3_20()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQLAND)) return true;
    if (jj_3R_62()) return true;
    return false;
  }

 inline bool jj_3R_61()
 {
    if (jj_done) return true;
    if (jj_3R_62()) return true;
    return false;
  }

 inline bool jj_3R_145()
 {
    if (jj_done) return true;
    if (jj_scan_token(FOR)) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_158()
 {
    if (jj_done) return true;
    if (jj_3R_165()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_167()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_56()
 {
    if (jj_done) return true;
    if (jj_scan_token(PLUSPLUS)) return true;
    return false;
  }

 inline bool jj_3R_98()
 {
    if (jj_done) return true;
    if (jj_scan_token(LONG)) return true;
    return false;
  }

 inline bool jj_3R_146()
 {
    if (jj_done) return true;
    if (jj_scan_token(CREATE)) return true;
    if (jj_scan_token(TABLE)) return true;
    return false;
  }

 inline bool jj_3R_55()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUSMINUS)) return true;
    return false;
  }

 inline bool jj_3R_185()
 {
    if (jj_done) return true;
    if (jj_3R_192()) return true;
    return false;
  }

 inline bool jj_3R_59()
 {
    if (jj_done) return true;
    if (jj_3R_87()) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_97()
 {
    if (jj_done) return true;
    if (jj_scan_token(INT)) return true;
    return false;
  }

 inline bool jj_3_24()
 {
    if (jj_done) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3R_250()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_160()
 {
    if (jj_done) return true;
    if (jj_scan_token(BIT_OR)) return true;
    return false;
  }

 inline bool jj_3R_137()
 {
    if (jj_done) return true;
    if (jj_scan_token(THROW)) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3R_249()
 {
    if (jj_done) return true;
    if (jj_3R_238()) return true;
    return false;
  }

 inline bool jj_3_11()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_55()) {
    jj_scanpos = xsp;
    if (jj_3R_56()) return true;
    }
    return false;
  }

 inline bool jj_3_19()
 {
    if (jj_done) return true;
    if (jj_scan_token(OR)) return true;
    if (jj_3R_61()) return true;
    return false;
  }

 inline bool jj_3R_198()
 {
    if (jj_done) return true;
    if (jj_3R_61()) return true;
    return false;
  }

 inline bool jj_3R_109()
 {
    if (jj_done) return true;
    if (jj_3R_133()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_11()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3R_96()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHORT)) return true;
    return false;
  }

 inline bool jj_3R_134()
 {
    if (jj_done) return true;
    if (jj_3R_158()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_160()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_247()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_249()) {
    jj_scanpos = xsp;
    if (jj_3R_250()) return true;
    }
    return false;
  }

 inline bool jj_3_17()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACKET)) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3R_248()
 {
    if (jj_done) return true;
    if (jj_3R_251()) return true;
    return false;
  }

 inline bool jj_3R_189()
 {
    if (jj_done) return true;
    if (jj_3R_198()) return true;
    return false;
  }

 inline bool jj_3R_95()
 {
    if (jj_done) return true;
    if (jj_scan_token(CHAR)) return true;
    return false;
  }

 inline bool jj_3R_108()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    return false;
  }

 inline bool jj_3R_179()
 {
    if (jj_done) return true;
    if (jj_3R_185()) return true;
    return false;
  }

 inline bool jj_3R_136()
 {
    if (jj_done) return true;
    if (jj_scan_token(LOGICAL_AND)) return true;
    return false;
  }

 inline bool jj_3R_84()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_108()) jj_scanpos = xsp;
    if (jj_3R_109()) return true;
    return false;
  }

 inline bool jj_3R_246()
 {
    if (jj_done) return true;
    if (jj_3R_248()) return true;
    return false;
  }

 inline bool jj_3R_245()
 {
    if (jj_done) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3R_94()
 {
    if (jj_done) return true;
    if (jj_scan_token(BYTE)) return true;
    return false;
  }

 inline bool jj_3R_151()
 {
    if (jj_done) return true;
    if (jj_scan_token(ROLLBACK)) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_110()
 {
    if (jj_done) return true;
    if (jj_3R_134()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_136()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_227()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACKET)) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_245()) jj_scanpos = xsp;
    if (jj_scan_token(R_BRACKET)) return true;
    return false;
  }

 inline bool jj_3R_225()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODULO)) return true;
    return false;
  }

 inline bool jj_3_16()
 {
    if (jj_done) return true;
    if (jj_3R_59()) return true;
    return false;
  }

 inline bool jj_3R_93()
 {
    if (jj_done) return true;
    if (jj_scan_token(BOOLEAN)) return true;
    return false;
  }

 inline bool jj_3R_150()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMIT)) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_224()
 {
    if (jj_done) return true;
    if (jj_scan_token(DIV)) return true;
    return false;
  }

 inline bool jj_3R_112()
 {
    if (jj_done) return true;
    if (jj_scan_token(LOGICAL_OR)) return true;
    return false;
  }

 inline bool jj_3_15()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    if (jj_scan_token(DOT)) return true;
    return false;
  }

 inline bool jj_3R_182()
 {
    if (jj_done) return true;
    if (jj_3R_189()) return true;
    return false;
  }

 inline bool jj_3R_223()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASTERISK)) return true;
    return false;
  }

 inline bool jj_3R_244()
 {
    if (jj_done) return true;
    if (jj_3R_247()) return true;
    return false;
  }

 inline bool jj_3R_229()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEW)) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_15()) { jj_scanpos = xsp; break; }
    }
    xsp = jj_scanpos;
    if (jj_3_16()) {
    jj_scanpos = xsp;
    if (jj_3R_246()) return true;
    }
    return false;
  }

 inline bool jj_3R_85()
 {
    if (jj_done) return true;
    if (jj_3R_110()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_112()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_149()
 {
    if (jj_done) return true;
    if (jj_scan_token(BEGIN)) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_214()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_223()) {
    jj_scanpos = xsp;
    if (jj_3R_224()) {
    jj_scanpos = xsp;
    if (jj_3R_225()) return true;
    }
    }
    return false;
  }

 inline bool jj_3_4()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    if (jj_scan_token(DOT)) return true;
    return false;
  }

 inline bool jj_3R_102()
 {
    if (jj_done) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_4()) { jj_scanpos = xsp; break; }
    }
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_171()
 {
    if (jj_done) return true;
    if (jj_3R_179()) return true;
    return false;
  }

 inline bool jj_3R_220()
 {
    if (jj_done) return true;
    if (jj_3R_87()) return true;
    return false;
  }

 inline bool jj_3R_219()
 {
    if (jj_done) return true;
    if (jj_3R_230()) return true;
    return false;
  }

 inline bool jj_3R_226()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACE)) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_244()) jj_scanpos = xsp;
    if (jj_scan_token(R_BRACE)) return true;
    return false;
  }

 inline bool jj_3R_218()
 {
    if (jj_done) return true;
    if (jj_3R_229()) return true;
    return false;
  }

 inline bool jj_3R_181()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_scan_token(183)) {
    jj_scanpos = xsp;
    if (jj_scan_token(91)) {
    jj_scanpos = xsp;
    if (jj_scan_token(88)) {
    jj_scanpos = xsp;
    if (jj_scan_token(114)) {
    jj_scanpos = xsp;
    if (jj_scan_token(115)) {
    jj_scanpos = xsp;
    if (jj_scan_token(116)) {
    jj_scanpos = xsp;
    if (jj_scan_token(117)) {
    jj_scanpos = xsp;
    if (jj_scan_token(120)) {
    jj_scanpos = xsp;
    if (jj_scan_token(118)) {
    jj_scanpos = xsp;
    if (jj_scan_token(121)) {
    jj_scanpos = xsp;
    if (jj_scan_token(122)) {
    jj_scanpos = xsp;
    if (jj_scan_token(123)) {
    jj_scanpos = xsp;
    if (jj_scan_token(124)) {
    jj_scanpos = xsp;
    if (jj_scan_token(125)) {
    jj_scanpos = xsp;
    if (jj_scan_token(126)) {
    jj_scanpos = xsp;
    if (jj_scan_token(127)) {
    jj_scanpos = xsp;
    if (jj_scan_token(128)) {
    jj_scanpos = xsp;
    if (jj_scan_token(129)) {
    jj_scanpos = xsp;
    if (jj_scan_token(131)) {
    jj_scanpos = xsp;
    if (jj_scan_token(132)) {
    jj_scanpos = xsp;
    if (jj_scan_token(133)) {
    jj_scanpos = xsp;
    if (jj_scan_token(134)) {
    jj_scanpos = xsp;
    if (jj_scan_token(135)) {
    jj_scanpos = xsp;
    if (jj_scan_token(136)) {
    jj_scanpos = xsp;
    if (jj_scan_token(137)) {
    jj_scanpos = xsp;
    if (jj_scan_token(142)) {
    jj_scanpos = xsp;
    if (jj_scan_token(143)) {
    jj_scanpos = xsp;
    if (jj_scan_token(145)) {
    jj_scanpos = xsp;
    if (jj_scan_token(146)) {
    jj_scanpos = xsp;
    if (jj_scan_token(147)) {
    jj_scanpos = xsp;
    if (jj_scan_token(148)) {
    jj_scanpos = xsp;
    if (jj_scan_token(149)) {
    jj_scanpos = xsp;
    if (jj_scan_token(150)) {
    jj_scanpos = xsp;
    if (jj_scan_token(151)) {
    jj_scanpos = xsp;
    if (jj_scan_token(152)) {
    jj_scanpos = xsp;
    if (jj_scan_token(153)) {
    jj_scanpos = xsp;
    if (jj_scan_token(154)) {
    jj_scanpos = xsp;
    if (jj_scan_token(155)) {
    jj_scanpos = xsp;
    if (jj_scan_token(156)) {
    jj_scanpos = xsp;
    if (jj_scan_token(157)) {
    jj_scanpos = xsp;
    if (jj_scan_token(158)) {
    jj_scanpos = xsp;
    if (jj_scan_token(159)) {
    jj_scanpos = xsp;
    if (jj_scan_token(160)) {
    jj_scanpos = xsp;
    if (jj_scan_token(85)) {
    jj_scanpos = xsp;
    if (jj_scan_token(84)) {
    jj_scanpos = xsp;
    if (jj_scan_token(83)) return true;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_217()
 {
    if (jj_done) return true;
    if (jj_3R_228()) return true;
    return false;
  }

 inline bool jj_3R_216()
 {
    if (jj_done) return true;
    if (jj_3R_227()) return true;
    return false;
  }

 inline bool jj_3R_215()
 {
    if (jj_done) return true;
    if (jj_3R_226()) return true;
    return false;
  }

 inline bool jj_3R_138()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRY)) return true;
    if (jj_3R_47()) return true;
    return false;
  }

 inline bool jj_3R_54()
 {
    if (jj_done) return true;
    if (jj_3R_84()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_214()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_76()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACKET)) return true;
    return false;
  }

 inline bool jj_3R_57()
 {
    if (jj_done) return true;
    if (jj_3R_85()) return true;
    return false;
  }

 inline bool jj_3R_176()
 {
    if (jj_done) return true;
    if (jj_3R_182()) return true;
    return false;
  }

 inline bool jj_3R_174()
 {
    if (jj_done) return true;
    if (jj_scan_token(FROM)) return true;
    return false;
  }

 inline bool jj_3R_75()
 {
    if (jj_done) return true;
    if (jj_3R_102()) return true;
    return false;
  }

 inline bool jj_3R_208()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_215()) {
    jj_scanpos = xsp;
    if (jj_3R_216()) {
    jj_scanpos = xsp;
    if (jj_3R_217()) {
    jj_scanpos = xsp;
    if (jj_3R_218()) {
    jj_scanpos = xsp;
    if (jj_3R_219()) {
    jj_scanpos = xsp;
    if (jj_3R_220()) return true;
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_74()
 {
    if (jj_done) return true;
    if (jj_3R_101()) return true;
    return false;
  }

 inline bool jj_3R_122()
 {
    if (jj_done) return true;
    if (jj_3R_145()) return true;
    return false;
  }

 inline bool jj_3R_121()
 {
    if (jj_done) return true;
    if (jj_3R_144()) return true;
    return false;
  }

 inline bool jj_3R_73()
 {
    if (jj_done) return true;
    if (jj_3R_100()) return true;
    return false;
  }

 inline bool jj_3R_120()
 {
    if (jj_done) return true;
    if (jj_3R_143()) return true;
    return false;
  }

 inline bool jj_3R_119()
 {
    if (jj_done) return true;
    if (jj_3R_142()) return true;
    return false;
  }

 inline bool jj_3R_72()
 {
    if (jj_done) return true;
    if (jj_3R_99()) return true;
    return false;
  }

 inline bool jj_3R_118()
 {
    if (jj_done) return true;
    if (jj_3R_141()) return true;
    return false;
  }

 inline bool jj_3R_117()
 {
    if (jj_done) return true;
    if (jj_3R_140()) return true;
    return false;
  }

 inline bool jj_3R_71()
 {
    if (jj_done) return true;
    if (jj_3R_98()) return true;
    return false;
  }

 inline bool jj_3R_116()
 {
    if (jj_done) return true;
    if (jj_3R_139()) return true;
    return false;
  }

 inline bool jj_3R_115()
 {
    if (jj_done) return true;
    if (jj_3R_138()) return true;
    return false;
  }

 inline bool jj_3R_70()
 {
    if (jj_done) return true;
    if (jj_3R_97()) return true;
    return false;
  }

 inline bool jj_3R_114()
 {
    if (jj_done) return true;
    if (jj_3R_137()) return true;
    return false;
  }

 inline bool jj_3R_53()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    return false;
  }

 inline bool jj_3R_69()
 {
    if (jj_done) return true;
    if (jj_3R_96()) return true;
    return false;
  }

 inline bool jj_3R_68()
 {
    if (jj_done) return true;
    if (jj_3R_95()) return true;
    return false;
  }

 inline bool jj_3R_67()
 {
    if (jj_done) return true;
    if (jj_3R_94()) return true;
    return false;
  }

 inline bool jj_3R_86()
 {
    if (jj_done) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3_1()
 {
    if (jj_done) return true;
    if (jj_scan_token(DOT)) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_66()
 {
    if (jj_done) return true;
    if (jj_3R_93()) return true;
    return false;
  }

 inline bool jj_3R_104()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_114()) {
    jj_scanpos = xsp;
    if (jj_3R_115()) {
    jj_scanpos = xsp;
    if (jj_3R_116()) {
    jj_scanpos = xsp;
    if (jj_3R_117()) {
    jj_scanpos = xsp;
    if (jj_3R_118()) {
    jj_scanpos = xsp;
    if (jj_3R_119()) {
    jj_scanpos = xsp;
    if (jj_3R_120()) {
    jj_scanpos = xsp;
    if (jj_3R_121()) {
    jj_scanpos = xsp;
    if (jj_3R_122()) return true;
    }
    }
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_52()
 {
    if (jj_done) return true;
    if (jj_scan_token(PLUS)) return true;
    return false;
  }

 inline bool jj_3R_58()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_86()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3R_44()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_66()) {
    jj_scanpos = xsp;
    if (jj_3R_67()) {
    jj_scanpos = xsp;
    if (jj_3R_68()) {
    jj_scanpos = xsp;
    if (jj_3R_69()) {
    jj_scanpos = xsp;
    if (jj_3R_70()) {
    jj_scanpos = xsp;
    if (jj_3R_71()) {
    jj_scanpos = xsp;
    if (jj_3R_72()) {
    jj_scanpos = xsp;
    if (jj_3R_73()) {
    jj_scanpos = xsp;
    if (jj_3R_74()) {
    jj_scanpos = xsp;
    if (jj_3R_75()) return true;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_76()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_50()
 {
    if (jj_done) return true;
    if (jj_scan_token(ELSE)) return true;
    if (jj_scan_token(IF)) return true;
    return false;
  }

 inline bool jj_3R_212()
 {
    if (jj_done) return true;
    if (jj_3R_181()) return true;
    return false;
  }

 inline bool jj_3R_148()
 {
    if (jj_done) return true;
    if (jj_scan_token(ALTER)) return true;
    if (jj_scan_token(TABLE)) return true;
    return false;
  }

 inline bool jj_3_10()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_52()) {
    jj_scanpos = xsp;
    if (jj_3R_53()) return true;
    }
    if (jj_3R_54()) return true;
    return false;
  }

 inline bool jj_3R_191()
 {
    if (jj_done) return true;
    if (jj_3R_54()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_10()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_125()
 {
    if (jj_done) return true;
    if (jj_3R_148()) return true;
    return false;
  }

 inline bool jj_3R_124()
 {
    if (jj_done) return true;
    if (jj_3R_147()) return true;
    return false;
  }

 inline bool jj_3R_222()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3R_123()
 {
    if (jj_done) return true;
    if (jj_3R_146()) return true;
    return false;
  }

 inline bool jj_3_9()
 {
    if (jj_done) return true;
    if (jj_scan_token(ELSE)) return true;
    if (jj_3R_51()) return true;
    return false;
  }

 inline bool jj_3R_152()
 {
    if (jj_done) return true;
    if (jj_scan_token(DELETE)) return true;
    if (jj_3R_174()) return true;
    return false;
  }

 inline bool jj_3R_166()
 {
    if (jj_done) return true;
    if (jj_3R_171()) return true;
    return false;
  }

 inline bool jj_3R_221()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3_14()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    if (jj_3R_58()) return true;
    if (jj_scan_token(R_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3_8()
 {
    if (jj_done) return true;
    if (jj_3R_50()) return true;
    return false;
  }

 inline bool jj_3R_106()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_123()) {
    jj_scanpos = xsp;
    if (jj_3R_124()) {
    jj_scanpos = xsp;
    if (jj_3R_125()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_199()
 {
    if (jj_done) return true;
    if (jj_3R_208()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_14()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3R_175()
 {
    if (jj_done) return true;
    if (jj_3R_181()) return true;
    return false;
  }

 inline bool jj_3R_77()
 {
    if (jj_done) return true;
    if (jj_3R_51()) return true;
    return false;
  }

 inline bool jj_3R_155()
 {
    if (jj_done) return true;
    if (jj_scan_token(SELECT)) return true;
    if (jj_3R_176()) return true;
    return false;
  }

 inline bool jj_3R_207()
 {
    if (jj_done) return true;
    if (jj_scan_token(RSIGNEDSHIFT)) return true;
    return false;
  }

 inline bool jj_3R_211()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_221()) {
    jj_scanpos = xsp;
    if (jj_3R_222()) return true;
    }
    return false;
  }

 inline bool jj_3R_132()
 {
    if (jj_done) return true;
    if (jj_3R_155()) return true;
    return false;
  }

 inline bool jj_3R_242()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQL_STRING_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_131()
 {
    if (jj_done) return true;
    if (jj_3R_154()) return true;
    return false;
  }

 inline bool jj_3R_92()
 {
    if (jj_done) return true;
    if (jj_scan_token(CHARACTER_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_206()
 {
    if (jj_done) return true;
    if (jj_scan_token(191)) return true;
    return false;
  }

 inline bool jj_3R_47()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACE)) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_77()) { jj_scanpos = xsp; break; }
    }
    if (jj_scan_token(R_BRACE)) return true;
    return false;
  }

 inline bool jj_3R_130()
 {
    if (jj_done) return true;
    if (jj_3R_153()) return true;
    return false;
  }

 inline bool jj_3R_129()
 {
    if (jj_done) return true;
    if (jj_3R_152()) return true;
    return false;
  }

 inline bool jj_3R_139()
 {
    if (jj_done) return true;
    if (jj_scan_token(IF)) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_128()
 {
    if (jj_done) return true;
    if (jj_3R_151()) return true;
    return false;
  }

 inline bool jj_3R_241()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_127()
 {
    if (jj_done) return true;
    if (jj_3R_150()) return true;
    return false;
  }

 inline bool jj_3R_126()
 {
    if (jj_done) return true;
    if (jj_3R_149()) return true;
    return false;
  }

 inline bool jj_3R_91()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQL_STRING_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_193()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_206()) {
    jj_scanpos = xsp;
    if (jj_3R_207()) return true;
    }
    return false;
  }

 inline bool jj_3R_90()
 {
    if (jj_done) return true;
    if (jj_scan_token(INTEGER_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_238()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_241()) {
    jj_scanpos = xsp;
    if (jj_3R_242()) return true;
    }
    return false;
  }

 inline bool jj_3R_107()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_126()) {
    jj_scanpos = xsp;
    if (jj_3R_127()) {
    jj_scanpos = xsp;
    if (jj_3R_128()) {
    jj_scanpos = xsp;
    if (jj_3R_129()) {
    jj_scanpos = xsp;
    if (jj_3R_130()) {
    jj_scanpos = xsp;
    if (jj_3R_131()) {
    jj_scanpos = xsp;
    if (jj_3R_132()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3_13()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACKET)) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3R_190()
 {
    if (jj_done) return true;
    if (jj_3R_199()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_13()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_159()
 {
    if (jj_done) return true;
    if (jj_3R_166()) return true;
    return false;
  }

 inline bool jj_3R_105()
 {
    if (jj_done) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_63()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_90()) {
    jj_scanpos = xsp;
    if (jj_3R_91()) {
    jj_scanpos = xsp;
    if (jj_3R_92()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_184()
 {
    if (jj_done) return true;
    if (jj_3R_191()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_193()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_240()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3R_140()
 {
    if (jj_done) return true;
    if (jj_scan_token(BREAK)) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_239()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3R_197()
 {
    if (jj_done) return true;
    if (jj_scan_token(LEQ)) return true;
    return false;
  }

 inline bool jj_3R_243()
 {
    if (jj_done) return true;
    if (jj_scan_token(DOT)) return true;
    return false;
  }

 inline bool jj_3R_236()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_239()) {
    jj_scanpos = xsp;
    if (jj_3R_240()) return true;
    }
    return false;
  }

 inline bool jj_3R_78()
 {
    if (jj_done) return true;
    if (jj_scan_token(EQUALS)) return true;
    return false;
  }

 inline bool jj_3R_210()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_141()
 {
    if (jj_done) return true;
    if (jj_scan_token(CONTINUE)) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_147()
 {
    if (jj_done) return true;
    if (jj_scan_token(DROP)) return true;
    if (jj_scan_token(TABLE)) return true;
    return false;
  }

 inline bool jj_3R_196()
 {
    if (jj_done) return true;
    if (jj_scan_token(LT)) return true;
    return false;
  }

 inline bool jj_3R_183()
 {
    if (jj_done) return true;
    if (jj_3R_190()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_243()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_49()
 {
    if (jj_done) return true;
    if (jj_3R_57()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_78()) jj_scanpos = xsp;
    return false;
  }


public: 
  void setErrorHandler(ErrorHandler *eh) {
    if (errorHandler) delete errorHandler;
    errorHandler = eh;
  }

  TokenManager *token_source = nullptr;
  CharStream   *jj_input_stream = nullptr;
  /** Current token. */
  Token        *token = nullptr;
  /** Next token. */
  Token        *jj_nt = nullptr;

private: 
  int           jj_ntk;
  JJCalls       jj_2_rtns[25];
  bool          jj_rescan;
  int           jj_gc;
  Token        *jj_scanpos, *jj_lastpos;
  int           jj_la;
  /** Whether we are looking ahead. */
  bool          jj_lookingAhead;
  bool          jj_semLA;
  int           jj_gen;
  int           jj_la1[139];
  ErrorHandler *errorHandler = nullptr;

protected: 
  bool          hasError;

  Token *head; 
public: 
  AlinousLang(TokenManager *tokenManager);
  virtual ~AlinousLang();
void ReInit(TokenManager* tokenManager);
void clear();
Token * jj_consume_token(int kind);
bool  jj_scan_token(int kind);
Token * getNextToken();
Token * getToken(int index);
int jj_ntk_f();
private:
  int jj_kind;
  int **jj_expentries;
  int *jj_expentry;
  void jj_add_error_token(int kind, int pos);
protected:
  /** Generate ParseException. */
  virtual void  parseError();
private:
  int  indent;	// trace indentation
  bool trace = false; // trace enabled if true

public:
  bool trace_enabled();
  void enable_tracing();
  void disable_tracing();
  void jj_rescan_token();
  void jj_save(int index, int xla);


private:
  bool jj_done;
};
}
#endif
