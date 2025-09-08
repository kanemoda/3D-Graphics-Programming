build:
	@echo "Compiling..."
	@gcc -Wall -std=c99 ./src/*.c -lSDL2 -lm -o renderer

run:
	@./renderer

clean:
	@echo "Cleaning up..."
	@rm renderer