#####################################
## Parallel & Distributed Systems  ##
## Project 4                       ##
##                                 ##
## Ⓒ 2021 K. Chatzis              ##
## kachatzis <at> ece.auth.gr      ##
#####################################

CC := mpic++

SRC_DIR := ./src

OBJ_DIR := ./obj

CFLAGS := -Wall -fopenmp -lm -O3 -g -Iinclude -pg
# CFLAGS := -Wall -fopenmp -lm -O0 -fstack-protector-all -fstrong-eval-order=some -g -Iinclude

TARGET := debug

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) ./*/*.o
	
.PHONY: all clean