#pragma once

#include <QtWidgets/QMainWindow>
#include<qmessagebox.h>
#include<qpainter.h>
#include<qtimer.h>


#include<queue>
#include "ui_Prim.h"

class Edge_info
{
public:
    QLineF line;//位置
    QColor color;//颜色
    int value;//权值
    Edge_info(){}
    Edge_info(QLineF line,QColor color,int v)
    {
        this->line = line;
        this->color = color;
        this->value = v;
    }
    ~Edge_info() {};
};

typedef struct node
{
    int dis;
    int pos;
    int from;
    node(int dis,int pos,int from)
    {
        this->dis = dis;
        this->from = from;
        this->pos = pos;
    }
    bool operator < (const node& x)const {
        return x.dis < dis;
    }
}Node,*LinkNode;

class Prim : public QMainWindow
{
    Q_OBJECT

public:
    Prim(QWidget *parent = nullptr);
    ~Prim();

private:
    Ui::PrimClass ui;
    static const int INF = 0x3f3f3f3f;
    //std::map<QString, std::shared_ptr<Edge_info>>Edges;
    std::map<QString, Edge_info*>Edges;
    std::map<QString, QColor>Nodes;

    //邻接表
    QVector<QPair<int, int>>AdjacencyList[20];


    //计算箭头坐标
    QPair<QPointF, QPointF>ComputeArrowHead(const QLineF line);
    void paintEvent(QPaintEvent* event);
    void visit(QString begin_name,QString end_name);
    //void init();

private slots:
    void on_AddEdge_clicked();
    void on_Prim_clicked();
    void on_Reset_clicked();
};
