#pragma once
#include "windows_header.h"

namespace amo
{
	class AmoraConsole;

	class IScene
	{
	public:
		virtual ~IScene() = default;

	public:
		virtual void initialize() { }

		virtual void update(double dt) { }

		virtual void render(AmoraConsole*) { }

		virtual void handle_event(INPUT_RECORD) { }
	};
}