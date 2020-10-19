#include "stdafx.h"
#include "BoxObject.h"

BoxObject::BoxObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(150, 100, 90);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_BOX");
}

void BoxObject::update()
{
}

void BoxObject::release()
{
}

void BoxObject::render()
{
	_img->setScale(2);
	CAMERA_MANAGER->renderZ(_img, _position, _size);
}

void BoxObject::collision(Vector3 ** pos)
{
}
