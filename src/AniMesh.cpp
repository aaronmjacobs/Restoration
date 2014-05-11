#include "AniMesh.h"
#include "FancyAssert.h"
#include "Loader.h"

#include <assimp/postprocess.h>
#include <fstream>

AniMesh::AniMesh(const std::string &fileName)
: Mesh(fileName) {
   importer.SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 3);

   // Make sure the file exists and can be read
   std::ifstream ifile(fileName);
   ASSERT(ifile, "Unable to open file: %s", fileName.c_str());
   ifile.close();

   scene = importer.ReadFile(fileName, aiProcess_GenSmoothNormals |
                      aiProcess_Triangulate);
   ASSERT(scene, "Unable to import scene: %s", fileName.c_str());

   convertToGlmMat(&rootInverseTransform, scene->mRootNode->mTransformation.Inverse());

   int tBoneNum = scene->mMeshes[0]->mNumBones;

   for (int i = 0; i < tBoneNum; i++) {
      int tBoneIndx = 0;
      std::string tBoneName(scene->mMeshes[0]->mBones[i]->mName.C_Str());

      convertToGlmMat(&boneOffset[tBoneIndx], scene->mMeshes[0]->mBones[i]->mOffsetMatrix);

      for (int j = 0; j < scene->mMeshes[0]->mNumVertices; j++) {
         boneWeights[i].push_back(0.0f);
      }

      for (int j = 0; j < scene->mMeshes[0]->mBones[i]->mNumWeights; j++) {
         boneWeights[i][scene->mMeshes[0]->mBones[i]->mWeights[j].mVertexId] = scene->mMeshes[0]->mBones[i]->mWeights[j].mWeight;
      }
   }

   for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++) {
      glm::vec3 bones(0.0f), weights(0.0f);
      for (int j = 0; j < scene->mMeshes[0]->mNumBones; j++) {
         if (boneWeights[j][i] > weights.x) {
            bones.z = bones.y;
            bones.y = bones.x;
            bones.x = j;
            weights.z = weights.y;
            weights.y = weights.x;
            weights.x = boneWeights[j][i];
         }
         else if (boneWeights[j][i] > weights.y) {
            bones.z = bones.y;
            bones.y = j;
            weights.z = weights.y;
            weights.y = boneWeights[j][i];
         }
         else if (boneWeights[j][i] > weights.z) {
            bones.z = j;
            weights.z = boneWeights[j][i];
         }
      }
      vertBones.push_back(bones);
      vertWeights.push_back(weights);
   }

   for (int i = 0; i < MAX_BONES; i++) {
      boneTransforms[i] = glm::mat4(1.0f);
   }

   startTime = glfwGetTime();
}

AniMesh::~AniMesh() {
}

void AniMesh::loadAnimation() {

}

void AniMesh::updateAnimation() {
   float curTime = glfwGetTime() - startTime;
   float tps = (float)(scene->mAnimations[0]->mTicksPerSecond);
   if (tps == 0.0f) tps = 25.0f;
   float aniTime = fmod(curTime * tps, scene->mAnimations[0]->mDuration);
   glm::mat4 id = glm::mat4(1.0f);
   updateMatrices(aniTime, scene->mRootNode, id);
}

void AniMesh::updateMatrices(float aniTime, const aiNode* curNode, glm::mat4 parTransform) {
   glm::mat4 nodeTransform(0.0f);
   convertToGlmMat(&nodeTransform, curNode->mTransformation);

   int boneNum;
   for (boneNum = 0; boneNum < scene->mMeshes[0]->mNumBones && scene->mMeshes[0]->mBones[boneNum]->mName != curNode->mName; boneNum++) {}

   const aiNodeAnim* aniNode = NULL;

   for (int i = 0; i < scene->mAnimations[0]->mNumChannels; i++) {
      if (scene->mAnimations[0]->mChannels[i]->mNodeName == curNode->mName) {
         aniNode = scene->mAnimations[0]->mChannels[i];
      }
   }

   if (aniNode) {
      glm::vec3 scale = interpolateScale(aniTime, aniNode);
      glm::mat4 scaleMatrix = glm::scale(scale);
      glm::vec3 position = interpolatePosition(aniTime, aniNode);
      glm::mat4 positionMatrix = glm::translate(position);
      glm::quat rotation = interpolateRotation(aniTime, aniNode);
      glm::mat4 rotationMatrix = glm::toMat4(rotation);

      nodeTransform = positionMatrix * rotationMatrix * scaleMatrix;
   }

   glm::mat4 totalTransform = parTransform * nodeTransform;

   if (scene->mMeshes[0]->mNumBones != boneNum) {
      boneTransforms[boneNum] = rootInverseTransform * totalTransform * boneOffset[boneNum];
   }

   for (int i = 0; i < curNode->mNumChildren; i++) {
      updateMatrices(aniTime, curNode->mChildren[i], totalTransform);
   }
}

