#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FPS 0

#define CELL_SIZE 5 
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)
#define AMOUNT_OF_CELLS (GRID_WIDTH * GRID_HEIGHT)

typedef struct Cell{
  int id;
  Vector2 pos;
  bool active;
}Cell;

typedef struct Ant{
  Vector2 pos;
  int direction;
}Ant;

typedef enum Direction{
  UP,
  RIGHT,
  DOWN,
  LEFT
}Direction;

Cell createCell(int x, int y, int id);
void initCells(Cell *cells);
void drawCells(Cell *cells);
Ant createAnt();
void moveAnt(Ant *ant, Cell *cells);

int main(){ 
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Langton's ant");
  SetTargetFPS(FPS);

  Cell *cells = malloc(sizeof(Cell) * AMOUNT_OF_CELLS);
  initCells(cells);

  Ant ant = createAnt(cells);

  while(!WindowShouldClose()){
    BeginDrawing();

      ClearBackground(BLACK);

      drawCells(cells);

      moveAnt(&ant, cells);

    EndDrawing();
  }
  free(cells);
  CloseWindow();
  return 0;
}

Cell createCell(int x, int y, int id){
  Cell cell;
  cell.id = id;
  cell.pos = (Vector2){ x, y };
  cell.active = false;
  return cell;
}

void initCells(Cell *cells){
  int index = 0;
  for(int y = 0; y < GRID_HEIGHT; y++){
    for(int x = 0; x < GRID_WIDTH; x++){
      cells[index] = createCell(x * CELL_SIZE, y * CELL_SIZE, index);
      index++;
    }
  }
  cells[(AMOUNT_OF_CELLS / 2) + (GRID_WIDTH / 2 - 1)].active = true;
}

void drawCells(Cell *cells){
  for(int i = 0; i < AMOUNT_OF_CELLS; i++){
    Color colour = cells[i].active ? BLACK : WHITE;
    DrawRectangle(cells[i].pos.x, cells[i].pos.y, CELL_SIZE, CELL_SIZE, colour);
  }
}

Ant createAnt(Cell *cells){
  Ant ant;
  ant.pos = (Vector2){ cells[(AMOUNT_OF_CELLS / 2) + (GRID_WIDTH / 2 - 1)].pos.x, cells[(AMOUNT_OF_CELLS / 2) + (GRID_WIDTH / 2 - 1)].pos.y };
  ant.direction = UP;
  return ant;
}

void moveAnt(Ant *ant, Cell *cells){
  int x = ant->pos.x / CELL_SIZE;
  int y = ant->pos.y / CELL_SIZE;
  int index = y * GRID_WIDTH + x;
  cells[index].active = !cells[index].active;
  if (cells[index].active) {
    ant->direction = (ant->direction + 3) % 4;
  } else {
    ant->direction = (ant->direction + 1) % 4;
  }
  switch (ant->direction) {
    case UP:
      y = (y - 1 + GRID_HEIGHT) % GRID_HEIGHT; 
      break;
    case RIGHT: 
      x = (x + 1) % GRID_WIDTH; 
      break;
    case DOWN:  
      y = (y + 1) % GRID_HEIGHT; 
      break;
    case LEFT:  
      x = (x - 1 + GRID_WIDTH) % GRID_WIDTH; 
      break;
  }
  ant->pos.x = x * CELL_SIZE;
  ant->pos.y = y * CELL_SIZE;
}


