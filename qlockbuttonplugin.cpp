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
    return QIcon(QLatin1String(":/images/lockbutton.ico"));
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
    return "<ui language=\"c++\" displayname=\"Lock Button\">\n"
           " <widget class=\"QLockButton\" name=\"lockButton\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>300</width>\n"
           "    <height>300</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>Lock/unlock button</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>A button with lock/unlock behaviour.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString QLockButtonPlugin::includeFile() const
{
    return QStringLiteral("qlockbutton/qlockbutton.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qlockbuttonplugin, QLockButtonPlugin)
#endif // QT_VERSION < 0x050000
