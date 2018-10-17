game : single_play.o map.o setting.o rank.o multi_play.o
	gcc -o game single_play.o multi_play.o map.o rank.o setting.o -lncurses
single_play.o : single_play.c game.h
	gcc -c single_play.c
multi_play.o : multi_play.c game.h
	gcc -c multi_play.c
map.o : map.c game.h
	gcc -c map.c
rank.o : rank.c game.h
	gcc -c rank.c
setting.o : setting.c game.h
	gcc -c setting.c
clean:
	rm -rf single_play.o multi_play.o map.o rank.o setting.o
	