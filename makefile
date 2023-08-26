# Define the compiler
CC = gcc

# Define the flags for the compiler
CFLAGS = -Wall -g

# Define the folder for the source files
SRC_DIR = src

# Define the folder for the object files
OBJ_DIR = objects

# Define the object files
SERVER_OBJ = $(OBJ_DIR)/server.o
CLIENT_OBJ = $(OBJ_DIR)/client.o
KMEANS_OBJ = $(OBJ_DIR)/kmeans.o
MATRIX_OBJ = $(OBJ_DIR)/matrix.o

# Define the target executable files
SERVER_EXE = server
CLIENT_EXE = client

# Define the rule for building the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Define the rule for building the server executable
$(SERVER_EXE): $(SERVER_OBJ) $(KMEANS_OBJ) $(MATRIX_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Define the rule for building the client executable
$(CLIENT_EXE): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Define the rule for cleaning the object files and executables
clean:
	rm -f $(OBJ_DIR)/*.o $(SERVER_EXE) $(CLIENT_EXE)

# Define the default rule
all: $(SERVER_EXE) $(CLIENT_EXE)
