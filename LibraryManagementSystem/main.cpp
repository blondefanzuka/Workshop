#include "Library.h"

int main() {
    Library library;
    library.loadItemsFromFile();
    library.menu();
    return 0;
}
