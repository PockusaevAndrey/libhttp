

set(DEB_PREFIX "BUILD")
set(TYPES BIN SBIN LIB INCLUDE SYSCONF SHAREDSTATE LOCALSTATE RUNSTATE DATA INFO LOCALE MAN DOC)

macro(check_args)
    foreach (ARG ${ARGN})
        if ("${${ARG}}" STREQUAL "")
            string(REPLACE "${DEB_PREFIX}_" "" output ${ARG})
            message(SEND_ERROR "not found ${output} in arguments")
        endif ()
    endforeach ()
endmacro()

macro(deb_dependence)
    set(options)
    set(oneValueArgs TARGET DIRECTORY MODULE TYPE FILE)
    set(multiValueArgs )
    cmake_parse_arguments(DEPEND "${options}" "${oneValueArgs}" "multiValueArgs" ${ARGN})
    if (EXISTS DEPEND_TYPE AND NOT DEPEND_TYPE IN_LIST TYPES)
        message(FATAL_ERROR "INVALID dependence type")
    endif ()
    if (DEFINED DEPEND_DIRECTORY)
        install(DIRECTORY ${DEPEND_DIRECTORY} TYPE ${DEPEND_TYPE} COMPONENT ${DEPEND_TARGET})
    elseif (DEFINED DEPEND_FILE)
        install(FILES ${DEPEND_FILE} TYPE ${DEPEND_TYPE} COMPONENT ${DEPEND_TARGET})
    elseif (DEFINED DEPEND_MODULE)
        string(REGEX MATCH "\/[a-zA-Z]+$" A ${DEPEND_MODULE})
        string(REPLACE "/" "" A ${A})
        set(DEPEND_MODULE${A}_INCLUDES ${DEPEND_MODULE}/include/)
        file(GLOB DEPEND_MODULE${A}_FILES "${DEPEND_MODULE}/*.a.*" "${DEPEND_MODULE}/*.so.*")
        install(DIRECTORY ${DEPEND_MODULE${A}_INCLUDES} TYPE INCLUDE COMPONENT ${DEPEND_TARGET})
        install(FILES ${DEPEND_MODULE${A}_FILES} TYPE LIB COMPONENT ${DEPEND_TARGET})
    else ()
        message(FATAL_ERROR "No found type. please set DIRECTORY, FILES or MODULE")
    endif ()
endmacro()

macro(build_deb)
    set(options VERBATIM)
    set(oneValueArgs TARGET NAME VERSION SUMMARY VENDOR CONTACT MAINTAINER)
    set(multiValueArgs LIB_DEPENDS)
    cmake_parse_arguments(${DEB_PREFIX} "${options}" "${oneValueArgs}"
            "${multiValueArgs}" ${ARGN})

    check_args(
            BUILD_TARGET
            BUILD_NAME
            BUILD_VERSION
            BUILD_SUMMARY
            BUILD_VENDOR
            BUILD_MAINTAINER
            BUILD_CONTACT
    )
    string(REPLACE ";" ", " PREDEPENDS "${BUILD_LIB_DEPENDS}")

    set(CPACK_PACKAGE_NAME ${BUILD_NAME}
            CACHE STRING "The resulting package name"
            )

    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${BUILD_SUMMARY}
            CACHE STRING "Package description for the package metadata"
            )

    set(CPACK_VERBATIM_VARIABLES ${VERBATIM})
    set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
    set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/deb")
    set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
    set(CPACK_PACKAGE_CONTACT ${BUILD_CONTACT})
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${BUILD_MAINTAINER})
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS YES)
    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS)
    set(CPACK_DEBIAN_FILE_NAME "${BUILD_NAME}_${BUILD_VERSION}.deb")
    set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
    set(CPACK_DEB_COMPONENT_INSTALL YES)
    set(CPACK_DEBIAN_PACKAGE_PREDEPENDS ${PREDEPENDS})
    include(CPack)
    install(
            TARGETS ${BUILD_TARGET}
            EXPORT "${BUILD_NAME}Targets"
            COMPONENT ${BUILD_NAME}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND cpack -G DEB VERBATIM)
endmacro()
