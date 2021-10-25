CXX = gcc
CC = $(CXX)
#-ftest-coverage -fprofile-arcs -lgcov 
CFLAGS = -O2 -Werror -Wall -Wextra -Wpedantic -std=c99 -lm -lgmp \
	-fno-asm -g -s -std=c11 \
	-Wno-format-nonliteral \
	-Wformat=2 -Wformat-security \
	-Wnull-dereference -Wstack-protector -Wtrampolines -Wvla \
	-Warray-bounds=2 \
	-Wtraditional-conversion -Wshift-overflow=2 -Wcast-qual \
	-Wconversion -Wlogical-op -Wduplicated-cond \
	-Wformat-signedness -Wshadow -Wstrict-overflow=4 \
	-Wundef -Wstrict-prototypes -Wswitch-default -Wswitch-enum \
	-Wstack-usage=1000000 \
	-D_FORTIFY_SOURCE=2 \
	#-fstack-protector-strong -fPIE -fsanitize=address \
	-fsanitize=leak -fno-omit-frame-pointer -fsanitize=undefined \
	-fsanitize=bounds-strict -fsanitize=float-divide-by-zero \
	-fsanitize=float-cast-overflow

SRC_FILES = $(wildcard src/*.c) $(wildcard src/**/*.c)
TST_FILES = $(wildcard test/*.c) $(wildcard test/**/*.c) $(wildcard test/**/**/*.c)
TO_TEST_FILES = $(filter-out src/main.c, $(SRC_FILES))

OBJECTS = $(SRC_FILES:%.c=%.o)
OBJECTSCOVO = $(SRC_FILES:%.c=%.gcno)
OBJECTSCOVA = $(SRC_FILES:%.c=%.gcda)
OBJECTS_TO_TEST = $(TO_TEST_FILES:%.c=%.o)
OBJECTS_TEST = $(TST_FILES:%.c=%.o)
TARGET = surfaces
TARGET_TEST = surfaces_test

.PHONY: all
	all: $(TARGET) $(TARGET_TEST)

$(TARGET): $(OBJECTS)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS)
	rm -rf $(TARGET) $(OBJECTSCOVO)
	rm -rf $(TARGET) $(OBJECTSCOVA)

.PHONY: trace
trace:
	valgrind --tool=drd --show-stack-usage=yes ./$(TARGET)

.PHONY: profile
profile:
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes ./$(TARGET)

.PHONY: debug
debug:
	gdb ./$(TARGET)

.PHONY: doc
doc:
	doxygen doc/surfaces.conf

.PHONY: cleandoc
cleandoc:
	rm -rf doc/html

.PHONY: check
check:
	cppcheck --check-config --enable=all --std=c99 --suppress=missingIncludeSystem ./src -I ./src

.PHONY: test
test:$(OBJECTS_TEST) 
	$(CXX) $(OBJECTS_TO_TEST) $(OBJECTS_TEST) $(CFLAGS) -lcunit -o $(TARGET_TEST)

.PHONY: cleantest
cleantest:
	rm -rf $(TARGET_TEST) $(OBJECTS_TEST)	
	