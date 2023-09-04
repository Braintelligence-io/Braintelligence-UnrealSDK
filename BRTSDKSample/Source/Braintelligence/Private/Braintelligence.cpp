#include "Braintelligence.h"

#include "BraintelligenceSettings.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FBraintelligenceModule"

// ------------------------------------------------------------------------------------------------

void FBraintelligenceModule::StartupModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"Settings",
			LOCTEXT("RuntimeSettingsName", "Braintelligence"),
			LOCTEXT("RuntimeSettingsDescription", "Configure Braintelligence"),
			GetMutableDefault<UBraintelligenceSettings>());
	}
}

// ------------------------------------------------------------------------------------------------

void FBraintelligenceModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings(
			"Project",
			"Plugins",
			"Settings");
	}
}

// ------------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBraintelligenceModule, Braintelligence)
