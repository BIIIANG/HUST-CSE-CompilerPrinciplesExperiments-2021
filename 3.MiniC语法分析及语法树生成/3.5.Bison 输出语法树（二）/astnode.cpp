#include "astnode.h"

extern int spaces;

void printspaces()
{
    for (int i = 0; i < spaces; ++i)
        std::cout << " ";
}
void printGrammerInfo(std::string nodeName, int line)
{
    printspaces();
    std::cout << nodeName << " (" << line << ")" << std::endl;
}
int parseNIdentifier(NIdentifier &nIdentifier)
{
    printspaces();
    std::cout << "ID: " << nIdentifier.name << std::endl;
    return 0;
}

int NInteger::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "INT: " << value << std::endl;
    spaces -= 2;
    return 0;
}
int NFloat::parse() // mark
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "FLOAT: " << value << std::endl;
    spaces -= 2;
    return 0;
}
int NChar::parse() // mark
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "CHAR: " << value << std::endl;
    spaces -= 2;
    return 0;
}
int NIdentifier::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "ID: " << name << std::endl;
    spaces -= 2;
    return 0;
}

int NDotOperator::parse() // mark
{
    // Exp DOT ID
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->exp.parse();
    printspaces();
    std::cout << "DOT" << std::endl;
    parseNIdentifier(this->id);
    spaces -= 2;
    return 0;
}
int NListOperator::parse() // mark
{
    // Exp LB Exp RB
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->lhs.parse();
    printspaces();
    std::cout << "LB" << std::endl;
    this->rhs.parse();
    printspaces();
    std::cout << "RB" << std::endl;
    spaces -= 2;
    return 0;
}
int NArgs::parse() // mark
{
    // Exp COMMA Args
    // | Exp
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->exp.parse();
    if (this->nArgs)
    {
        printspaces();
        std::cout << "COMMA" << std::endl;
        this->nArgs->parse();
    }
    spaces -= 2;
    return 0;
}
int NMethodCall::parse() // mark
{
    // ID LP Args RP
    // | ID LP RP
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    parseNIdentifier(this->id);
    printspaces();
    std::cout << "LP" << std::endl;
    if (this->nargs)
    {
        this->nargs->parse();
    }
    printspaces();
    std::cout << "RP" << std::endl;
    spaces -= 2;
    return 0;
}
int NParenOperator::parse() // mark
{
    // LP Exp RP
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "LP" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "RP" << std::endl;
    spaces -= 2;
    return 0;
}
int NSingleOperator::parse() // mark
{
    // PLUSPLUS Exp %prec UPLUSPLUS
    // | MINUSMINUS Exp %prec UMINUSMINUS
    // | Exp PLUSPLUS
    // | Exp MINUSMINUS
    // | MINUS Exp %prec UMINUS
    // | NOT Exp
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    if (this->name == "PLUSPLUS" || this->name == "MINUSMINUS")
    {
        this->hs.parse();
        printspaces();
        std::cout << this->name << std::endl;
    }
    else
    {
        printspaces();
        std::cout << this->name << std::endl;
        this->hs.parse();
    }
    spaces -= 2;
    return 0;
}
int NBinaryOperator::parse() // mark
{
    // Exp AND Exp
    // | Exp OR Exp
    // | Exp RELOP Exp
    // | Exp PLUS Exp
    // | Exp MINUS Exp
    // | Exp STAR Exp
    // | Exp DIV Exp
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->lhs.parse();
    printspaces();
    if (this->name == "==" || this->name == "!=" || this->name == "<=" || this->name == ">=" || this->name == "<" || this->name == ">")
    {
        std::cout << "RELOP" << std::endl;
    }
    else
    {
        std::cout << this->name << std::endl;
    }
    this->rhs.parse();
    spaces -= 2;
    return 0;
}
int NAssignment::parse() // mark
{
    // Exp ASSIGNOP Exp
    // | Exp PLUSASS Exp
    // | Exp MINUSASS Exp
    // | Exp STARASS Exp
    // | Exp DIVASS Exp
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->lhs.parse();
    printspaces();
    std::cout << this->name << std::endl;
    this->rhs.parse();
    spaces -= 2;
    return 0;
}

int NSpecifier::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "TYPE: " << type << std::endl;
    spaces -= 2;
    return 0;
}

