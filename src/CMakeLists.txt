project(shirokuma)

set(SOURCE_FILES main.cpp
                 game.cpp
                 scenes/mainmenu.cpp
                 systems/sudokulogic.cpp)

add_executable(shirokuma ${SOURCE_FILES})
target_link_libraries(shirokuma polarbear)
target_include_directories(shirokuma PRIVATE ../include)

install(TARGETS shirokuma EXPORT shirokuma
        RUNTIME DESTINATION bin)