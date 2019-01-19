/* AlinousLang.cc */
#include "AlinousLang.h"
#include "TokenMgrError.h"
namespace alinouslang {
  unsigned int jj_la1_0[] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};
  unsigned int jj_la1_1[] = {
0x1000000,0x2000000,0x80,0x0,0x0,0x0,0x0,0x0,0xe0000000,};
  unsigned int jj_la1_2[] = {
0x0,0x0,0x0,0x70000,0x70000,0x100000,0x100000,0x70000,0x10000003,};
  unsigned int jj_la1_3[] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};
  unsigned int jj_la1_4[] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};
  unsigned int jj_la1_5[] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};
  unsigned int jj_la1_6[] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};

  /** Constructor with user supplied TokenManager. */




CompilationUnit
               * AlinousLang::compilationUnit() {CompilationUnit* unit = new CompilationUnit();
        PackageDeclare* pkg = nullptr;
        ClassDeclare* clazz = nullptr;
    if (!hasError) {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case PACKAGE:{
      if (!hasError) {
      pkg = packageDeclare();
      }
      if (!hasError) {
unit->setPackage(pkg);
      }
      break;
      }
    default:
      jj_la1[0] = jj_gen;
      ;
    }
    }
    if (!hasError) {
    while (!hasError) {
      if (!hasError) {
      clazz = classDeclare();
      }
      if (!hasError) {
unit->setPosition(clazz);
                        unit->addClassDeclare(clazz);
      }
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case CLASS:{
        ;
        break;
        }
      default:
        jj_la1[1] = jj_gen;
        goto end_label_1;
      }
    }
    end_label_1: ;
    }
    if (!hasError) {
    jj_consume_token(0);
    }
return unit;
assert(false);
}


PackageDeclare              * AlinousLang::packageDeclare() {PackageDeclare* pkg = nullptr;
        PackageNameDeclare* name = nullptr;
        Token* t = nullptr;
    if (!hasError) {
    t = jj_consume_token(PACKAGE);
    }
    if (!hasError) {
pkg=new PackageDeclare();
                pkg->setPosition(t);
    }
    if (!hasError) {
    name = packageNameDeclare();
    }
    if (!hasError) {
pkg->setName(name);
                pkg->setPosition(name);
    }
    if (!hasError) {
    jj_consume_token(SEMI_COLON);
    }
    if (!hasError) {
pkg->setPosition(t);
    }
__ONERROR(pkg);
                return pkg;
assert(false);
}


PackageNameDeclare                  * AlinousLang::packageNameDeclare() {PackageNameDeclare* names = nullptr;
        Token* t = nullptr;
    if (!hasError) {
    t = jj_consume_token(IDENTIFIER);
    }
    if (!hasError) {
names = new PackageNameDeclare();
                names->addSegment(_STR(t));
                names->setPosition(t);
    }
    if (!hasError) {
    while (!hasError) {
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case DOT:{
        ;
        break;
        }
      default:
        jj_la1[2] = jj_gen;
        goto end_label_2;
      }
      if (!hasError) {
      jj_consume_token(DOT);
      }
      if (!hasError) {
      t = jj_consume_token(IDENTIFIER);
      }
      if (!hasError) {
names->addSegment(_STR(t));
                        names->setPosition(t);
      }
    }
    end_label_2: ;
    }
    if (!hasError) {

    }
__ONERROR(names);
                return names;
assert(false);
}


ClassDeclare            * AlinousLang::classDeclare() {ClassDeclare* clazz = nullptr;
        Token* cls = nullptr;
        Token* name = nullptr;
        ClassDeclareBlock* block = nullptr;
    if (!hasError) {
    cls = jj_consume_token(CLASS);
    }
    if (!hasError) {
    name = jj_consume_token(IDENTIFIER);
    }
    if (!hasError) {
clazz = new ClassDeclare();
                 clazz->setName(_STR(name));
    }
    if (!hasError) {
    block = classDeclareBlock();
    }
    if (!hasError) {
clazz->setPositions(cls, block);
            clazz->setBlock(block);
    }
__ONERROR(clazz);
                return clazz;
assert(false);
}


