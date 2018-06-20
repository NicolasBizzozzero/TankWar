SRC_DIR = src
BIN_DIR = bin
COMPILE_FLAGS = -Wall

.PHONY: default all clean


all: main
	@mkdir -p $(BIN_DIR)


default: main
	@mkdir -p $(BIN_DIR)


main: aleatoire.o couleurs.o string.o case.o tank.o affichage.o grille.o jeu.o main.o
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/main $(BIN_DIR)/aleatoire.o $(BIN_DIR)/couleurs.o $(BIN_DIR)/string.o $(BIN_DIR)/case.o $(BIN_DIR)/tank.o $(BIN_DIR)/affichage.o $(BIN_DIR)/grille.o $(BIN_DIR)/jeu.o $(BIN_DIR)/main.o


aleatoire.o: $(SRC_DIR)/common/aleatoire.c
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/aleatoire.o -c $(SRC_DIR)/common/aleatoire.c $(COMPILE_FLAGS)


couleurs.o: $(SRC_DIR)/common/couleurs.c
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/couleurs.o -c $(SRC_DIR)/common/couleurs.c $(COMPILE_FLAGS)


string.o: $(SRC_DIR)/common/string.c
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/string.o -c $(SRC_DIR)/common/string.c $(COMPILE_FLAGS)


case.o: $(SRC_DIR)/core/case.c
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/case.o -c $(SRC_DIR)/core/case.c $(COMPILE_FLAGS)


tank.o: $(SRC_DIR)/core/tank.c $(SRC_DIR)/common/boolean.h $(SRC_DIR)/core/case.h
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/tank.o -c $(SRC_DIR)/core/tank.c $(COMPILE_FLAGS)


affichage.o: $(SRC_DIR)/core/affichage.c $(SRC_DIR)/common/couleurs.h $(SRC_DIR)/common/string.h
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/affichage.o -c $(SRC_DIR)/core/affichage.c $(COMPILE_FLAGS)


grille.o: $(SRC_DIR)/core/grille.c $(SRC_DIR)/common/couleurs.h $(SRC_DIR)/common/boolean.h $(SRC_DIR)/core/tank.h $(SRC_DIR)/core/case.h
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/grille.o -c $(SRC_DIR)/core/grille.c $(COMPILE_FLAGS)


jeu.o: $(SRC_DIR)/core/grille.h $(SRC_DIR)/common/boolean.h $(SRC_DIR)/common/couleurs.h $(SRC_DIR)/common/aleatoire.h
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/jeu.o -c $(SRC_DIR)/core/jeu.c $(COMPILE_FLAGS)


main.o: $(SRC_DIR)/main.c $(SRC_DIR)/common/aleatoire.h $(SRC_DIR)/core/grille.h $(SRC_DIR)/core/affichage.h $(SRC_DIR)/core/jeu.h $(SRC_DIR)/core/tank.h $(SRC_DIR)/common/boolean.h
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/main.o -c $(SRC_DIR)/main.c $(COMPILE_FLAGS)


clean:
	rm -rf $(BIN_DIR)/*
