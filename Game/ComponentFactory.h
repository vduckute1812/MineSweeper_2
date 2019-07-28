#pragma once
class Object;

class ComponentFactory
{
public:
	static 	Object* CreateComponent(unsigned int type, Object* onject = nullptr);
};

