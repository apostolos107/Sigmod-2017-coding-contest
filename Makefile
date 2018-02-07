SOURCE = ngrams.c trie/trie.c hash_table/hash_table.c trie/trie_node.c tools.c heap/heap.c  bloom_filter/bloom_filter.c heap/heap_hash.c job_scheduler/job_scheduler.c job_scheduler/job.c
OBJS = ngrams.o trie.o hash_table.o trie_node.o tools.o heap.o  bloom_filter.o heap_hash.o job_scheduler.o job.o
EXEC = NGrams.exe
CC	= gcc
FLAGS   = -g -c -O2
FILES_FOLDER = test_files
all: clean $(EXEC)

test_file: all
	time ./$(EXEC) -i $(FILES_FOLDER)/$(file).init -q $(FILES_FOLDER)/$(file).work > out << -EOF
	diff ./out $(FILES_FOLDER)/$(file).result


$(EXEC): $(OBJS)
	$(CC) -g $? -o $@ -lpthread

ngrams.o: ngrams.c
	$(CC) $(FLAGS) $?

hash_table.o: hash_table/hash_table.c
	$(CC) $(FLAGS) $?

bloom_filter.o: bloom_filter/bloom_filter.c
	$(CC) $(FLAGS) $?

trie.o: trie/trie.c
	$(CC) $(FLAGS) $?

trie_node.o: trie/trie_node.c
	$(CC) $(FLAGS) $?

tools.o: tools.c
	$(CC) $(FLAGS) $?

heap.o: heap/heap.c
	$(CC) $(FLAGS) $?

job_scheduler.o: job_scheduler/job_scheduler.c
	$(CC) $(FLAGS) $?

job.o: job_scheduler/job.c
	$(CC) $(FLAGS) $?

heap_hash.o: heap/heap_hash.c
	$(CC) $(FLAGS) $?

test: test_entry
	./test_entry

test_entry: trie.o hash_table.o trie_node.o tools.o heap.o bloom_filter.o heap_hash.o test_entry.o
	$(CC) -o $@ $?

test_entry.o: test_entry.c
	$(CC) $(FLAGS) $?

clean:
	rm -rf $(EXEC) $(OBJS) out
