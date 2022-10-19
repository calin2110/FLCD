#include <iostream>
#include "SymbolTable.h"

int main() {
    SymbolTable st = SymbolTable();
    st.add("calin");
    st.add("calin");
    st.add("cbkin");
    st.add(30);
    st.add(30);
    st.add(true);
    st.add(true);
    st.add("ed");
    st.add("paul");

    st.add("\"calin_e_smecher\"");
    std::cout << st.search("calin")->position << "\n";
    std::cout << st.search("ed")->position << "\n";
    std::cout << st.search("paul")->position << "\n";

    auto t = st.search("\"calin_e_smecher\"");
    std::cout << std::any_cast<const char*>(st.search("\"calin_e_smecher\"")->symbol) << "\n";
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
