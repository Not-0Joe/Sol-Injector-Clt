#include "Controller.h"
#include "InputHandler.h"
#include "UI.h"
#include "ProcessManager.h"
#include "InjectionOptions.h"
#include "Utils.h"

void Controller::useMenuOption(InputHandler::RequestedOption option)
{
	// logic for when the user picks a certain menu option
	switch (option)
	{
		case InputHandler::GetTargetProcessWithPID:
		{
			// call funcion to get the target process with its pid
			UI::info("Enter target PID");
			int pid = InputHandler::getUserPID();
			// call ProsessManager to use pid to check if target is running
			bool wasProcessFound = ProcessManager::checkProcessListForTarget(pid);
			if (wasProcessFound)
			{
				UI::printInjectionMenu();
				InputHandler::InjectionMethod injectionMethod = InputHandler::getInjectionMethod();
				switch (injectionMethod)
				{
					case InputHandler::InjectionMethod::loadlibraryWithRemoteThread:
					{
						const std::wstring dllPath = InputHandler::getDllPath();
						InjectionOptions::LoadLibraryWithRemoteThread(pid, dllPath);
						UI::success("LoadLibrary Injection Done");
						Utils::clearAndIgnoreInput();
						Utils::waitForKey();
						break;
					}

				}
			}
			else
			{
				UI::error("Process was not found. make sure its running and try again");
				break;
				return;
			}

		}
		case InputHandler::ListAllProcesses:
		{
			ProcessManager::listAllProcesses();
			UI::info("All processes have been listed. press any key");
			Utils::clearAndIgnoreInput();
			Utils::waitForKey();
			break;
		}
		case InputHandler::CopyDiscordLink:
		{
			const std::string discordLink{ "https://discord.gg/yCEmcGeq3a" };
			Utils::copyDiscordLink(discordLink);
			UI::info("Link Copied to clipbord");
			Utils::clearAndIgnoreInput();
			Utils::waitForKey();
			break;
		}
		default:
		{
			UI::error("Defualt case hit in Controller");
			break;
		}
	}
	

}