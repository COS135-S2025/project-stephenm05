# rtb links our three .o files to the rtb object to run
rtb: card.o player.o deck.o main.o
	gcc $^ -o $@

# beginning of individual file compilation

# compiles card.c
card.o: card.c card.h
	gcc -c $< -o $@

# compiles player.c
player.o: player.c player.h card.h
	gcc -c $< -o $@

# compiles deck.c
deck.o: deck.c deck.h card.h
	gcc -c $< -o $@

# compiles main.c
main.o: main.c deck.h player.h card.h
	gcc -c $< -o $@

# cleans up files created during compilation when explicitly run
clean: 
	rm -f rtb
	rm -f *.o