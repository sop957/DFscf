#include "widget.h"
#include "ui_widget.h"
#include "QLabel"
#include "QPushButton"
#include "QTimer"
#include "QFont"
#include "QLineEdit"
#include "QPlainTextEdit"
#include "QScrollArea"
#include "QScrollBar"
#include <QTextBrowser>
#include <string>
#include "QTime"
#include <QGuiApplication>
#include <QClipboard>
#include <QAudioDevice>
#include <QAudioOutput>
#include <QMediaPlayer>
void copyAndroid(const QString &text)
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    if (clipboard) {
        clipboard->setText(text);
        qDebug() << "文本已复制到剪贴板:" << text;
    }
}
int minute=0;       // 分钟 (0-59)
double second=0;      // 秒 (0-59)
int msec=0;         // 毫秒 (0-999)
QTime currentTime;
std::vector<std::string> WuPinName =  {
    // 原有物品（已转简体）
    "典狱长收藏室房卡", "三级监狱权限卡", "生物样本室房卡", "监狱资讯室房卡", "二级监狱权限卡", "人偶影印室房卡",
    "水位控制室房卡", "餐厅洗碗间房卡", "一级监狱权限卡", "地下金库储藏间房卡", "总会镶室房卡", "旅店用餐间房卡",
    "博物馆展套间房卡", "浴场贵宾室房卡", "Relink植入手术室房卡", "医疗会议室房卡", "博物馆废弃展廊房卡", "1号资讯室房卡",
    "总裁会客室", "黑室服务器室", "蓝室核心", "东区吊桥", "蓝室数据中心", "蓝室玻璃房",
    "组装厂房二楼实验室房卡", "西区大门房卡", "员工通道房卡", "东楼经理室房卡", "变电站技术室房卡", "西楼控制室房卡",
    "西楼监视室房卡", "设备领用室房卡", "售票游公室房卡", "军警保管室房卡", "水泥厂宿舍201房卡", "中心贵宾室房卡",
    "体能针", "普罗透斯干扰器", "感知强化剂", "M2肌肉注射剂", "潜能活化针", "OE2战斗兴奋剂",
    "感知活化针", "M1肌肉强化针", "去甲肾上腺素",
    "高级装甲维修组合", "高级头盔维修组合", "精密装甲维修包", "精密头盔维修包", "标准装甲维修包",
    "标准头盔维修包", "自毁装甲维修包", "自毁头盔维修包",
    "微型反应堆", "试裂聚变供能单元", "助力电池组", "装甲电池", "高能瓦斯罐", "燃料电池",
    "高性能燃油", "固体燃料", "电动车电池",
    "绝密服务器", "云储存阵列", "已封存音讯", "潮汐监狱地图-4", "量子储存器", "实验数据",
    "Alpha脑模机实验数据-渡鸦", "阵列服务器", "军用地雷匣",
    "三角蚌小珍珠", "马赛克灯台", "仿典匕首", "阿萨拉特色提灯", "阿萨拉风情水烟壶", "阿萨拉特色酒壶",
    "海盗弯刀", "黄金饰章", "椅角瑞饰", "珠宝头冠", "喜姆瓷偶", "金枝桂冠",
    "赛伊德的手弩", "雷斯的乐谱本", "功绩勋章", "卫队长扳指", "优秀雇员奖章", "格赫罗斯的审判",
    "天圆地方", "黄金羚羚", "化石", "金条", "赛伊德的怀表", "名贵机械表",
    "鎏金卡牌", "本地特色首饰", "座钟",
    "非洲之心", "海洋之泪", "主战坦克模型", "纵横", "印象派名画", "万金涡冠",
    "名瓷瓷器", "步战车模型", "雷斯的留声机", "克努迪乌斯半身像", "滑膛枪展品", "黄金鲸鱼头颅雕像",
    "一拖一咖啡机", "强力吸尘器", "奥莉薇娅香槟", "钻石鱼子酱", "盒装挂耳咖啡", "飞行员眼镜",
    "蓝宝石龙舌兰", "咖啡", "纯金打火机",
    "强化碳纤维板", "军用炮弹", "超声波切割刀", "军用炸弹", "紫外线灯", "液压破门器",
    "陆军万用表", "移动电缆", "自旋型手锯",
    "医疗无人机", "骨锯", "电子显微镜", "听诊器", "医用酒精", "探热器",
    "输液工具", "小药瓶", "注射器",
    "复苏呼吸机", "ECMO", "自助体外除颤器", "医疗机器人", "呼吸机", "静脉定位器",
    "心脏支架", "血氧机", "植入式去颤器",
    "重型登山背包", "GT5野战背包", "D3战术登山背包", "HLS-2重型背包", "ALS背负系统", "生存战术背包",
    "GT1户外登山背包", "D2战术登山背包", "野战徒步背包",
    "GIR野战胸挂", "DRC先进侦察胸挂", "突击者战术背心", "强袭战术背心", "G01战术胸挂", "DSA战术胸挂",
    "HD3战术胸挂", "简易携行胸挂", "通用战术胸挂",
    "HA-2重型防弹衣（全新）", "重型突击背心（全新）", "FS复合防弹衣（全新）", "Hvk-2防弹衣（全新）", "精英防弹衣（全新）", "MK-2战术背心（全新）",
    "DT-AVS防弹衣（全新）", "突击手防弹衣（全新）", "武士防弹衣（全新）",
    "H70精英头盔（全新）", "GN重型夜视头盔（全新）", "DICH-1战术头盔（全新）", "GN重型头盔（全新）", "H09防暴头盔（全新）", "GN久战重型夜视头盔（全新）",
    "Mask-1铁壁头盔（全新）", "DICH训练头盔（全新）", "GT1战术头盔（全新）",

    // ---------- 新增枪械物品（简体中文） ----------
    // 步枪
    "M7战斗步枪", "K437突击步枪", "MK47突击步枪", "ASH-12战斗步枪", "K416突击步枪", "AS Val突击步枪",
    "KC17突击步枪", "M4A1突击步枪", "AUG突击步枪", "AK-12突击步枪", "SCAR-H战斗步枪", "AKM突击步枪",
    // 冲锋枪
    "MP7冲锋枪", "Vector冲锋枪", "P90冲锋枪", "QCQ171冲锋枪", "SR-3M紧凑突击步枪", "MK4冲锋枪",
    "MP5冲锋枪", "SMG-45冲锋枪", "勇士冲锋枪", //"野牛冲锋枪", "UZI冲锋枪",
    // 狙击步枪
    "AWM狙击步枪", "M700狙击步枪", "R93狙击步枪", "SV-98狙击步枪",
    // 射手步枪
    "M14射手步枪", "SR-25射手步枪", "PSG-1射手步枪", "SVD狙击步枪", "VSS射手步枪", "杠杆式步枪",
    "Mini-14射手步枪", "SKS射手步枪", "SR9精准射手步枪",
    // 轻机枪
    "M250通用机枪", "M249轻机枪", "PKM通用机枪", "QJB-201轻机枪",
    // 手枪
    "G18", "沙漠之鹰", "M1911", "93R", ".357左轮", "G17", "QSZ92G",
    // 特殊武器
    "复合弓"
};

