#ifndef _GAME_MODELS_H
#define _GAME_MODELS_H

#include "GL\glew.h"
#include "GL\freeglut.h"
#include "VertexFormat.h"
#include <vector>
#include <map>

namespace Models{

	struct Model{
		unsigned int vao; //vertex array objects
		std::vector<unsigned int> vbos; //vertex buffer objects

		Model() {}
	};

	class GameModels{
	public:
		GameModels();
		~GameModels();
		void CreateTriangleModel(const std::string& gameModelName);
		void DeleteModel(const std::string& gameModelName);
		unsigned int GetModel(const std::string& gameModelName);
	private:
		std::map<std::string, Model> GameModelList;//keep our models
	};
}
#endif
