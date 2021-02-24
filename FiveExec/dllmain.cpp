#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <random>
#include "ResourceManager.h"
#include "ResourceCache.h"
#include "ResourceMetaDataComponent.h"
#include "VFSManager.h"
#include <regex>

//Fixed by scopes
//original thread https://github.com/Mememan55/fivem_trashexec
//Credit to Mememan55 
//Removed ads lol

using namespace fx;
using namespace vfs;

auto resourceManager = Instance<ResourceManager>::Get();

bool repla(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string random_string()
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

void init() {

    _mkdir("C:\\retardFX");
    _mkdir("C:\\retardFX\\exec");

    GetAsyncKeyState(VK_F5);
    while (true) {
            std::string resourceName = random_string();
            std::string fileName = random_string();
            std::string buffer;

            buffer += "Citizen.CreateThread(function()";
            buffer += "Fixed by Primerose aka Scopes";
            buffer += "end)";

            std::string path;
            path += "C:\\retardFX\\exec\\";
            path += fileName;
            path += ".lua";

            std::ofstream script;
            script.open(path);
            script << buffer;
            script.close();


            std::ofstream metadata;
            metadata.open("C:\\retardFX\\exec\\__resource.lua");
            metadata << "resource_manifest_version '44febabe-d386-4d18-afbe-5e627f4af937'\n";
            metadata << "client_scripts {\n";
            metadata << "   '";
            metadata << fileName;
            metadata << ".lua'\n";
            metadata << "}";
            metadata.close();

            auto customResource = resourceManager->CreateResource(resourceName);
            customResource->SetComponent(new ResourceCacheEntryList{});
            customResource->LoadFrom("C:\\retardFX\\exec");
            customResource->Start();

            remove(path.c_str());
            remove("C:\\retardFX\\exec\\__resource.lua");
        }

    }

void init2() {

    _mkdir("C:\\retardFX");
    _mkdir("C:\\retardFX\\exec");

    GetAsyncKeyState(VK_F6);
    while (true) {
        std::string resourceName = random_string();
        std::string fileName = random_string();
        std::string buffer;

        buffer += "Citizen.CreateThread(function()";
        buffer += "Fixed by Primerose aka Scopes";
        buffer += "end)";

        std::string path;
        path += "C:\\retardFX\\exec\\";
        path += fileName;
        path += ".js";

        std::ofstream script;
        script.open(path);
        script << buffer;
        script.close();


        std::ofstream metadata;
        metadata.open("C:\\retardFX\\exec\\__resource.lua");
        metadata << "resource_manifest_version '44febabe-d386-4d18-afbe-5e627f4af937'\n";
        metadata << "client_scripts {\n";
        metadata << "   '";
        metadata << fileName;
        metadata << ".js'\n";
        metadata << "}";
        metadata.close();

        auto customResource = resourceManager->CreateResource(resourceName);
        customResource->SetComponent(new ResourceCacheEntryList{});
        customResource->LoadFrom("C:\\retardFX\\exec");
        customResource->Start();

        remove(path.c_str());
        remove("C:\\retardFX\\exec\\__resource.lua");
    }

}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init,init2, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

