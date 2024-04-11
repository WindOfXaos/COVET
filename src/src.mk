# Source files
SRCS += $(wildcard src/*.cpp) \
				$(wildcard src/*/*.cpp) \
				$(wildcard src/*/*/*.cpp) \

# Header files
INCDIR += -Isrc
