#ifndef CARDMOUTHELE_H
#define CARDMOUTHELE_H

#include "moveelement.h"

namespace qt {
//卡口
class CardMouthElement : public MoveElement
{
public:
    explicit CardMouthElement(const ZCHX::Data::ITF_CardMouth &ele, zchxMapWidget* f);
    void setData(const ZCHX::Data::ITF_CardMouth &ele);
    ZCHX::Data::ITF_CardMouth data() const;

    virtual std::vector<std::pair<double, double> > path() const;
    virtual void setPath(const std::vector<std::pair<double, double> > &path);
    virtual std::vector<std::pair<double, double> > & getPath();

//    int id() const;
//    void setId(int id);

    std::string name() const;
    void setName(const std::string &name);

    void updateOldPath();
    void updateGeometry(QPointF, int){}
    void drawElement(QPainter *painter);
private:
    std::vector<std::pair<double, double>> m_path; //初始路径
    std::string      m_name;
    ZCHX::Data::ITF_CardMouth m_data;
};
}


#endif // CARDMOUTHELE_H