int NVarDec::parse()
{
    printGrammerInfo(getNodeName(), line);

    if (v.size())
    {
        spaces += 2;
        for (int i = 0; i < v.size(); ++i)
        {
            printGrammerInfo(getNodeName(), line);

            spaces += 2;
        }
        parseNIdentifier(Id);
        // Id.parse();
        spaces -= 2;
        for (int i = 0; i < v.size(); ++i)
        {
            printspaces();
            std::cout << "LB" << std::endl;
            printspaces();
            std::cout << "INT: " << v[i] << std::endl;
            printspaces();
            std::cout << "RB" << std::endl;
            spaces -= 2;
        }
    }
    else
    {
        spaces += 2;
        parseNIdentifier(Id);
        // Id.parse();
        spaces -= 2;
    }
    return 0;
}
int NParamDec::parse() // mark
{
    // Specifier VarDec
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->nSpecifier.parse();
    this->varDec.parse();
    spaces -= 2;
    return 0;
}
int NVarList::parse() // mark
{
    // ParamDec
    // | ParamDec COMMA VarList
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->nParamDec.parse();
    if (this->nVarList)
    {
        printspaces();
        std::cout << "COMMA" << std::endl;
        this->nVarList->parse();
    }
    spaces -= 2;
    return 0;
}
int NFunDec::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    parseNIdentifier(Id);
    // Id.parse();
    printspaces();
    std::cout << "LP" << std::endl;
    if (arguments)
        arguments->parse();
    printspaces();
    std::cout << "RP" << std::endl;
    spaces -= 2;
    return 0;
}
int NDec::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    vardec.parse();
    if (exp)
    {
        printspaces();
        std::cout << "ASSIGNOP" << std::endl;
        exp->parse();
    }
    spaces -= 2;
    return 0;
}
int NDecList::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    dec.parse();
    if (nDecList)
    {
        printspaces();
        std::cout << "COMMA" << std::endl;
        nDecList->parse();
    }
    spaces -= 2;
    return 0;
}
int NDef::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nSpecifier.parse();
    if (nDecList)
        nDecList->parse();
    printspaces();
    std::cout << "SEMI" << std::endl;
    spaces -= 2;
    return 0;
}
int NDefList::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nDef.parse();
    if (nDefList)
        nDefList->parse();
    spaces -= 2;
    return 0;
}

int NStructSpecifier::parse() // mark
{
    // STRUCT OptTag LC DefList RC
    // | STRUCT Tag
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "STRUCT" << std::endl;
    //tag->parse();
    if (deflist)
    {
        this->optTag->parse();
        printspaces();
        std::cout << "LC" << std::endl;
        deflist->parse();
        printspaces();
        std::cout << "RC" << std::endl;
    }
    else
    {
        this->tag->parse();
    }
    spaces -= 2;
    return 0;
}
// new class
int NStructSpSpecifier::parse() // mark
{
    // StructSpecifier
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->nStructSpecifier.parse();
    spaces -= 2;
    return 0;
}
// new class
int NOptTag::parse()
{
    // StructSpecifier
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    parseNIdentifier(this->nIdentifier);
    spaces -= 2;
    return 0;
}
// new class
int NTag::parse()
{
    // StructSpecifier
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    parseNIdentifier(this->nIdentifier);
    spaces -= 2;
    return 0;
}

int NStmtList::parse() // mark
{
    // %empty
    // | Stmt StmtList
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    nStmt.parse();
    if (nStmtList)
        nStmtList->parse();
    spaces -= 2;
    return 0;
}
int NCompSt::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "LC" << std::endl;
    if (ndeflist)
        ndeflist->parse();
    if (nstmtlist)
        nstmtlist->parse();
    printspaces();
    std::cout << "RC" << std::endl;
    spaces -= 2;
    return 0;
}
int NExpStmt::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->exp.parse();
    printspaces();
    std::cout << "SEMI" << std::endl;
    spaces -= 2;
    return 0;
}
int NCompStStmt::parse() // mark
{
    // CompSt
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->compst.parse();
    spaces -= 2;
    return 0;
}
int NRetutnStmt::parse()
{
    // RETURN Exp SEMI
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "RETURN" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "SEMI" << std::endl;
    spaces -= 2;
    return 0;
}
int NIfStmt::parse() // mark
{
    // IF LP Exp RP Stmt %prec LOWER_THEN_ELSE
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "IF" << std::endl;
    printspaces();
    std::cout << "LP" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "RP" << std::endl;
    this->stmt.parse();
    spaces -= 2;
    return 0;
}
int NIfElseStmt::parse() // mark
{
    // IF LP Exp RP Stmt ELSE Stmt
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "IF" << std::endl;
    printspaces();
    std::cout << "LP" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "RP" << std::endl;
    this->stmt.parse();
    printspaces();
    std::cout << "ELSE" << std::endl;
    this->stmt_else.parse();
    spaces -= 2;
    return 0;
}
int NWhileStmt::parse() // mark
{
    // WHILE LP Exp RP Stmt
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "WHILE" << std::endl;
    printspaces();
    std::cout << "LP" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "RP" << std::endl;
    this->stmt.parse();
    spaces -= 2;
    return 0;
}
int NBreakStmt::parse() // mark
{
    // BREAK SEMI
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "BREAK" << std::endl;
    printspaces();
    std::cout << "SEMI" << std::endl;
    spaces -= 2;
    return 0;
}

int NExtDecList::parse() // mark
{
    // VarDec
    // | VarDec COMMA ExtDecList
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->nVarDec.parse();
    if (this->nExtDecList)
    {
        printspaces();
        std::cout << "COMMA" << std::endl;
        this->nExtDecList->parse();
    }
    spaces -= 2;
    return 0;
}
int NExtDef::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    specifier.parse();
    if (fundec)
    {
        fundec->parse();
        if (compst)
        {
            compst->parse();
        }
    }
    else
    {
        if (nextdeclist)
        {
            nextdeclist->parse();
        }
        printspaces();
        std::cout << "SEMI" << std::endl;
    }

    spaces -= 2;
    return 0;
}
int NExtDefList::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    nExtDef.parse();
    if (nExtDefList)
        nExtDefList->parse();
    spaces -= 2;
    return 0;
}
int NProgram::parse()
{
    printGrammerInfo("Program", line);
    spaces += 2;
    if (nextdeflist)
        nextdeflist->parse();
    spaces -= 2;
    return 0;
}
