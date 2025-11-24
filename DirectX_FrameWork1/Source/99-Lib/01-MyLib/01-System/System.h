#pragma once


class System
{
private:

	System();

public:
	static System& GetInstance()
	{
		static System instance;
		return instance;
	}

	void Init();
	void ActionComponentMng();
	void UnInit();

};