void AniMesh::convertToGlmMat(glm::mat4* glmMat,  aiMatrix4x4 aiMat) {
   *glmMat = glm::mat4(aiMat.a1, aiMat.a2, aiMat.a3, aiMat.a4,
                       aiMat.b1, aiMat.b2, aiMat.b3, aiMat.b4,
                       aiMat.c1, aiMat.c2, aiMat.c3, aiMat.c4,
                       aiMat.d1, aiMat.d2, aiMat.d3, aiMat.d4);
}

glm::quat AniMesh::interpolateRotation(float aniTime, const aiNodeAnim* aniNode) {
   int indx = findRotation(aniTime, aniNode);
   float dt = aniNode->mRotationKeys[indx + 1].mTime - aniNode->mRotationKeys[indx].mTime;
   float amt = (aniTime - aniNode->mRotationKeys[indx].mTime) / dt;

   glm::quat q1 = glm::quat(aniNode->mRotationKeys[indx].mValue.w,
                            aniNode->mRotationKeys[indx].mValue.x,
                            aniNode->mRotationKeys[indx].mValue.y,
                            aniNode->mRotationKeys[indx].mValue.z);

   glm::quat q2 = glm::quat(aniNode->mRotationKeys[indx + 1].mValue.w,
                            aniNode->mRotationKeys[indx + 1].mValue.x,
                            aniNode->mRotationKeys[indx + 1].mValue.y,
                            aniNode->mRotationKeys[indx + 1].mValue.z);

   glm::quat ret = glm::mix(q1, q2, amt);

   return ret;
}

int AniMesh::findRotation(float aniTime, const aiNodeAnim* aniNode) {
   for (int i = 0; i < aniNode->mNumRotationKeys - 1; i++) {
      if (aniTime < (float)aniNode->mRotationKeys[i + 1].mTime) {
         return i;
      }
   }

   ASSERT(false, "Could not find rotation");
   return -1;
}

glm::vec3 AniMesh::interpolateScale(float aniTime, const aiNodeAnim* aniNode) {
   int indx = findScale(aniTime, aniNode);
   float dt = aniNode->mScalingKeys[indx + 1].mTime - aniNode->mScalingKeys[indx].mTime;
   float amt1 = (aniTime - aniNode->mScalingKeys[indx].mTime) / dt;
   float amt2 = 1.0f - amt1;

   glm::vec3 sca1 = glm::vec3(aniNode->mScalingKeys[indx].mValue.x,
                              aniNode->mScalingKeys[indx].mValue.y,
                              aniNode->mScalingKeys[indx].mValue.z);

   glm::vec3 sca2 = glm::vec3(aniNode->mScalingKeys[indx + 1].mValue.x,
                              aniNode->mScalingKeys[indx + 1].mValue.y,
                              aniNode->mScalingKeys[indx + 1].mValue.z);

   glm::vec3 ret = (amt1 * sca1) + (amt2 * sca2);

   return ret;
}

int AniMesh::findScale(float aniTime, const aiNodeAnim* aniNode) {
   for (int i = 0; i < aniNode->mNumScalingKeys - 1; i++) {
      if (aniTime < (float)aniNode->mScalingKeys[i + 1].mTime) {
         return i;
      }
   }

   ASSERT(false, "Could not find scale");
   return -1;
}

glm::vec3 AniMesh::interpolatePosition(float aniTime, const aiNodeAnim* aniNode) {
   int indx = findPosition(aniTime, aniNode);
   float dt = aniNode->mPositionKeys[indx + 1].mTime - aniNode->mPositionKeys[indx].mTime;
   float amt1 = (aniTime - aniNode->mPositionKeys[indx].mTime) / dt;
   float amt2 = 1.0f - amt1;

   glm::vec3 pos1 = glm::vec3(aniNode->mPositionKeys[indx].mValue.x,
                              aniNode->mPositionKeys[indx].mValue.y,
                              aniNode->mPositionKeys[indx].mValue.z);

   glm::vec3 pos2 = glm::vec3(aniNode->mPositionKeys[indx + 1].mValue.x,
                              aniNode->mPositionKeys[indx + 1].mValue.y,
                              aniNode->mPositionKeys[indx + 1].mValue.z);
   
   glm::vec3 ret = (amt1 * pos1) + (amt2 * pos2);
   
   return ret;
}

int AniMesh::findPosition(float aniTime, const aiNodeAnim* aniNode) {
   for (int i = 0; i < aniNode->mNumPositionKeys - 1; i++) {
      if (aniTime < (float)aniNode->mPositionKeys[i + 1].mTime) {
         return i;
      }
   }

   ASSERT(false, "Could not find position");
   return -1;
}