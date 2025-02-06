CC = gcc                         # Compiler to use
CFLAGS = -Wall -g                # Compilation flags: all warnings & debug info
EXEC = game                      # Name of the executable file

# Source files
SRCS = main.c game.c stack.c move.c board.c 

# Header files
HEADERS = game.h                 

# Object files
OBJS = $(SRCS:.c=.o)             # Automatically generate object file names from source files

# Default target (compiles the project) + links object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)      

# Compile .c files into .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@   

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)         

# Full clean (additional cleanup for the executable)
fclean: clean
	rm -f $(EXEC)                

# Rebuild the project from scratch
re: fclean $(EXEC)

.PHONY: clean fclean re           # Declare phony targets to avoid conflicts with files
