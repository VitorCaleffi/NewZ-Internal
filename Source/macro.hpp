#pragma once

#ifdef _MSC_VER
#define attr_inline inline
#define attr_alwaysinline __forceinline
#define func_name __FUNCTION__
#define func_fullname __FUNCSIG__
#define func_rawname __FUNCDNAME__
#endif

#define __this__ Address(this)