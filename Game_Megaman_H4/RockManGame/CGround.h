#include "GameObj.h"

class CGround : public CGameObj
{
private:
public:
	CGround();
	CGround(LPDIRECT3DDEVICE9, int, int, int);
	void Update(float t){};
	~CGround();
};

