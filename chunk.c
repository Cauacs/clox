#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "chunk.h"

void initChunk(Chunk *chunk){
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code=NULL;

  //Encoded string
  chunk->lines = NULL;
  //Line of the last bytecode
  chunk->lastLine= 1;
  //last used index of the string
  chunk->lastIndex = -1;

  chunk->lastPrintedLine = 0;

  //init the constants array
  initValueArray(&chunk->constants);
}
void writeLine(int line, Chunk* chunk) {
  //empty string(first opcode)
  if(chunk->lastIndex == -1){
    chunk->lines[0] = '1';
    chunk->lastIndex = 0;
    return;
  }
  //changed line
  if(line != chunk->lastLine){
    chunk->lines[chunk->lastIndex + 1] = 'L';
    chunk->lines[chunk->lastIndex + 2] = '1';
    chunk->lastIndex += 2;
    chunk->lastLine++;
    return;
  }
  //same line
  else if(line == chunk->lastLine){
    int opCount = chunk->lines[chunk->lastIndex] - '0';
    opCount++;
    chunk->lines[chunk->lastIndex] = opCount + '0';
  }
}

int getLine(Chunk* chunk, int offset){
  int goal = offset + 1;
  int count = 0;
  int i = 0;
  int line = 1;
  //convert to char
  do {
    if(chunk->lines[i] != 'L'){
      count += chunk->lines[i] - '0';
    }
    else if(chunk->lines[i] == 'L'){
      line++;
    }
    i++;
  }while(count < goal);

  return line;
}

void writeChunk(Chunk *chunk , uint8_t byte, int line){
  if(chunk->capacity < chunk->count + 1){
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    chunk->lines = GROW_ARRAY(char, chunk->lines, oldCapacity, chunk->capacity);
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


