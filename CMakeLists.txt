
cmake_minimum_required(VERSION 3.16)
project(geant_plate)

# Geant4
find_package(Geant4 REQUIRED ui_all vis_all)

# ROOT (needed because you use TFile/TTree in RootIO.cc)
find_package(ROOT REQUIRED COMPONENTS Core RIO Tree Hist)
include(${ROOT_USE_FILE})

add_executable(geant_plate
  src/main.cc
  src/DetectorConstruction.cc
  src/ActionInitialization.cc
  src/PrimaryGeneratorAction.cc
  src/RunAction.cc
  src/EventAction.cc
  src/SteppingAction.cc
  src/RootIO.cc
  src/Wide_layers.cc
  src/Thin_layers.cc
  src/PrimaryGeneratorMessenger.cc
  src/DetectorMessenger.cc
)

target_include_directories(geant_plate PRIVATE
  ${Geant4_INCLUDE_DIRS}
  ${ROOT_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(geant_plate PRIVATE
  ${Geant4_LIBRARIES}
  ${ROOT_LIBRARIES}
)
