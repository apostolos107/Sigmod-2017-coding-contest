SOURCE = ngrams.c trie.c trie_node.c tools.c
OBJS = ngrams.o trie.o trie_node.o tools.o
EXEC =NGrams.exe
CC	= gcc
FLAGS   = -g -c

all: clean $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -g $? -o $@

ngrams.o: ngrams.c
	$(CC) $(FLAGS) $?

trie.o: trie.c
	$(CC) $(FLAGS) $?

trie_node.o: trie_node.c
	$(CC) $(FLAGS) $?

tools.o: tools.c
	$(CC) $(FLAGS) $?

clean:
	rm -rf $(EXEC) $(OBJS)
