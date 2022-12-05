//
// Created by popca on 30/11/2022.
//

#include "../header/EnhancedCFGGrammar.h"
#include "../../exception/GrammarFormatException.h"

EnhancedCFGGrammar::EnhancedCFGGrammar(const Grammar &grammar) {
    if (!grammar.is_grammar_context_free()) {
        throw GrammarFormatException("Enhanced Grammar must take a CFG Grammar!");
    }

    terminals = std::unordered_set<std::string>{};
    terminals.insert(grammar.terminals.begin(), grammar.terminals.end());

    nonterminals = std::unordered_set<std::string>{};
    nonterminals.insert(grammar.nonterminals.begin(), grammar.nonterminals.end());

    std::string current_start = grammar.start_symbol + "'";
    nonterminals.insert(current_start);

    start_symbol = current_start;

    productions = std::unordered_map<std::string, std::list<Production>>{};
    for (const std::string& nonterminal: nonterminals) {
        productions[nonterminal] = std::list<Production>{};
    }

    for (const Production& production: grammar.productions) {
        productions[production.lhs.front()].push_back(production);
    }
    productions[start_symbol].emplace_back(std::list<std::string>{start_symbol}, std::list<std::string>{grammar.start_symbol});
}

std::unordered_set<std::string> EnhancedCFGGrammar::get_terminals_and_nonterminals() const {
    std::unordered_set<std::string> elements{};
    elements.insert(terminals.begin(), terminals.end());
    elements.insert(nonterminals.begin(), nonterminals.end());
    return elements;
}