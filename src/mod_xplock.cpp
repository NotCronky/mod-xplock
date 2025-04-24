#include "Chat.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Config.h"
#include "mod_xplock.h"

using namespace Acore::ChatCommands;

namespace
{
    class xplock_commands : public CommandScript
    {
    public:
        xplock_commands() : CommandScript("xplock_commands") {}

        ChatCommandTable GetCommands() const override
        {
            static ChatCommandTable xplockCommandTable =
            {
                { "xplock", HandleXpLockCommand, SEC_PLAYER, Console::No }
            };

            return xplockCommandTable;
        }

        static bool HandleXpLockCommand(ChatHandler* handler)
        {
            if (!sConfigMgr->GetOption<bool>(CONFIG_ENABLE_XP_COMMAND, true))
            {
                handler->SendSysMessage("XP Lock command is disabled in the config.");
                handler->SetSentErrorMessage(true);
                return false;
            }

            Player* player = handler->GetSession()->GetPlayer();
            if (!player)
                return false;

            if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN))
            {
                player->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);
                handler->PSendSysMessage("XP gain has been |cffff0000UNLOCKED|r.");
            }
            else
            {
                player->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);
                handler->PSendSysMessage("XP gain has been |cff00ff00LOCKED|r.");
            }

            return true;
        }
    };
}

void Addmod_xplockScripts()
{
    new xplock_commands();
}
