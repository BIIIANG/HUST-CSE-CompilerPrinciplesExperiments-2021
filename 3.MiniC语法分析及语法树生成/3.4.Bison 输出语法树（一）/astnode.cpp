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
    std::cout << "INT"
              << ": " << value << std::endl;
    spaces -= 2;
    return 0;
}
int NFloat::parse()
{

    return 0;
}
int NChar::parse()
{

    return 0;
}
int NIdentifier::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "ID"
              << ": " << name << std::endl;
    spaces -= 2;
    return 0;
}
int NDotOperator::parse()
{

    return 0;
}
int NListOperator::parse()
{

    return 0;
}
int NArgs::parse()
{

    return 0;
}
int NMethodCall::parse()
{

    return 0;
}
int NParenOperator::parse()
{

    return 0;
}
int NSingleOperator::parse()
{

    return 0;
}
int NBinaryOperator::parse()
{

    return 0;
}
int NAssignment::parse()
{

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
int NParamDec::parse()
{

    return 0;
}
int NVarList::parse()
{

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
    {
        nDefList->parse();
    }
    spaces -= 2;
    return 0;
}
int NStructSpecifier::parse()
{

    return 0;
}
int NStmtList::parse()
{
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
int NCompStStmt::parse()
{

    return 0;
}
int NRetutnStmt::parse()
{
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
int NIfStmt::parse()
{

    return 0;
}
int NIfElseStmt::parse()
{

    return 0;
}
int NWhileStmt::parse()
{
    return 0;
}
int NBreakStmt::parse()
{

    return 0;
}
int NExtDecList::parse()
{
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
