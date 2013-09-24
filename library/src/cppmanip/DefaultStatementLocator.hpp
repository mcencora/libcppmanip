#ifndef CPPMANIP_9F771D23280342E49A56A67096A3B6E5_HPP
#define CPPMANIP_9F771D23280342E49A56A67096A3B6E5_HPP
#include "StatementLocator.hpp"
#include "LocationRange.hpp"
#include <clang/Basic/SourceManager.h>
#include <clang/AST/Stmt.h>

namespace cppmanip
{

class DefaultStatementLocator : public StatementLocator
{
public:
    typedef std::function<LocationRange(clang::SourceManager&, clang::Stmt& )> GetStmtRange;
    DefaultStatementLocator(GetStmtRange getStmtRange, LocationRange selection)
        : getStmtRange(getStmtRange), selection(selection) { }
    virtual clang::StmtRange findStatementsInFunction(const clang::FunctionDecl& decl);
private:
    clang::StmtRange findStatementsInCompoundStatements(clang::SourceManager& srcMgr, clang::CompoundStmt& compoundStmt);
    clang::StmtRange tryNestedCompoundStatements(clang::SourceManager& srcMgr, clang::Stmt& stmt);
    GetStmtRange getStmtRange;
    LocationRange selection;
};

}
#endif // CPPMANIP_9F771D23280342E49A56A67096A3B6E5_HPP
