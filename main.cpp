#include <iostream>
#include <string>
#include <libconfig.h++>

int main() {
    libconfig::Config cfg;

    // 1. Wczytanie pliku konfiguracyjnego
    try {
        cfg.readFile("config.cfg");
    } 
    catch(const libconfig::FileIOException &fioex) {
        std::cerr << "Blad wejscia/wyjscia podczas czytania pliku." << std::endl;
        return -1;
    } 
    catch(const libconfig::ParseException &pex) {
        std::cerr << "Blad parsowania w pliku " << pex.getFile() << " linia " 
                  << pex.getLine() << ": " << pex.getError() << std::endl;
        return -1;
    }

    // 2. Pobieranie podstawowych wartości (id, name, ver)
    try {
        int id = cfg.lookup("id");
        std::string name = cfg.lookup("name");
        std::string ver = cfg.lookup("ver");

        std::cout << "ID: " << id << "\n";
        std::cout << "Nazwa: " << name << "\n";
        std::cout << "Wersja: " << ver << "\n\n";

        // 3. Pobieranie i iteracja po liście obiektów (tab)
        const libconfig::Setting& tab = cfg.lookup("tab");
        std::cout << "Zawartosc listy 'tab':\n";
        
        for(int i = 0; i < tab.getLength(); ++i) {
            const libconfig::Setting& element = tab[i];
            
            int x, z;
            // Pobieranie wartości z konkretnego elementu listy
            if(element.lookupValue("x", x) && element.lookupValue("z", z)) {
                std::cout << "  Element [" << i << "] -> x: " << x << ", z: " << z << "\n";
            }
        }
    } 
    catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Nie znaleziono wymaganej opcji w pliku konfiguracyjnym." << std::endl;
    }

    return 0;
}
