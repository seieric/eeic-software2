CC = gcc

helloworld1: calc_magicnumber
	$(CC) -Wall -o $@ $@.c

calc_magicnumber:
	$(CC) -Wall -o $@ $@.c

.PHONY: clean
clean:
	rm -f helloworld1 calc_magicnumber