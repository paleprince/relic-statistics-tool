#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////
void MainWindow::on_pushButton_clicked(){
///36-44 51-53
    ui->lineEdit_36->setText("0");
    ui->lineEdit_37->setText("0");
    ui->lineEdit_38->setText("0");
    ui->lineEdit_39->setText("0");
    ui->lineEdit_40->setText("0");
    ui->lineEdit_41->setText("0");
    ui->lineEdit_42->setText("0");
    ui->lineEdit_43->setText("0");
    ui->lineEdit_44->setText("0");
    ui->lineEdit_51->setText("0");
    ui->lineEdit_52->setText("0");
    ui->lineEdit_53->setText("0");
}


void MainWindow::on_output_sourceChanged(QUrl const&){

}

///////////////////////////////////////////////////////下面是无意义代码

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
   // MyTest::modify_k("暴击率",arg1.toDouble());
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
   // MyTest::modify_k("暴击率",arg1.toDouble());
}

void MainWindow::on_crit_rate_textChanged(const QString &arg1)
{
    //MyTest::modify_k("暴击伤害",arg1.toDouble());
}

void MainWindow::on_speed_textChanged(const QString &arg1)
{
    //MyTest::modify_k("速度",arg1.toDouble());
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
  //  MyTest::modify_k("攻击%",arg1.toDouble());
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
   //MyTest::modify_k("防御%",arg1.toDouble());
}

void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
   // MyTest::modify_k("生命%",arg1.toDouble());
}

void MainWindow::on_lineEdit_7_cursorPositionChanged(int arg1, int arg2)
{
    ///
}

void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
   // MyTest::modify_k("击破特攻",arg1.toDouble());
}

void MainWindow::on_lineEdit_8_textChanged(const QString &arg1)
{
  //  MyTest::modify_k("效果命中",arg1.toDouble());
}

void MainWindow::on_lineEdit_9_textChanged(const QString &arg1)
{
  //  MyTest::modify_k("效果抵抗",arg1.toDouble());
}

void MainWindow::on_lineEdit_10_textChanged(const QString &arg1)
{
  //  MyTest::modify_T(arg1.toInt());
}

void MainWindow::on_lineEdit_11_textChanged(const QString &arg1)
{
 //   MyTest::modify_n4(arg1.toInt());
}

void MainWindow::on_lineEdit_12_textChanged(const QString &arg1)
{
 //   MyTest::modify_n2(arg1.toInt());
}



///////////////////////////////////////////////////无意义代码区域





///////////////////////////////////////////////////////////


#include <bits/stdc++.h>
#include "basic.h"
#include "single_distribution.h"
#include "relics_obtain.h"


void MainWindow::on_start_2_clicked()
{
    static int L = 12;//Basic :: L;
    static double qwq;
    static std::string s[Basic :: L]; static double k[Basic :: L];
    s[0] = "暴击率";
    s[1] = "暴击伤害";
    s[2] = "速度";
    s[3] = "攻击%";
    s[4] = "防御%";
    s[5] = "生命%";
    s[6] = "击破特攻";
    s[7] = "效果命中";
    s[8] = "效果抵抗";
    s[9] = "攻击";
    s[10] = "防御";
    s[11] = "生命";

    k[0] = MainWindow::ui->lineEdit_2->text().toDouble();
    k[1] = MainWindow::ui->lineEdit_3->text().toDouble();
    k[2] = MainWindow::ui->lineEdit_13->text().toDouble();
    k[3] = MainWindow::ui->lineEdit_14->text().toDouble();
    k[4] = MainWindow::ui->lineEdit_15->text().toDouble();
    k[5] = MainWindow::ui->lineEdit_16->text().toDouble();
    k[6] = MainWindow::ui->lineEdit_17->text().toDouble();
    k[7] = MainWindow::ui->lineEdit_18->text().toDouble();
    k[8] = MainWindow::ui->lineEdit_19->text().toDouble(); // 副词条权重
    k[9] = MainWindow::ui->lineEdit_54->text().toDouble();
    k[10] = MainWindow::ui->lineEdit_55->text().toDouble();
    k[11] = MainWindow::ui->lineEdit_56->text().toDouble(); // 副词条权重
    qwq = MainWindow::ui->comboBox_6->currentText().toDouble(); //评分间隔 [0.1,0.5,1]
    Single_distribution::input(s,k,L,qwq);

    static int tp,cnt;
    tp = Basic::id(MainWindow::ui->comboBox_5->currentText().toStdString()); // 主词条选择
    cnt = MainWindow::ui->lineEdit_20->text().toInt(); // 强化次数

    static bool isconfirmed; // 是否提前确定胚子
    static int at[5]; // 提前确定的胚子副词条
    isconfirmed = MainWindow::ui->checkBox->isChecked();
    if (isconfirmed){
        at[1] = Basic::id(ui->comboBox_7->currentText().toStdString());
        at[2] = Basic::id(ui->comboBox_8->currentText().toStdString());
        at[3] = Basic::id(ui->comboBox_9->currentText().toStdString());
        if (ui->comboBox_10->currentText() != "无词条")
            at[4] = Basic::id(ui->comboBox_10->currentText().toStdString());
        else at[4] = -1;
        Single_distribution :: input_confirm(at);
    }
    else Single_distribution :: input_not_confirm();

    ui->output_2->setText(QString::fromStdString(Single_distribution :: Query_single_Relic(tp,cnt)));
}

