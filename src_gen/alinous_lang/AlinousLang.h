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
VariableIdentifier                  * typeIdentifier();
AbstractExpression                  * literal();
NullLiteral           * nullLiteral();
NumberLiteral             * numberLiteral();
BooleanLiteral              * booleanLiteral();
LiteralExpression                 * literalExpression();
AbstractSQLStatement
                    * ddlStatement();
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
SQLFunctionCall               * sqlFunctionCall();
void sqlFunctionCallArguments(SQLFunctionCall* exp);
SQLPlaceHolder              * sqlPlaceHolder();
SQLParenthesisExpression                        * sqlParenthesisExpression();
SQLLiteral          * sqlLiteral();
SQLBooleanLiteral                 * sqlBooleanLiteral();
SQLColumnIdentifier                   * sqlColumnIdentifier();
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

 inline bool jj_3R_213()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_216()) {
    jj_scanpos = xsp;
    if (jj_3R_217()) return true;
    }
    return false;
  }

 inline bool jj_3R_179()
 {
    if (jj_done) return true;
    if (jj_scan_token(LEQ)) return true;
    return false;
  }

 inline bool jj_3R_218()
 {
    if (jj_done) return true;
    if (jj_scan_token(DOT)) return true;
    return false;
  }

 inline bool jj_3R_68()
 {
    if (jj_done) return true;
    if (jj_scan_token(EQUALS)) return true;
    return false;
  }

 inline bool jj_3R_131()
 {
    if (jj_done) return true;
    if (jj_scan_token(CONTINUE)) return true;
    return false;
  }

 inline bool jj_3R_215()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3R_178()
 {
    if (jj_done) return true;
    if (jj_scan_token(LT)) return true;
    return false;
  }

 inline bool jj_3R_166()
 {
    if (jj_done) return true;
    if (jj_3R_172()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_218()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_214()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3R_42()
 {
    if (jj_done) return true;
    if (jj_3R_52()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_68()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3_17()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQLAND)) return true;
    if (jj_3R_54()) return true;
    return false;
  }

 inline bool jj_3R_53()
 {
    if (jj_done) return true;
    if (jj_3R_54()) return true;
    return false;
  }

 inline bool jj_3R_177()
 {
    if (jj_done) return true;
    if (jj_scan_token(GEQ)) return true;
    return false;
  }

 inline bool jj_3R_211()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_214()) {
    jj_scanpos = xsp;
    if (jj_3R_215()) return true;
    }
    return false;
  }

 inline bool jj_3R_162()
 {
    if (jj_done) return true;
    if (jj_3R_166()) return true;
    return false;
  }

 inline bool jj_3R_168()
 {
    if (jj_done) return true;
    if (jj_3R_174()) return true;
    return false;
  }

 inline bool jj_3R_132()
 {
    if (jj_done) return true;
    if (jj_scan_token(RETURN)) return true;
    return false;
  }

 inline bool jj_3R_176()
 {
    if (jj_done) return true;
    if (jj_scan_token(GT)) return true;
    return false;
  }

 inline bool jj_3R_41()
 {
    if (jj_done) return true;
    if (jj_3R_42()) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_212()
 {
    if (jj_done) return true;
    if (jj_scan_token(INTEGER_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_169()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_176()) {
    jj_scanpos = xsp;
    if (jj_3R_177()) {
    jj_scanpos = xsp;
    if (jj_3R_178()) {
    jj_scanpos = xsp;
    if (jj_3R_179()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3_16()
 {
    if (jj_done) return true;
    if (jj_scan_token(OR)) return true;
    if (jj_3R_53()) return true;
    return false;
  }

 inline bool jj_3R_163()
 {
    if (jj_done) return true;
    if (jj_3R_167()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_169()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3_11()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    if (jj_3R_39()) return true;
    if (jj_scan_token(R_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_210()
 {
    if (jj_done) return true;
    if (jj_scan_token(_NULL)) return true;
    return false;
  }

 inline bool jj_3R_158()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_11()) {
    jj_scanpos = xsp;
    if (jj_3R_162()) return true;
    }
    return false;
  }

 inline bool jj_3R_209()
 {
    if (jj_done) return true;
    if (jj_3R_213()) return true;
    return false;
  }

 inline bool jj_3R_133()
 {
    if (jj_done) return true;
    if (jj_scan_token(WHILE)) return true;
    return false;
  }

 inline bool jj_3R_208()
 {
    if (jj_done) return true;
    if (jj_3R_212()) return true;
    return false;
  }

 inline bool jj_3R_207()
 {
    if (jj_done) return true;
    if (jj_3R_211()) return true;
    return false;
  }

 inline bool jj_3R_104()
 {
    if (jj_done) return true;
    if (jj_3R_39()) return true;
    return false;
  }

 inline bool jj_3R_206()
 {
    if (jj_done) return true;
    if (jj_3R_210()) return true;
    return false;
  }

 inline bool jj_3R_171()
 {
    if (jj_done) return true;
    if (jj_scan_token(CMP_NOTEQUALS)) return true;
    return false;
  }

 inline bool jj_3R_205()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_206()) {
    jj_scanpos = xsp;
    if (jj_3R_207()) {
    jj_scanpos = xsp;
    if (jj_3R_208()) {
    jj_scanpos = xsp;
    if (jj_3R_209()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3R_164()
 {
    if (jj_done) return true;
    if (jj_3R_168()) return true;
    return false;
  }

 inline bool jj_3R_157()
 {
    if (jj_done) return true;
    if (jj_scan_token(NOT)) return true;
    return false;
  }

 inline bool jj_3R_170()
 {
    if (jj_done) return true;
    if (jj_scan_token(CMP_EQUALS)) return true;
    return false;
  }

 inline bool jj_3R_40()
 {
    if (jj_done) return true;
    if (jj_scan_token(STATIC)) return true;
    return false;
  }

 inline bool jj_3R_94()
 {
    if (jj_done) return true;
    if (jj_3R_104()) return true;
    return false;
  }

 inline bool jj_3_2()
 {
    if (jj_done) return true;
    if (jj_3R_39()) return true;
    return false;
  }

 inline bool jj_3R_153()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_157()) jj_scanpos = xsp;
    if (jj_3R_158()) return true;
    return false;
  }

 inline bool jj_3R_165()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_170()) {
    jj_scanpos = xsp;
    if (jj_3R_171()) return true;
    }
    return false;
  }

 inline bool jj_3R_140()
 {
    if (jj_done) return true;
    if (jj_scan_token(ROLLBACK)) return true;
    return false;
  }

 inline bool jj_3R_222()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_scan_token(182)) {
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

 inline bool jj_3R_74()
 {
    if (jj_done) return true;
    if (jj_3R_98()) return true;
    return false;
  }

 inline bool jj_3R_73()
 {
    if (jj_done) return true;
    if (jj_3R_97()) return true;
    return false;
  }

 inline bool jj_3R_72()
 {
    if (jj_done) return true;
    if (jj_3R_96()) return true;
    return false;
  }

 inline bool jj_3R_71()
 {
    if (jj_done) return true;
    if (jj_3R_95()) return true;
    return false;
  }

 inline bool jj_3R_70()
 {
    if (jj_done) return true;
    if (jj_3R_94()) return true;
    return false;
  }

 inline bool jj_3_5()
 {
    if (jj_done) return true;
    if (jj_3R_41()) return true;
    return false;
  }

 inline bool jj_3R_69()
 {
    if (jj_done) return true;
    if (jj_3R_93()) return true;
    return false;
  }

 inline bool jj_3R_159()
 {
    if (jj_done) return true;
    if (jj_3R_163()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_165()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3R_134()
 {
    if (jj_done) return true;
    if (jj_scan_token(DO)) return true;
    return false;
  }

 inline bool jj_3R_77()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_scan_token(182)) {
    jj_scanpos = xsp;
    if (jj_scan_token(90)) {
    jj_scanpos = xsp;
    if (jj_scan_token(87)) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_139()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMIT)) return true;
    return false;
  }

 inline bool jj_3R_44()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_69()) {
    jj_scanpos = xsp;
    if (jj_3_5()) {
    jj_scanpos = xsp;
    if (jj_3R_70()) {
    jj_scanpos = xsp;
    if (jj_3R_71()) {
    jj_scanpos = xsp;
    if (jj_3R_72()) {
    jj_scanpos = xsp;
    if (jj_3R_73()) {
    jj_scanpos = xsp;
    if (jj_3R_74()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_152()
 {
    if (jj_done) return true;
    if (jj_scan_token(191)) return true;
    return false;
  }

 inline bool jj_3_3()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_40()) jj_scanpos = xsp;
    xsp = jj_scanpos;
    if (jj_3_2()) jj_scanpos = xsp;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_146()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_152()) jj_scanpos = xsp;
    if (jj_3R_153()) return true;
    return false;
  }

 inline bool jj_3_6()
 {
    if (jj_done) return true;
    if (jj_3R_42()) return true;
    return false;
  }

 inline bool jj_3R_161()
 {
    if (jj_done) return true;
    if (jj_scan_token(BIT_AND)) return true;
    return false;
  }

 inline bool jj_3R_138()
 {
    if (jj_done) return true;
    if (jj_scan_token(BEGIN)) return true;
    return false;
  }

 inline bool jj_3R_91()
 {
    if (jj_done) return true;
    if (jj_scan_token(VOID)) return true;
    return false;
  }

 inline bool jj_3R_203()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    if (jj_3R_52()) return true;
    return false;
  }

 inline bool jj_3R_160()
 {
    if (jj_done) return true;
    if (jj_3R_164()) return true;
    return false;
  }

 inline bool jj_3R_151()
 {
    if (jj_done) return true;
    if (jj_scan_token(PLUSPLUS)) return true;
    return false;
  }

 inline bool jj_3R_154()
 {
    if (jj_done) return true;
    if (jj_3R_159()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_161()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_150()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUSMINUS)) return true;
    return false;
  }

 inline bool jj_3R_90()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING)) return true;
    return false;
  }

 inline bool jj_3R_145()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_150()) {
    jj_scanpos = xsp;
    if (jj_3R_151()) return true;
    }
    return false;
  }

 inline bool jj_3R_89()
 {
    if (jj_done) return true;
    if (jj_scan_token(LONG)) return true;
    return false;
  }

 inline bool jj_3R_156()
 {
    if (jj_done) return true;
    if (jj_scan_token(189)) return true;
    return false;
  }

 inline bool jj_3R_123()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_145()) jj_scanpos = xsp;
    if (jj_3R_146()) return true;
    return false;
  }

 inline bool jj_3R_135()
 {
    if (jj_done) return true;
    if (jj_scan_token(FOR)) return true;
    return false;
  }

 inline bool jj_3R_147()
 {
    if (jj_done) return true;
    if (jj_3R_154()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_156()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_49()
 {
    if (jj_done) return true;
    if (jj_scan_token(PLUSPLUS)) return true;
    return false;
  }

 inline bool jj_3R_88()
 {
    if (jj_done) return true;
    if (jj_scan_token(INT)) return true;
    return false;
  }

 inline bool jj_3R_48()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUSMINUS)) return true;
    return false;
  }

 inline bool jj_3R_51()
 {
    if (jj_done) return true;
    if (jj_3R_77()) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_87()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHORT)) return true;
    return false;
  }

 inline bool jj_3R_149()
 {
    if (jj_done) return true;
    if (jj_scan_token(BIT_OR)) return true;
    return false;
  }

 inline bool jj_3R_127()
 {
    if (jj_done) return true;
    if (jj_scan_token(THROW)) return true;
    return false;
  }

 inline bool jj_3R_141()
 {
    if (jj_done) return true;
    if (jj_scan_token(DELETE)) return true;
    return false;
  }

 inline bool jj_3R_191()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3_10()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_48()) {
    jj_scanpos = xsp;
    if (jj_3R_49()) return true;
    }
    return false;
  }

 inline bool jj_3R_155()
 {
    if (jj_done) return true;
    if (jj_3R_160()) return true;
    return false;
  }

 inline bool jj_3R_100()
 {
    if (jj_done) return true;
    if (jj_3R_123()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_10()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3R_144()
 {
    if (jj_done) return true;
    if (jj_scan_token(SELECT)) return true;
    return false;
  }

 inline bool jj_3R_86()
 {
    if (jj_done) return true;
    if (jj_scan_token(CHAR)) return true;
    return false;
  }

 inline bool jj_3R_124()
 {
    if (jj_done) return true;
    if (jj_3R_147()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_149()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_199()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3_15()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACKET)) return true;
    if (jj_3R_52()) return true;
    return false;
  }

 inline bool jj_3R_122()
 {
    if (jj_done) return true;
    if (jj_3R_144()) return true;
    return false;
  }

 inline bool jj_3R_121()
 {
    if (jj_done) return true;
    if (jj_3R_143()) return true;
    return false;
  }

 inline bool jj_3R_198()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3R_120()
 {
    if (jj_done) return true;
    if (jj_3R_142()) return true;
    return false;
  }

 inline bool jj_3R_119()
 {
    if (jj_done) return true;
    if (jj_3R_141()) return true;
    return false;
  }

 inline bool jj_3R_85()
 {
    if (jj_done) return true;
    if (jj_scan_token(BYTE)) return true;
    return false;
  }

 inline bool jj_3R_118()
 {
    if (jj_done) return true;
    if (jj_3R_140()) return true;
    return false;
  }

 inline bool jj_3R_117()
 {
    if (jj_done) return true;
    if (jj_3R_139()) return true;
    return false;
  }

 inline bool jj_3R_221()
 {
    if (jj_done) return true;
    if (jj_3R_222()) return true;
    return false;
  }

 inline bool jj_3R_116()
 {
    if (jj_done) return true;
    if (jj_3R_138()) return true;
    return false;
  }

 inline bool jj_3R_99()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    return false;
  }

 inline bool jj_3R_190()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_198()) {
    jj_scanpos = xsp;
    if (jj_3R_199()) return true;
    }
    return false;
  }

 inline bool jj_3R_126()
 {
    if (jj_done) return true;
    if (jj_scan_token(LOGICAL_AND)) return true;
    return false;
  }

 inline bool jj_3R_98()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
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
    return false;
  }

 inline bool jj_3R_75()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_99()) jj_scanpos = xsp;
    if (jj_3R_100()) return true;
    return false;
  }

 inline bool jj_3R_84()
 {
    if (jj_done) return true;
    if (jj_scan_token(BOOLEAN)) return true;
    return false;
  }

 inline bool jj_3R_220()
 {
    if (jj_done) return true;
    if (jj_3R_221()) return true;
    return false;
  }

 inline bool jj_3R_83()
 {
    if (jj_done) return true;
    if (jj_scan_token(CHARACTER_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_148()
 {
    if (jj_done) return true;
    if (jj_3R_155()) return true;
    return false;
  }

 inline bool jj_3R_101()
 {
    if (jj_done) return true;
    if (jj_3R_124()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_126()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_82()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQL_STRING_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_81()
 {
    if (jj_done) return true;
    if (jj_scan_token(INTEGER_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_202()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODULO)) return true;
    return false;
  }

 inline bool jj_3_14()
 {
    if (jj_done) return true;
    if (jj_3R_51()) return true;
    return false;
  }

 inline bool jj_3R_55()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_81()) {
    jj_scanpos = xsp;
    if (jj_3R_82()) {
    jj_scanpos = xsp;
    if (jj_3R_83()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_201()
 {
    if (jj_done) return true;
    if (jj_scan_token(DIV)) return true;
    return false;
  }

 inline bool jj_3R_137()
 {
    if (jj_done) return true;
    if (jj_scan_token(DROP)) return true;
    return false;
  }

 inline bool jj_3_4()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    if (jj_scan_token(DOT)) return true;
    return false;
  }

 inline bool jj_3R_103()
 {
    if (jj_done) return true;
    if (jj_scan_token(LOGICAL_OR)) return true;
    return false;
  }

 inline bool jj_3R_92()
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

 inline bool jj_3_13()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    if (jj_scan_token(DOT)) return true;
    return false;
  }

 inline bool jj_3R_200()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASTERISK)) return true;
    return false;
  }

 inline bool jj_3R_204()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEW)) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_13()) { jj_scanpos = xsp; break; }
    }
    xsp = jj_scanpos;
    if (jj_3_14()) {
    jj_scanpos = xsp;
    if (jj_3R_220()) return true;
    }
    return false;
  }

 inline bool jj_3R_78()
 {
    if (jj_done) return true;
    if (jj_3R_101()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_103()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_67()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACKET)) return true;
    return false;
  }

 inline bool jj_3R_193()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_200()) {
    jj_scanpos = xsp;
    if (jj_3R_201()) {
    jj_scanpos = xsp;
    if (jj_3R_202()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_189()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_66()
 {
    if (jj_done) return true;
    if (jj_3R_92()) return true;
    return false;
  }

 inline bool jj_3R_125()
 {
    if (jj_done) return true;
    if (jj_3R_148()) return true;
    return false;
  }

 inline bool jj_3R_65()
 {
    if (jj_done) return true;
    if (jj_3R_91()) return true;
    return false;
  }

 inline bool jj_3R_64()
 {
    if (jj_done) return true;
    if (jj_3R_90()) return true;
    return false;
  }

 inline bool jj_3R_142()
 {
    if (jj_done) return true;
    if (jj_scan_token(INSERT)) return true;
    return false;
  }

 inline bool jj_3R_197()
 {
    if (jj_done) return true;
    if (jj_3R_77()) return true;
    return false;
  }

 inline bool jj_3R_63()
 {
    if (jj_done) return true;
    if (jj_3R_89()) return true;
    return false;
  }

 inline bool jj_3R_196()
 {
    if (jj_done) return true;
    if (jj_3R_205()) return true;
    return false;
  }

 inline bool jj_3R_195()
 {
    if (jj_done) return true;
    if (jj_3R_204()) return true;
    return false;
  }

 inline bool jj_3R_62()
 {
    if (jj_done) return true;
    if (jj_3R_88()) return true;
    return false;
  }

 inline bool jj_3R_56()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQL_NOT)) return true;
    return false;
  }

 inline bool jj_3R_194()
 {
    if (jj_done) return true;
    if (jj_3R_203()) return true;
    return false;
  }

 inline bool jj_3R_128()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRY)) return true;
    return false;
  }

 inline bool jj_3R_61()
 {
    if (jj_done) return true;
    if (jj_3R_87()) return true;
    return false;
  }

 inline bool jj_3R_47()
 {
    if (jj_done) return true;
    if (jj_3R_75()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_193()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_60()
 {
    if (jj_done) return true;
    if (jj_3R_86()) return true;
    return false;
  }

 inline bool jj_3R_52()
 {
    if (jj_done) return true;
    if (jj_3R_78()) return true;
    return false;
  }

 inline bool jj_3R_59()
 {
    if (jj_done) return true;
    if (jj_3R_85()) return true;
    return false;
  }

 inline bool jj_3_1()
 {
    if (jj_done) return true;
    if (jj_scan_token(DOT)) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_58()
 {
    if (jj_done) return true;
    if (jj_3R_84()) return true;
    return false;
  }

 inline bool jj_3R_188()
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

 inline bool jj_3R_113()
 {
    if (jj_done) return true;
    if (jj_3R_135()) return true;
    return false;
  }

 inline bool jj_3R_112()
 {
    if (jj_done) return true;
    if (jj_3R_134()) return true;
    return false;
  }

 inline bool jj_3R_111()
 {
    if (jj_done) return true;
    if (jj_3R_133()) return true;
    return false;
  }

 inline bool jj_3R_110()
 {
    if (jj_done) return true;
    if (jj_3R_132()) return true;
    return false;
  }

 inline bool jj_3R_109()
 {
    if (jj_done) return true;
    if (jj_3R_131()) return true;
    return false;
  }

 inline bool jj_3R_108()
 {
    if (jj_done) return true;
    if (jj_3R_130()) return true;
    return false;
  }

 inline bool jj_3R_107()
 {
    if (jj_done) return true;
    if (jj_3R_129()) return true;
    return false;
  }

 inline bool jj_3R_39()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_58()) {
    jj_scanpos = xsp;
    if (jj_3R_59()) {
    jj_scanpos = xsp;
    if (jj_3R_60()) {
    jj_scanpos = xsp;
    if (jj_3R_61()) {
    jj_scanpos = xsp;
    if (jj_3R_62()) {
    jj_scanpos = xsp;
    if (jj_3R_63()) {
    jj_scanpos = xsp;
    if (jj_3R_64()) {
    jj_scanpos = xsp;
    if (jj_3R_65()) {
    jj_scanpos = xsp;
    if (jj_3R_66()) return true;
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
      if (jj_3R_67()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_106()
 {
    if (jj_done) return true;
    if (jj_3R_128()) return true;
    return false;
  }

 inline bool jj_3R_105()
 {
    if (jj_done) return true;
    if (jj_3R_127()) return true;
    return false;
  }

 inline bool jj_3R_46()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    return false;
  }

 inline bool jj_3R_192()
 {
    if (jj_done) return true;
    if (jj_scan_token(DOLLAR)) return true;
    return false;
  }

 inline bool jj_3R_76()
 {
    if (jj_done) return true;
    if (jj_3R_52()) return true;
    return false;
  }

 inline bool jj_3_19()
 {
    if (jj_done) return true;
    if (jj_scan_token(IS)) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_56()) jj_scanpos = xsp;
    if (jj_scan_token(_NULL)) return true;
    return false;
  }

 inline bool jj_3R_95()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_105()) {
    jj_scanpos = xsp;
    if (jj_3R_106()) {
    jj_scanpos = xsp;
    if (jj_3R_107()) {
    jj_scanpos = xsp;
    if (jj_3R_108()) {
    jj_scanpos = xsp;
    if (jj_3R_109()) {
    jj_scanpos = xsp;
    if (jj_3R_110()) {
    jj_scanpos = xsp;
    if (jj_3R_111()) {
    jj_scanpos = xsp;
    if (jj_3R_112()) {
    jj_scanpos = xsp;
    if (jj_3R_113()) return true;
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

 inline bool jj_3R_102()
 {
    if (jj_done) return true;
    if (jj_3R_125()) return true;
    return false;
  }

 inline bool jj_3R_45()
 {
    if (jj_done) return true;
    if (jj_scan_token(PLUS)) return true;
    return false;
  }

 inline bool jj_3R_50()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_76()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3R_43()
 {
    if (jj_done) return true;
    if (jj_scan_token(ELSE)) return true;
    if (jj_scan_token(IF)) return true;
    return false;
  }

 inline bool jj_3_9()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_45()) {
    jj_scanpos = xsp;
    if (jj_3R_46()) return true;
    }
    if (jj_3R_47()) return true;
    return false;
  }

 inline bool jj_3R_173()
 {
    if (jj_done) return true;
    if (jj_3R_47()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_9()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3_8()
 {
    if (jj_done) return true;
    if (jj_scan_token(ELSE)) return true;
    if (jj_3R_44()) return true;
    return false;
  }

 inline bool jj_3_12()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    if (jj_3R_50()) return true;
    if (jj_scan_token(R_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3_7()
 {
    if (jj_done) return true;
    if (jj_3R_43()) return true;
    return false;
  }

 inline bool jj_3R_180()
 {
    if (jj_done) return true;
    if (jj_3R_188()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_12()) jj_scanpos = xsp;
    return false;
  }

 inline bool jj_3R_187()
 {
    if (jj_done) return true;
    if (jj_scan_token(RSIGNEDSHIFT)) return true;
    return false;
  }

 inline bool jj_3_18()
 {
    if (jj_done) return true;
    if (jj_scan_token(LIKE)) return true;
    if (jj_3R_55()) return true;
    return false;
  }

 inline bool jj_3R_136()
 {
    if (jj_done) return true;
    if (jj_scan_token(CREATE)) return true;
    return false;
  }

 inline bool jj_3R_80()
 {
    if (jj_done) return true;
    if (jj_3R_102()) return true;
    return false;
  }

 inline bool jj_3R_57()
 {
    if (jj_done) return true;
    if (jj_3R_77()) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    return false;
  }

 inline bool jj_3R_115()
 {
    if (jj_done) return true;
    if (jj_3R_137()) return true;
    return false;
  }

 inline bool jj_3R_114()
 {
    if (jj_done) return true;
    if (jj_3R_136()) return true;
    return false;
  }

 inline bool jj_3R_185()
 {
    if (jj_done) return true;
    if (jj_3R_192()) return true;
    return false;
  }

 inline bool jj_3R_184()
 {
    if (jj_done) return true;
    if (jj_3R_191()) return true;
    return false;
  }

 inline bool jj_3R_186()
 {
    if (jj_done) return true;
    if (jj_scan_token(190)) return true;
    return false;
  }

 inline bool jj_3R_93()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACE)) return true;
    return false;
  }

 inline bool jj_3_20()
 {
    if (jj_done) return true;
    if (jj_3R_57()) return true;
    return false;
  }

 inline bool jj_3R_183()
 {
    if (jj_done) return true;
    if (jj_3R_190()) return true;
    return false;
  }

 inline bool jj_3R_182()
 {
    if (jj_done) return true;
    if (jj_3R_55()) return true;
    return false;
  }

 inline bool jj_3R_129()
 {
    if (jj_done) return true;
    if (jj_scan_token(IF)) return true;
    return false;
  }

 inline bool jj_3R_181()
 {
    if (jj_done) return true;
    if (jj_3R_189()) return true;
    return false;
  }

 inline bool jj_3R_219()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_BRACKET)) return true;
    return false;
  }

 inline bool jj_3R_97()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_114()) {
    jj_scanpos = xsp;
    if (jj_3R_115()) return true;
    }
    return false;
  }

 inline bool jj_3R_175()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_186()) {
    jj_scanpos = xsp;
    if (jj_3R_187()) return true;
    }
    return false;
  }

 inline bool jj_3R_143()
 {
    if (jj_done) return true;
    if (jj_scan_token(UPDATE)) return true;
    return false;
  }

 inline bool jj_3R_174()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_181()) {
    jj_scanpos = xsp;
    if (jj_3R_182()) {
    jj_scanpos = xsp;
    if (jj_3R_183()) {
    jj_scanpos = xsp;
    if (jj_3_20()) {
    jj_scanpos = xsp;
    if (jj_3R_184()) {
    jj_scanpos = xsp;
    if (jj_3R_185()) return true;
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_79()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQL_NOT)) return true;
    return false;
  }

 inline bool jj_3R_172()
 {
    if (jj_done) return true;
    if (jj_3R_180()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_219()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_96()
 {
    if (jj_done) return true;
    if (jj_scan_token(SEMI_COLON)) return true;
    return false;
  }

 inline bool jj_3R_167()
 {
    if (jj_done) return true;
    if (jj_3R_173()) return true;
    Token * xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3R_175()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

 inline bool jj_3R_217()
 {
    if (jj_done) return true;
    if (jj_scan_token(SQL_STRING_LITERAL)) return true;
    return false;
  }

 inline bool jj_3R_54()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_79()) jj_scanpos = xsp;
    if (jj_3R_80()) return true;
    return false;
  }

 inline bool jj_3R_130()
 {
    if (jj_done) return true;
    if (jj_scan_token(BREAK)) return true;
    return false;
  }

 inline bool jj_3R_216()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING_LITERAL)) return true;
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
  JJCalls       jj_2_rtns[21];
  bool          jj_rescan;
  int           jj_gc;
  Token        *jj_scanpos, *jj_lastpos;
  int           jj_la;
  /** Whether we are looking ahead. */
  bool          jj_lookingAhead;
  bool          jj_semLA;
  int           jj_gen;
  int           jj_la1[120];
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
