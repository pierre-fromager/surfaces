CXX = gcc
CC = $(CXX)
#-ftest-coverage -fprofile-arcs -lgcov 
CFLAGS = -O2 -Werror -Wall -Wextra -Wpedantic -std=c99 \
	-lm -lgmp -lmpfr \
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
	#-D_FORTIFY_SOURCE=2 \
	-fstack-protector-strong -fPIE -fsanitize=address \
	-fsanitize=leak -fno-omit-frame-pointer -fsanitize=undefined \
	-fsanitize=bounds-strict -fsanitize=float-divide-by-zero \
	-fsanitize=float-cast-overflow

DOC = doc
SRC = src
TST = test
SRC_LIB_FILE = $(SRC)/libpolysurf
SRC_FILES = $(wildcard $(SRC)/*.c) $(wildcard$(SRC)/**/*.c)
TST_FILES = $(wildcard $(TST)/*.c) $(wildcard $(TST)/**/*.c) $(wildcard $(TST)/**/**/*.c)
ALL_SRC_BUT_MAIN = $(filter-out $(SRC)/main.c, $(SRC_FILES))

OBJECTS = $(SRC_FILES:%.c=%.o)
#OBJECTSCOVO = $(SRC_FILES:%.c=%.gcno)
#OBJECTSCOVA = $(SRC_FILES:%.c=%.gcda)
OBJECTS_TO_TEST = $(ALL_SRC_BUT_MAIN:%.c=%.o)
OBJECTS_TO_LIB = $(ALL_SRC_BUT_MAIN:%.c=%.o)
OBJECTS_TEST = $(TST_FILES:%.c=%.o)
TARGET = surfaces
TARGET_LIB = libpolysurf
TARGET_TEST = surfaces_test

.PHONY: all
	all: $(TARGET) $(TARGET_TEST)

$(TARGET): $(OBJECTS)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS)  
	#rm $(TARGET_TEST) 
	rm $(TARGET_LIB).so.1.0  	

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
	doxygen $(DOC)/surfaces.conf

.PHONY: cleandoc
cleandoc:
	rm -rf $(DOC)/html

.PHONY: check
check:
	cppcheck --check-config --enable=all --std=c99 --suppress=missingIncludeSystem $(SRC) -I $(SRC)

.PHONY: test
test:$(OBJECTS_TEST) 
	$(CXX) $(OBJECTS_TO_TEST) $(OBJECTS_TEST) $(CFLAGS) -lcunit -o $(TARGET_TEST)

.PHONY: cleantest
cleantest:
	rm -rf $(TARGET_TEST) $(OBJECTS_TEST)	

.PHONY: lib
lib:
	$(CXX) -fPIC -fvisibility=hidden -shared -Wl,-soname,$(TARGET_LIB).so.1 \
		$(CFLAGS) -o $(TARGET_LIB).so.1.0 $(SRC)/$(TARGET_LIB).o

# ldconfig -v 2>/dev/null | grep -v ^$'\t'
# http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html
# https://docencia.ac.upc.edu/FIB/USO/Bibliografia/unix-c-libraries.html
	