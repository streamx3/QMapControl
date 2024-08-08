// Qt includes.
#include <QApplication>
#include <cmath>

// Local includes.
#include "gps.h"
#include "gpsclient.h"

int main(int argc, char *argv[])
{
    // Create a QApplication.
    QApplication app(argc, argv);

    GpsClient gpsClient;


    // Create a GPS widget.
    GPS gps;

    QObject::connect(&gpsClient, &GpsClient::gpsRawUpdate, [&gps](gps_data_t &data){
        qDebug() << "Update";
        auto climb = data.fix.climb ;
        if(std::isnan(climb)){
            climb = 0;
        }
        auto lat = data.fix.latitude;
        auto lon = data.fix.longitude;
        if(!std::isnan(lat) && !std::isnan(lon)){
            qDebug().noquote().nospace() << qSetRealNumberPrecision(10) << "[" << lat << ":" << lon << "] cl: " << climb;
            PointWorldCoord point(data.fix.longitude, data.fix.latitude);
            gps.updatePosition(0.0, point);
        } else {
            qDebug() << "Position missing";
        }
    });

    if (gpsClient.connectToGpsd()) {
        qDebug() << "Connected to GPSD";
    } else {
        qDebug() << "Failed to connect to GPSD";
    }

    gps.resize(480, 640);
    gps.setWindowTitle("QMapControl: GPS");

    // Show the widget.
    gps.show();

    // Execute the application.
    return app.exec();
}
