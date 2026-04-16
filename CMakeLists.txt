cmake_minimum_required(VERSION 3.10)
project(PacMan)

# Nastavení C++ standardu na 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pokud máte SFML nainstalované v nestandardním umístění (jako C:/SFML), 
# můžete CMake napovědět pomocí SFML_DIR.
# set(SFML_DIR "C:/SFML/lib/cmake/SFML")

# Najít SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Definice zdrojových souborů (cesty jsou relativní k tomuto souboru)
set(SOURCES
    PacMan/Main.cpp
    PacMan/Game.cpp
    PacMan/Ghost.cpp
    PacMan/Map.cpp
    PacMan/Player.cpp
)

set(HEADERS
    PacMan/Game.hpp
    PacMan/Ghost.hpp
    PacMan/Map.hpp
    PacMan/Player.hpp
)

# Vytvoření spustitelného souboru
add_executable(PacMan ${SOURCES} ${HEADERS})

# Nastavení include adresářů (aby fungovalo #include "Game.hpp" v Main.cpp)
target_include_directories(PacMan PRIVATE PacMan)

# Linkování SFML knihoven
target_link_libraries(PacMan sfml-graphics sfml-window sfml-system)

# Nastavení kopírování fontu do výstupního adresáře (volitelné, ale užitečné)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/PacMan/AniMe Vision - MB_EN Regular.ttf"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
