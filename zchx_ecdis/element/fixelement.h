#ifndef FIXELEMENT_H
#define FIXELEMENT_H

#include "IDrawElement.hpp"

namespace qt {
template <typename T>
class ZCHX_ECDIS_EXPORT FixElement : public Element
{
public:
    explicit  FixElement(const T& data, ZCHX::Data::ELETYPE type, const QString& layer, zchxMapWidget* w)
        :Element(data.getLat(), data.getLon(), w, type)
    {
        setData(data);
        setLayer(layer);
        setFix(true);
    }

    T data() const {return m_data;}
    virtual void setData(const T& data) {
        m_data = data;
        setIsUpdate(true);
        setID(m_data.getID());
    }
    std::string name() const {return m_data.getDisplayName().toStdString();}
//    void updateGeometry(QPointF pos, QSize size)
//    {
//        m_boundingRect.setSize(size);
//        m_boundingRect.moveCenter(pos);
//        Element::updateGeometry(pos, size);
//    }

protected:
    T       m_data;
};

}

#endif // FIXELEMENT_H
