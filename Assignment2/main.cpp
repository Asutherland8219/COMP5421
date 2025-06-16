#include <iostream>
#include "IndexerUI/IndexerUI.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    std::cout << "Starting Text File Indexer\n";
    IndexerUI indexer_ui;;
    indexer_ui.run();

    std::cout << "Program finished. \n";
    return 0;
    }
