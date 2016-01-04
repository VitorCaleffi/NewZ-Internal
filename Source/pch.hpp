#pragma once

// win api & directx9
#include <windows.h>
#include <d3d9.h>

// stl library
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>
#include <map>

// c library
#include <stdint.h>

// our important headers
#include "macro.hpp"
#include "types.hpp"

// the cheat itself
#include "Thread.hpp"
#include "Hooks.hpp"
#include "SDK.hpp"

// memory stuff
#include "VTable.hpp"
#include "Sigscanner.hpp"
#include "Module.hpp"

// math stuff
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Math.hpp"

// the menu
#include "Control.hpp"
#include "Form.hpp"
#include "Checkbox.hpp"

// misc: rendering, logging and event handling
#include "Render.hpp"
#include "Logger.hpp"
#include "Event.hpp"

//linked librarys: direct3d9
#pragma comment(lib, "d3d9.lib")
