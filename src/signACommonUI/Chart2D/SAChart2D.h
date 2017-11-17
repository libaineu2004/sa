#ifndef SACHART2D_H
#define SACHART2D_H
#include "SA2DGraph.h"
#include "SACommonUIGlobal.h"
#include <memory>
class QUndoStack;
class SAChart2DPrivate;
class SAAbstractRegionSelectEditor;
class SAAbstractDatas;
class SAXYSeries;
class SABarSeries;
///
/// \brief sa 2d 曲线绘图的基本窗口封装，包括支持SAAbstractDatas的处理
///
class SA_COMMON_UI_EXPORT SAChart2D : public SA2DGraph
{
    Q_OBJECT
    Q_DISABLE_COPY(SAChart2D)
    SA_IMPL(SAChart2D)
public:
    SAChart2D(QWidget *parent = nullptr);
    ~SAChart2D();
    enum SelectionMode{
        NoneSelection ///< 无选择
        ,RectSelection ///< 矩形选框
        ,EllipseSelection ///< 椭圆选框
        ,PolygonSelection ///< 多边形选框
    };

    //添加曲线
    QwtPlotCurve* addCurve(const double *xData, const double *yData, int size);
    QwtPlotCurve* addCurve(const QVector<QPointF>& xyDatas);
    QwtPlotCurve* addCurve(const QVector< double > &xData, const QVector< double > &yData);
    SAXYSeries *addCurve(SAAbstractDatas* datas);
    SAXYSeries* addCurve(SAAbstractDatas* datas,double xStart,double xDetal);
    SAXYSeries* addCurve(SAAbstractDatas* x,SAAbstractDatas* y,const QString& name = QString());
    QList<SAXYSeries *> addCurves(QList<SAAbstractDatas*> datas);
    void addCurve(QwtPlotCurve* cur);
    void addCurve(SAXYSeries* cur);
    //添加bar
    QwtPlotHistogram* addBar(const QVector< QwtIntervalSample > &sample);
    SABarSeries *addBar(SAAbstractDatas* datas);
    void addBar(QwtPlotHistogram* cur);
    void addBar(SABarSeries* cur);
    //添加样条线
    QwtPlotMarker* addVLine(double val);
    QwtPlotMarker* addHLine(double val);
    void addPlotMarker(QwtPlotMarker* marker);
    //移除一个对象
    void removeItem(QwtPlotItem* item);
    //移除范围内数据
    void removeDataInRang(QList<QwtPlotCurve *> curves);
    //获取选择范围内的数据,如果当前没有选区，返回false
    bool getDataInSelectRange(QVector<QPointF>& xy,QwtPlotCurve *cur);
    //开始选择模式
    void enableSelection(SelectionMode mode, bool on = true);
    //判断当前的选择模式
    bool isEnableSelection(SelectionMode mode) const;
    //清除所有选区
    void clearAllSelectedRegion();
    //判断是否有选区
    bool isRegionVisible() const;
    //获取当前正在显示的选择区域
    SelectionMode currentSelectRegionMode() const;
    //获取当前选择编辑器
    SAAbstractRegionSelectEditor* getRegionSelectEditor();
    const SAAbstractRegionSelectEditor* getRegionSelectEditor() const;
    //获取当前可见的选区的范围
    QPainterPath getSelectionRange() const;
    //ctrl+z || ctrl + y
    void redo();
    void undo();
    //获取redo undo stack
    QUndoStack* undoStack();
protected:
    //开始矩形选框模式
    void startRectSelectMode();
    //开始椭圆选框模式
    void startEllipseSelectMode();
    //开始椭圆选框模式
    void startPolygonSelectMode();
    //结束选区模式但不清空
    void stopSelectMode();
protected slots:
    // 选区选择完成
    void onSelectionFinished(const QPainterPath& shape);
private:
    QList<SAXYSeries *> addDatas(const QList<SAAbstractDatas*>& datas);
protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

};

#endif // SACHART2D_H
