#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "Vector3.h"
class Texture {
public://informacoes das texturas
	Texture(Vector3 texture_amb,Vector3 texture_dif,Vector3 texture_esp);
	Vector3 texture_amb={0,0,0};
	Vector3 texture_dif={0,0,0};
	Vector3 texture_esp={0,0,0};
};

#endif /* TEXTURE_H_ */
