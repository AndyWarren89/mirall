/*
 * Copyright (C) by Klaas Freitag <freitag@owncloud.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef OWNCLOUDGUI_H
#define OWNCLOUDGUI_H

#include "mirall/systray.h"
#include "mirall/connectionvalidator.h"
#include "mirall/progressdispatcher.h"

#include <QObject>
#include <QPointer>
#include <QAction>
#include <QMenu>
#include <QSignalMapper>

namespace Mirall {

class SettingsDialog;
class ItemProgressDialog;
class Application;
class LogBrowser;

class ownCloudGui : public QObject
{
    Q_OBJECT
public:
    explicit ownCloudGui(Application *parent = 0);

    void setupContextMenu();
    void startupConnected(bool connected , const QStringList &fails);

    bool checkConfigExists(bool openSettings);

signals:
    void setupProxy();

public slots:
    void slotComputeOverallSyncStatus();
    void slotShowTrayMessage(const QString &title, const QString &msg);
    void slotShowOptionalTrayMessage(const QString &title, const QString &msg);
    void slotFolderOpenAction( const QString& alias );
    void slotRefreshQuotaDisplay( qint64 total, qint64 used );
    void slotRebuildRecentMenus();
    void slotProgressSyncProblem(const QString& folder, const Progress::SyncProblem& problem);
    void slotUpdateProgress(const QString &folder, const Progress::Info& progress);
    void slotShowGuiMessage(const QString &title, const QString &message);
    void slotFoldersChanged();
    void slotItemProgressDialog();
    void slotSettings();
    void slotShutdown();
    void slotSyncStateChange( const QString& alias );
    void slotTrayClicked( QSystemTrayIcon::ActivationReason reason );
    void slotToggleLogBrowser();
    void slotOpenOwnCloud();
    void slotHelp();
    void slotOpenPath(const QString& path);

private slots:
    void slotDisplayIdle();

private:
    void setupActions();

    QPointer<Systray> _tray;
    QPointer<SettingsDialog> _settingsDialog;
    QPointer<ItemProgressDialog> _progressDialog;
    QPointer<LogBrowser>_logBrowser;
       // tray's menu
    QMenu *_contextMenu;
    QMenu *_recentActionsMenu;

    QAction *_actionOpenoC;
    QAction *_actionSettings;
    QAction *_actionQuota;
    QAction *_actionStatus;
    QAction *_actionRecent;
    QAction *_actionHelp;
    QAction *_actionQuit;

    QSignalMapper *_folderOpenActionMapper;
    QSignalMapper *_recentItemsMapper;

    Application *_app;

    QStringList _startupFails;
};

} // namespace Mirall

#endif // OWNCLOUDGUI_H
