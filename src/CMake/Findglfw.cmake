    find_library( GLFW_LIBRARY
            NAMES
                glfw3 glfw
            PATHS
                ${GLFW_LOCATION}/lib
                $ENV{GLFW_LOCATION}/lib
                /usr/lib64
                /usr/lib
                /usr/local/lib64
                /usr/local/lib
                NO_DEFAULT_PATH
                DOC "The GLFW library"
            )
