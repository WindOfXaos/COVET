# Source files
SRCS += $(wildcard vendor/imgui/*.cpp) \
					vendor/stb/stb_image.cpp \
					vendor/glad/glad.cpp \
# Should be glad.c but we can get away with it for the sake of simplicity

# Header files
INCDIR += -Ivendor -Ivendor/GLFW/include

# Rule for building cross-platform GLFW static library:
GLFW: lib/libglfw3.a
	@echo "GLFW build complete"

lib/libglfw3.a:
	@echo " Building GLFW..."
	cd vendor/GLFW && \
	rm -rf CMakeCache.txt CMakeFiles && \
	cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_INSTALL=OFF . -G "Unix Makefiles" && \
	$(MAKE) && \
	mv src/libglfw3.a ../../lib/libglfw3.a
