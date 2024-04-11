# Source files
SRCS += $(wildcard vendor/imgui/*.cpp) \
					vendor/stb/stb_image.cpp \
					vendor/glad/glad.cpp \
# Should be glad.c but we can get away with it for the sake of simplicity

# Header files
INCDIR += -Ivendor
