cmake_minimum_required(VERSION 3.10)
project(CountryApp)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем текущую папку в пути поиска заголовочных файлов
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Название исполняемого файла и исходники
add_executable(CountryApp countryApp.cpp Country.cpp)