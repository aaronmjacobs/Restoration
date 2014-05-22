#include "AniMesh.h"
#include "FancyAssert.h"
#include "Loader.h"

#include <assimp/postprocess.h>
#include <fstream>

const std::string AniMesh::CLASS_NAME = "AniMesh";

AniMesh::AniMesh(const std::string &fileName, const std::string &aniName)
: Mesh(fileName), numModes(0), aniMode(0) {
   loadAnimation(fileName, aniName);
   const aiScene* scene = scenes[0];

   convertToGlmMat(&rootInverseTransform, scene->mRootNode->mTransformation.Inverse());

   int tBoneNum = scene->mMeshes[0]->mNumBones;

   for (int i = 0; i < tBoneNum; i++) {
      int tBoneIndx = i;
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

   // Weights
   float *weights = getWeights();
   glGenBuffers(1, &wbo);
   glBindBuffer(GL_ARRAY_BUFFER, wbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vertWeights.size(), weights, GL_STATIC_DRAW);
   delete[] weights;

   // Joints
   float *joints = getJoints();
   glGenBuffers(1, &jbo);
   glBindBuffer(GL_ARRAY_BUFFER, jbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vertBones.size(), joints, GL_STATIC_DRAW);
   delete[] joints;

   startTime = glfwGetTime();
}

AniMesh::~AniMesh() {
}

Json::Value AniMesh::serialize() const {
   Json::Value root = Mesh::serialize();

   // Class name
   root["@class"] = CLASS_NAME;

   Json::Value animations;
   for (std::map<std::string, int>::const_iterator itr = aniMap.begin();
        itr != aniMap.end(); ++itr) {
      Json::Value animation;
      // The first loaded animation is the default
      animation["default"] = itr->second == 0;
      animation["name"] = itr->first;
      ASSERT(aniFileMap.count(itr->first), "No file name for animation: %s", itr->first.c_str());
      animation["file"] = aniFileMap.at(itr->first);

      animations.append(animation);
   }
   root["animations"] = animations;

   return root;
}

void AniMesh::loadAnimation(const std::string &fileName, const std::string &aniName) {
   importers[numModes].SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 3);

   std::ifstream ifile(fileName);
   ASSERT(ifile, "Unable to open file: %s", fileName.c_str());
   ifile.close();

   const aiScene *scene = importers[numModes].ReadFile(fileName, aiProcess_GenSmoothNormals |
      aiProcess_Triangulate);

   ASSERT(scene, "Unable to import scene: %s", fileName.c_str());

   scenes.push_back(scene);
   aniMap[aniName] = numModes++;
   aniFileMap[aniName] = fileName;
}

void AniMesh::hardApplyAnimation(const std::string &aniName) {
   aniMode = aniMap[aniName];
   startTime = glfwGetTime();
}

void AniMesh::softApplyAnimation(const std::string &aniName) {
   aniMode = aniMap[aniName];
}

void AniMesh::updateAnimation() {
   float curTime = glfwGetTime() - startTime;
   float tps = (float)(scenes[aniMode]->mAnimations[0]->mTicksPerSecond);
   if (tps == 0.0f) tps = 25.0f;
   float aniTime = fmod(curTime * tps, scenes[aniMode]->mAnimations[0]->mDuration);
   glm::mat4 id = glm::mat4(1.0f);
   updateMatrices(aniTime, scenes[aniMode]->mRootNode, id);
}

void AniMesh::updateMatrices(float aniTime, const aiNode* curNode, glm::mat4 parTransform) {
   glm::mat4 nodeTransform(0.0f);
   convertToGlmMat(&nodeTransform, curNode->mTransformation);

   int boneNum;
   for (boneNum = 0; boneNum < scenes[aniMode]->mMeshes[0]->mNumBones && scenes[aniMode]->mMeshes[0]->mBones[boneNum]->mName != curNode->mName; boneNum++) {}

   const aiNodeAnim* aniNode = NULL;

   for (int i = 0; i < scenes[aniMode]->mAnimations[0]->mNumChannels; i++) {
      if (scenes[aniMode]->mAnimations[0]->mChannels[i]->mNodeName == curNode->mName) {
         aniNode = scenes[aniMode]->mAnimations[0]->mChannels[i];
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

   if (scenes[aniMode]->mMeshes[0]->mNumBones != boneNum) {
      boneTransforms[boneNum] = rootInverseTransform * totalTransform * boneOffset[boneNum];
   }

   for (int i = 0; i < curNode->mNumChildren; i++) {
      updateMatrices(aniTime, curNode->mChildren[i], totalTransform);
   }
}

void AniMesh::convertToGlmMat(glm::mat4* glmMat, aiMatrix4x4 aiMat) {
   *glmMat = glm::mat4(aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1,
      aiMat.a2, aiMat.b2, aiMat.c2, aiMat.d2,
      aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3,
      aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4);
}

glm::quat AniMesh::interpolateRotation(float aniTime, const aiNodeAnim* aniNode) {
   glm::quat ret;
   if (aniNode->mNumRotationKeys == 1) {
      ret = glm::quat(aniNode->mRotationKeys[0].mValue.w,
         aniNode->mRotationKeys[0].mValue.x,
         aniNode->mRotationKeys[0].mValue.y,
         aniNode->mRotationKeys[0].mValue.z);
   }
   else {
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

      ret = glm::mix(q1, q2, amt);
   }
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
   glm::vec3 ret;
   if (aniNode->mNumScalingKeys == 1) {
      ret = glm::vec3(aniNode->mScalingKeys[0].mValue.x,
         aniNode->mScalingKeys[0].mValue.y,
         aniNode->mScalingKeys[0].mValue.z);
   }
   else {
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

      ret = (amt2 * sca1) + (amt1 * sca2);
   }
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
   glm::vec3 ret;
   if (aniNode->mNumScalingKeys == 1) {
      ret = glm::vec3(aniNode->mPositionKeys[0].mValue.x,
         aniNode->mPositionKeys[0].mValue.y,
         aniNode->mPositionKeys[0].mValue.z);
   }
   else {
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

      ret = (amt2 * pos1) + (amt1 * pos2);
   }
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

float* AniMesh::getBones() {
   const int VALUES_PER_MATRIX = 16;

   float *packedBones = new float[MAX_BONES * VALUES_PER_MATRIX];
   for (int i = 0; i < MAX_BONES; ++i) {
      memcpy(&packedBones[i * VALUES_PER_MATRIX], glm::value_ptr(boneTransforms[i]), VALUES_PER_MATRIX * sizeof(float));
   }

   return packedBones;
}

float* AniMesh::getWeights() {
   const int VALUES_PER_WEIGHT = 3;

   float *packedWeights = new float[vertWeights.size() * VALUES_PER_WEIGHT];
   for (int i = 0; i < vertWeights.size(); ++i) {
      memcpy(&packedWeights[i * VALUES_PER_WEIGHT], glm::value_ptr(vertWeights[i]), VALUES_PER_WEIGHT * sizeof(float));
   }

   return packedWeights;
}

float* AniMesh::getJoints() {
   const int VALUES_PER_JOINT = 3;

   float *packedJoints = new float[vertBones.size() * VALUES_PER_JOINT];
   for (int i = 0; i < vertBones.size(); ++i) {
      memcpy(&packedJoints[i * VALUES_PER_JOINT], glm::value_ptr(vertBones[i]), VALUES_PER_JOINT * sizeof(float));
   }

   return packedJoints;
}
