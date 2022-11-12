//
// Created by popca on 11/11/2022.
//

#pragma once

class TestFA {
    private:
        static void test_FA() {

        }

        static void test_identifier_FA() {
            IdentifierFA fa{};
            assert(fa.is_deterministic());
            assert(fa.is_sequence_accepted("calin"));
            assert(fa.is_sequence_accepted("Calinr"));
            assert(fa.is_sequence_accepted("_calin"));
            assert(!fa.is_sequence_accepted("23calin"));
            assert(fa.is_sequence_accepted("ca52lin"));
            assert(fa.is_sequence_accepted("cal6_in"));
            assert(!fa.is_sequence_accepted("?43543"));
        }

        static void test_integer_constant_FA() {
            IntegerConstantFA fa{};
            assert(fa.is_deterministic());
            assert(fa.is_sequence_accepted("123"));
            assert(fa.is_sequence_accepted("0"));
            assert(!fa.is_sequence_accepted("+0"));
            assert(!fa.is_sequence_accepted("-0"));
            assert(fa.is_sequence_accepted("+1234"));
            assert(!fa.is_sequence_accepted("123+5"));
            assert(!fa.is_sequence_accepted("123+"));
            assert(fa.is_sequence_accepted("-69"));
            assert(!fa.is_sequence_accepted("64$?512"));
            assert(fa.is_sequence_accepted("4151560532"));
        }

    public:
        static void test_all() {
            test_FA();
            test_identifier_FA();
            test_integer_constant_FA();
        }
};