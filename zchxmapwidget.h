#ifndef ZCHXMAPWIDGET_H
#define ZCHXMAPWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QPixmap>
#include "zchxecdisutils.h"

struct MapData{
    QPixmap img;
    int x;
    int y;
};

class zchxMapView;
class zchxMapLoadThread;

class zchxMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit zchxMapWidget(QWidget *parent = 0);
    ~zchxMapWidget();
    void setCurZoom(int zoom);
    int  zoom() const;
    void setCenterLL(const Wgs84LonLat& pnt );
    Wgs84LonLat centerLonlat() const;
private:
    void updateCurrentPos(const QPoint& p);

protected:
    void paintEvent(QPaintEvent* e);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void resizeEvent(QResizeEvent *);
#ifndef QT_NO_WHEELEVENT
    virtual void wheelEvent(QWheelEvent *);
#endif

signals:
    void signalDisplayCurPos(double lon, double lat);
    void signalSendNewMap(double, double, int);

public slots:
    void append(const QPixmap& img, int x, int y);    
    void clear() {mDataList.clear(); update();}
    void slotRecvNewMap(double lon, double lat, int zoom);
private:
    QList<MapData> mDataList;
    zchxMapView*        mView;
    zchxMapLoadThread*  mMapThread;
    Wgs84LonLat         mCenter;
    qint64              mLastWheelTime;
    bool                mDrag;
    QPoint              mPressPnt;
};

#endif // ZCHXMAPWIDGET_H
