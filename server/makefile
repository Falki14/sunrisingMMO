TARGET  := sunrisingServerCore

CFILES  := $(wildcard source/*.cpp)
OFILES  := $(patsubst source/%,build.linux/%,$(CFILES:.cpp=.o))

CFLAGS  := -g -Wall -Iinclude
LDFLAGS :=
OBJLIBS := -lpthread

.PHONY: all clean

all: build.linux $(TARGET)

build.linux:
	@mkdir build.linux/

$(TARGET): $(OFILES)
	@$(CXX) -o $@ $^ $(LDFLAGS)  $(OBJLIBS)

$(OFILES): build.linux/%.o : source/%.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(OBJLIBS)

clean:
	@$(RM) build.linux/