#include "RE/P/PlayerControls.h"

#include "RE/A/ActivateHandler.h"
#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	PlayerControls::PlayerControls()
	{
		Ctor();
	}

	PlayerControls* PlayerControls::GetSingleton()
	{
		static REL::Relocation<PlayerControls**> singleton{ Offset::PlayerControls::Singleton };
		return *singleton;
	}

	PlayerControls* PlayerControls::Ctor()
	{
		using func_t = decltype(&PlayerControls::Ctor);
		static REL::Relocation<func_t> func{ Offset::PlayerControls::Ctor };
		return func(this);
	}
}
