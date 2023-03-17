#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

/*in bytecode format each instruction has a one-byte operation code(opcode). This number control what king of instruction we're dealing with -add, subtract, lookup variable etc.*/

typedef enum {
  OP_CONSTANT,
  OP_RETURN,

} OpCode;

typedef struct{
  //how many of those allocated entries are aactually in use.
  int count;
  //number of elements in the array we have allocated.
  int capacity;
  //pointer to the array.
  uint8_t* code;
  //array of lines
  char* lines;
  //constant pool
  ValueArray constants;

  int lastLine;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);
#endif