// 对应的价格数组（单位：哈夫币）
std::vector<long long> WuPinJiaGe = {
    // 原有物品价格
    5282984, 5058426, 4765041, 2414466, 2315645, 1981714,
    1979909, 1330695, 886584, 3359485, 2395630, 2099759,
    1514128, 1660374, 1394527, 1140850, 1066225, 919598,
    6373420, 3555210, 3469334, 1802000, 1631761, 1166545,
    824862, 920000, 888000, 3725832, 2852652, 993486,
    394374, 303605, 475982, 415341, 360999, 303740,
    40235, 29160, 36750, 36250, 24810, 18203,
    18000, 10500, 6325,
    397800, 380230, 123570, 98505, 33840,
    68100, 17975, 17858,
    8455049, 3134521, 4884371, 9414882, 554025, 370066,
    146146, 68903, 81073,
    3065834, 4516146, 503253, 1132544, 291888, 240258,
    1195732, 1650525, 152022,
    59750, 144418, 118324, 41310, 32537, 25044,
    21772, 20680, 17348, 145282, 91550, 85856,
    97194, 90955, 82213, 143237, 130108, 361581,
    3654948, 432780, 350040, 333903, 216831, 212469,
    197787, 398896, 210497,
    13145200, 20000000, 2593099, 17621942, 2216389, 13947732,
    1888716, 1386437, 1282036, 9999999999999, 9999999999999, 9999999999999,
    3663878, 5809558, 358645, 184852, 355097, 86419,
    81502, 68903, 62155,
    5067761, 1459184, 210731, 135122, 97634, 83202,
    66770, 296991, 64518,
    35205, 19301, 14584, 14841, 8668, 11146,
    9999999999999, 9999999999999, 9999999999999,
    11027486, 9169702, 3644106, 2996276, 447606, 78711,
    81439, 60114, 58466,
    712887, 182250, 147730, 114260, 96990, 76730,
    60500, 56580, 40440,
    106123, 79135, 55286, 27090, 10157, 6052,
    5334, 4755, 4130,
    9999999999999, 484516, 456593, 398344, 393770, 173216,
    152871, 170320, 130792,
    9999999999999, 731840, 357186, 346315, 350656, 177748,
    396469, 175394, 181201,

    // ---------- 新增枪械物品价格 ----------
    // 步枪
    203014, 128184, 74621, 117301, 153894, 136191,
    193831, 71148, 94774, 9999999999999, 9999999999999, 9999999999999,
    // 冲锋枪
    135580, 192945, 51805, 78723, 72663, 51453,
    38432, 38081, 38035, //0, 0,
    // 狙击步枪
    749379, 108000, 69895, 62295,
    // 射手步枪
    147675, 150908, 99900, 70200, 53513, 60775,
    39092, 33660, 10799,
    // 轻机枪
    170944, 42618, 72953, 51673,
    // 手枪
    23415, 17030, 17374, 15335, 16580, 5000, 4799,
    // 特殊武器
    78000
};


