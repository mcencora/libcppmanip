#include "DefaultStatementLocator.hpp"
#include <clang/AST/Stmt.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/StmtCXX.h>

namespace cppmanip
{

clang::StmtRange DefaultStatementLocator::findStatementsInCompoundStatements(
        clang::SourceManager& srcMgr,
        clang::CompoundStmt& compoundStmt)
{
    auto first = std::find_if(
        compoundStmt.child_begin(), compoundStmt.child_end(),
        [&](clang::Stmt *s) { return getStmtRange(srcMgr, *s).overlapsWith(selection); });
    auto last = std::find_if(
        first, compoundStmt.child_end(),
        [&](clang::Stmt *s) { return !getStmtRange(srcMgr, *s).overlapsWith(selection); });

    clang::StmtRange range(first, last);
    if (std::distance(first, last) == 1)
    {
        clang::StmtRange r2 = tryNestedCompoundStatements(srcMgr, **first);
        if (!r2.empty())
        {
            return r2;
        }
    }
    return range;
}

clang::StmtRange DefaultStatementLocator::tryNestedCompoundStatements(clang::SourceManager& srcMgr, clang::Stmt& stmt)
{
    switch (stmt.getStmtClass())
    {
        case clang::Stmt::CXXTryStmtClass:
        {
            auto t = clang::dyn_cast<clang::CXXTryStmt>(&stmt);
            clang::StmtRange r = findStatementsInCompoundStatements(srcMgr, *t->getTryBlock());
            return r;
        }
        case clang::Stmt::IfStmtClass:
        {
            auto s = clang::dyn_cast<clang::IfStmt>(&stmt);
            clang::StmtRange r = findStatementsInCompoundStatements(srcMgr, *clang::dyn_cast<clang::CompoundStmt>(s->getThen()));
            return r;
        }
    }
    return clang::StmtRange();
}

clang::StmtRange DefaultStatementLocator::findStatementsInFunction(const clang::FunctionDecl& decl)
{
    return findStatementsInCompoundStatements(decl.getASTContext().getSourceManager(), *clang::dyn_cast<clang::CompoundStmt>(decl.getBody()));
}

}
