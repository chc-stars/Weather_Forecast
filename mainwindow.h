#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//菜单
#include <QContextMenuEvent>

//鼠标事件
#include <QMouseEvent>

//网络请求
#include <QNetworkAccessManager>
#include <QNetworkReply>

// 提示框
#include <QMessageBox>

// Json
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <Weather_Data.h>

// 读取文件
#include <QFile>

// 键值对
#include <QMap>

// 绘制相关
#include <QPainter>
#include <QBrush>
#include <QPen>

// 定义宏
#define INCREMENT 1.5   // 温度升高、降低1度， y轴移动的像素点增量
#define PAINT_RADIUS 3  // 曲线秒点的大小
#define TEXT_OFFSET_X 12  // 温度文本X偏移
#define TEXT_OFFSET_Y 12  // 温度文本Y偏移


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    Ui::MainWindow *ui;

    // 退出菜单
    QMenu* mExitMenu;
    // 退出行为
    QAction* mExitAction;
    // 鼠标点击的pos距离左上角的pos偏移
    QPoint mOffset;
    // 网络请求
    QNetworkAccessManager* mNetWorkAccessManager;
    // 今天的数据
    Today mToday;
    // 未来几天的数据
    Day mDay[6];
    // 获取天气信息
    void getWeatherInfo (QString cityCode);
    // 解析json数据
    void parseJson(QByteArray data);
    // 去除多余内容，只保留int数据
    int parseString(QString str);
    // 更新UI控件
    void UpDateUI();

    // UI的List 用于循环赋值
    // 1.星期和日期

    QList<QLabel*> mWeekList;
    QList<QLabel*> mDateList;

    // 2.天气和日期
    QList<QLabel*> mTypeList;
    QList<QLabel*> mTypeIconList;

    // 3.天气污染指数
    QList<QLabel*> mQulityList;

    // 4.风力和风向
    QList<QLabel*> mFlList;
    QList<QLabel*> mFxList;

    QMap<QString, QString> mTypeMap;

    //检查空气质量
    int checkedQulity(int aqi);
    // 高温曲线
    void paintHighCurve();
    // 低温曲线
    void paintLowCurve();

protected:

    void contextMenuEvent(QContextMenuEvent *event);
    // 鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    // 鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    // 事件过滤器， 默认无，需重写
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    // 请求成功后执行的槽函数， 用于处理服务器返回的数据，例如解析等
    void onReplied(QNetworkReply* reply);
    // 搜索按钮
    void onBtnSerchClicked();

};

#include <QDebug>
class weathertool{
private:
    inline static QMap<QString, QString> mCityMap = {};
    static void initCityMap(){
        QString filePath = "://citycode.json";
        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray json = file.readAll();     // 读取文件到json
        file.close();

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(json, &err);
        if(err.error != QJsonParseError::NoError || !doc.isArray()){
            return;
        }
        QJsonArray rootArray = doc.array();

        for(int i = 0; i < rootArray.size(); ++i){
            QString cityName = rootArray[i].toObject().value("city_name").toString();
            QString cityCode = rootArray[i].toObject().value("city_code").toString();
            //qDebug << cityName << cityCode;

            // 判断编号是否存在
            if(cityCode.size() > 0){
                mCityMap.insert(cityName, cityCode);
            }
        }
    }

public:
    static QString getCityCode(QString cityName){
        // 检查是否为空， 为空先初始化
        if(mCityMap.isEmpty()){
            initCityMap();
        }

        // 在map寻找传入的城市名称，返回值可以遍历
        QMap<QString, QString>::Iterator it = mCityMap.find(cityName);

        // 到结尾了，未找到，加上市，再搜索一遍
        if(it == mCityMap.end()){
            it = mCityMap.find(cityName + "市");

        }

        // 找到了
        if(it != mCityMap.end()){
            return it.value();

        }
        // 还是未找到，返回空值
        return "";

    }


};
#endif // MAINWINDOW_H
