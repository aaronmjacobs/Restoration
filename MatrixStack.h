#ifndef MATRIX_STACK_H
#define MATRIX_STACK_H

#include <glm/glm.hpp>

#include <stack>

class MatrixStack {
private:
   glm::mat4 currentMatrix;
   std::stack<glm::mat4> matrixStack;

public:
   MatrixStack();
   void push();
   void pop();
   glm::mat4* getMatrix();
};

#endif