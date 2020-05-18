add_executable(creational_patterns test.cpp
    builder.h
    factory_method.h
    abstract_factory.h
    prototype.h
    singleton.h)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(creational_patterns PUBLIC OpenMP::OpenMP_CXX)
endif()
