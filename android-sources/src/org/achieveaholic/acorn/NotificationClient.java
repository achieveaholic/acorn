/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtAndroidExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

package org.achieveaholic.acorn;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;

import androidx.core.app.NotificationCompat;
import androidx.core.app.TaskStackBuilder;

public class NotificationClient extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static NotificationManager notificationManager;
    private static NotificationCompat.Builder builder;
    private static NotificationClient instance;
    private static Context context;

    private static final String TASK_NOTIFICATION_ID = "acorn.task.reminder";

    public NotificationClient()
    {
        instance = this;
    }

    public static void notify(String message)
    {
        if (context == null) {
            context = instance.getApplicationContext();
        }
        if (notificationManager == null) {
            notificationManager = (NotificationManager)instance.getSystemService(Context.NOTIFICATION_SERVICE);

            int smallIcon;
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                final String id = NotificationClient.TASK_NOTIFICATION_ID;
                final CharSequence name = "Task reminder";
                final String description = "Task reminder notifications";
                final int importance = NotificationManager.IMPORTANCE_HIGH;
                final NotificationChannel mChannel = new NotificationChannel(id, name, importance);
                mChannel.setDescription(description);
                mChannel.enableLights(true);
                mChannel.setLightColor(Color.MAGENTA);
                mChannel.enableVibration(true);
                mChannel.setVibrationPattern(new long[]{100, 200, 300, 400, 500, 400, 300, 200, 400});
                mChannel.setShowBadge(false);
                notificationManager.createNotificationChannel(mChannel);

                smallIcon = R.drawable.icon_notification;
            } else {
                smallIcon = R.drawable.icon;
            }

            builder = new NotificationCompat.Builder(context, NotificationClient.TASK_NOTIFICATION_ID)
                    .setSmallIcon(smallIcon)
                    .setContentTitle("Acorn test notification!")
                    .setContentText(message);

            Intent resultIntent = new Intent(context, NotificationClient.class);
            TaskStackBuilder stackBuilder = TaskStackBuilder.create(context);
            stackBuilder.addParentStack(NotificationClient.class);
            stackBuilder.addNextIntent(resultIntent);
            PendingIntent resultPendingIntent = stackBuilder.getPendingIntent(0, PendingIntent.FLAG_UPDATE_CURRENT);

            builder.setContentIntent(resultPendingIntent);
        }

        builder.setContentText(message);
        notificationManager.notify(1, builder.build());
    }
}
