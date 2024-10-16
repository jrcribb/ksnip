/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "InstanceLock.h"

InstanceLock::InstanceLock()
{
    QString key = QString("KsnipInstanceLock_%1").arg(getuid());
    mSingular = new QSharedMemory(key, this);
}

InstanceLock::~InstanceLock()
{
	if(mSingular->isAttached()) {
		mSingular->detach();
	}
}

bool InstanceLock::lock()
{
    return create();
}

bool InstanceLock::create()
{
	if(mSingular->attach()) {
		mSingular->detach();
	}

    return mSingular->create(1);
}

bool InstanceLock::attachDetach()
{
	if (mSingular->attach(QSharedMemory::ReadOnly)) {
		mSingular->detach();
		return true;
	}
	return false;
}
