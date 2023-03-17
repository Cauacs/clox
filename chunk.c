#include <stdlib.h>

#include "memory.h"
#include "chunk.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void initChunk(Chunk *chunk){
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code=NULL;
  chunk->lines = "";
  chunk->lastLine= 1;
  //init the constants array
  initValueArray(&chunk->constants);
}
void writeLine(int line, Chunk* chunk) {
  int last = strlen(chunk->lines) - 1;
  //empty string(first opcode)
  if(last == -1){
    chunk->lines = "1";
    return;
  }
  //changed line
  if(line != chunk->lastLine){
    strcat(chunk->lines, "L1");
    chunk->lastLine++;
    return;
  }
  //same line
  else if(line == chunk->lastLine){
    int opCount = chunk->lines[last] - '0';
    opCount++;
   chunk->lines[last] = opCount + '0';
  }
 }


void writeChunk(Chunk *chunk , uint8_t byte, int line){
  if(chunk->capacity < chunk->count + 1){
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    //chunk->lines = GROW_ARRAY(char, chunk->lines, oldCapacity, chunk->capacity);
  }
  writeLine(line, chunk);
  chunk->code[chunk->count] = byte;
  // chunk->lines[chunk->count] = line;
  chunk->count++;
}

void freeChunk(Chunk *chunk){
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

//add a constant to the array of constants
//return the index where the constant was appended
int addConstant(Chunk* chunk, Value value){
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

