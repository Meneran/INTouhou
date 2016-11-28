CXX:=clang++
LDXX:=$(CXX)
CXXFLAGS+=-Wall -Wextra -Wpedantic -std=c++14
LDLIBS+=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

LINT:=cpplint
LINTFLAGS+=--extensions=hpp,cpp --filter=-legal/copyright,-runtime/int,-runtime/explicit,-runtime/references


BINDIR:=$(CURDIR)/bin
BUILDDIR:=$(CURDIR)/build
SRCDIR:=$(CURDIR)/src
HEADERSDIR:=$(CURDIR)/src
TESTSDIR:=$(CURDIR)/gtest
DOCDIR:=$(CURDIR)/doc

DEBUGDIR:=$(BUILDDIR)/debug
RELEASEDIR:=$(BUILDDIR)/release
TESTINGDIR:=$(BUILDDIR)/tests

SRC:=$(wildcard $(SRCDIR)/*.cpp)
TESTS_SRC:=$(wildcard $(TESTSDIR)/*.cpp)
INCLUDE:=$(wildcard $(SRCDIR)/*.hpp)
DEBUGOBJS:=$(patsubst $(SRCDIR)/%.cpp,$(DEBUGDIR)/%.o,$(SRC))
RELEASEOBJS:=$(patsubst $(SRCDIR)/%.cpp,$(RELEASEDIR)/%.o,$(SRC))
TESTINGOBJS:= $(filter-out $(DEBUGDIR)/main.o, $(DEBUGOBJS)) $(patsubst $(TESTSDIR)/%.cpp, $(TESTINGDIR)/%.o, $(TESTS_SRC))

EXECNAME:=INTouhou
TESTSNAME:=runtests

debug: CXXFLAGS+=-g
debug: $(DEBUGOBJS)
	@mkdir -p $(BINDIR)
	@printf "\033[0;32m"
	@printf "Creating $(EXECNAME) (debug) binary file in: $(BINDIR)\n"
	@printf "\033[0m"
	@$(LDXX) $(CXXFLAGS) -o $(BINDIR)/$(EXECNAME) $^ $(LDLIBS)

release: CXXFLAGS+=-DNDEBUG
release: $(RELEASEOBJS)
	@mkdir -p $(BINDIR)
	@printf "\033[0;32m"
	@printf "Creating $(EXECNAME) (release) binary file in: $(BINDIR)\n"
	@printf "\033[0m"
	@$(LDXX) $(CXXFLAGS) -o $(BINDIR)/$(EXECNAME) $^ $(LDLIBS)

tests: LDLIBS+=-lgtest
tests: $(TESTINGOBJS) $(filter-out $(DEBUGDIR)/main.o,  $(DEBUGOBJS))
	@mkdir -p $(BINDIR)
	@printf "\033[0;32m"
	@printf "Creating $(TESTSNAME) binary file in: $(BINDIR)\n"
	@printf "\033[0m"
	@$(LDXX) $(CXXFLAGS) -o $(BINDIR)/${TESTSNAME} $^ $(LDLIBS)

doc:
	@printf "\033[0;34m"
	@printf "Generating Documentation\n"
	@doxygen $(DOCDIR)/doxygen.cfg
	@printf "\033[0m"
.PHONY: doc

lint:
	@printf "\033[0;36m"
	@$(LINT) $(LINTFLAGS) $(SRC) $(INCLUDE) $(TESTS_SRC) | true
	@printf "\033[0m"
.PHONY: lint

clean:
	@printf "\033[0;33m"
	@printf "Cleaning build directory\n"
	@printf "\033[0m"
	@rm -rf $(BUILDDIR) 2>/dev/null
.PHONY: clean

mrproper: clean
	@printf "\033[0;33m"
	@printf "Cleaning bin directory\n"
	@printf "\033[0m"
	@rm -rf $(BINDIR) 2> /dev/null
	@printf "\033[0;33m"
	@printf "Cleaning doc directory\n"
	@printf "\033[0m"
	@rm -rf $(DOCDIR)/{html,latex} 2> /dev/null
.PHONY: mrproper

$(DEBUGDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(DEBUGDIR)
	@printf "\033[0;35m"
	@printf "Creating object file $(@F)\n"
	@printf "\033[0m"
	@$(CXX) -I$(HEADERSDIR) $(CXXFLAGS) -c $< -o $@

$(RELEASEDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(RELEASEDIR)
	@printf "\033[0;35m"
	@printf "Creating object file $(@F)\n"
	@printf "\033[0m"
	@$(CXX) -I$(HEADERSDIR) $(CXXFLAGS) -c $< -o $@

$(TESTINGDIR)/%.o: $(TESTSDIR)/%.cpp
	@mkdir -p $(TESTINGDIR)
	@printf "\033[0;35m"
	@printf "Creating object file $(@F)\n"
	@printf "\033[0m"
	@$(CXX) -I$(HEADERSDIR) $(CXXFLAGS) -c $< -o $@

