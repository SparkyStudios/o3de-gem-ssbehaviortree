if (CMAKE_BUILD_TYPE EQUAL "release")
    set(BEHAVIORTREECPP_LIBS ${BASE_PATH}/osx/lib/behaviortree_cpp_v3.lib)
else()
    set(BEHAVIORTREECPP_LIBS ${BASE_PATH}/osx/lib/behaviortree_cpp_v3d.lib)
endif()
