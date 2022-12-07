//
// Created by popca on 07/12/2022.
//

#pragma once

#include <iostream>
#include <fstream>
#include "../grammar/header/EnhancedCFGGrammar.h"
#include <cassert>
#include "../parser/header/Parser.h"

class TestParser {
private:
    template<typename T>
    static void assert_sets_are_equal(const std::unordered_set<T> &set1,
                                      const std::unordered_set<T> &set2) {
        assert(set1.size() == set2.size());
        for (const T &item: set1) {
            assert(set2.find(item) != set2.end());
        }
    }

    static Grammar read_grammar_from_file(const std::string &filepath) {
        std::ifstream file("../files/test/test_grammar.in");
        Grammar grammar{};
        file >> grammar;
        file.close();
        return grammar;
    }

    static EnhancedCFGGrammar create_enhanced_grammar_from_file(const std::string &filepath) {
        Grammar grammar = read_grammar_from_file(filepath);
        return EnhancedCFGGrammar{grammar};
    }

    static Parser create_parser_for_grammar(const std::string &grammar_filepath) {
        EnhancedCFGGrammar enhancedCfgGrammar = create_enhanced_grammar_from_file(grammar_filepath);
        return Parser(enhancedCfgGrammar);
    }


    static void test_closure() {
        Parser parser = create_parser_for_grammar("../files/test/test_grammar.in");
        std::unordered_set<LR0Item> closure{};
        std::unordered_set<LR0Item> supposed_closure{};

        closure = parser.create_closure_LR0(
                std::unordered_set<LR0Item>{}
        );
        supposed_closure = std::unordered_set<LR0Item>{};
        assert_sets_are_equal(closure, supposed_closure);

        closure = parser.create_closure_LR0(
                std::unordered_set<LR0Item>{
                    LR0Item("S", std::list<std::string>{"a"}, std::list<std::string>{"A"})
                }
        );
        supposed_closure = std::unordered_set<LR0Item>({
            LR0Item{"S", std::list<std::string>{"a"}, std::list<std::string>{"A"}},
            LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"b", "A"}},
            LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"c"}}
        });
        assert_sets_are_equal(closure, supposed_closure);

        closure = parser.create_closure_LR0(
                std::unordered_set<LR0Item>{
                    LR0Item("A", std::list<std::string>{"a", "A"}, std::list<std::string>{})
                }
        );
        supposed_closure = std::unordered_set<LR0Item>({
            LR0Item{"A", std::list<std::string>{"a", "A"}, std::list<std::string>{}}
        });
        assert_sets_are_equal(closure, supposed_closure);

        closure = parser.create_closure_LR0(
                std::unordered_set<LR0Item>{
                    LR0Item("A", std::list<std::string>{"b"}, std::list<std::string>{"A"})
                }
        );
        supposed_closure = std::unordered_set<LR0Item>({
            LR0Item{"A", std::list<std::string>{"b"}, std::list<std::string>{"A"}},
            LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"b", "A"}},
            LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"c"}}
        });
        assert_sets_are_equal(closure, supposed_closure);
    }

    static void test_goto() {
        std::ifstream file("../files/test/test_grammar.in");
        Grammar grammar{};
        file >> grammar;
        file.close();
        EnhancedCFGGrammar enhancedCfgGrammar = EnhancedCFGGrammar(grammar);
        Parser parser{enhancedCfgGrammar};


        State state = parser.create_goto_LR0(
                State(
                        std::unordered_set<LR0Item>({
                            LR0Item("S'", std::list<std::string>{}, std::list<std::string>{"S"}),
                            LR0Item("S", std::list<std::string>{}, std::list<std::string>{"a", "A"})
                            })
                ),"a"
        );
        State supposed_state = State(
                std::unordered_set<LR0Item>({
                    LR0Item("S", std::list<std::string>{"a"}, std::list<std::string>{"A"}),
                    LR0Item("A", std::list<std::string>{}, std::list<std::string>{"b", "A"}),
                    LR0Item("A", std::list<std::string>{}, std::list<std::string>{"c"})
                })
        );
        assert(state == supposed_state);

        state = parser.create_goto_LR0(
                State(
                        std::unordered_set<LR0Item>({
                            LR0Item{"S", std::list<std::string>{"a"}, std::list<std::string>{"A"}},
                            LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"b", "A"}},
                            LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"c"}}
                        })
                ),"A"
        );
        supposed_state = State(
                std::unordered_set<LR0Item>({
                    LR0Item{"S", std::list<std::string>{"a", "A"}, std::list<std::string>{}}
                })
        );
        assert(state == supposed_state);

        state = parser.create_goto_LR0(
                State(
                    std::unordered_set<LR0Item>({
                        LR0Item{"A", std::list<std::string>{"c"}, std::list<std::string>{}}
                    })
                ), "A"
        );
        supposed_state = State(
                std::unordered_set<LR0Item>{}
        );
        assert(state == supposed_state);
    }

    static void test_canonical_collection() {
        Parser parser = create_parser_for_grammar("../files/test/test_grammar.in");

        std::unordered_set<State> canonical_collection = parser.create_col_can_LR0();
        std::unordered_set<State> supposed_canonical_collection =
                std::unordered_set<State>({
                    State(
                            std::unordered_set<LR0Item>({
                                LR0Item{"S'", std::list<std::string>{}, std::list<std::string>{"S"}},
                                LR0Item{"S", std::list<std::string>{}, std::list<std::string>{"a", "A"}}
                            })
                    ),
                    State(
                            std::unordered_set<LR0Item>({
                                LR0Item{"S'", std::list<std::string>{"S"}, std::list<std::string>{}}
                            })
                    ),
                    State(
                            std::unordered_set<LR0Item>({
                                LR0Item{"S", std::list<std::string>{"a"}, std::list<std::string>{"A"}},
                                LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"b", "A"}},
                                LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"c"}}
                            })
                    ),
                    State(
                            std::unordered_set<LR0Item>({
                                LR0Item{"S", std::list<std::string>{"a", "A"}, std::list<std::string>{}}
                            })
                    ),
                    State(
                            std::unordered_set<LR0Item>({
                                LR0Item{"A", std::list<std::string>{"b"}, std::list<std::string>{"A"}},
                                LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"b", "A"}},
                                LR0Item{"A", std::list<std::string>{}, std::list<std::string>{"c"}}
                            })
                    ),
                    State(
                            std::unordered_set<LR0Item>({
                                LR0Item{"A", std::list<std::string>{"c"}, std::list<std::string>{}}
                            })
                    ),
                    State(
                            std::unordered_set<LR0Item>({
                                LR0Item{"A", std::list<std::string>{"b", "A"}, std::list<std::string>{}}
                            })
                    ),
                });
        assert_sets_are_equal(canonical_collection, supposed_canonical_collection);
    }

public:
    static void test_all() {
        test_closure();
        std::cout << "Closure tests passed!\n";

        test_goto();
        std::cout << "Goto tests passed!\n";

        test_canonical_collection();
        std::cout << "Canonical collection tests passed!\n";

        std::cout << "All parser tests passed!\n";
    }

};