namespace Relics_score{
    typedef double db; std::string Output; db ans;
    void w(std::string s){ Output += s; }
    void w(char s){ Output += s; }
    void w(int s){ if (s < 0) w("-"),s=-s; if (s > 9) w(s/10); Output += (char)('0' + s%10); }
    void w(db x){
        if (fabs(x) < 1e-7){ w(0); return;} if (x < 0) w("-"),x=-x;
        w((int)x),w("."),x -= (int)x;
        for (int i = 0; i < 7; ++i) x *= 10,w((char)('0' + (int)x)),x -= (int)x;
    }
    std::string work(std::string s[12],db k[12],db v[12]){
        for (int i = 0; i < 12; ++i){
            if (k[i] < 0 || k[i] > 100) return "invalid input : 副词条权重不在区间 [0,100] 中\n";
            if (k[i] < 0 || v[i] > 1000) return "invalid input : 副词条数值不在区间 [0,1000] 中\n";
        }
        static int id;
        ans = 0; Output = "";
        for (int i = 0; i < 12; ++i) id = Basic::id(s[i]),ans += k[i] * v[i] / Basic::Rate::v[id][1];
        w("遗器评分 : "),w(ans),w("\n");
        return Output;
    }
}

void MainWindow::on_start_3_clicked()
{
    static std::string s[12]; static double k[12],v[12];
    s[0] = "暴击率";
    s[1] = "暴击伤害";
    s[2] = "速度";
    s[3] = "攻击%";
    s[4] = "防御%";
    s[5] = "生命%";
    s[6] = "击破特攻";
    s[7] = "效果命中";
    s[8] = "效果抵抗";
    s[9] = "攻击";
    s[10] = "防御";
    s[11] = "生命";
    k[0] = MainWindow::ui->lineEdit_27->text().toDouble();
    k[1] = MainWindow::ui->lineEdit_28->text().toDouble();
    k[2] = MainWindow::ui->lineEdit_29->text().toDouble();
    k[3] = MainWindow::ui->lineEdit_30->text().toDouble();
    k[4] = MainWindow::ui->lineEdit_31->text().toDouble();
    k[5] = MainWindow::ui->lineEdit_32->text().toDouble();
    k[6] = MainWindow::ui->lineEdit_33->text().toDouble();
    k[7] = MainWindow::ui->lineEdit_34->text().toDouble();
    k[8] = MainWindow::ui->lineEdit_35->text().toDouble();
    k[9] = MainWindow::ui->lineEdit_48->text().toDouble();
    k[10] = MainWindow::ui->lineEdit_49->text().toDouble();
    k[11] = MainWindow::ui->lineEdit_50->text().toDouble();


    v[0] = MainWindow::ui->lineEdit_36->text().toDouble();
    v[1] = MainWindow::ui->lineEdit_37->text().toDouble();
    v[2] = MainWindow::ui->lineEdit_38->text().toDouble();
    v[3] = MainWindow::ui->lineEdit_39->text().toDouble();
    v[4] = MainWindow::ui->lineEdit_40->text().toDouble();
    v[5] = MainWindow::ui->lineEdit_41->text().toDouble();
    v[6] = MainWindow::ui->lineEdit_42->text().toDouble();
    v[7] = MainWindow::ui->lineEdit_43->text().toDouble();
    v[8] = MainWindow::ui->lineEdit_44->text().toDouble();
    v[9] = MainWindow::ui->lineEdit_51->text().toDouble();
    v[10] = MainWindow::ui->lineEdit_52->text().toDouble();
    v[11] = MainWindow::ui->lineEdit_53->text().toDouble();

    static std::string Output; Output = Relics_score::work(s,k,v);
    ui->output_3->setText(QString::fromStdString(Output));
}
