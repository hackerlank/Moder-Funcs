#include <windows.h>
#include <string>
#include <assert.h>
#include <process.h>
#include <algorithm>
#include <regex>
#include <fstream>

#include "SAMPFUNCS_API.h"
#include "game_api\game_api.h"

SAMPFUNCS *SF = new SAMPFUNCS();

std::vector <std::string> Vector;
stFontInfo *font;
stTextureInfo *texture;
bool Spectate = false;
DWORD LastID;

void SayToChat(const char *text, ...)
{
	char g_flLog[1024];
	va_list  ap;
	va_start(ap, text);
	vsprintf(g_flLog, text, ap);
	va_end(ap);
	SF->getSAMP()->getPlayers()->pLocalPlayer->Say(g_flLog);
}

bool ini_file_exist(std::string ini_file_name)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFindIni;

	hFindIni = FindFirstFile(ini_file_name.c_str(), &FindFileData);
	if (hFindIni != INVALID_HANDLE_VALUE)
	{
		return true;
	}
	return false;
}

bool сreate_ini_file(std::string new_ini_file_name)
{
	if (!ini_file_exist(new_ini_file_name))
	{
		FILE *fp = fopen(new_ini_file_name.c_str(), "w");
		if (fp != NULL)
			fclose(fp);

		return true;
	}
	return false;
}

void LoggingAll(std::string string)
{
	char buff[0x100];
	SYSTEMTIME *time = new SYSTEMTIME();
	GetLocalTime(time);
	if (ini_file_exist("SAMPFUNCS\\chatlogAll.log"))
	{
		сreate_ini_file("SAMPFUNCS\\chatlogAll.log");
	}
	sprintf(buff, "[%02d-%02d-%02d:%03d %02d-%02d-%04d] %s\n", time->wHour, time->wMinute, time->wSecond, time->wMilliseconds, time->wDay, time->wMonth, time->wYear, string.c_str());
	std::fstream *file = new std::fstream();
	file->open("SAMPFUNCS\\chatlogAll.log", std::ios_base::app);
	file->write(buff, strlen(buff));
	file->close();
}

void LoggingToday(std::string string)
{
	char buff[0x100];
	SYSTEMTIME *time = new SYSTEMTIME();
	GetLocalTime(time);	
	sprintf(buff, "SAMPFUNCS\\%02d-%02d-%04d.log", time->wDay, time->wMonth, time->wYear);
	if (ini_file_exist(buff))
	{
		сreate_ini_file(buff);
	}
	std::fstream *file = new std::fstream();
	file->open(buff, std::ios_base::app);
	sprintf(buff, "[%02d-%02d-%02d:%03d] %s\n", time->wHour, time->wMinute, time->wSecond, time->wMilliseconds, string.c_str());
	file->write(buff, strlen(buff));
	file->close();
}

bool CALLBACK incomingRPC(stRakNetHookParams *params)
{
	if (params->packetId == ScriptRPCEnumeration::RPC_ScrClientMessage)
	{
		char buff[0x100];
		DWORD len, color;
		char message[255];
		params->bitStream->Read(color);
		params->bitStream->Read(len);
		params->bitStream->Read(message, len);
		params->bitStream->ResetReadPointer();
		message[len] = '\0';
		LoggingAll(message);
		LoggingToday(message);
		std::string str = message;
		std::smatch results;
		if (std::regex_match(str, results, std::regex(R"(^\*\*\* (.+) \(ID: (\d+)\) покинул\(а\) сервер \((.+)\)\.$)")))
		{
			sprintf(buff, "{009ACD}%s {FF7F24}[%d] {FFFFFF}покинул(a) сервер. Причина: {DA70D6}%s", results[1].str().c_str(), std::stoi(results[2].str()), results[3].str().c_str());
			str = buff;
			Vector.push_back(str);
			return false;
		}				
		if (std::regex_match(str, results, std::regex(R"(^\*\*\* (.+) \(ID: (\d+)\) подключился к серверу \(IP: (.+)\).$)")))
		{
			sprintf(buff, "{009ACD}%s {FF7F24}[%d] {FFFFFF}подключился к серверу. {DA70D6}(IP: %s)", results[1].str().c_str(), std::stoi(results[2].str()), results[3].str().c_str());
			str = buff;
			Vector.push_back(str);
			return false;
		}
		std::transform(str.begin(), str.end(), str.begin(), tolower);

		if (std::regex_match(str, results, std::regex(R"(^\>\> ПМ от (.+)\((\d+)\)\: 0 хп плиз$)")) || std::regex_match(str, results, std::regex(R"(^\>\> ПМ от (.+)\((\d+)\)\: 0 hp plis$)")))
		{
			SayToChat("/sethp %d 0", std::stoi(results[2].str()));
		}
	}
	if (params->packetId == ScriptRPCEnumeration::RPC_ScrPlayerSpectatePlayer)
	{
		WORD id; byte type;
		params->bitStream->Read(id);
		params->bitStream->Read(type);		
		LastID = id;
		Spectate = true;
	}
	return true;
}

bool CALLBACK HUD(CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion)
{
	if (SUCCEEDED(SF->getRender()->BeginRender()))
	{
		SF->getRender()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		SF->getRender()->getD3DDevice()->SetSamplerState(NULL, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		if (!Vector.empty())
		{
			int a;
			int y = font->DrawHeight();
			if (Vector.size() < 10)
				a = 0;
			else
			{
				a = Vector.size() - 10;
			}

			for (int i = a; i < Vector.size(); i++)
			{
				{

					font->Print(Vector[i].c_str(), -1, 10, SF->getSAMP()->getChat()->dwChatboxOffset + 50 + y*10 - y *(Vector.size() - i), false, false);
				}
			}
		}
		int x, y;		
		SF->getRender()->EndRender();
	}
	return true;
}

void CALLBACK mainloop()
{
	static bool init = false;
	if (!init)
	{
		if (GAME == nullptr)
			return;
		if (GAME->GetSystemState() != eSystemState::GS_PLAYING_GAME)
			return;
		if (!SF->getSAMP()->IsInitialized())
			return;
		SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, HUD);
		SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_RPC, incomingRPC);
		font = SF->getRender()->CreateNewFont("Arial", 10, FCR_BOLD + FCR_SHADOW + FCR_BORDER);	
		SF->getSAMP()->getChat()->AddChatMessage(-1, "{FF7F24}Moder FUNCS {FFFFFF}by Dark_Knight Loaded");
		init = true;
	}
	if (Spectate)
	{
		BitStream *BS = new BitStream();
		BS->Write(SF->getSAMP()->getPlayers()->GetAimData(LastID)->vecAimPos[0]);
		BS->Write(SF->getSAMP()->getPlayers()->GetAimData(LastID)->vecAimPos[1]);
		BS->Write(SF->getSAMP()->getPlayers()->GetAimData(LastID)->vecAimPos[2]);
		SF->Log("%d %.0f %.0f %.0f", LastID , SF->getSAMP()->getPlayers()->GetAimData(LastID)->vecAimPos[0], SF->getSAMP()->getPlayers()->GetAimData(LastID)->vecAimPos[1], SF->getSAMP()->getPlayers()->GetAimData(LastID)->vecAimPos[2]);
		//SF->getRakNet()->emulateRecvRPC(ScriptRPCEnumeration::RPC_ScrSetPlayerCameraPos, BS);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	switch (dwReasonForCall)
	{
		case DLL_PROCESS_ATTACH:
			SF->initPlugin(mainloop, hModule);
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
