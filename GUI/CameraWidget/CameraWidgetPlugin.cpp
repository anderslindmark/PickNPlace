/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "CameraWidget.h"
#include "CameraWidgetPlugin.h"

#include <QtPlugin>

CameraWidgetPlugin::CameraWidgetPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void CameraWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool CameraWidgetPlugin::isInitialized() const
{
    return initialized;
}

QWidget *CameraWidgetPlugin::createWidget(QWidget *parent)
{
    return new CameraWidget(parent);
}

QString CameraWidgetPlugin::name() const
{
    return "CameraWidget";
}

QString CameraWidgetPlugin::group() const
{
    return "Pick n Place";
}

QIcon CameraWidgetPlugin::icon() const
{
    return QIcon();
}

QString CameraWidgetPlugin::toolTip() const
{
    return "";
}

QString CameraWidgetPlugin::whatsThis() const
{
    return "";
}

bool CameraWidgetPlugin::isContainer() const
{
    return false;
}

QString CameraWidgetPlugin::domXml() const
{
    return "<widget class=\"CameraWidget\" name=\"cameraWidget\">\n"
           " <property name=\"geometry\">\n"
           "  <rect>\n"
           "   <x>0</x>\n"
           "   <y>0</y>\n"
           "   <width>100</width>\n"
           "   <height>100</height>\n"
           "  </rect>\n"
           " </property>\n"
           " <property name=\"toolTip\" >\n"
           "  <string>Pick n Place camera widget</string>\n"
           " </property>\n"
           " <property name=\"whatsThis\" >\n"
		   "  <string>The camera widget displays images from a pick n place camera.</string>\n"
           " </property>\n"
           "</widget>\n";
}

QString CameraWidgetPlugin::includeFile() const
{
    return "CameraWidget.h";
}

Q_EXPORT_PLUGIN2(CameraWidgetPlugin, CameraWidgetPlugin)

