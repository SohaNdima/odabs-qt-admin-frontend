cmake_minimum_required(VERSION 3.16)

project(MedicalAppointmentsSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(MedicalAppointmentsSystem_HEADERS authentication.h networkmanager.h notificationmanager.h notificationmanager.h
    appointmentdetailslistmodel.h appointmentdatelistmodel.h appointmentdate.h dialogmanager.h
    specializationfieldlistmodel.h
)
set(MedicalAppointmentsSystem_SOURCES main.cpp authentication.cpp networkmanager.cpp notificationmanager.cpp
    appointmentdetailslistmodel.cpp appointmentdatelistmodel.cpp appointmentdate.cpp dialogmanager.cpp
    specializationfieldlistmodel.cpp
)
set(MedicalAppointmentsSystem_RESOURCES assets.qrc)

find_package(Qt6 6.3 COMPONENTS Quick REQUIRED)

QT6_ADD_RESOURCES(MedicalAppointmentsSystem_RESOURCES_RCC ${MedicalAppointmentsSystem_RESOURCES})

qt_add_executable(appMedicalAppointmentsSystem
    ${MedicalAppointmentsSystem_HEADERS}
    ${MedicalAppointmentsSystem_SOURCES}
    ${MedicalAppointmentsSystem_RESOURCES_RCC}
)

qt_add_qml_module(appMedicalAppointmentsSystem
    URI MedicalAppointmentsSystem
    VERSION 1.0
    QML_FILES main.qml Theme.qml LoginPage.qml ContentViewManager.qml NeuTextField.qml NeuButton.qml AccountMenuView.qml AccountCalendarView.qml MonthDateDelegate.qml AccountAppointmentsView.qml
    AppointmentsDelegate.qml MenuButton.qml DialogViewer.qml NewDoctorDialog.qml Notification.qml
)

set_target_properties(appMedicalAppointmentsSystem PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appMedicalAppointmentsSystem
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appMedicalAppointmentsSystem
    PRIVATE Qt6::Quick)
