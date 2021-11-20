#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Config.h"

offsets Offsets;
c_config g_configs;

//-> Remember to check if names of files in your SDK are right with these below
std::string AthenaClass = "\\SDK\\Athena_classes.hpp";
std::string EngineClass = "\\SDK\\Engine_classes.hpp";
std::string AthenaAIClass = "\\SDK\\AthenaAI_classes.hpp";

int stringToInt(std::string input)
{
	unsigned int x;
	std::stringstream ss;
	ss << std::hex << input;
	ss >> x;
	return x;
}

int GetOffsetFromLine(std::string line)
{
	std::string offset = line.substr(line.find_first_of("/") + 3, line.find_first_of('(') - line.find_first_of("/") - 3);
	return stringToInt(offset);
}

int GetOffset(std::string File, std::string Class, std::string Offset)
{
	std::ifstream infile(File);
	std::string line;

	bool once = false;

	while (std::getline(infile, line))
	{
		if (line == (Class))
			once = !once;

		if (once)
			if (line.find(Offset) != std::string::npos)
				return GetOffsetFromLine(line);
	}
}

int main()
{
	//-> v142 / c++ 17-20
	/*
	std::string m_directory = std::filesystem::current_path().string();
	
	if (!std::filesystem::exists(m_directory + "\\SDK"))
	{
		MessageBoxA(NULL, "File Not Found", "File Not Found", 0);
		return 0;
	}
	*/

	std::string m_directory = std::experimental::filesystem::current_path().string();

	if (!std::experimental::filesystem::exists(m_directory + "\\SDK"))
	{
		MessageBoxA(NULL, "File Not Found", "File Not Found", 0);
		return 0;
	}

	EngineClass = m_directory + EngineClass;
	AthenaClass = m_directory + AthenaClass;
	AthenaAIClass = m_directory + AthenaAIClass;

	g_configs.init();

	//-> struct UWorld
	Offsets.UWorld.PersistentLevel = GetOffset(EngineClass, "// Class Engine.World", "PersistentLevel");
	Offsets.UWorld.OwningGameInstance = GetOffset(EngineClass, "// Class Engine.World", "OwningGameInstance");

	//-> struct UGameInstance
	Offsets.UGameInstance.LocalPlayers = GetOffset(EngineClass, "// Class Engine.GameInstance", "LocalPlayers");

	//-> struct UPlayer
	Offsets.ULocalPlayer.PlayerController = GetOffset(EngineClass, "// Class Engine.Player", "PlayerController");

	//-> struct APlayerController
	Offsets.APlayerController.Pawn = GetOffset(EngineClass, "// Class Engine.Controller", "Pawn");
	Offsets.APlayerController.Character = GetOffset(EngineClass, "// Class Engine.Controller", "Character");
	Offsets.APlayerController.CameraManager = GetOffset(EngineClass, "// Class Engine.PlayerController", "CameraManager");
	Offsets.APlayerController.ControlRotation = GetOffset(EngineClass, "// Class Engine.PlayerController", "ControlRotation");

	//-> struct AActor
	Offsets.AActor.rootComponent = GetOffset(EngineClass, "// Class Engine.Actor", "RootComponent");
	Offsets.AActor.PlayerState = GetOffset(EngineClass, "// Class Engine.Pawn", "PlayerState");
	Offsets.AActor.WieldedItemComponent = GetOffset(AthenaClass, "// Class Athena.AthenaCharacter", "WieldedItemComponent");
	Offsets.AActor.HealthComponent = GetOffset(AthenaClass, "// Class Athena.AthenaCharacter", "HealthComponent");
	Offsets.AActor.DrowningComponent = GetOffset(AthenaClass, "// Class Athena.AthenaPlayerCharacter", "DrowningComponent");

	//-> struct APlayerState
	Offsets.APlayerState.PlayerName = GetOffset(EngineClass, "// Class Engine.PlayerState", "PlayerName");

	//-> struct APlayerCameraManager
	Offsets.APlayerCameraManager.CameraCache = GetOffset(EngineClass, "// Class Engine.PlayerCameraManager", "CameraCache");

	//-> struct AItemProxy
	Offsets.AItemProxy.AItemInfo = GetOffset(AthenaClass, "// Class Athena.ItemProxy", "ItemInfo");

	//-> struct AItemInfo
	Offsets.AItemInfo.UItemDesc = GetOffset(AthenaClass, "// Class Athena.ItemInfo", "Desc");

	//-> struct ABootyItemInfo
	Offsets.ABootyItemInfo.BootyType = GetOffset(AthenaClass, "// Class Athena.BootyItemInfo", "BootyType");
	Offsets.ABootyItemInfo.Rarity = GetOffset(AthenaClass, "// Class Athena.BootyItemInfo", "Rarity");

	//-> struct AShip
	Offsets.AShip.CrewOwnershipComponent = GetOffset(AthenaClass, "// Class Athena.Ship", "CrewOwnershipComponent");
	Offsets.AShip.ShipInternalWaterComponent = GetOffset(AthenaClass, "// Class Athena.Ship", "ShipInternalWaterComponent");
	Offsets.AShip.ShipOwningActor = GetOffset(AthenaClass, "// Class Athena.HullDamage", "Root");

	//-> struct ACannon
	Offsets.ACannon.TimePerFire = GetOffset(AthenaClass, "// Class Athena.Cannon", "TimePerFire");
	Offsets.ACannon.ProjectileSpeed = GetOffset(AthenaClass, "// Class Athena.Cannon", "ProjectileSpeed");
	Offsets.ACannon.ProjectileGravityScale = GetOffset(AthenaClass, "// Class Athena.Cannon", "ProjectileGravityScale");
	Offsets.ACannon.ServerPitch = GetOffset(AthenaClass, "// Class Athena.Cannon", "ServerPitch");

	//-> struct UCrewOwnershipComponent
	Offsets.UCrewOwnershipComponent.CrewId = GetOffset(AthenaClass, "// Class Athena.CrewOwnershipComponent", "CachedCrewId");

	//-> struct UCrewOwnershipComponent
	Offsets.ACrewService.Crews = GetOffset(AthenaClass, "// Class Athena.CrewService", "Crews");

	//-> struct AFauna
	Offsets.AFauna.Name = GetOffset(AthenaAIClass, "// Class AthenaAI.Fauna", "DisplayName");

	//-> struct AMaptTable
	Offsets.AMapTable.MapPins = GetOffset(AthenaClass, "// Class Athena.MapTable", "MapPins");
	Offsets.AMapTable.ServerCenter = GetOffset(AthenaClass, "// Class Athena.MapTable", "ServerCentreLocation");
	Offsets.AMapTable.TrackedShips = GetOffset(AthenaClass, "// Class Athena.MapTable", "TrackedShips");

	//-> struct UWieldedItemComponent
	Offsets.UWieldedItemComponent.WieldedItem = GetOffset(AthenaClass, "// Class Athena.WieldedItemComponent", "WieldedItem");

	//-> struct AWieldableItem
	Offsets.AWieldableItem.ItemInfo = GetOffset(AthenaClass, "// Class Athena.WieldableItem", "ItemInfo");

	g_configs.save("offsets");

	system("PAUSE");

	return 0;
}