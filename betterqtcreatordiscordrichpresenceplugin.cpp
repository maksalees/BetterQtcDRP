#include "betterqtcreatordiscordrichpresenceplugin.h"
#include "betterqtcreatordiscordrichpresenceconstants.h"

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projecttree.h>

namespace BetterQtCreatorDiscordRichPresence {
    namespace Internal {

        BetterQtCreatorDiscordRichPresencePlugin::BetterQtCreatorDiscordRichPresencePlugin()
        {
            // Create your members
        }

        BetterQtCreatorDiscordRichPresencePlugin::~BetterQtCreatorDiscordRichPresencePlugin()
        {
            // Unregister objects from the plugin manager's object pool
            // Delete members
        }

        bool BetterQtCreatorDiscordRichPresencePlugin::initialize(const QStringList &arguments, QString *errorString)
        {
            // Register objects in the plugin manager's object pool
            // Load settings
            // Add actions to menus
            // Connect to other plugins' signals
            // In the initialize function, a plugin can be sure that the plugins it
            // depends on have initialized their members.

            Q_UNUSED(arguments)
            Q_UNUSED(errorString)

            //Register Discord Rich Presence
            initDiscord();
            DiscordRichPresence presence;
            memset(&presence, 0, sizeof(presence));
            presence.state = "Idle";
            presence.details = "Startup Screen";
            presence.largeImageKey = "qtcreator-logo";
            presence.largeImageText = "Working with Qt Creator";
            presence.instance = 1;
            Discord_UpdatePresence(&presence);

            //Connect to file editing signals
            connect(Core::EditorManager::instance(), &Core::EditorManager::currentEditorChanged, [=](Core::IEditor *editor) {
                DiscordRichPresence presence;
                memset(&presence, 0, sizeof(presence));

                if (editor == nullptr) return;

                //Depending on file extension choose an icon
                QString mimeType = editor->document()->mimeType();

                const char *smallImageKey = "", *smallImageText;
                if (mimeType == "text/x-c++hdr") { // C++ Header
                    smallImageKey = "file-cpphdr";
                    smallImageText = "C++ Header";
                } else if (mimeType == "text/x-c++src") { // C++ Source
                    smallImageKey = "file-cppsrc";
                    smallImageText = "C++ Source";
                } else if (mimeType == "text/x-chdr") { // C Header
                    smallImageKey = "file-chdr";
                    smallImageText = "C Header";
                } else if (mimeType == "text/x-csrc") { // C Source
                    smallImageKey = "file-csrc";
                    smallImageText = "C Source";
                } else if (mimeType == "application/vnd.qt.qmakeprofile" || mimeType == "application/vnd.qt.qmakeproincludefile") { // QMake Profile
                    smallImageKey = "file-qtprj";
                    smallImageText = "QMake Project Profile";
                } else if (mimeType == "application/x-designer") { // Designer
                    smallImageKey = "file-qtui";
                    smallImageText = "Qt User Interface File";
                } else if (mimeType == "application/vnd.qt.xml.resource") { // Qt Resource
                    smallImageKey = "file-qtres";
                    smallImageText = "Qt Resource File";
                } else if (mimeType == "application/x-desktop") { // Desktop File
                    smallImageKey = "file-desktop";
                    smallImageText = "Desktop File";
                } else if (mimeType == "application/json") { // JSON File
                    smallImageKey = "file-json";
                    smallImageText = "JSON File";
                } else if (mimeType == "text/plain") { // Text File
                    smallImageKey = "file-txt";
                    smallImageText = "Plain Text";
                } else if (mimeType == "application/xml") { // XML File
                    smallImageKey = "file-xml";
                    smallImageText = "XML File";
                } else if (mimeType == "text/html") { // HTML File
                    smallImageKey = "file-html";
                    smallImageText = "HTML File";
                } else if (mimeType == "application/javascript") { // JavaScript File
                    smallImageKey = "file-javascript";
                    smallImageText = "JavaScript File";
                } else if (mimeType == "text/x-qml") { // QML File
                    smallImageKey = "file-qml";
                    smallImageText = "QML File";
                } else if (mimeType == "text/x-cmake-project") { // CMake Project
                    smallImageKey = "file-makefile";
                    smallImageText = "CMake Project";
                } else if (mimeType == "text/x-cmake") { // CMake File
                    smallImageKey = "file-makefile";
                    smallImageText = "CMake File";
                } else if (mimeType == "text/x-makefile") { // Makefile
                    smallImageKey = "file-makefile";
                    smallImageText = "Makefile";
                } else if (mimeType == "text/x-python") { // Python File
                    smallImageKey = "file-python";
                    smallImageText = "Python File";
                } else if (mimeType == "text/x-python-project") { // Python Project
                    smallImageKey = "file-python";
                    smallImageText = "Python Project";
                } else if (mimeType == "application/octet-stream") { // Binary File
                    smallImageKey = "file-binary";
                    smallImageText = "Binary File";
                } else if (mimeType.startsWith("image")) { // Image
                    smallImageKey = "file-image";
                    smallImageText = "Image";
                } else if (mimeType.startsWith("audio")) { // Audio
                    smallImageKey = "file-audio";
                    smallImageText = "Audio";
                } else if (mimeType.startsWith("font")) { // Font
                    smallImageKey = "file-font";
                    smallImageText = "Font";
                } else if (mimeType == "text/vnd.qtcreator.git.submit") { // Git commit window
                    smallImageKey = "git-commit-window";
                    smallImageText = "Git commit window";
                }

                if (smallImageKey != nullptr && smallImageKey[0] == '\0') {
                    presence.largeImageKey = "qtcreator-logo";
                    presence.largeImageText = "Working with Qt Creator";
                } else {
                    presence.largeImageKey = smallImageKey;
                    presence.largeImageText = smallImageText;
                    presence.smallImageKey = "qtcreator-logo-small";
                    presence.smallImageText = "Working with Qt Creator";
                }

                ProjectExplorer::Project* current = ProjectExplorer::ProjectTree::currentProject();
                char stateString[256];
                if (current == nullptr) {
                    if (editor->isDesignModePreferred()) {
                        sprintf(stateString, "Designing some UI");
                    } else {
                        sprintf(stateString, "Editing a file");
                    }
                    oldProject = "";
                } else {
                    sprintf(stateString, "%s", current->displayName().prepend("Working on ").toUtf8().data());

                    if (oldProject != current->displayName()) {
                        oldProject = current->displayName();
                    }
                }
                presence.state = stateString;

                char detailsString[256];
                sprintf(detailsString, "%s", editor->document()->filePath().fileName().toUtf8().data());
                presence.details = detailsString;

                presence.instance = 1;
                Discord_UpdatePresence(&presence);
            });

            return true;
        }

