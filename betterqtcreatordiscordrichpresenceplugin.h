#pragma once

#include "betterqtcreatordiscordrichpresence_global.h"

#include <extensionsystem/iplugin.h>
#include <discord_rpc.h>
#include <QAction>

namespace BetterQtCreatorDiscordRichPresence {
    namespace Internal {

        class BetterQtCreatorDiscordRichPresencePlugin : public ExtensionSystem::IPlugin
        {
                Q_OBJECT
                Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "BetterQtCreatorDiscordRichPresence.json")

            public:
                BetterQtCreatorDiscordRichPresencePlugin();
                ~BetterQtCreatorDiscordRichPresencePlugin();

                bool initialize(const QStringList &arguments, QString *errorString);
                void extensionsInitialized();
                ShutdownFlag aboutToShutdown();

            private:
                void initDiscord();
                QString oldProject;
        };

    } // namespace Internal
} // namespace BetterQtCreatorDiscordRichPresence
