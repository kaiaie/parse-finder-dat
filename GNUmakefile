# This Makefile uses order-only pre-requistites and functions 
# which AFAIK, only GNU Make currently supports. :-(
PROJECT:=parse-finder-dat
VERSION_FILE:=project.d/version
VERSION:=$(shell cat $(VERSION_FILE))
CCFLAGS_FILE:=project.d/builds/default/ccflags
CCFLAGS:=$(shell cat $(CCFLAGS_FILE))

# Where the source files are
SRC:=src

# Where we want working files created
# (Note: This directory is deleted by "make clean" so be careful!)
TMP:=tmp

# Where we want the output files created
# Everything gets copied here in a packaging-friendly structure
# (Note: This directory is deleted by "make clean" so be careful!)
OUT:=out

# The parser program itself
BIN:=$(OUT)/bin/$(PROJECT)

# The files the parser program needs...
BIN_SRC_FILES:=$(shell cat project.d/modules/prog/files)
# The corresponding object files...
BIN_OBJ_FILES:=$(BIN_SRC_FILES:.c=.o)
# ... and with the working path appended
BIN_OBJ_FILES_FULL:=$(foreach f, $(BIN_OBJ_FILES), $(TMP)/prog/$(f))
# The corresponding dependency files...
BIN_DEP_FILES:=$(BIN_SRC_FILES:.c=.d)
# ... and with the working path appended
BIN_DEP_FILES_FULL:=$(foreach f, $(BIN_DEP_FILES), $(TMP)/prog/$(f))

# The parser library that does most of the work
LIB:=$(OUT)/lib/lib$(PROJECT)-$(VERSION).a
# The include file that defines the library's interface
LIB_INCLUDE:=$(OUT)/include/$(shell cat project.d/modules/lib/include)

# The files the library needs...
LIB_SRC_FILES:=$(shell cat project.d/modules/lib/files)
# The corresponding object files...
LIB_OBJ_FILES:=$(LIB_SRC_FILES:.c=.o)
# ... and with the working path appended
LIB_OBJ_FILES_FULL:=$(foreach f, $(LIB_OBJ_FILES), $(TMP)/lib/$(f))
# The corresponding dependency files...
LIB_DEP_FILES:=$(LIB_SRC_FILES:.c=.d)
# ... and with the working path appended
LIB_DEP_FILES_FULL:=$(foreach f, $(LIB_DEP_FILES), $(TMP)/lib/$(f))


# The tester app (note: it goes in TMP because it's not part of the
# distribution)
TESTS:=$(TMP)/run-tests

# The files the parser program needs...
TESTS_SRC_FILES:=$(shell cat project.d/modules/tests/files)
# The corresponding object files...
TESTS_OBJ_FILES:=$(TESTS_SRC_FILES:.c=.o)
# ... and with the working path appended
TESTS_OBJ_FILES_FULL:=$(foreach f, $(TESTS_OBJ_FILES), $(TMP)/tests/$(f))
# The corresponding dependency files...
TESTS_DEP_FILES:=$(TESTS_SRC_FILES:.c=.d)
# ... and with the working path appended
TESTS_DEP_FILES_FULL:=$(foreach f, $(BIN_DEP_FILES), $(TMP)/prog/$(f))

.PHONY: all tests clean

# All build artefacts (note we don't build the tests as part of this)
all: $(BIN) $(LIB) $(LIB_INCLUDE)

# Builds the test harness (requires libtap)
tests: $(TESTS)

# Clears all build artifacts
clean:
	rm -rfv $(OUT) $(TMP)

# Build program
$(BIN): $(BIN_OBJ_FILES_FULL) $(LIB) | $(OUT)/ $(OUT)/bin/
	$(CC) -static -o $@ $(BIN_OBJ_FILES_FULL) -L$(OUT)/lib -l$(PROJECT)-$(VERSION)

$(TMP)/prog/main.o: $(SRC)/prog/main.c $(VERSION_FILE) $(CCFLAGS_FILE) | $(TMP)/ $(TMP)/prog/
	$(CC) $(CCFLAGS) -DPROJECT_VERSION=$(VERSION) -c $< -o $@

$(TMP)/prog/main.d: $(SRC)/prog/main.c | $(TMP)/ $(TMP)/prog/
	$(CC) $(CCFLAGS) -DPROJECT_VERSION=$(VERSION) -MM $< -MT $(TMP)/prog/main.o -MF $@


# Build library
$(LIB): $(LIB_OBJ_FILES_FULL) | $(OUT)/ $(OUT)/lib/
	ar rcs $@ $^
	ranlib $@

$(TMP)/lib/parser.o: $(SRC)/lib/parser.c $(VERSION_FILE) $(CCFLAGS_FILE) | $(TMP)/ $(TMP)/lib/
	$(CC) $(CCFLAGS) -DPROJECT_VERSION=$(VERSION) -c $< -o $@

$(TMP)/lib/parser.d: $(SRC)/lib/parser.c | $(TMP)/ $(TMP)/lib/
	$(CC) $(CCFLAGS) -DPROJECT_VERSION=$(VERSION) -MM $< -MT $(TMP)/lib/parser.o -MF $@

$(LIB_INCLUDE): $(SRC)/lib/parser.h | $(OUT)/ $(OUT)/include/
	cp $< $@


# Build tests. Note: We don't link static because libtap only comes as a 
# shared lib
$(TESTS): $(TESTS_OBJ_FILES_FULL) $(LIB) | $(TMP)/
	$(CC) -o $@ $(TESTS_OBJ_FILES_FULL) -L$(OUT)/lib -l$(PROJECT)-$(VERSION) -ltap

$(TMP)/tests/testmain.o: $(SRC)/tests/testmain.c $(VERSION_FILE) $(CCFLAGS_FILE) | $(TMP)/ $(TMP)/tests/
	$(CC) $(CCFLAGS) -DPROJECT_VERSION=$(VERSION) -c $< -o $@

$(TMP)/tests/testmain.d: $(SRC)/tests/testmain.c | $(TMP)/ $(TMP)/tests/
	$(CC) $(CCFLAGS) -DPROJECT_VERSION=$(VERSION) -MM $< -MT $(TMP)/tests/testmain.o -MF $@


# Automatically-generated dependency files
-include $(BIN_DEP_FILES_FULL)
-include $(LIB_DEP_FILES_FULL)
-include $(TESTS_DEP_FILES_FULL)

# Create output directories
$(OUT)/ \
$(OUT)/bin/ \
$(OUT)/include/ \
$(OUT)/lib/ \
$(TMP)/ \
$(TMP)/prog/ \
$(TMP)/lib/ \
$(TMP)/tests/ :
	mkdir -p $@
