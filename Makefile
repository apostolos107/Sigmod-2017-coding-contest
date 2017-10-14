SOURCE = ngrams.c trie.c tools.c
OBJS = ngrams.o trie.o tools.o
EXEC =NGrams.exe
CC	= gcc
FLAGS   = -g -c

# All: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) -g $? -o $@

ngrams.o: ngrams.c
	$(CC) $(FLAGS) $?

trie.o: trie.c
	$(CC) $(FLAGS) $?

tools.o: tools.c
	$(CC) $(FLAGS) $?

clean:
	rm -rf $(EXEC) $(OBJS)
