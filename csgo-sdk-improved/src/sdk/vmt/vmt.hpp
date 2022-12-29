#pragma once

#include "../../defs.hpp"

#define CALL_VIRTUAL(type, index, conv, ...) vmt::CallVirtual<type, conv>(index, FILE_AND_LINE, __VA_ARGS__)
#define GET_VIRTUAL(pclass, index) vmt::GetVirtual(pclass, index, FILE_AND_LINE)

namespace vmt
{
    enum ECallingConvention
    {
        CDECL_CONV = 0,
        STDCALL_CONV,
        FASTCALL_CONV,
        THISCALL_CONV
    };

    void *GetVirtual(void *pClass, int index, const char *szFilePath, int line);

    template <typename T, ECallingConvention Convention, typename... Args>
    inline T CallVirtual(int index, const char *szFilePath, int line, void *pClass, Args... args)
    {
        if constexpr (Convention == CDECL_CONV)
        {
            using FnType = T(CDECL_CALL *)(void *, Args...);
            return reinterpret_cast<FnType>(GetVirtual(pClass, index, szFilePath, line))(pClass, args...);
        }
        else if constexpr (Convention == STDCALL_CONV)
        {
            using FnType = T(STDCALL_CALL *)(void *, Args...);
            return reinterpret_cast<FnType>(GetVirtual(pClass, index, szFilePath, line))(pClass, args...);
        }
        else if constexpr (Convention == FASTCALL_CONV)
        {
            using FnType = T(FASTCALL_CALL *)(void *, Args...);
            return reinterpret_cast<FnType>(GetVirtual(pClass, index, szFilePath, line))(pClass, args...);
        }
        else if constexpr (Convention == THISCALL_CONV)
        {
            using FnType = T(THISCALL_CALL *)(void *, Args...);
            return reinterpret_cast<FnType>(GetVirtual(pClass, index, szFilePath, line))(pClass, args...);
        }
    }
} // namespace vmt
