CC = clang
CFLAGS = -Weverything -O3 -Wno-vla -lm
CDEVFLAGS = -Weverything -Wno-vla -ggdb3 -lm
CASMFLAGS = -Weverything -Wno-vla -lm -masm=intel -S
CTESTFLAGS = -Weverything -Wno-vla -lm
MAIN = main
TEST = test

SRCS = $(shell find ! -name "*_test.c" -name "*.c")
TESTSRCS = $(shell find ! -name "main.c" -name "*.c")

all: $(MAIN)
	@echo The program has been compiled succesfully.

$(MAIN): $(SRCS)
	$(CC) $(CFLAGS) -o $(MAIN) $(SRCS)

dev: $(MAIN)dev
	@echo The program has been compiled in dev succesfully.
	valgrind --leak-check=full ./$(MAIN)

$(MAIN)dev: $(SRCS)
	$(CC) $(CDEVFLAGS) -o $(MAIN) $(SRCS)

asm: $(MAIN)asm
	@echo The program has been compiled to asm succesfully.

$(MAIN)asm: $(SRCS)
	$(CC) $(CASMFLAGS) $(SRCS)

test: $(MAIN)test

$(MAIN)test: $(SRCS)
	$(CC) $(CTESTFLAGS) -o $(TEST) $(TESTSRCS)

clean:
	$(RM) $(MAIN)
