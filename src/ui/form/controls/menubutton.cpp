#include "menubutton.h"

#include <QGuiApplication>
#include <QMenu>
#include <QMouseEvent>

#include <form/tray/trayicon.h>
#include <manager/windowmanager.h>
#include <util/iconcache.h>
#include <util/ioc/ioccontainer.h>

MenuButton::MenuButton(QWidget *parent) : PushButton(parent)
{
    setupUi();
}

TrayIcon *MenuButton::trayIcon() const
{
    return IoC<WindowManager>()->trayIcon();
}

void MenuButton::setupUi()
{
    setIcon(IconCache::icon(":/icons/large_tiles.png"));

    setMenu(trayIcon()->menu());
}

void MenuButton::mouseReleaseEvent(QMouseEvent *e)
{
    const bool mousePressed = this->mousePressed();

    PushButton::mouseReleaseEvent(e);

    if (!mousePressed)
        return;

    if (menu()->isVisible())
        return; // standard behavior

    trayIcon()->processMouseClick(e->button(), e->modifiers());
}
