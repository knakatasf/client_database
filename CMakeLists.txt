cmake_minimum_required(VERSION 3.27)
project(Client_Database)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_RPATH /usr/local/mysql-connector-c++-8.2.0/lib64)
set(COMBINED_PROJECT TRUE)

include(FetchContent)
FetchContent_Declare(
        xlnt
        GIT_REPOSITORY https://github.com/tfussell/xlnt.git
        GIT_TAG origin/master
)
FetchContent_MakeAvailable(xlnt)

include_directories(/usr/local/mysql-connector-c++-8.2.0/include/jdbc)
link_directories(/usr/local/mysql-connector-c++-8.2.0/lib64)

# Add the OpenSSL library as a dependency (if needed)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Create the executable
add_executable(Client_Database
        main.cpp
        DBManager.cpp
        DBManager.h
        Client.cpp
        Client.h)

target_link_libraries(Client_Database
        PRIVATE xlnt
        curl mysqlcppconn)

