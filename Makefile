ifdef DEBUG
  ifeq ($(DEBUG), 1)
	PRE_CFLAGS = -g -O0 -DDEBUG=$(DEBUG)
  else
	PRE_CFLAGS = -O3
  endif
else 
  PRE_CFLAGS = -O3
endif

CC          = g++
LD          = g++
CFLAG       = -Wall -Wextra $(PRE_CFLAGS)
PROG_NAME   = simket

SRC_DIR     = ./src
BUILD_DIR   = ./build
BIN_DIR     = .
SRC_LIST = main.cpp \
					 QReg.cpp

CFLAG+=-I$(SRC_DIR)/submodules/eigen

SRC_LIST_TMP = $(patsubst %,./%,$(SRC_LIST))
SRC_FULL_LIST = $(patsubst %,$(SRC_DIR)/%,$(SRC_LIST))
OBJ_LIST = $(subst .cpp,.o,$(SRC_LIST_TMP))
OBJ_FULL_LIST = $(subst ./,$(BUILD_DIR)/,$(OBJ_LIST))
DEP_FILES = $(OBJ_FULL_LIST:%.o=%.d)

default: $(PROG_NAME)

$(PROG_NAME): libsimket.a
	$(LD) libsimket.a -o $(BIN_DIR)/$@

libsimket.a: $(OBJ_FULL_LIST)
	$(AR) rcs $@ $(OBJ_FULL_LIST)

$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp
	$(eval obj_file := $(subst .d,.o,$@))
	@mkdir -p $(@D) || true
	$(CC) $(CFLAG) -MM $< -MT $(obj_file) -MF $@ 

-include $(DEP_FILES)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D) || true
	$(CC) $(CFLAG) -o $(BUILD_DIR)/$*.o -c $<


.PHONY: clean 
clean:
	-rm -f $(BIN_DIR)/$(PROG_NAME) $(BUILD_DIR)/*
