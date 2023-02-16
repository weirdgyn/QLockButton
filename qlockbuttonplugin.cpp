#include "qlockbutton/qlockbutton.h"
#include "qlockbuttonplugin.h"

#include <QtPlugin>

QLockButtonPlugin::QLockButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QLockButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QLockButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QLockButtonPlugin::createWidget(QWidget *parent)
{
    return new QLockButton(parent);
}

QString QLockButtonPlugin::name() const
{
    return QLatin1String("QLockButton");
}

QString QLockButtonPlugin::group() const
{
    return QLatin1String("");
}

QIcon QLockButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/lockbutton.ico"));
}

QString QLockButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QLockButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QLockButtonPlugin::isContainer() const
{
    return false;
}

QString QLockButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QLockButton\" name=\"qLockButton\">\n</widget>\n");
}

QString QLockButtonPlugin::includeFile() const
{
    return QLatin1String("qlockbutton/qlockbutton.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qlockbuttonplugin, QLockButtonPlugin)
#endif // QT_VERSION < 0x050000
