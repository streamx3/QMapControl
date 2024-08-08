#include "gpsclient.h"
#include <QDebug>

const char *GpsClient::mode_str[MODE_STR_NUM] = {
    "n/a",
    "None",
    "2D",
    "3D"
};

GpsClient::GpsClient(QObject *parent) : QObject(parent), connected(false) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GpsClient::readGpsData);
    packing = false;
}

GpsClient::~GpsClient() {
    disconnectFromGpsd();
}

bool GpsClient::connectToGpsd(const QString &host, const QString &port) {
    if (gps_open(host.toStdString().c_str(), port.toStdString().c_str(), &gps_data) != 0) {
        qDebug() << "Open error. Bye, bye";
        return false;
    }
    gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, nullptr);
    timer->start(100); // Read GPS data every second
    connected = true;
    return true;
}

void GpsClient::disconnectFromGpsd() {
    if (connected) {
        gps_stream(&gps_data, WATCH_DISABLE, nullptr);
        gps_close(&gps_data);
        timer->stop();
        connected = false;
    }
}

bool GpsClient::isConnected() const {
    return connected;
}

void GpsClient::readGpsData() {
    if (gps_waiting(&gps_data, 0)) {
        if (gps_read(&gps_data, nullptr, 0) == -1) {
            qWarning() << "GPSD Read error. Leaving";
            disconnectFromGpsd();
            return;
        }

        if (!(gps_data.set & MODE_SET)) {
            // did not even get mode, nothing to see here
            // qDebug() << "GPSD Mode unset. Leaving";
            return;
        }

        if (gps_data.fix.mode < 0 || gps_data.fix.mode >= MODE_STR_NUM) {
            gps_data.fix.mode = 0;
        }

        emit gpsRawUpdate(gps_data);

        QString fixMode = mode_str[gps_data.fix.mode];
        QString timestamp = "n/a";
        if (gps_data.set & TIME_SET) {
            timestamp = QString("%1.%2")
            .arg(gps_data.fix.time.tv_sec)
                .arg(gps_data.fix.time.tv_nsec, 9, 10, QLatin1Char('0'));
        }

        double latitude = NAN;
        double longitude = NAN;
        if (std::isfinite(gps_data.fix.latitude) && std::isfinite(gps_data.fix.longitude)) {
            latitude = gps_data.fix.latitude;
            longitude = gps_data.fix.longitude;
        }

        emit gpsDataUpdated(latitude, longitude, fixMode, timestamp);
    } else {
        disconnectFromGpsd();
        sleep(1);
        connectToGpsd();
    }
}

void GpsClient::setPacking(bool enable) {
    packing = enable;
}