int so_y=100;
int so_x=30;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(700,660);
    this->setWindowTitle("SCF");
    QFont df("微软雅黑", 17);  // 字体家族，大小
    this->setFont(df);

    QLineEdit *lineEdit = new QLineEdit(this);

    // 设置占位符文本
    lineEdit->setPlaceholderText("请搜索哈夫币");
    // 启用清空按钮（输入内容后显示）
    lineEdit->setClearButtonEnabled(true);
    // 设置最大输入长度
    lineEdit->setMaxLength(50);

    lineEdit->setStyleSheet(
        "QLineEdit {"
        "    background-color: #0C181C;"          // 背景色 - 深蓝
        "    color: #FFFFFF;"                     // 文本颜色 - 白
        "    border: 2px solid #BDC3C7;"         // 边框
        "    border-radius: 8px;"                 // 圆角
        "    padding: 8px 12px;"                  // 内边距
        "    font-size: 14px;"                    // 字体大小
        "    font-family: 'Microsoft YaHei';"     // 字体家族
        "}"
        );

    //隐藏
    lineEdit->hide();

    this->setStyleSheet("background-color: #0F1E24;");

    /*QString primaryButton =
        "QPushButton {"
        "    background-color: #4A7B4A;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 10px 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #5A9A5A; }"
        "QPushButton:pressed { background-color: #3A6A3A; }";
    */
    // 设置整个应用程序的默认字体
    QString IDbutcss =     "QPushButton {"
                       "    background-color: #01FC93;"      // 背景色 - 绿色
                       "    color: #0F1E24;"                   // 字体颜色 - 深蓝
                       "    border: none;"                   // 无边框
                       "    border-radius: 5px;"             // 圆角
                       "    padding: 10px 20px;"             // 内边距
                       "    font-size: 17px;"                // 字体大小
                       "    font-weight: bold;"              // 字体粗细
                       "}"
                       "QPushButton:pressed {"
                       "    background-color: #01D47E;"  // 按下时稍深的绿色
                       "    color: #0F1E24;"             // 按下时字体颜色保持不变或调整
                       "}";


    QLabel *ID1 = new QLabel("ID:不幽默的砂糖橘  |  (已复制)" , this);ID1->hide();ID1->move(6,350);ID1->setFixedSize(330,30);
    ID1->setStyleSheet("color: #01FC93");
    QLabel *ID2 = new QLabel("ID:兴高采烈的高子  |  (已复制)" , this);ID2->hide();ID2->move(6,350);ID2->setFixedSize(330,30);
    ID2->setStyleSheet("color: #01FC93");
    QLabel *ID3 = new QLabel("ID:霍香正气的霍子  |  (已复制)" , this);ID3->hide();ID3->move(6,350);ID3->setFixedSize(330,30);
    ID3->setStyleSheet("color: #01FC93");
    QLabel *ID4 = new QLabel("ID:等饭的自私吃土  |  (已复制)" , this);ID4->hide();ID4->move(6,350);ID4->setFixedSize(330,30);
    ID4->setStyleSheet("color: #01FC93");
    QLabel *ID5 = new QLabel("ID:葘淼 | (已复制)" , this);ID5->hide();ID5->move(6,350);ID5->setFixedSize(230,30);
    ID5->setStyleSheet("color: #01FC93");
    QPushButton *FanHui = new QPushButton("←" , this);
    FanHui->setStyleSheet(IDbutcss);
    FanHui->hide();
    QLabel *jiazaiOK = new QLabel("班级游戏ID大全:" , this);
    //jiazaiOK->setStyleSheet("font-size: 16pt; color: #ADD8E6;");
    jiazaiOK->move(30,30);
    jiazaiOK->setFixedSize(230,30);
    jiazaiOK->hide();
    QLabel *KaiShiL1 = new QLabel("欢迎来到三角洲SCF游戏辅助", this);
    KaiShiL1->setFixedSize(330, 30);
    KaiShiL1->move(30,0);
    KaiShiL1->setFont(df);
    KaiShiL1->setStyleSheet("color: #01FC93");
    QLabel *KaiShiL2 = new QLabel("版本:1.4.0", this);
    KaiShiL2->move(30,30);
    KaiShiL2->setFixedSize(150,30);
    KaiShiL2->setFont(df);
    KaiShiL2->setStyleSheet("color: #01FC93");
    //KaiShiL2->setStyleSheet("color: #01FC93");
    QLabel *KaiShiL3 = new QLabel("作者:王光骅", this);
    KaiShiL3->move(30,60);
    KaiShiL3->setFixedSize(150,30);
    KaiShiL3->setFont(df);
    KaiShiL3->setStyleSheet("color: #01FC93");
    //KaiShiL3->setStyleSheet("color: #01FC93");
    QLabel *KaiShiL4 = new QLabel("功能:", this);
    KaiShiL4->move(30,90);
    KaiShiL4->setFont(df);
    KaiShiL4->setStyleSheet("color: #01FC93");
    QPushButton *gn_but1 = new QPushButton("1.班级游戏ID大全",this);
    QString butPath;
