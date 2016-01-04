#include "pch.hpp"

void* g_pClientLogic = nullptr;
void* g_pGameWorld = nullptr;

void* ClientGameLogic__localPlayer_ = nullptr;
Address ClientGameLogic__localPlayerXor = 0;
void* ClientGameLogic__localPlayerIdx_ = nullptr;

void* ObjectManager__pObjectArray = nullptr;
void* ObjectManager__MaxObjects = nullptr;

void NewZ::Setup ( )
{
	auto NewZ = "TheNewZ.exe";

	static Pattern _g_pClientLogic__Sigs [] =
	{
		{ "A1 [?? ?? ?? ?? 0F B7 88", PatternType::Pointer32 },
		{ "83 3D [?? ?? ?? ?? 00 56 57 74 ?? 6A", PatternType::Pointer32 },
		DoNotContinue()
	};
	g_pClientLogic = PatternScanner::FindPattern ( NewZ, _g_pClientLogic__Sigs );
	Log ( ) << "g_pClientLogic " << g_pClientLogic << End;

	static Pattern _g_pGameWorld__Sigs [] =
	{
		{ "8B 35 [?? ?? ?? ?? 83 C4 ? EB", PatternType::Pointer32 },
		{ "7F ?? 83 3D [?? ?? ?? ?? 00 75 ?? 68", PatternType::Pointer32 },
		DoNotContinue ( )
	};
	g_pGameWorld = PatternScanner::FindPattern ( NewZ, _g_pGameWorld__Sigs );
	Log ( ) << "g_pGameWorld " << g_pGameWorld << End;

	static Pattern ClientGameLogic__localPlayer_Sigs [] =
	{
		{ "83 C4 ?? 8B 8B [?? ?? ?? ?? 89 4C", PatternType::Offset },
		DoNotContinue ( )
	};
	ClientGameLogic__localPlayer_ = PatternScanner::FindPattern ( NewZ, ClientGameLogic__localPlayer_Sigs );
	{
		auto lclplr_bytes = reinterpret_cast< uint8_t* >( &ClientGameLogic__localPlayer_ );
		auto lclplr_xorbytes = reinterpret_cast< uint8_t* >( &ClientGameLogic__localPlayerXor );
		lclplr_xorbytes [ 0 ] = lclplr_bytes [ 11 ];
		lclplr_xorbytes [ 1 ] = lclplr_bytes [ 21 ];
		lclplr_xorbytes [ 2 ] = lclplr_bytes [ 16 ];
		lclplr_xorbytes [ 3 ] = lclplr_bytes [ 26 ];

		Log ( ) << "ClientGameLogic::localPlayer_ " << ClientGameLogic__localPlayer_ << " (Offset)" << End;

		ClientGameLogic__localPlayer_ = *static_cast< void** >( ClientGameLogic__localPlayer_ );

		Log ( ) << "ClientGameLogic::localPlayer_ " << ClientGameLogic__localPlayerXor << " (XOR)" << End;
		Log ( ) << "ClientGameLogic::localPlayer_ " << ClientGameLogic__localPlayer_ << End;
	}

	static Pattern ClientGameLogic__localPlayerIdx_Sigs [] =
	{
		{ "83 C4 ?? 83 BB [?? ?? ?? ?? FF 74", PatternType::Pointer32 },
		DoNotContinue ( )
	};
	ClientGameLogic__localPlayerIdx_ = PatternScanner::FindPattern ( NewZ, ClientGameLogic__localPlayerIdx_Sigs );
	Log ( ) << "ClientGameLogic::localPlayerIdx_ " << ClientGameLogic__localPlayerIdx_ << End;

	static Pattern ObjectManager__pObjectArray_Sig [] =
	{
		{ "8B 47 [?? 8B 4F ?? 83 3C", PatternType::Pointer8 }, // 8B 47 ?? 8B 4F ?? 83 3C 81 00
		DoNotContinue ( )
	};
	ObjectManager__pObjectArray = PatternScanner::FindPattern ( NewZ, ObjectManager__pObjectArray_Sig );
	Log ( ) << "ObjectManager::pObjectArray " << ObjectManager__pObjectArray << End;

	static Pattern ObjectManager__MaxObjects_Sig [] =
	{
		{ "5E 5B C2 04 00 85 F6 7C ?? 3B 77 [?? 7C ?? 68", PatternType::Pointer8 },
		DoNotContinue ( )
	};
	ObjectManager__MaxObjects = PatternScanner::FindPattern ( NewZ, ObjectManager__MaxObjects_Sig );
	Log ( ) << "ObjectManager::pObjectArray " << ObjectManager__MaxObjects << End;
}

attr_alwaysinline NewZ::ClientGameLogic * NewZ::GetClientLogic ( void )
{
	return static_cast< ClientGameLogic* >( g_pClientLogic );
}

attr_alwaysinline NewZ::ObjectManager * NewZ::GetObjectManager ( void )
{
	return static_cast< ObjectManager* >( g_pGameWorld );
}

NewZ::obj_Player * NewZ::ClientGameLogic::GetLocalPlayer ( )
{
	return reinterpret_cast< obj_Player* >( *reinterpret_cast<Address*>( __this__ + Address ( ClientGameLogic__localPlayer_ ) ) ^ ClientGameLogic__localPlayerXor );
}

int NewZ::ClientGameLogic::GetLocalPlayerIndex ( )
{
	return *reinterpret_cast< int* >( Address(this) + Address(ClientGameLogic__localPlayerIdx_) );
}
