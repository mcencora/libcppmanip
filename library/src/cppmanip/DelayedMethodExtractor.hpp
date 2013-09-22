#ifndef CPPMANIP_799523E01B0442A6ABBA2BFB7EF4F97A_HPP
#define CPPMANIP_799523E01B0442A6ABBA2BFB7EF4F97A_HPP
#include "MethodExtractor.hpp"
#include "FunctionPrinter.hpp"
#include "LocalVariableLocator.hpp"
#include "TextModifier.hpp"
#include "SourceExtractor.hpp"

namespace cppmanip
{

class DelayedMethodExtractor : public MethodExtractor
{
public:
    DelayedMethodExtractor(
        OffsetBasedTextModifier& sourceOperations, FunctionPrinter& functionPrinter, LocalVariableLocator& localVariableLocator);

    void extractStatmentsFromFunctionIntoNewFunction(
        clang::StmtRange stmts, const clang::FunctionDecl& originalFunction, const std::string& extractedFunctionName);

private:

    typedef LocalVariableLocator::Variables Variables;

    OffsetBasedTextModifier& sourceOperations;
    FunctionPrinter& functionPrinter;
    LocalVariableLocator& localVariableLocator;

    void printExtractedFunction(clang::SourceLocation at, const std::string& name, const Variables& variables, clang::SourceRange stmtsRange, SourceExtractor& sourceExtractor);
    void replaceStatementsWithFunctionCall(clang::SourceRange stmtsRange, const std::string& functionName, const Variables& variables, SourceExtractor& sourceExtractor);
    void replaceRangeWith(clang::SourceRange without, std::string replace, SourceExtractor& sourceExtractor);
    FunctionPrinter::Strings getTypesAndNames(Variables variables, SourceExtractor& sourceExtractor);
    FunctionPrinter::Strings getNames(Variables variables, SourceExtractor& sourceExtractor);
    void failIfVariablesAreDeclaredByAndUsedAfterStmts(clang::StmtRange stmts, const clang::FunctionDecl& originalFunction, const std::string& extractedFunctionName, SourceExtractor& sourceExtractor);
};

}
#endif // CPPMANIP_799523E01B0442A6ABBA2BFB7EF4F97A_HPP
