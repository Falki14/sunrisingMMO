TARGET  := sunrisingServerCore

CFILES  := $(wildcard source/*.c)
OFILES  := $(patsubst source/%,build.linux/%,$(CFILES:.c=.o))

CFLAGS  := -g -Wall -Iinclude
LDFLAGS :=
OBJLIBS := -lpthread

.PHONY: all clean

all: build.linux $(TARGET)

build.linux:
	@mkdir build.linux/

$(TARGET): $(OFILES)
	@$(CC) -o $@ $^ $(LDFLAGS)  $(OBJLIBS)

$(OFILES): build.linux/%.o : source/%.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(OBJLIBS)

clean:
	@$(RM) build.linux/