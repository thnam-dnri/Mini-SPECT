cmake_minimum_required(VERSION 3.16)
project(SPECT_Simulation)

# Find Geant4 package
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

# Find ROOT
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${ROOT_INCLUDE_DIRS})

# Source files
set(SOURCES
    main.cc
    DetectorConstruction.cc
    SensitiveDetector.cc
    PrimaryGeneratorAction.cc
    RunAction.cc
    EventAction.cc
    SteppingAction.cc
    PhysicsList.cc
    SimMessenger.cc
)

# Create executable
add_executable(SPECT_Simulation ${SOURCES})

# Link libraries
target_link_libraries(SPECT_Simulation
    ${Geant4_LIBRARIES}
    ${ROOT_LIBRARIES}
)