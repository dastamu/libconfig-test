cmake_minimum_required(VERSION 3.15)
project(libconfig_test C CXX)

# Wymagany standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Konfiguracja submodułu libconfig
# Oryginalne repozytorium libconfig używa głównie Autotools, 
# ale najprostszym i najbardziej niezawodnym sposobem na wpięcie go jako submoduł 
# w CMake jest bezpośrednie zbudowanie jego plików źródłowych jako biblioteki statycznej.

set(LIBCONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libconfig/lib)

# Pełna lista plików źródłowych C (dodano pliki util, wincompat itp.)
set(LIBCONFIG_C_SOURCES
    ${LIBCONFIG_DIR}/libconfig.c
    ${LIBCONFIG_DIR}/grammar.c
    ${LIBCONFIG_DIR}/scanner.c
    ${LIBCONFIG_DIR}/scanctx.c
    ${LIBCONFIG_DIR}/strbuf.c
    ${LIBCONFIG_DIR}/util.c
    ${LIBCONFIG_DIR}/wincompat.c
    ${LIBCONFIG_DIR}/strvec.c
)

# Plik źródłowy C++
set(LIBCONFIG_CPP_SOURCES
    ${LIBCONFIG_DIR}/libconfigcpp.c++
)

# Tworzymy lokalny cel biblioteki statycznej łącząc oba typy plików
add_library(libconfig STATIC ${LIBCONFIG_C_SOURCES} ${LIBCONFIG_CPP_SOURCES})

# POPRAWKA 2: Dla pewności wymuszamy na CMake odpowiednie kompilatory dla plików
set_source_files_properties(${LIBCONFIG_C_SOURCES} PROPERTIES LANGUAGE C)
set_source_files_properties(${LIBCONFIG_CPP_SOURCES} PROPERTIES LANGUAGE CXX)

# Wskazujemy katalogi z plikami nagłówkowymi submodułu
target_include_directories(libconfig PUBLIC ${LIBCONFIG_DIR})

# Wyłączenie ostrzeżeń dla kodu zewnętrznej biblioteki
if(MSVC)
    target_compile_options(libconfig PRIVATE /W0)
else()
    target_compile_options(libconfig PRIVATE -w)
endif()

# 2. Konfiguracja Twojego programu
add_executable(main main.cpp)

# Linkowanie biblioteki
target_link_libraries(main PRIVATE libconfig)

# 3. Kopiowanie pliku konfiguracyjnego do folderu uruchomieniowego
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.cfg
    ${CMAKE_CURRENT_BINARY_DIR}/config.cfg
    COPYONLY
)
