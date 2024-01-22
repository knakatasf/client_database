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

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(Client_Database
        src/main.cpp
        src/DBManager.cpp
        include/DBManager.h
        src/Client.cpp
        include/Client.h
        src/MyDBFrame.cpp
        include/MyDBFrame.h
        include/DBAppConfig.h
        include/MyDBApp.h
        include/MyDBApp.h
        src/InsertDialog.cpp
        include/InsertDialog.h
        src/SearchDialog.cpp
        include/SearchDialog.h
        src/ResultEditDialog.cpp
        include/ResultEditDialog.h
        src/main.cpp
        src/main.cpp
        src/ImportDialog.cpp
        include/ImportDialog.h
)

target_include_directories(Client_Database
        PRIVATE ${wxWidgets_INCLUDE_DIRS}
        /usr/local/include/wx-3.2)

target_link_libraries(Client_Database
        PRIVATE xlnt
        curl mysqlcppconn
        ${wxWidgets_LIBRARIES})

