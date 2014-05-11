#include "FancyAssert.h"
#include "lib/stb_image.h"
#include "PlainTextureMaterial.h"
#include "Mesh.h"

const std::string PlainTextureMaterial::CLASS_NAME = "PlainTextureMaterial";

PlainTextureMaterial::PlainTextureMaterial(const std::string &jsonFileName,
	SPtr<ShaderProgram> shaderProgram) : Material(jsonFileName, shaderProgram){

	uTexture = shaderProgram->getUniform("uTexture");
	aTexCoord = shaderProgram->getAttribute("aTexCoord");

}

PlainTextureMaterial::PlainTextureMaterial(const std::string &jsonFileName,
	SPtr<ShaderProgram> shaderProgram, const std::string &textureFileName)
	: Material(jsonFileName, shaderProgram), textureFileName(textureFileName){
	
	uTexture = shaderProgram->getUniform("uTexture");
	aTexCoord = shaderProgram->getAttribute("aTexCoord");

}

PlainTextureMaterial::~PlainTextureMaterial() {
	if (texture_id){
		glDeleteTextures(1, &texture_id);
	}
}

void PlainTextureMaterial::createTexture(){
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	int x, y, comp;

	// Call the stb_image function for width, height, data.
	FILE *file = fopen(textureFileName.c_str(), "rb");
	ASSERT(file, "Unable to open file: %s", textureFileName.c_str());
	unsigned char *data = stbi_load_from_file(file, &x, &y, &comp, 0);
	fclose(file);

	if (comp == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else if (comp == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else {
		ASSERT(false, "composition of image is not 3 or 4");
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
}

void PlainTextureMaterial::setFBOTexture(SPtr<FrameBuffer> fb){
	texture_id = fb->getTextureID();
}

void PlainTextureMaterial::apply(SPtr<Mesh> mesh){
	shaderProgram->use();

	/* Texture Shading */
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0 + texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glUniform1i(uTexture, texture_id);
	glEnableVertexAttribArray(aTexCoord);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getTBO());
	glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

Json::Value PlainTextureMaterial::serialize() const {
	Json::Value root;

	// Class name
	root["@class"] = CLASS_NAME;

	// Shader program
	root["shaderProgram"] = shaderProgram->getJsonFileName();

	// Texture
	root["texture"] = textureFileName;
	return root;
}