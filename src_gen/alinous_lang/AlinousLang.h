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
PackageDeclare              * packageDeclare();
PackageNameDeclare                  * packageNameDeclare();
ClassDeclare            * classDeclare();
ClassDeclareBlock                 * classDeclareBlock();
MethodDeclare             * methodDeclare(AccessControlDeclare* ctrl, bool _static, AbstractType* type, Token* identifier);
MemberVariableDeclare                     * memberVariableDeclare(AccessControlDeclare* ctrl, bool _static, AbstractType* type, Token* identifier);
AccessControlDeclare                    * accessControlDeclare();
ArgumentsListDeclare                    * argumentsListDeclare();
ArgumentDeclare               * argumentDeclare();
AbstractType            * typeDeclare();
CharType        * charType();
ShortType         * shortType();
IntType       * intType();
LongType        * longType();
StringType          * stringType();
VoidType        * voidType();
StatementBlock
              * statementBlock();
IfStatement
           * ifStatement();
AbstractExpression
                  * expression();
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
ParenthesisExpression                     * parenthesisExpression();
VariableIdentifier                  * variableIdentifier();
AbstractExpression                  * literal();
NullLiteral           * nullLiteral();
NumberLiteral             * numberLiteral();
BooleanLiteral              * booleanLiteral();
LiteralExpression                 * literalExpression();
 inline bool jj_2_1(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_1() || jj_done);
 { jj_save(0, xla); }
  }

 inline bool jj_3R_17()
 {
    if (jj_done) return true;
    if (jj_3R_23()) return true;
    return false;
  }

 inline bool jj_3R_19()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHORT)) return true;
    return false;
  }

 inline bool jj_3R_16()
 {
    if (jj_done) return true;
    if (jj_3R_22()) return true;
    return false;
  }

 inline bool jj_3_1()
 {
    if (jj_done) return true;
    if (jj_scan_token(L_PARENTHESIS)) return true;
    if (jj_3R_11()) return true;
    return false;
  }

 inline bool jj_3R_15()
 {
    if (jj_done) return true;
    if (jj_3R_21()) return true;
    return false;
  }

 inline bool jj_3R_22()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING)) return true;
    return false;
  }

 inline bool jj_3R_14()
 {
    if (jj_done) return true;
    if (jj_3R_20()) return true;
    return false;
  }

 inline bool jj_3R_13()
 {
    if (jj_done) return true;
    if (jj_3R_19()) return true;
    return false;
  }

 inline bool jj_3R_12()
 {
    if (jj_done) return true;
    if (jj_3R_18()) return true;
    return false;
  }

 inline bool jj_3R_20()
 {
    if (jj_done) return true;
    if (jj_scan_token(INT)) return true;
    return false;
  }

 inline bool jj_3R_23()
 {
    if (jj_done) return true;
    if (jj_scan_token(VOID)) return true;
    return false;
  }

 inline bool jj_3R_18()
 {
    if (jj_done) return true;
    if (jj_scan_token(CHAR)) return true;
    return false;
  }

 inline bool jj_3R_11()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_12()) {
    jj_scanpos = xsp;
    if (jj_3R_13()) {
    jj_scanpos = xsp;
    if (jj_3R_14()) {
    jj_scanpos = xsp;
    if (jj_3R_15()) {
    jj_scanpos = xsp;
    if (jj_3R_16()) {
    jj_scanpos = xsp;
    if (jj_3R_17()) return true;
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_21()
 {
    if (jj_done) return true;
    if (jj_scan_token(LONG)) return true;
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
  JJCalls       jj_2_rtns[2];
  bool          jj_rescan;
  int           jj_gc;
  Token        *jj_scanpos, *jj_lastpos;
  int           jj_la;
  /** Whether we are looking ahead. */
  bool          jj_lookingAhead;
  bool          jj_semLA;
  int           jj_gen;
  int           jj_la1[38];
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
