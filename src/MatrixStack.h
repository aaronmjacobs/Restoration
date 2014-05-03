#ifndef MATRIX_STACK_H
#define MATRIX_STACK_H

#include "GLMIncludes.h"

#include <stack>

/**
 * Matrix stack, which allows for hierarchical drawing.
 */
class MatrixStack {
private:
   /**
    * The active matrix.
    */
   glm::mat4 currentMatrix;

   /**
    * The stack of matrices.
    */
   std::stack<glm::mat4> matrixStack;

public:
   /**
    * Constructs a matrix stack, setting the active matrix to the identity matrix.
    */
   MatrixStack();

   /**
    * Does cleanup.
    */
   virtual ~MatrixStack();

   /**
    * Pushes the active matrix onto the stack.
    */
   void push();

   /**
    * Pops the matrix stack, setting the active matrix to the popped value.
    */
   void pop();

   /**
    * Gets a reference to the active matrix.
    */
   glm::mat4& getMatrix();
};

#endif
