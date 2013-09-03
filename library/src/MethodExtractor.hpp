#ifndef METHODEXTRACTOR_HPP
#define METHODEXTRACTOR_HPP
#include <clang/AST/RecursiveASTVisitor.h>
#include "SourceExtractor.hpp"
#include "TextOperationApplier.hpp"

class MethodExtractor : public clang::RecursiveASTVisitor<MethodExtractor>
{
public:
    MethodExtractor(
        SourceExtractor& sourceExtractor, const std::string& extractedMethodName,
        OffsetRange selection, TextOperationApplier& sourceOperations);

    bool VisitFunctionDecl(clang::FunctionDecl* decl);

private:
    SourceExtractor& sourceExtractor;
    std::string extractedMethodName;
    OffsetRange selection;
    TextOperationApplier& sourceOperations;

    bool functionDoesNotContainSelection(const clang::FunctionDecl& f);
    void handleFunctionDecl(const clang::FunctionDecl& decl);
    void extractStatmentsFromFunction(clang::ConstStmtRange stmts, const clang::FunctionDecl& originalFunction);
    bool selectionOverlapsWithStmt(const clang::Stmt& stmt);
    clang::ConstStmtRange findStatementsTouchingSelection(const clang::FunctionDecl& func);
    void printExtractedFunction(clang::SourceLocation at, const std::string& name, clang::SourceRange stmtsRange);
    void printFunction(const std::string& name, const std::string& body, unsigned offset);
    void replaceStatementsWithFunctionCall(clang::SourceRange stmtsRange, const std::string& functionName);
    void replaceRangeWith(clang::SourceRange without, std::string replace);
};

#endif // METHODEXTRACTOR_HPP