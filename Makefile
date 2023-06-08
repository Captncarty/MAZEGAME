CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -framework OpenGL -lGL -lSDL2 -lglut

SRCDIR = src
OBJDIR = build

# List all your source files here
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/mazegame: $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o build/mazegame