ClassDeclareBlock                 * AlinousLang::classDeclareBlock() {ClassDeclareBlock* block = nullptr;
        Token* begin, *end;
        MethodDeclare* method = nullptr;
        MemberVariableDeclare* member = nullptr;
    if (!hasError) {
    begin = jj_consume_token(L_BRACE);
    }
    if (!hasError) {
block = new ClassDeclareBlock();
                block->setPosition(begin);
    }
    if (!hasError) {
    while (!hasError) {
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case PRIVATE:
      case PROTECTED:
      case PUBLIC:{
        ;
        break;
        }
      default:
        jj_la1[3] = jj_gen;
        goto end_label_3;
      }
      if (jj_2_1(5)) {
        if (!hasError) {
        method = methodDeclare();
        }
        if (!hasError) {
block->addMethod(method);
        }
      } else {
        switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
        case PRIVATE:
        case PROTECTED:
        case PUBLIC:{
          if (!hasError) {
          member = memberVariableDeclare();
          }
          if (!hasError) {
block->addVariable(member);
          }
          break;
          }
        default:
          jj_la1[4] = jj_gen;
          jj_consume_token(-1);
          errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
        }
      }
    }
    end_label_3: ;
    }
    if (!hasError) {
    end = jj_consume_token(R_BRACE);
    }
    if (!hasError) {
block->setPosition(end);
    }
__ONERROR(block);
                return block;
assert(false);
}


MethodDeclare             * AlinousLang::methodDeclare() {MethodDeclare* method = new MethodDeclare();
        Token* t = nullptr;
        AccessControlDeclare* ctrl = nullptr;
        AbstractType* type = nullptr;
        ArgumentsListDeclare* args = nullptr;
    if (!hasError) {
    ctrl = accessControlDeclare();
    }
    if (!hasError) {
method->setAccessControl(ctrl);
                method->setPosition(ctrl);
    }
    if (!hasError) {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case STATIC:{
      if (!hasError) {
      t = jj_consume_token(STATIC);
      }
      if (!hasError) {
method->setStatic(true);
                method->setPosition(t);
      }
      break;
      }
    default:
      jj_la1[5] = jj_gen;
      ;
    }
    }
    if (!hasError) {
    type = typeDeclare();
    }
    if (!hasError) {
method->setType(type);
                method->setPosition(type);
    }
    if (!hasError) {
    t = jj_consume_token(IDENTIFIER);
    }
    if (!hasError) {
method->setName(_STR(t));
            method->setPosition(t);
    }
    if (!hasError) {
    args = argumentsListDeclare();
    }
    if (!hasError) {
method->setArguments(args);
                method->setPosition(args);
    }
    if (!hasError) {
    t = jj_consume_token(SEMI_COLON);
    }
    if (!hasError) {
method->setPosition(t);
    }
__ONERROR(method);
                return method;
assert(false);
}


MemberVariableDeclare                     * AlinousLang::memberVariableDeclare() {MemberVariableDeclare* variable = new MemberVariableDeclare();
        Token* t = nullptr;
        AccessControlDeclare* ctrl = nullptr;
        AbstractType* type = nullptr;
    if (!hasError) {
    ctrl = accessControlDeclare();
    }
    if (!hasError) {
variable->setAccessControl(ctrl);
                variable->setPosition(ctrl);
    }
    if (!hasError) {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case STATIC:{
      if (!hasError) {
      t = jj_consume_token(STATIC);
      }
      if (!hasError) {
variable->setStatic(true);
                variable->setPosition(t);
      }
      break;
      }
    default:
      jj_la1[6] = jj_gen;
      ;
    }
    }
    if (!hasError) {
    type = typeDeclare();
    }
    if (!hasError) {
variable->setType(type);
                variable->setPosition(type);
    }
    if (!hasError) {
    t = jj_consume_token(IDENTIFIER);
    }
    if (!hasError) {
variable->setName(_STR(t));
                variable->setPosition(t);
    }
    if (!hasError) {
    t = jj_consume_token(SEMI_COLON);
    }
    if (!hasError) {
variable->setPosition(t);
    }
__ONERROR(variable);
                return variable;
assert(false);
}


