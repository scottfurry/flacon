/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Flacon - audio File Encoder
 * https://github.com/flacon/flacon
 *
 * Copyright: 2012-2013
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * END_COMMON_COPYRIGHT_HEADER */


#ifndef CONVERTER_H
#define CONVERTER_H

#include "types.h"
#include <QObject>
#include <QDateTime>
#include <QVector>

class DiscPipeline;
class Disc;
class Track;
class Profile;

class Converter : public QObject
{
    Q_OBJECT
public:
    struct Job {
        Disc *disk = nullptr;
        QVector<const Track*> tracks;
    };

    typedef QVector<Job> Jobs;
    explicit Converter(QObject *parent = nullptr);
    virtual ~Converter();

    bool isRunning();
    static bool canConvert();

signals:
    void started();
    void finished();
    void trackProgress(const Track &track, TrackState state, Percent percent);

public slots:
    void start(const Profile &profile);
    void start(const Jobs &jobs, const Profile &profile);
    void stop();

private slots:
    void startThread();

private:
    int mThreadCount;
    QVector<DiscPipeline*> mDiscPiplines;

    bool check(const Profile &profile) const;
};

#endif // CONVERTER_H
