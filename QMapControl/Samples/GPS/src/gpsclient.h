#ifndef GPSCLIENT_H
#define GPSCLIENT_H

#include <QObject>
#include <QTimer>
#include <cmath>
#include <gps.h>

class GpsClient : public QObject {
    Q_OBJECT

public:
    explicit GpsClient(QObject *parent = nullptr);
    ~GpsClient();

    bool connectToGpsd(const QString &host = "localhost", const QString &port = "2947");
    void disconnectFromGpsd();
    bool isConnected() const;
    void setPacking(bool enable);

signals:
    void gpsDataUpdated(double latitude, double longitude, QString fixMode, QString timestamp);
    void gpsRawUpdate(gps_data_t &data);

private slots:
    void readGpsData();

private:
    struct gps_data_t gps_data;
    QTimer *timer;
    bool connected;
    bool packing;

    static constexpr int MODE_STR_NUM = 4;
    static const char *mode_str[MODE_STR_NUM];
};

#endif // GPSCLIENT_H
