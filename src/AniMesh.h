#ifndef ANI_MESH_H
#define ANI_MESH_H

#define MAX_BONES 100

#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

/**
 * Animated Mesh built of vertices and normals.
 */
class AniMesh : public Mesh {
private:
   const aiScene *scene;

   //The start time for the animation
   float startTime;

   //The root transformation for the skeleton
   glm::mat4 rootInverseTransform;

   //list of all bone offsets
   glm::mat4 boneOffset[MAX_BONES];

   //list of bone weights for each vertex
   std::vector<float> boneWeights[MAX_BONES];

   //holds transformations for all bones at the curent time - - - THIS NEEDS TO GO TO SHADER
   glm::mat4 boneTransforms[MAX_BONES];

   //lists for holding 3 most influencial bones and their weights per vertex - - - THESE NEED TO GO TO SHADER
   std::vector<glm::vec3> vertBones;
   std::vector<glm::vec3> vertWeights;

   //function to update boneTransforms
   void updateMatrices(float aniTime, const aiNode *curNode, glm::mat4 parTransform);

   //function for converting between matrix formats
   void convertToGlmMat(glm::mat4 *glmMat, aiMatrix4x4 aiMat);

   //functions to interpolate values
   glm::quat interpolateRotation(float aniTime, const aiNodeAnim *aniNode);
   glm::vec3 interpolateScale(float aniTime, const aiNodeAnim *aniNode);
   glm::vec3 interpolatePosition(float aniTime, const aiNodeAnim *aniNode);

   //functions to find current values
   int findRotation(float aniTime, const aiNodeAnim *aniNode);
   int findScale(float aniTime, const aiNodeAnim *aniNode);
   int findPosition(float aniTime, const aiNodeAnim *aniNode);

public:
   /**
    * Constructs a mesh from the model file with the given file name, allocating
    * the required GL buffers.
    */
   AniMesh(const std::string &fileName);

   /**
    * Deallocates the GL buffers.
    */
   virtual ~AniMesh();

   void loadAnimation();
   
   virtual void updateAnimation();
};

#endif