#ifndef VIDEOTARGETELE_H
#define VIDEOTARGETELE_H

#include "fixelement.h"

namespace qt {
//人车船
class ZCHX_ECDIS_EXPORT VideoTargetElement : public FixElement<ZCHX::Data::ITF_VideoTarget>
{
public:
    explicit VideoTargetElement(const ZCHX::Data::ITF_VideoTarget & data, zchxMapWidget* work);

    uint getTargetStatus() const;
    uint getTargetType() const;
    uint getAlarmType() const;
    QString getObjId() const;
    QString getAlarmColor() const;

    void drawElement(QPainter* painter);
    void copyDataFromOther(std::shared_ptr<Element> other);
private:
    QStringList  mTargetIImgList;
};

}

#endif // VIDEOTARGETELE_H
