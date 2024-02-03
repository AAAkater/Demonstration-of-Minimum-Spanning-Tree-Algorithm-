#include "Prim.h"

void Prim::on_AddEdge_clicked()
{
    QString begin_node = ui.Begin->currentText();//起点节点名称
    QString end_node = ui.End->currentText();//终点节点名称
    QString value = ui.EdgeValue->text();//边权

    //值为空 || 不是全数字 || 终点和起点相同
    if (value == "" || !value.contains(QRegularExpression("^\\d+$")) || begin_node == end_node)
    {
        QMessageBox::critical(this, "错误", "非法输入");
        ui.EdgeValue->setText("");
        return;
    }
    //清空输入框
    ui.EdgeValue->setText("");


    int radius = 30;

    QPointF begin_pos = this->findChild<QLabel*>(begin_node)->pos() + QPointF(radius, radius);//起点节点圆心坐标
    QPointF end_pos = this->findChild<QLabel*>(end_node)->pos() + QPointF(radius, radius);//终点节点圆心坐标


    //double dx = begin_pos.x() - end_pos.x();
    //double dy = begin_pos.y() - end_pos.y();
    //double dis = sqrt(dx * dx + dy * dy);
    //double ux = dx / dis;
    //double uy = dy / dis;

    //begin_pos = QPointF(begin_pos.x() - radius * ux, begin_pos.y() - radius * uy);
    //end_pos = QPointF(end_pos.x() + radius * ux, end_pos.y() + radius * uy);

    QLineF qline(begin_pos, end_pos);//重新计算边的两点坐标


    int begin_number = begin_node.mid(1).toInt();//起点节点编号
    int end_number = end_node.mid(1).toInt();//终点节点编号
    int edge_value = value.toInt();//边权


    //建立双向边
    this->AdjacencyList[begin_number].emplaceBack(end_number, edge_value);
    this->AdjacencyList[end_number].emplaceBack(begin_number, edge_value);
	//给节点染色	
	this->Nodes[begin_node] = Qt::blue;
	this->Nodes[end_node] = Qt::blue;
    //存储边的信息 如颜色 位置 值
    //auto new_edge = std::make_shared<Edge_info>(qline, Qt::blue, edge_value);
    Edge_info* new_edge = new Edge_info(qline, Qt::blue, edge_value);
    QString edge_name_1 = begin_node + "<->" + end_node;
    QString edge_name_2 = end_node + "<->" + begin_node;
    this->Edges[edge_name_1] = new_edge;
    this->Edges[edge_name_2] = new_edge;

    update();
}


void Prim::on_Prim_clicked()
{
    int dis[10];
    bool vis[10];
    memset(dis, Prim::INF, sizeof dis);
    memset(vis, false, sizeof vis);
    int res = 0;
    auto Prim = [&](int begin) -> int 
        {
            std::priority_queue<Node>q;
            dis[begin] = 0;
            q.push(*new node(dis[begin], begin, begin));

            while (!q.empty())
            {
                Node now = q.top();
                int pos = now.pos;
                int Dis = now.dis;
                q.pop();
                if (vis[pos])
                    continue;
                vis[pos] = true;
                if (now.from != now.pos)
                {
                    this->visit("v" + QString::number(now.from), "v" + QString::number(now.pos));
                    res += Dis;
                }

                qDebug() << now.from << " " << now.pos << "\n";

                for (const auto& [to, w] : this->AdjacencyList[pos])
                {
                    if (dis[to] > w)
                    {
                        dis[to] = w;
                        q.push(*new node(dis[to], to, pos));
                    }
                }

            }
            return res;
        };


    int len=Prim(1);
    this->findChild<QLabel*>("text")->setText(QString::number(len));

}


void Prim::on_Reset_clicked()
{
    this->findChild<QLabel*>("text")->setText("0");
    for (auto& [EdgeName, EdgeInfo] : this->Edges)
        EdgeInfo->~Edge_info();
    this->Edges.clear();

    for (auto& [NodeName, NodeColor] : this->Nodes)
        NodeColor = Qt::blue;

    for (auto& item : this->AdjacencyList)
        item.clear();
    
    update();
}