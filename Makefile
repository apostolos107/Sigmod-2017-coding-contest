SOURCE = trie.c
OBJS = trie.o
EXEC =NGrams.exe
CC	= gcc
FLAGS   = -g -c

# All: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) -g $? -o $@

trie.o: trie.c
	$(CC) $(FLAGS) $?


clean:
	rm -rf $(EXEC) $(OBJS)