        void BetterQtCreatorDiscordRichPresencePlugin::extensionsInitialized()
        {
            // Retrieve objects from the plugin manager's object pool
            // In the extensionsInitialized function, a plugin can be sure that all
            // plugins that depend on it are completely initialized.
        }

        ExtensionSystem::IPlugin::ShutdownFlag BetterQtCreatorDiscordRichPresencePlugin::aboutToShutdown()
        {
            // Save settings
            // Disconnect from signals that are not needed during shutdown
            // Hide UI (if you add UI that is not in the main window directly)

            Discord_Shutdown();
            return SynchronousShutdown;
        }

        void BetterQtCreatorDiscordRichPresencePlugin::initDiscord() {
            DiscordEventHandlers handlers;
            memset(&handlers, 0, sizeof(handlers));
            handlers.ready = [](const DiscordUser* user) {
                Q_UNUSED(user);
                qDebug() << "Discord ready!";
            };
            handlers.errored = [](int errorCode, const char* message) {
                qDebug() << QString("Discord error! Code: %1, message: %2").arg(errorCode).arg(QString::fromStdString(message));
            };
            handlers.disconnected = [](int errorCode, const char* message) {
                qDebug() << QString("Discord disconnected! Code: %1, message: %2").arg(errorCode).arg(QString::fromStdString(message));
            };
            Discord_Initialize("707316362552541215", &handlers, true, nullptr);
        }

    } // namespace Internal
} // namespace BetterQtCreatorDiscordRichPresence
