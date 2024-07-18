#include <pch.h>

#include <Core/WSystemCore.h>

#define W_SYS_MOD_API __declspec(dllexport)
extern "C"
{
    W_SYS_MOD_API RC::CppUserModBase* start_mod()
    {
        return new WSystemCore();
    }

    W_SYS_MOD_API void uninstall_mod(const CppUserModBase* mod)
    {
        delete mod;
    }
}