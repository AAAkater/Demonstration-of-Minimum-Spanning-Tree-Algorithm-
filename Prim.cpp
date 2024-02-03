#include "Prim.h"

Prim::Prim(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

Prim::~Prim()
{}

void Prim::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //边
    for (const auto& [EdgeName, EdgeInfo] : this->Edges)
    {
        QColor EdgeColor = EdgeInfo->color;
        QLineF EdgeLine = EdgeInfo->line;
        int EdgeValue = EdgeInfo->value;


        double midx = (EdgeLine.p1().x() + EdgeLine.p2().x()) / 2.0;
        double midy = (EdgeLine.p1().y() + EdgeLine.p2().y()) / 2.0;

        //在边的中点 显示边长度
        painter.setPen(QPen(Qt::black));
        painter.setFont(QFont("Microsoft YaHei UI", 20));
        painter.drawText(QPointF(midx, midy), QString::number(EdgeValue));
        //画边
        painter.setPen(QPen(EdgeColor, 3));
        painter.drawLine(EdgeLine);

        //const auto [p1, p2] = this->ComputeArrowHead(EdgeLine);
        //painter.drawLine(EdgeLine.p2(), p1);
        //painter.drawLine(EdgeLine.p2(), p2);
    }

    //节点
    for (const auto& node : this->findChildren<QLabel*>())
    {
        //该label不是节点就跳过
        if (this->Nodes.find(node->objectName()) == this->Nodes.end())
            continue;

        QString NodeName = node->objectName();
        QColor NodeColor = this->Nodes[NodeName];
        QString rgb = QString("rgb(%1,%2,%3)")
            .arg(NodeColor.red())
            .arg(NodeColor.green())
            .arg(NodeColor.blue());

        node->setAutoFillBackground(true);
        node->setStyleSheet(QString(
            "color:white;"
            "border-radius:25px;"
            "background-color: %1;").arg(rgb));//节点颜色
    }


}

//计算箭头坐标
QPair<QPointF, QPointF> Prim::ComputeArrowHead(const QLineF line)
{
    QPointF begin = line.p1();
    QPointF end = line.p2();

    //画箭头 
    int arrowSize = 10;//箭头大小
    double arrowAngle = M_PI / 6;//箭头夹角

    double angle = std::atan2(line.dy(), line.dx());
    QPointF arrowP1 = end - QPointF(cos(angle + arrowAngle) * arrowSize, sin(angle + arrowAngle) * arrowSize);
    QPointF arrowP2 = end - QPointF(cos(angle - arrowAngle) * arrowSize, sin(angle - arrowAngle) * arrowSize);


    return qMakePair(arrowP1, arrowP2);
}


//void Prim::init()
//{
//
//
//
//    for (auto& [EdgeName, EdgeInfo] : this->Edges)
//        EdgeInfo->~Edge_info();
//    this->Edges.clear();
//
//
//
//}


void Prim::visit(QString begin_name, QString end_name)
{

    qDebug() << begin_name << " " << end_name;
    this->Edges[begin_name + "<->" + end_name]->color = Qt::red;
    this->Nodes[begin_name] = Qt::red;
    this->Nodes[end_name] = Qt::red;


    int interval = 1000; // 0.1秒延迟
    QTimer::singleShot(interval, [&]() {
            update();
        });


    QEventLoop loop;
    QTimer::singleShot(interval, &loop, &QEventLoop::quit);
    loop.exec();


}