#ifdef Q_OS_ANDROID//判断环境
    butPath = "assets:/button.png";
#else
    butPath = "button.png";
#endif
    QPixmap original(butPath);
    QPixmap scaled = original.scaled(48, 50,
                                     Qt::IgnoreAspectRatio,
                                     Qt::SmoothTransformation);
    //QPixmap scaled = original.scaled(130, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    gn_but1->setIcon(QIcon(scaled));
    gn_but1->setIconSize(scaled.size());
    gn_but1->setStyleSheet("QPushButton {"
                          "border: none;"
                          "color: #01FC93;"
                          "font-size: 15px;"
                          "font-weight: bold;"
                          "text-align: center;"
                          "}"
                          "QPushButton:hover {"
                          "color: lightblue;"
                          "}");
    gn_but1->setFixedSize(180,80);//设置按钮大小
    gn_but1->move(30,120);
    //gn_but1->setIcon(QIcon("button.png"));

    gn_but1->setIconSize(gn_but1->size());
    gn_but1->show();
    QPushButton *gn_but2 = new QPushButton("2.三角洲2W以上物品搜索",this);
    gn_but2->setIcon(QIcon(scaled));
    gn_but2->setIconSize(scaled.size());
    gn_but2->setStyleSheet("QPushButton {"
                           "border: none;"
                           "color: #01FC93;"
                           "font-size: 15px;"
                           "font-weight: bold;"
                           "text-align: center;"
                           "}"
                           "QPushButton:hover {"
                           "color: lightblue;"
                           "}");
    gn_but2->setFixedSize(360,80);//设置按钮大小
    gn_but2->move(-33,210);
    gn_but2->show();


    QPushButton *gn_but3 = new QPushButton("3.音频库",this);
    gn_but3->setIcon(QIcon(scaled));
    gn_but3->setIconSize(scaled.size());
    gn_but3->setStyleSheet("QPushButton {"
                           "border: none;"
                           "color: #01FC93;"
                           "font-size: 15px;"
                           "font-weight: bold;"
                           "text-align: center;"
                           "}"
                           "QPushButton:hover {"
                           "color: lightblue;"
                           "}");
    gn_but3->setFixedSize(360,80);//设置按钮大小
    gn_but3->move(-88,300);
    gn_but3->show();



    QPushButton *gn_but3_1 = new QPushButton("颗秒",this);
    gn_but3_1->setFixedSize(260,38);gn_but3_1->move(5,65);gn_but3_1->hide();
    gn_but3_1->setStyleSheet(IDbutcss);
    QPushButton *gn_but3_2 = new QPushButton("掉进陷阱",this);
    gn_but3_2->setFixedSize(260,38);gn_but3_2->move(5,115);gn_but3_2->hide();
    gn_but3_2->setStyleSheet(IDbutcss);
    QPushButton *gn_but3_3 = new QPushButton("天空属于哈夫克!",this);
    gn_but3_3->setFixedSize(260,38);gn_but3_3->move(5,165);gn_but3_3->hide();
    gn_but3_3->setStyleSheet(IDbutcss);
    QPushButton *gn_but2_1 = new QPushButton("清空搜索",this);gn_but2_1->setFixedSize(130,43);gn_but2_1->move(240,5);gn_but2_1->hide();
    gn_but2_1->setStyleSheet({
        "QPushButton {"
        "    background-color: #ff4444;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 10px 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #ff6666;"
        "}"
    });
    //功能1按钮

    QPushButton *gn_but1_1 = new QPushButton("王光骅三角洲ID  |  点击复制",this);gn_but1_1->setFixedSize(260,38);gn_but1_1->move(30,65);gn_but1_1->hide();
    gn_but1_1->setStyleSheet(IDbutcss);
    QPushButton *gn_but1_2 = new QPushButton("高兴三角洲ID  |  点击复制",this);gn_but1_2->setFixedSize(260,38);gn_but1_2->move(30,105);gn_but1_2->hide();
    gn_but1_2->setStyleSheet(IDbutcss);
    QPushButton *gn_but1_id3 = new QPushButton("霍明涵三角洲ID  |  点击复制",this);gn_but1_id3->setFixedSize(260,38);gn_but1_id3->move(30,145);gn_but1_id3->hide();
    gn_but1_id3->setStyleSheet(IDbutcss);
    QPushButton *gn_but1_id4 = new QPushButton("冯傲然三角洲ID  |  点击复制",this);gn_but1_id4->setFixedSize(260,38);gn_but1_id4->move(30,185);gn_but1_id4->hide();
    gn_but1_id4->setStyleSheet(IDbutcss);
    QPushButton *gn_but1_id5 = new QPushButton("汤琪鸣三角洲ID  |  点击复制",this);gn_but1_id5->setFixedSize(260,38);gn_but1_id5->move(30,225);gn_but1_id5->hide();
    gn_but1_id5->setStyleSheet(IDbutcss);
    //注意了！！！下面这212~217的代码不能删，删了会出搜索的BUG！！！（我也不知道是什么原因）
    QPushButton *gn_but2_2 = new QPushButton("↑",this);gn_but2_2->setFixedSize(30,40);gn_but2_2->move(3,160);gn_but2_2->hide();//控制文字滑动
    QPushButton *gn_but2_3 = new QPushButton("↓",this);gn_but2_3->setFixedSize(30,40);gn_but2_3->move(3,200);gn_but2_3->hide();//控制文字滑动
    QPushButton *gn_but2_x1 = new QPushButton("←",this);gn_but2_x1->setFixedSize(30,40);gn_but2_x1->move(160,3);gn_but2_x1->hide();//控制文字滑动
    QPushButton *gn_but2_x2 = new QPushButton("→",this);gn_but2_x2->setFixedSize(30,40);gn_but2_x2->move(190,3);gn_but2_x2->hide();//控制文字滑动



    QPushButton *gn_but2_SoSuoBut = new QPushButton("搜索",this);gn_but2_SoSuoBut->setFixedSize(90,40);gn_but2_SoSuoBut->move(130,5);gn_but2_SoSuoBut->hide();
    //QPushButton *gn_but2_PL_L = new QPushButton("切换显示方式",this);gn_but2_PL_L->setFixedSize(150,40);gn_but2_PL_L->move(180,5);gn_but2_PL_L->hide();
    gn_but2_SoSuoBut->setStyleSheet({
        IDbutcss
        /*"QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #3d8b40;"

        "}"
*/
    });

    //返回按钮


    connect(gn_but1,&QPushButton::clicked,this,[=](){
        //清除所有与该界面无关的按钮和文字
        KaiShiL1->hide();
        KaiShiL2->hide();
        KaiShiL3->hide();
        KaiShiL4->hide();
        gn_but1->hide();
        gn_but2->hide();
        gn_but3->hide();
        jiazaiOK->show();
        FanHui->show();
        //开始设置组件
        gn_but1_1->show();//显示王光骅游戏ID按钮
        gn_but1_2->show();//显示高兴游戏ID按钮
        gn_but1_id3->show();
        gn_but1_id4->show();
        gn_but1_id5->show();


    });


    connect(gn_but1_1,&QPushButton::clicked,this,[=](){
        //王光骅游戏ID按钮点击
        copyAndroid("不幽默的沙糖桔");
        //隐藏其他信息
        ID2->hide();
        ID3->hide();
        ID4->hide();
        ID5->hide();
        //显示ID信息
        ID1->show();
    });
    connect(gn_but1_2,&QPushButton::clicked,this,[=](){
        //高兴游戏ID按钮点击
        copyAndroid("兴高采烈的高子");
        //隐藏其他信息
        ID1->hide();
        ID3->hide();
        ID4->hide();
        ID5->hide();
        //显示ID信息
        ID2->show();

    });
    connect(gn_but1_id3,&QPushButton::clicked,this,[=](){
        //霍子游戏ID按钮点击
        copyAndroid("霍香正气的霍子");
        //隐藏其他信息
        ID1->hide();
        ID2->hide();
        ID4->hide();
        ID5->hide();
        //显示ID信息
        ID3->show();
    });
    connect(gn_but1_id4,&QPushButton::clicked,this,[=](){
        //冯傲然游戏ID按钮点击
        copyAndroid("等饭的自私吃土");
        //隐藏其他信息
        ID1->hide();
        ID2->hide();
        ID3->hide();
        ID5->hide();
        //显示ID信息
        ID4->show();
    });
    connect(gn_but1_id5,&QPushButton::clicked,this,[=](){
        //汤琪鸣游戏ID按钮点击
        copyAndroid("葘淼");
        //隐藏其他信息
        ID1->hide();
        ID2->hide();
        ID3->hide();
        ID4->hide();
        //显示ID信息
        ID5->show();
    });

    bool PLorL = false;//用来指定搜索文本方式

    //方式1:false
    QLabel*SoSuoText = new QLabel(this);
    //SoSuoText->setReadOnly(true);
    SoSuoText->hide();
    SoSuoText->setFixedSize(650, 600);
    SoSuoText->move(30, 100);

    //方式2:true
    QPlainTextEdit *LSoSuoText = new QPlainTextEdit(this);
    LSoSuoText->setReadOnly(true);
    LSoSuoText->hide();
    LSoSuoText->setFixedSize(650, 600);
    LSoSuoText->move(30, 100);
    QString SoSuo;

    QString TextSoSuo;
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->move(0,250);
    scrollArea->verticalScrollBar()->setMinimumWidth(10);
    scrollArea->setStyleSheet(
        "#scrollAreaWidgetContents {"
        "    color: #FFFFFF; "
        "    background-color: #0B1519; /* 深色背景 */"
        "}"
        "QScrollBar:vertical {"
        "    width: 13px;"
        "    background: #909090;"  // 垂直滚动条背景 - 灰色
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #2196F3;"  // 垂直滑块 - 浅蓝色
        "    min-height: 5px;"
        "    border-radius: 5px;"
        "}"

        "QScrollBar:horizontal {"
        "    height: 13px;"  // 水平滚动条高度
        "    background: #909090;"  // 水平滚动条背景 - 灰色
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: #2196F3;"  // 水平滑块 - 浅蓝色
        "    min-width: 60px;"  // 水平滑块最小宽度
        "    border-radius: 10px;"
        "}"
        );
    scrollArea->hide();

    scrollArea->setGeometry(0, 130, 335, 460);
    connect(gn_but2_SoSuoBut, &QPushButton::clicked, this, [=](){
        qDebug() << "搜索按钮被点击 - 开始";
        qDebug() << "=== 搜索按钮点击开始 ===";
        qDebug() << "WuPinJiaGe size:" << WuPinJiaGe.size();
        qDebug() << "WuPinName size:" << WuPinName.size();

        //获取时间避免点击频繁导致卡死
        //获取时间
        if(minute == 0){//是第一次点击
            qDebug() << "第一次点击";
            currentTime = QTime::currentTime();
            minute = currentTime.minute();        // 分钟 (0-59)
            second = currentTime.second();        // 秒 (0-59)
            msec = currentTime.msec();
        }
        else{//不是第一次
            minute = currentTime.minute();        // 分钟 (0-59)
            msec = currentTime.msec();//毫秒
            second = currentTime.second() + (msec/1000.0);        // 秒 (0-59)

            //由于不是第1次点击了，所以开始判断是否点击频繁
            if(minute < QTime::currentTime().minute()){//之前的分钟小于现在的分钟
                if(second + 1.5 < 60 + (QTime::currentTime().second() + (QTime::currentTime().msec() / 1000.0))){
                    qDebug() << "pass1" << "min:" << minute << "sec:" <<second << "msec:" << msec;
                }
                else{
                    qDebug() << "点击过于频繁" << "min:" << minute << "sec:" <<second << "msec:" << msec;
                    return;
                }
            }
            else if(minute == QTime::currentTime().minute()){
                if(second + 1.5 < (QTime::currentTime().second() + (QTime::currentTime().msec() / 1000.0)) * 1.0){
                    qDebug() << "pass2" << "min:" << minute << "sec:" <<second << "msec:" << msec<<"msec:"<<msec;
                }
                else{
                    qDebug() << "点击过于频繁" << "min:" << minute << "sec:" <<second << "msec:" << msec;
                    return;
                }
            }
            else{
                qDebug() << "点击过于频繁" << "min:" << minute << "sec:" <<second << "msec:" << msec;
                return;
            }
            currentTime = QTime::currentTime();
        }

        // 毫秒 (0-999)
        double secondWith100ms = second + msec / 1000.0;
        qDebug() << "分钟:" << minute << "秒(精确到100ms):" << QString::number(secondWith100ms, 'f', 1);
        if(!WuPinJiaGe.empty()) {
            qDebug() << "第一个价格:" << WuPinJiaGe[0];
        }
        if(!WuPinName.empty()) {
            qDebug() << "第一个物品:" << QString::fromStdString(WuPinName[0]);
        }

        // 清空之前的搜索结果
        QWidget *scrollContent = scrollArea->widget();
        if (scrollContent) {
            // 删除所有子控件
            QLayout *layout = scrollContent->layout();
            if (layout) {
                QLayoutItem *item;
                while ((item = layout->takeAt(0)) != nullptr) {
                    if (item->widget()) {
                        item->widget()->deleteLater();
                    }
                    delete item;
                }
            }
        } else {
            // 如果没有widget，创建一个新的
            scrollContent = new QWidget;
            scrollContent->setLayout(new QVBoxLayout);
            scrollArea->setWidget(scrollContent);
        }

        QApplication::processEvents();

        QString inputText = lineEdit->text().trimmed();
        qDebug() << "输入文本:" << inputText;
        if(inputText == "sb" || inputText == "SB"){
            QLabel *errorLabel = new QLabel("可恶啊，你在骂我！！！有什么事情好好说啊！！！！！");
            errorLabel->setStyleSheet("color: red;");  // 修改颜色
            scrollContent->layout()->addWidget(errorLabel);
            return;
        }
        if(inputText == "天空属于"){
            QLabel *errorLabel = new QLabel("哈夫克！");
            errorLabel->setStyleSheet("color: #01FC93;");  // 修改颜色
            scrollContent->layout()->addWidget(errorLabel);
            return;
        }
        if(inputText == "地面属于"){
            QLabel *errorLabel = new QLabel("尼罗鳄！");
            errorLabel->setStyleSheet("color: #01FC93;");  // 修改颜色
            scrollContent->layout()->addWidget(errorLabel);
            return;
        }
        if(inputText == "三角洲启动" || inputText == "三角洲启动！"){
            QLabel *errorLabel = new QLabel("↑ ↑ ↓ →");
            errorLabel->setStyleSheet("color: #01FC93;");  // 修改颜色
            scrollContent->layout()->addWidget(errorLabel);
            return;
        }
        if(inputText == "哈夫克"){
            QLabel *errorLabel = new QLabel("天空属于哈夫克——   哈夫克与你同频，信息予你无限∞");
            errorLabel->setStyleSheet("color: #01FC93;");  // 修改颜色
            scrollContent->layout()->addWidget(errorLabel);
            return;
        }
        // 输入验证
        if(inputText.isEmpty()) {
            QLabel *errorLabel = new QLabel("请输入搜索金额");
            errorLabel->setStyleSheet("color: #01FC93;");  // 修改颜色
            scrollContent->layout()->addWidget(errorLabel);
            qDebug() << "输入为空";
            return;
        }

        bool ok;
        int targetPrice = inputText.toInt(&ok);
        if(!ok || targetPrice <= 0) {
            QLabel *errorLabel = new QLabel("请输入有效的正数金额");
            errorLabel->setStyleSheet("color: #01FC93;");  // 修改颜色
            scrollContent->layout()->addWidget(errorLabel);
            qDebug() << "输入无效";
            return;
        }
        qDebug() << "开始搜索，目标价格:" << targetPrice;

        // 安全检查
        if(WuPinJiaGe.empty() || WuPinName.empty()) {
            QLabel *errorLabel = new QLabel("数据未初始化");
            errorLabel->setStyleSheet("color: #01FC93;");  // 修改颜色
            scrollContent->layout()->addWidget(errorLabel);
            qDebug() << "数据未初始化";
            return;
        }

        // 确保两个vector大小相同
        int minSize = std::min(WuPinJiaGe.size(), WuPinName.size());
        qDebug() << "最小数组大小:" << minSize;

        int foundCount = 0;
        QVBoxLayout *contentLayout = qobject_cast<QVBoxLayout*>(scrollContent->layout());

        // 添加标题标签
        QLabel *titleLabel = new QLabel;
        titleLabel->setText(QString("搜索价格低于 %1 的物品:").arg(targetPrice));
        titleLabel->setStyleSheet("color: #01FC93; font-weight: bold; margin-bottom: 20px;");  // 修改颜色
        contentLayout->addWidget(titleLabel);

        for(size_t i = 0; i < minSize; i++) {
            if(WuPinJiaGe[i] <= targetPrice) {
                // 安全检查字符串
                std::string itemNameStr = WuPinName[i];
                if(itemNameStr.empty()) {
                    itemNameStr = "未知物品";
                }

                QString itemName = QString::fromStdString(itemNameStr);
                QString itemPrice = QString::number(WuPinJiaGe[i]);

                // 创建每个物品的标签
                QLabel *itemLabel = new QLabel;
                itemLabel->setStyleSheet("color: #01FC93; font-weight: bold; border-bottom: 2px;");  // 修改颜色
                itemLabel->setText(QString("%1 - 价格: %2 哈夫币").arg(itemName).arg(itemPrice));

                itemLabel->setWordWrap(true); // 允许文本换行
                contentLayout->addWidget(itemLabel);

                foundCount++;
            }
        }

        qDebug() << "搜索完成，找到" << foundCount << "个物品";

        // 更新标题显示找到的数量
        if (foundCount > 0) {
            titleLabel->setText(QString("找到 %1 个价格低于 %2 的物品:").arg(foundCount).arg(targetPrice));
            titleLabel->setStyleSheet("color: #01FC93; font-weight: bold; border-bottom: 13px");  // 修改颜色
        } else {
            titleLabel->setText(QString("未找到价格低于 %1 的物品").arg(targetPrice));
            titleLabel->setStyleSheet("color: #01FC93; font-weight: bold;");  // 修改颜色
        }

        // 添加拉伸因子，让内容从顶部开始显示
        contentLayout->addStretch();


        scrollArea->show();
        qDebug() << "结果显示完成";
    });
    connect(gn_but2_1,&QPushButton::clicked,this,[=](){
        lineEdit->clear();
        QWidget *scrollContent = scrollArea->widget();
        if (scrollContent) {
            // 删除所有子控件
            QLayout *layout = scrollContent->layout();
            if (layout) {
                QLayoutItem *item;
                while ((item = layout->takeAt(0)) != nullptr) {
                    if (item->widget()) {
                        item->widget()->deleteLater();
                    }
                    delete item;
                }
            }
        } else {
            // 如果没有widget，创建一个新的
            scrollContent = new QWidget;
            scrollContent->setLayout(new QVBoxLayout);
            scrollArea->setWidget(scrollContent);
        }
    });
    connect(gn_but2,&QPushButton::clicked,this,[=](){
        //2W以上物品价值搜索
        //清除所有与该界面无关的按钮和文字
        KaiShiL1->hide();
        KaiShiL2->hide();
        KaiShiL3->hide();
        KaiShiL4->hide();
        gn_but1->hide();
        gn_but2->hide();
        gn_but3->hide();
        FanHui->show();
        //开始设置组件
        lineEdit->show();
        lineEdit->move(30,50);
        lineEdit->setFixedSize(350,35);
        gn_but2_1->show();
        gn_but2_SoSuoBut->show();
        //scrollArea->show();

        //gn_but2_PL_L->show();


    });

    connect(gn_but3,&QPushButton::clicked,this,[=](){
        //音频库
        //清除所有与该界面无关的按钮和文字
        KaiShiL1->hide();
        KaiShiL2->hide();
        KaiShiL3->hide();
        KaiShiL4->hide();
        gn_but1->hide();
        gn_but2->hide();
        gn_but3->hide();
        FanHui->show();
        //开始设置组件
        gn_but3_1->show();
        gn_but3_2->show();
        gn_but3_3->show();
    });
    connect(gn_but3_1,&QPushButton::clicked,this,[](){
        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(3.0);
        player->setSource(QUrl("qrc:/audio/kemiao.mp3"));
        player->play();
    });
    connect(gn_but3_2,&QPushButton::clicked,this,[](){
        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(5.0);
        player->setSource(QUrl("qrc:/audio/saiyide.mp3"));
        player->play();
    });
    connect(gn_but3_3,&QPushButton::clicked,this,[](){
        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(8.0);
        player->setSource(QUrl("qrc:/audio/TKHAWK.mp3"));
        player->play();
    });
    connect(FanHui,&QPushButton::clicked,this,[=](){
        //显示主界面文字
        KaiShiL1->show();
        KaiShiL2->show();
        KaiShiL3->show();
        KaiShiL4->show();
        //隐藏其他组件
        FanHui->hide();//返回按钮
        jiazaiOK->hide();
        gn_but1->show();
        gn_but2->show();
        gn_but3->show();
        lineEdit->hide();
        SoSuoText->hide();

        gn_but1_1->hide();
        gn_but1_2->hide();
        gn_but1_id3->hide();
        gn_but1_id4->hide();
        gn_but1_id5->hide();

        gn_but2_1->hide();
        gn_but3_1->hide();
        gn_but3_2->hide();
        gn_but3_3->hide();
        gn_but2_SoSuoBut->hide();
        scrollArea->hide();
        //gn_but2_PL_L->hide();

        ID1->hide();
        ID2->hide();
        ID3->hide();
        ID4->hide();
        ID5->hide();

    });

    this->show();

}

Widget::~Widget()
{
    delete ui;
}
