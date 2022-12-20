#include <iostream>
#include <cassert>
#include <utility>
#include "scanner/header/Scanner.h"
#include "exception/LexicalException.h"
#include "finite_automata/header/FiniteAutomata.h"
#include "finite_automata/header/IdentifierFA.h"
#include "finite_automata/header/IntegerConstantFA.h"
#include "test/TestFA.h"
#include "grammar/header/Grammar.h"
#include "parser/header/Parser.h"
#include "test/TestParser.h"
#include "exception/LR0Exception.h"
#include "exception/ConflictException.h"

std::unordered_set<std::string> read_reserved_words(const std::string &filepath) {
    std::ifstream file(filepath);
    std::string reserved_word;
    std::unordered_set<std::string> res_words{};
    while (file >> reserved_word) {
        res_words.insert(reserved_word);
    }
    file.close();
    return res_words;
}

std::unordered_set<char> read_separators(const std::string &filepath) {
    std::ifstream file(filepath);
    std::string separator_word;
    std::unordered_set<char> separators{};
    while (file >> separator_word) {
        separators.insert(separator_word[0]);
    }
    std::cout << separators.size() << "\n";
    file.close();
    return separators;
}

PIF scan(const std::string& filepath) {
    std::unordered_set<std::string> reserved_words = read_reserved_words("../files/scanner/token.in");
    std::unordered_set<char> separators = read_separators("../files/scanner/separators.in");
    std::unordered_set<char> look_ahead_separators = read_separators("../files/scanner/look_ahead_separators.in");
    Scanner scanner{reserved_words, separators, look_ahead_separators};
    PIF pif = scanner.scan(filepath).first;
    std::cout << "Lexically correct\n";
    return pif;
}

std::deque<std::string> transform_pif(const PIF& pif) {
    std::list<Token> tokens = pif.get_tokens();
    std::deque<std::string> input{};
    std::for_each(tokens.begin(), tokens.end(), [&input](const Token& token){
        input.push_back(token.name);
    });
    return input;
}

Grammar read_grammar_from_file(const std::string& filepath) {
    Grammar grammar{};
    std::ifstream file(filepath);
    file >> grammar;
    file.close();
    return grammar;
}

SyntaxTree parse(std::deque<std::string> input, const Grammar& grammar) {
    EnhancedCFGGrammar enhancedCfgGrammar{grammar};
    Parser parser{enhancedCfgGrammar};
    SyntaxTree tree = parser.run(input);
    return tree;
}

void run(const std::string& program_filepath,
         const std::string& grammar_filepath) {
    try {
        PIF pif = scan(program_filepath);
        std::deque<std::string> input = transform_pif(pif);
        Grammar grammar = read_grammar_from_file(grammar_filepath);
        SyntaxTree syntaxTree = parse(input, grammar);
        std::cout << syntaxTree;
    } catch (LexicalException &lexicalException) {
        std::cout << "Lexical error\n";
        std::cout << lexicalException.what() << "\n";
    } catch (LR0Exception &lr0Exception) {
        std::cout << "Syntactic error\n";
        std::cout << lr0Exception.what() << "\n";
    } catch (ConflictException &conflictException) {
        std::cout << "Grammar error - there are conflicts in the grammar\n";
        std::cout << conflictException.what() << "\n";
    }
}

void run(std::deque<std::string> input,
         const std::string& grammar_filepath) {
    Grammar grammar = read_grammar_from_file(grammar_filepath);
    SyntaxTree syntaxTree = parse(std::move(input), grammar);
    std::cout << syntaxTree;
}

void test_parser_functions() {
    TestParser::test_all();
}

int main() {
    std::cout << "Running the parser for simple input...\n";
    run(
            std::deque<std::string>({"a", "b", "b", "c"}),
            "testg.in"
    );
    std::cout << "Finished running the parser for simple input\n";

    std::cout << "Running the parser for mini-language program...\n";
    run(
            "../files/programs/p4.cln",
            "../files/grammar/g2.in"
    );
    std::cout << "Finished running the parser for correct mini-language program\n";

    std::cout << "Running the parser for errorful mini-language program...\n";
    run(
            "../files/programs/p4err.cln",
            "../files/grammar/g2.in"
    );
    std::cout << "Finished running the parser for errorful mini-language program\n";
    return 0;
}

