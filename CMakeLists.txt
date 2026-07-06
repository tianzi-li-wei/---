cmake_minimum_required(VERSION 4.1.1)

project(Xiangqi VERSION 0.1 LANGUAGES CXX)

set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Network)

include(GNUInstallDirs)

qt_standard_project_setup(REQUIRES 6.11)

qt_add_executable(appXiangqi
    main.cpp
    README.md
    core/Constants.h
    core/Piece.h
    core/MoveResult.h
    core/ChessBoard.h
    core/ChessBoard.cpp
    core/RuleEngine.h
    core/RuleEngine.cpp

    controller/AppController.h
    controller/AppController.cpp
    controller/BoardModel.h
    controller/BoardModel.cpp
    controller/GameController.h
    controller/GameController.cpp

    network/NetworkManager.h
    network/NetworkManager.cpp
)

qt_add_qml_module(appXiangqi
    URI Xiangqi
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/BoardView.qml
        qml/PieceItem.qml
)

target_compile_features(appXiangqi PRIVATE cxx_std_23)

target_link_libraries(appXiangqi
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Network
)

set(CMAKE_INSTALL_PREFIX "/opt/${PROJECT_NAME}" CACHE PATH "Install path prefix" FORCE)

install(TARGETS appXiangqi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)