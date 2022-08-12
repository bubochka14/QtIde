set(APP_NAME "qt_ide")

set(SOURCE
    main.cpp
    codeeditor.cpp
    codeeditor.h
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    syntaxhighlighter.cpp
    syntaxhighlighter.h
    )
add_executable(${APP_NAME} ${SOURCE})

target_include_directories(${APP_NAME}
    PUBLIC QT${QT_VERSION_MAJOR}_INCLUDE_DIRS

    )
target_link_libraries(${APP_NAME}
    PUBLIC Qt${QT_VERSION_MAJOR}::Core
    PUBLIC Qt${QT_VERSION_MAJOR}::Widgets

    )
