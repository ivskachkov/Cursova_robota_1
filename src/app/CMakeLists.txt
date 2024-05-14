set(SOURCES
    window.ui
    window.cpp
    main.cpp
    matrix_model.cpp
    decart_graph_widget.cpp
)

qt_add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Sql
    Qt6::Widgets
    Qt6::Charts
)