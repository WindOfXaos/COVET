# Unit Test:
BUILDDIR = build
TEST = test
TESTSRCS := $(wildcard $(TEST)/*.cpp)
TESTOBJS := $(TESTSRCS:%.cpp=$(BUILDDIR)/%.o)
