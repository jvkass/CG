#include "Texture.h"
using namespace std;//adicionar as texturas do objeto

Texture::Texture(Vector3 texture_amb,Vector3 texture_dif,Vector3 texture_esp){
	this->texture_amb=texture_amb;
	this->texture_esp=texture_esp;
	this->texture_dif=texture_dif;
}