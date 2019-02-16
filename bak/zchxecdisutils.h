#ifndef ZCHXECDISUTILS_H
#define ZCHXECDISUTILS_H

#include <math.h>
#include <QString>
#include <QDateTime>
#include <QPixmap>

#define     GLOB_PI                                 (3.14159265358979323846)
#define     DOUBLE_EPS                              0.000001
#define     EARTH_HALF_CIRCUL_LENGTH                20037508.3427892
#define     MAP_IMG_SIZE                            256

#define         DATETIME_STRING(datetime)       (datetime.toString("yyyy-MM-dd hh:mm:ss"))
#define         FLOAT_STRING(val ,n)   (QString::number(val, 'f', n))
#define         INT_STRING(val)      (QString("").sprintf("%d", val))
#define         INT_COMMA_STRING(val) (QString("%L1").arg(val))
#define         TIMESTAMP16_STRING(val) ( DATETIME_STRING(QDateTime::fromMSecsSinceEpoch(val)))
#define         TIMESTAMP10_STRING(val) ( DATETIME_STRING(QDateTime::fromTime_t(val)))
#define         KPH2KTS(val)            ((val) / 1.852)
#define         MPS2KTS(val)            (KPH2KTS((val) * 3.6))
#define         TIMEOFDAY2UTC(val)      (QDateTime(QDate::currentDate()).toMSecsSinceEpoch() + (val*1000))

struct Mercator{
public:
    Mercator() {mX = 0.0; mY = 0.0;}
    Mercator(double x, double y){mX = x; mY= y;}
    bool operator ==(const Mercator& other)
    {
        return fabs(this->mX- other.mX) <= DOUBLE_EPS  && \
               fabs(this->mY - other.mY) <= DOUBLE_EPS ;
    }
    double mX;
    double mY;
};

struct Wgs84LonLat{
public:
    Wgs84LonLat() {mLon = 0.0; mLat = 0.0;}
    Wgs84LonLat(double x, double y){mLon = x; mLat= y;}
    bool operator ==(const Wgs84LonLat& other) const
    {
        return fabs(this->mLon - other.mLon) <= DOUBLE_EPS  && \
               fabs(this->mLat - other.mLat) <= DOUBLE_EPS ;
    }

    double mLon;
    double mLat;
};

struct Point2D{
    double x;
    double y;

    Point2D(double px, double py) {
        x = px;
        y = py;
    }

    Point2D()
    {
        x = 0;
        y = 0;
    }

    Point2D(const QPoint& p)
    {
        x = p.x();
        y = p.y();
    }

    Point2D(const QPointF& p)
    {
        x = p.x();
        y = p.y();
    }
};

//struct strLatLon{
//    double lat;
//    double lon;
//};

struct MapRangeData{
    Mercator    mLowerLeft;         //左下
    Mercator    mTopRight;          //右上
};

enum    TILE_ORIGIN_POS{
    TILE_ORIGIN_TOPLEFT = 0,        //左上
    TILE_ORIGIN_BOTTEMLEFT,         //左下
};

enum    TILE_SOURCE{
    TILE_GOOGLE = 0,
    TILE_TMS,
};

//每次加载瓦片地图的参数设定,主要是视窗的墨卡托范围,视窗屏幕坐标大小
struct MapLoadSetting{
    MapRangeData    mMapRange;
    double          mResolution;
    int             mZoom;
    int             mSource; //0:本地1:服务器地址
    int             mTilePos;
    Wgs84LonLat     mCenter;
};

//瓦片图片信息
struct TileImage {
    QPixmap    mImg;
    int         mPosX;
    int         mPosY;
    QString     mName;

    TileImage(){}

    TileImage(const QPixmap& img, int x, int y, const QString& name = QString())
    {
        mImg = img;
        mPosX = x;
        mPosY = y;
        mName = name;
    }
};

class TileImageList:public QList<TileImage>
{
public:
    TileImageList():QList<TileImage>() {}
//    ~TileImageList()
//    {
//        for(int i=0; i<size(); i++)
//        {
//            QPixmap* img = this->at(i).mImg;
//            if(img) delete img;
//        }
//    }

//    void clear()
//    {
//        for(int i=0; i<size(); i++)
//        {
//            QPixmap* img = this->at(i).mImg;
//            if(img) delete img;
//        }

//        QList<TileImage>::clear();
//    }

};

Q_DECLARE_METATYPE(TileImage)
Q_DECLARE_METATYPE(TileImageList)


class zchxEcdisUtils
{
public:
    zchxEcdisUtils();
    //墨卡托和wgs84互转
    static Wgs84LonLat mercatorToWgs84LonLat(const Mercator& mercator);
    static Mercator wgs84LonlatToMercator(const Wgs84LonLat& wgs84 );
    static double calResolution(int zoom);


};

#endif // ZCHXECDISUTILS_H