AccessControlDeclare                    * AlinousLang::accessControlDeclare() {Token* t = nullptr;
        AccessControlDeclare* ctrl = new AccessControlDeclare();
    if (!hasError) {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case PUBLIC:{
      if (!hasError) {
      t = jj_consume_token(PUBLIC);
      }
      if (!hasError) {
ctrl->setCtrl(AccessControlDeclare::PUBLIC);
                        ctrl->setPositions(_P(t, t));
      }
      break;
      }
    case PROTECTED:{
      if (!hasError) {
      t = jj_consume_token(PROTECTED);
      }
      if (!hasError) {
ctrl->setCtrl(AccessControlDeclare::PROTECTED);
                        ctrl->setPositions(_P(t, t));
      }
      break;
      }
    case PRIVATE:{
      if (!hasError) {
      t = jj_consume_token(PRIVATE);
      }
      if (!hasError) {
ctrl->setCtrl(AccessControlDeclare::PRIVATE);
                        ctrl->setPositions(_P(t, t));
      }
      break;
      }
    default:
      jj_la1[7] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
    }
    if (!hasError) {

    }
__ONERROR(ctrl);
                return ctrl;
assert(false);
}


ArgumentsListDeclare                    * AlinousLang::argumentsListDeclare() {ArgumentsListDeclare* arguments = new ArgumentsListDeclare();
        Token* t = nullptr;
    if (!hasError) {
    t = jj_consume_token(L_PARENTHESIS);
    }
    if (!hasError) {
    t = jj_consume_token(R_PARENTHESIS);
    }
    if (!hasError) {

    }
__ONERROR(arguments);
                return arguments;
assert(false);
}


AbstractType            * AlinousLang::typeDeclare() {AbstractType* dec = nullptr;
    if (!hasError) {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case CHAR:{
      if (!hasError) {
      dec = charType();
      }
      break;
      }
    case SHORT:{
      if (!hasError) {
      dec = shortType();
      }
      break;
      }
    case INT:{
      if (!hasError) {
      dec = intType();
      }
      break;
      }
    case LONG:{
      if (!hasError) {
      dec = longType();
      }
      break;
      }
    case STRING:{
      if (!hasError) {
      dec = stringType();
      }
      break;
      }
    case VOID:{
      if (!hasError) {
      dec = voidType();
      }
      break;
      }
    default:
      jj_la1[8] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
    }
    if (!hasError) {

    }
__ONERROR(dec);
                return dec;
assert(false);
}


CharType        * AlinousLang::charType() {CharType* dec = new CharType();
        Token* t=nullptr;
    if (!hasError) {
    t = jj_consume_token(CHAR);
    }
    if (!hasError) {
dec->setPositions(_P(t, t));
    }
__ONERROR(dec);
                return dec;
assert(false);
}


ShortType         * AlinousLang::shortType() {ShortType* dec = new ShortType();
        Token* t=nullptr;
    if (!hasError) {
    t = jj_consume_token(SHORT);
    }
    if (!hasError) {
dec->setPositions(_P(t, t));
    }
__ONERROR(dec);
                return dec;
assert(false);
}


IntType       * AlinousLang::intType() {IntType* dec = new IntType();
        Token* t=nullptr;
    if (!hasError) {
    t = jj_consume_token(INT);
    }
    if (!hasError) {
dec->setPositions(_P(t, t));
    }
__ONERROR(dec);
                return dec;
assert(false);
}


LongType        * AlinousLang::longType() {LongType* dec = new LongType();
        Token* t=nullptr;
    if (!hasError) {
    t = jj_consume_token(LONG);
    }
    if (!hasError) {
dec->setPositions(_P(t, t));
    }
__ONERROR(dec);
                return dec;
assert(false);
}


StringType          * AlinousLang::stringType() {StringType* dec = new StringType();
        Token* t=nullptr;
    if (!hasError) {
    t = jj_consume_token(STRING);
    }
    if (!hasError) {
dec->setPositions(_P(t, t));
    }
__ONERROR(dec);
                return dec;
assert(false);
}


VoidType        * AlinousLang::voidType() {VoidType* dec = new VoidType();
        Token* t=nullptr;
    if (!hasError) {
    t = jj_consume_token(VOID);
    }
    if (!hasError) {
dec->setPositions(_P(t, t));
    }
__ONERROR(dec);
                return dec;
assert(false);
}


  AlinousLang::AlinousLang(TokenManager *tokenManager){
    head = nullptr;
    ReInit(tokenManager);
}
AlinousLang::~AlinousLang()
{
  clear();
}

void AlinousLang::ReInit(TokenManager* tokenManager){
    clear();
    errorHandler = new ErrorHandler();
    hasError = false;
    token_source = tokenManager;
    head = token = new Token();
    token->kind = 0;
    token->next = nullptr;
    jj_lookingAhead = false;
    jj_rescan = false;
    jj_done = false;
    jj_scanpos = jj_lastpos = nullptr;
    jj_gc = 0;
    jj_kind = -1;
    indent = 0;
    trace = false;
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 9; i++) jj_la1[i] = -1;
  }


