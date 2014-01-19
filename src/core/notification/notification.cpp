/*
    SnoreNotify is a Notification Framework based on Qt
    Copyright (C) 2013-2014  Patrick von Reth <vonreth@kde.org>


    SnoreNotify is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SnoreNotify is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with SnoreNotify.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "notification.h"
#include "snore.h"
#include "notification/icon.h"
#include "notification/notification_p.h"
#include "plugins/plugincontainer.h"
#include <Qt>

using namespace Snore;


int Notification::m_defaultTimeout = 10;

int NotificationData::notificationMetaID = qRegisterMetaType<Notification>();


Notification::Notification () :
    d(NULL)
{
}

Notification::Notification(const Application &application, const Alert &alert, const QString &title, const QString &text, const Icon &icon, int timeout, NotificationEnums::Prioritys::prioritys priority):
    d(new  NotificationData(application,alert,title,text,icon,timeout,priority))
{

}

Notification::Notification(const Notification &old, const QString &title, const QString &text, const Icon &icon, int timeout, NotificationEnums::Prioritys::prioritys priority):
    d(new  NotificationData(old,title,text,icon,timeout,priority))
{
}

Notification::Notification ( const Notification &other ) :
    d(other.d)
{
}

Notification &Notification::operator=(const Notification &other)
{
    d = other.d;
    return *this;
}

Notification::~Notification()
{
}

uint Notification::id() const
{
    return d->m_id;
}

const Icon &Notification::icon() const
{
    return d->m_icon;
}

const int &Notification::timeout() const
{
    return d->m_timeout;
}

Notification Notification::old() const
{
    return d->m_toReplace;
}

bool Notification::isUpdate() const
{
    return d->m_toReplace.isValid();
}

const Action &Notification::actionInvoked() const
{
    return d->m_actionInvoked;
}

const Application &Notification::application() const
{
    return d->m_application;
}

QString Notification::title() const
{
    return d->m_title;
}

QString Notification::text() const
{
    return d->m_text;
}

const Alert &Notification::alert() const
{
    return d->m_alert;
}

bool Notification::isSticky() const
{
    return d->m_timeout == 0;
}

void Notification::setIsSticky(bool b)
{
    if(b)
    {
        d->m_timeout = 0;
    }
}

NotificationEnums::Prioritys::prioritys Notification::priority() const
{
    return d->m_priority;
}

void Notification::addAction(const Action &a)
{
    d->m_actions.insert(a.id(),a);
}


const QHash<int, Action> &Notification::actions() const
{
    return d->m_actions;
}

const NotificationEnums::CloseReasons::closeReasons &Notification::closeReason(){
    return d->m_closeReason;
}

Hint &Notification::hints()
{
    return d->m_hints;
}

const Hint &Notification::constHints() const
{
    return d->m_hints;
}

void Notification::setSilent(bool silent)
{
    d->m_hints.setValue("silent", silent);
}

bool Notification::isValid() const
{
    return d;
}

NotificationData *Notification::data()
{
    return d.data();
}
int Notification::defaultTimeout()
{
    return m_defaultTimeout;
}

void Notification::setDefaultTimeout(int defaultTimeout)
{
    m_defaultTimeout = defaultTimeout;
}

QDataStream &operator<< ( QDataStream &stream, const Notification &noti )
{
    stream << "Title: " << noti.title() << " Text: " << noti.text() << " ID: " << noti.id() ;
    return stream;
}



