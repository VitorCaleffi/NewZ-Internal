#pragma once

namespace NewZ
{
	void Setup ( );

	class GameObject;
	class obj_Player;

	class ClientGameLogic
	{
	public:
		obj_Player* GetLocalPlayer ( );
		int GetLocalPlayerIndex ( );

		attr_alwaysinline bool IsConnected ( )
		{
			return GetLocalPlayerIndex ( ) != -1;
		}
	};

	class ObjectManager
	{
	public:	
	};

	class r3dRenderer
	{
	public:
	};

	class GameObject
	{
	public:
	};

	class obj_Player : public GameObject
	{
	public:
	};

	extern attr_alwaysinline ClientGameLogic* GetClientLogic ( void );
	extern attr_alwaysinline ObjectManager* GetObjectManager ( void );
}