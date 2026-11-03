#include <iostream>
#include <string>
#include <cstring> // for std::strcmp
#include <libconfig.h++>

// Function that generates the default configuration file
void generateDefaultConfig(const std::string& filename) {
    libconfig::Config cfg;
    libconfig::Setting& root = cfg.getRoot();

    root.add("id", libconfig::Setting::TypeInt) = 1;
    root.add("name", libconfig::Setting::TypeString) = "appka";
    root.add("ver", libconfig::Setting::TypeString) = "1.0.0";

    // float & bool
    root.add("pi_value", libconfig::Setting::TypeFloat) = 3.14159265f;
    root.add("debug_mode", libconfig::Setting::TypeBoolean) = true;

    // Array
    libconfig::Setting& ports_set = root.add("allowed_ports", libconfig::Setting::TypeArray);
    ports_set.add(libconfig::Setting::TypeInt) = 80;
    ports_set.add(libconfig::Setting::TypeInt) = 443;
    ports_set.add(libconfig::Setting::TypeInt) = 8080;

    // List
    libconfig::Setting& tab = root.add("tab", libconfig::Setting::TypeList);

    libconfig::Setting& elem1 = tab.add(libconfig::Setting::TypeGroup);
    elem1.add("x", libconfig::Setting::TypeInt) = 1;
    elem1.add("z", libconfig::Setting::TypeInt) = 31;

    libconfig::Setting& elem2 = tab.add(libconfig::Setting::TypeGroup);
    elem2.add("x", libconfig::Setting::TypeInt) = 2;
    elem2.add("z", libconfig::Setting::TypeInt) = 32;

    libconfig::Setting& elem3 = tab.add(libconfig::Setting::TypeGroup);
    elem3.add("x", libconfig::Setting::TypeInt) = 3;
    elem3.add("z", libconfig::Setting::TypeInt) = 33;

    // Write to file
    try {
        cfg.writeFile(filename.c_str());
        std::cout << "Default configuration file generated: " << filename << std::endl;
    } 
    catch(const libconfig::FileIOException &fioex) {
        std::cerr << "File writing error: " << filename << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // --- Write to config file
    const std::string configFilename = "config.cfg";

    // Checking if the program was called with the '--get-config' parameter
    if (argc > 1 && std::strcmp(argv[1], "--get-config") == 0) {
        generateDefaultConfig(configFilename);
        return 0; // We exit the program after generating the config file
    }

    // --- Read from config file
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
        // Read Vars
        int id = cfg.lookup("id");
        std::string name = cfg.lookup("name");
        std::string ver = cfg.lookup("ver");
        float pi_value = cfg.lookup("pi_value");
        bool debug_mode = cfg.lookup("debug_mode");

        std::cout << "ID: " << id << "\n";
        std::cout << "NAME: " << name << "\n";
        std::cout << "VERSION: " << ver << "\n";
        std::cout << "PI: " << pi_value << "\n";
        std::cout << "DEBUG: " << (debug_mode ? "YES" : "NO") << "\n\n";

        // Read Array
        const libconfig::Setting& ports = cfg.lookup("allowed_ports");
        std::cout << "PORTS: ";
        for(int i = 0; i < ports.getLength(); ++i) {
            int port = ports[i];
            std::cout << port << (i < ports.getLength() - 1 ? ", " : "");
        }
        std::cout << "\n\n";

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
