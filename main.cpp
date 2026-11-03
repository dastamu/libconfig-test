#include <iostream>
#include <string>
#include <libconfig.h++>

int main() {
    libconfig::Config cfg;

    // Loading the configuration file
    try {
        cfg.readFile("config.cfg");
    } 
    catch(const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return -1;
    } 
    catch(const libconfig::ParseException &pex) {
        std::cerr << "Parsing error in file " << pex.getFile() << " in line " 
                  << pex.getLine() << ": " << pex.getError() << std::endl;
        return -1;
    }

    // Getting basic values ​​(id, name, ver)
    try {
        int id = cfg.lookup("id");
        std::string name = cfg.lookup("name");
        std::string ver = cfg.lookup("ver");

        std::cout << "ID: " << id << "\n";
        std::cout << "NAME: " << name << "\n";
        std::cout << "VERSION: " << ver << "\n\n";

        // Fetching and iterating through a list of objects (tab)
        const libconfig::Setting& tab = cfg.lookup("tab");
        std::cout << "List contents of 'tab':\n";
        
        for(int i = 0; i < tab.getLength(); ++i) {
            const libconfig::Setting& element = tab[i];
            
            int x, z;
            // Getting a value from a specific list item
            if(element.lookupValue("x", x) && element.lookupValue("z", z)) {
                std::cout << "  Item [" << i << "] -> x: " << x << ", z: " << z << "\n";
            }
        }
    } 
    catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "A required option was not found in the configuration file." << std::endl;
    }

    return 0;
}
