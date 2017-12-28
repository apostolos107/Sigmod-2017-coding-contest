SOURCE = ngrams.c trie.c hash_table.c trie_node.c tools.c heap.c  bloom_filter.c heap_hash.c job_scheduler.c job.c
OBJS = ngrams.o trie.o hash_table.o trie_node.o tools.o heap.o  bloom_filter.o heap_hash.o job_scheduler.o job.o
EXEC =NGrams.exe
CC	= gcc
FLAGS   = -g -c -O2
FILES_FOLDER = test_files
all: clean $(EXEC)

test_file: all
	time ./$(EXEC) -i $(FILES_FOLDER)/$(file).init -q $(FILES_FOLDER)/$(file).work > out << -EOF
	diff ./out $(FILES_FOLDER)/$(file).result


$(EXEC): $(OBJS)
	$(CC) -g $? -o $@

ngrams.o: ngrams.c
	$(CC) $(FLAGS) $?

hash_table.o: hash_table.c
	$(CC) $(FLAGS) $?

bloom_filter.o: bloom_filter.c
	$(CC) $(FLAGS) $?

trie.o: trie.c
	$(CC) $(FLAGS) $?

trie_node.o: trie_node.c
	$(CC) $(FLAGS) $?

tools.o: tools.c
	$(CC) $(FLAGS) $?

heap.o: heap.c
	$(CC) $(FLAGS) $?

job_scheduler.o: job_scheduler.c
	$(CC) $(FLAGS) $?

job.o: job.c
	$(CC) $(FLAGS) $?

test: test_entry
	./test_entry

test_entry: trie.o hash_table.o trie_node.o tools.o heap.o murmur3.o bloom_filter.o heap_hash.o test_entry.o
	$(CC) -o $@ $?

test_entry.o: test_entry.c
	$(CC) $(FLAGS) $?

clean:
	rm -rf $(EXEC) $(OBJS)