void AlinousLang::clear(){
  //Since token manager was generate from outside,
  //parser should not take care of deleting
  //if (token_source) delete token_source;
  if (head) {
    Token *next, *t = head;
    while (t) {
      next = t->next;
      delete t;
      t = next;
    }
  }
  if (errorHandler) {
    delete errorHandler, errorHandler = nullptr;
  }
}


Token * AlinousLang::jj_consume_token(int kind)  {
    Token *oldToken;
    if ((oldToken = token)->next != nullptr) token = token->next;
    else token = token->next = token_source->getNextToken();
    jj_ntk = -1;
    if (token->kind == kind) {
      jj_gen++;
      if (++jj_gc > 100) {
        jj_gc = 0;
        for (int i = 0; i < 1; i++) {
          JJCalls *c = &jj_2_rtns[i];
          while (c != nullptr) {
            if (c->gen < jj_gen) c->first = nullptr;
            c = c->next;
          }
        }
      }
      return token;
    }
    token = oldToken;
    jj_kind = kind;
    JJString image = kind >= 0 ? tokenImage[kind] : tokenImage[0];
    errorHandler->handleUnexpectedToken(kind, image.substr(1, image.size() - 2), getToken(1), this);
    hasError = true;
    return token;
  }


bool  AlinousLang::jj_scan_token(int kind){
    if (jj_scanpos == jj_lastpos) {
      jj_la--;
      if (jj_scanpos->next == nullptr) {
        jj_lastpos = jj_scanpos = jj_scanpos->next = token_source->getNextToken();
      } else {
        jj_lastpos = jj_scanpos = jj_scanpos->next;
      }
    } else {
      jj_scanpos = jj_scanpos->next;
    }
    if (jj_rescan) {
      int i = 0; Token *tok = token;
      while (tok != nullptr && tok != jj_scanpos) { i++; tok = tok->next; }
      if (tok != nullptr) jj_add_error_token(kind, i);
    }
    if (jj_scanpos->kind != kind) return true;
    if (jj_la == 0 && jj_scanpos == jj_lastpos) { return jj_done = true; }
    return false;
  }


/** Get the next Token. */

Token * AlinousLang::getNextToken(){
    if (token->next != nullptr) token = token->next;
    else token = token->next = token_source->getNextToken();
    jj_ntk = -1;
    jj_gen++;
    return token;
  }

/** Get the specific Token. */

Token * AlinousLang::getToken(int index){
    Token *t = token;
    for (int i = 0; i < index; i++) {
      if (t->next != nullptr) t = t->next;
      else t = t->next = token_source->getNextToken();
    }
    return t;
  }


int AlinousLang::jj_ntk_f(){
    if ((jj_nt=token->next) == nullptr)
      return (jj_ntk = (token->next=token_source->getNextToken())->kind);
    else
      return (jj_ntk = jj_nt->kind);
  }


  void AlinousLang::jj_add_error_token(int kind, int pos)  {
  }


 void  AlinousLang::parseError()   {
      fprintf(stderr, "Parse error at: %d:%d, after token: %s encountered: %s\n", token->beginLine, token->beginColumn, addUnicodeEscapes(token->image).c_str(), addUnicodeEscapes(getToken(1)->image).c_str());
   }


  bool AlinousLang::trace_enabled()  {
    return trace;
  }


  void AlinousLang::enable_tracing()  {
  }

  void AlinousLang::disable_tracing()  {
  }


  void AlinousLang::jj_rescan_token(){
    jj_rescan = true;
    for (int i = 0; i < 1; i++) {
      JJCalls *p = &jj_2_rtns[i];
      do {
        if (p->gen > jj_gen) {
          jj_la = p->arg; jj_lastpos = jj_scanpos = p->first;
          switch (i) {
            case 0: jj_3_1(); break;
          }
        }
        p = p->next;
      } while (p != nullptr);
    }
    jj_rescan = false;
  }


  void AlinousLang::jj_save(int index, int xla){
    JJCalls *p = &jj_2_rtns[index];
    while (p->gen > jj_gen) {
      if (p->next == nullptr) { p = p->next = new JJCalls(); break; }
      p = p->next;
    }
    p->gen = jj_gen + xla - jj_la; p->first = token; p->arg = xla;
  }


}
