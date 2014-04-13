#include "FancyAssert.h"
#include "MatrixStack.h"

MatrixStack::MatrixStack() {
   currentMatrix = glm::mat4(1.0f);
}

MatrixStack::~MatrixStack() {
}

void MatrixStack::push() {
   matrixStack.push(currentMatrix);
}

void MatrixStack::pop() {
   ASSERT(!matrixStack.empty(), "Tried to pop an empty matrix stack");

   currentMatrix = matrixStack.top();
   matrixStack.pop();
}

glm::mat4* MatrixStack::getMatrix() {
   return &currentMatrix;
}
