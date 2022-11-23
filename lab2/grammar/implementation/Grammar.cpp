//
// Created by popca on 23/11/2022.
//

#include "../header/Grammar.h"

std::istream &operator>>(std::istream &is, Grammar& grammar) {
    int count_nonterminals;
    is >> count_nonterminals;
    std::unordered_set<std::string> nonterminals{};
    for (int _ = 0; _ < count_nonterminals; _++) {
        std::string nonterminal;
        is >> nonterminal;
        nonterminals.insert(nonterminal);
    }

    int count_terminals;
    is >> count_terminals;
    std::unordered_set<std::string> terminals{};
    for (int _ = 0; _ < count_terminals; _++) {
        std::string terminal;
        is >> terminal;
        terminals.insert(terminal);
    }

    int count_productions;
    is >> count_productions;
    std::list<Production> productions{};

    std::string buffer;
    std::getline(is, buffer);
    for (int _ = 0; _ < count_productions; _++) {
        std::string production_line;
        std::getline(is, production_line);
        Production production = Production::read_from_line(production_line, terminals, nonterminals);
        productions.push_back(std::move(production));
    }

    std::string start_symbol;
    is >> start_symbol;


    grammar.terminals = terminals;
    grammar.nonterminals = nonterminals;
    grammar.productions = std::move(productions);
    grammar.start_symbol = start_symbol;
    return is;
}

void Grammar::print_nonterminals(std::ostream &ostream) {
    ostream << "NON TERMINALS: \n";
    for (const std::string& nonterminal: nonterminals) {
        ostream << nonterminal << " ";
    }
    ostream << "\n";
}

void Grammar::print_terminals(std::ostream &ostream) {
    ostream << "TERMINALS:\n";
    for (const std::string& terminal: terminals) {
        ostream << terminal << " ";
    }
    ostream << "\n";
}

void Grammar::print_productions(std::ostream &ostream) {
    ostream << "PRODUCTIONS:\n";
    for (Production& production: productions) {
        ostream << production;
    }
    ostream << "\n";
}

void Grammar::print_start_symbol(std::ostream &ostream) {
    ostream << "START SYMBOL: " << start_symbol << "\n";
}

bool Grammar::is_grammar_context_free() {
    for (const Production& production: productions) {
        if (production.lhs.size() != 1) {
            return false;
        }
    }
    return true;
}
