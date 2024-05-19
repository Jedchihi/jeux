game: main.o enigme.o minimap.o perso.o background.o texte.o tictactoe.o entity.o
	cc main.o enigme.o minimap.o perso.o background.o texte.o tictactoe.o entity.o -o game -lSDL -lSDL_gfx -lSDL_image -lSDL_ttf -lSDL_mixer -lm

main.o: main.c
	cc -c main.c -o main.o

enigme.o: enigme.c
	cc -c enigme.c -o enigme.o

minimap.o: minimap.c
	cc -c minimap.c -o minimap.o

perso.o: perso.c
	cc -c perso.c -o perso.o

background.o: background.c
	cc -c background.c -o background.o -g

texte.o: texte.c
	cc -c texte.c -o texte.o -g 

tictactoe.o: tictactoe.c
	cc -c tictactoe.c -o tictactoe.o -g

entity.o: entity.c
	cc -c entity.c -o entity.o
