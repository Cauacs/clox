#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]){
  Chunk chunk;
  initChunk(&chunk);

  //addConstant() return the index of the constant being added
  int constant = addConstant(&chunk, 1.2);
  //write the opcode
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);
  //write the constant index right after;
  writeChunk(&chunk, OP_RETURN, 1);
  writeChunk(&chunk, OP_RETURN, 2);
  writeChunk(&chunk, OP_RETURN, 2);
  writeChunk(&chunk, OP_RETURN, 3);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}
