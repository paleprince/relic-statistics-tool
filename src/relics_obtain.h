namespace Relics_obtain{
    typedef double db;
    const int L = Basic :: L;
    db nn4,nn2;
    int T,n4,n2; db k[L]; int choose_tp[6]; db choose_v[6];
    std::string Output;
    ///////////////////
    struct Relic{ // 遗器
        int c; int a[5]; db b[5];  // c:部位[0-5] , a:主词条a[0],副词条a[1-4] b:[1-4] 副词条词条数
        Relic(){
            c = -1;
            for (int i = 0; i <= 4; ++i) a[i] = -1,b[i] = -9999999;
        }
    };
    db rand_e(int tp){ // 随机词条档位
        assert(0 <= tp && tp < L-3); db r[3] = {1,1,1}; int x = Basic::Rand.generate2(3,r);
        return Basic::Rate::v[tp][x] / Basic::Rate::v[tp][1];
    }
    void init_4(Relic &t,int tp4 = -1){ // 初始化遗器-四件套
        static db tmp[L],r[] = {0.25,0.25,0.25,0.25};
        t = Relic();
        if (tp4 == -1) t.c = Basic::Rand.generate(4,r); else t.c = tp4; // 随机生成类型 / 确定类型
        t.a[0] = Basic::Rand.generate2(L,Basic::Rate::a[t.c]); // 主词条类型
        for (int i = 0; i < L; ++i) tmp[i] = Basic::Rate::b[i];

        tmp[t.a[0]] = 0; // 不会和主词条相同
        for (int i = 1; i <= 3; ++i)
            t.a[i] =  Basic::Rand.generate2(L,tmp),t.b[i] = rand_e(t.a[i]),tmp[t.a[i]] = 0;
        if (Basic::Rand.check(0.2)) //0.2概率4词条
            t.a[4] = Basic::Rand.generate2(L,tmp),t.b[4] = rand_e(t.a[4]);
    }
    void init_2(Relic &t,int tp2 = -1){ // 初始化遗器-二件套
        static db tmp[L],r[] = {0.5,0.5};
        t = Relic();
        if (tp2 == -1) t.c = Basic::Rand.generate(2,r) + 4; else t.c = tp2;  // 随机生成类型 / 确定类型
        t.a[0] = Basic::Rand.generate2(L,Basic::Rate::a[t.c]); // 主词条类型
        for (int i = 0; i < L; ++i) tmp[i] = Basic::Rate::b[i];
        tmp[t.a[0]] = 0; // 不会和主词条相同
        for (int i = 1; i <= 3; ++i)
            t.a[i] =  Basic::Rand.generate2(L,tmp),t.b[i] = rand_e(t.a[i]),tmp[t.a[i]] = 0;
        if (Basic::Rand.check(0.2)) //0.2概率4词条
            t.a[4] = Basic::Rand.generate2(L,tmp),t.b[4] = rand_e(t.a[4]);
    }
    void update(Relic &t){ // 强化一次
        if (t.a[4] == -1){ // 补词条
            static db tmp[L];
            for (int i = 0; i < L; ++i) tmp[i] = Basic::Rate::b[i];
            for (int i = 0; i <= 3; ++i) tmp[t.a[i]] = 0; // 不会和主词条/已有副词条相同
            t.a[4] =  Basic::Rand.generate2(L,tmp); t.b[4] = rand_e(t.a[4]);
            return;
        }
        static db r1[4] = {1,1,1,1}; int i = Basic::Rand.generate2(4,r1) + 1; t.b[i] += rand_e(t.a[i]); //强化
    }
    db f(Relic t){ // 遗器评分
        if (t.c == -1) return -99999; db res = 0;
        for (int i = 1; i <= 4; ++i) if (t.a[i] != -1) res += t.b[i] * k[t.a[i]];
        return res;
    }

    ////////////////////////
    void w(std::string s){ Output += s; }
    void w(char s){ Output += s; }
    void w(int s){ if (s < 0) w("-"),s=-s; if (s > 9) w(s/10); Output += (char)('0' + s%10); }
    void w(db x){
        if (fabs(x) < 1e-7){ w(0); return;} if (x < 0) w("-"),x=-x;
        w((int)x),w("."),x -= (int)x;//w((int)(x*100000));
        for (int i = 0; i < 5; ++i) x *= 10,w((char)('0' + (int)x)),x -= (int)x;
    }
    ///////////////////////////
    db ask(Relic t,int tp){
        for (int i = 1; i <= 4; ++i) if (t.a[i] == tp && t.b[i] >= 0) return t.b[i]; return 0;
    }

    const int MAXT = 100050;
    const int C = Basic::C;
    db data3[C+1],data4[MAXT]; // 每个部位的十合一次数 / 剩余遗器残骸数
    Relic now[6]; db fnow[6]; // 当前遗器和评分

    void upd_to_full(Relic t){
        update(t),update(t),update(t),update(t),update(t);
        if (f(t) > fnow[t.c]) now[t.c] = t,fnow[t.c] = f(t);
    }
    bool bad(Relic t){ // 判断是否完全没有提升
        if (t.a[0] != choose_tp[t.c]) return 1; // 主词条错误
        int maxs = f(t); db mx = 0;
        if (t.a[4] != -1){ for (int i = 1; i <= 4; ++i) mx = std::max(mx,k[t.a[i]]); }
        else{ for (int i = 0; i < L; ++i) mx = std::max(mx,k[i]); }
        maxs += mx * 5;
        return maxs <= fnow[t.c]; // 拉满强化需要比现在分数高
    }

    namespace preRead{ db qwq = 0.1; std::string s[12]; db k[12]; }

    const int N = 100050;
    int Len[C]; db p[C][N],val[C][N];
    void Choose_calc_init(int c){
        static db l[N],r[N],v[N]; static int n;
        db base = 0;
        for (int i = 0; i < L; ++i) base += Basic::Rate::a[c][i];
        base = Basic::Rate::a[c][choose_tp[c]] / base;
        if (choose_tp[c] == Basic::id("属性伤害")) base /= 7;

        Single_distribution::input(preRead::s,preRead::k,12,preRead::qwq);
        Single_distribution::Query_single_Relic(choose_tp[c],5);
        Single_distribution::output_load(n,l,r,v);

        Len[c] = n;
        assert(n <= 100010);
        p[c][n] = 0,val[c][n] = 0; p[c][n+1] = val[c][n+1] = 0; p[c][n+2] = val[c][n+2] = 0;


        for (int i = 1; i <= n; ++i) p[c][i] = v[i] * base,val[c][i] = (l[i]+r[i])/2.0 * v[i] * base;
        for (int i = n; i >= 1; --i) val[c][i] += val[c][i+1],p[c][i] += p[c][i+1];//期望后缀和

     //   std::cerr << "init " << c << '\n';
     //   std::cerr << "base " << base << '\n';
      //  for (int i = 0; i < 100; ++i) if (v[i] > 1e-7) std::cerr << v[i] << ' ' << l[i] << ' ' << r[i] << '\n';
      //  for (int i = 0; i < 20; ++i) std::cerr << val[c][i] << ' ' << p[c][i] << '\n';
    }
    db Choose_calc(int c,db now){
        if (now < 0) return val[c][1];
        int id = Single_distribution::id(now) + 1;
     //   if (c == 3) std::cerr << val[c][id + 1] - now * p[c][id+1] << '\n';
        return val[c][id + 1] - now * p[c][id+1]; // 遗器 > now 的期望分数 - now * (>now 的概率) = 提升期望
    }

    int Choose(){ // 从六件套中选择最应该合成的部位
        static db e[6];
        for (int i = 0; i < 6; ++i) e[i] = Choose_calc(i,fnow[i]);
        //std :: cerr << "Choose " << e[0] << ' ' << e[1] << ' ' << e[2] << ' ' << e[3] << ' ' << e[4] << ' ' << e[5] << '\n';
        int mx = 0; for (int i = 1; i < 6; ++i) if (e[i] > e[mx]) mx = i;
        return mx;
    }

    void Simulate(int Id_test){
        int i; Relic t;
        for (i = 0; i < 6; ++i) now[i] = Relic(),fnow[i] = choose_v[i];
        int cnt = 0,m4 = 0,m2 = 0,m = 0;
        for (i = 1; i <= n4; ++i) if (Basic::Rand.check(0.5)) ++m4; else ++cnt;
        for (i = 1; i <= n2; ++i) if (Basic::Rand.check(0.5)) ++m2; else ++cnt;
        for (i = 1; i <= m4; ++i){ init_4(t); if (bad(t)){ ++cnt; continue; } upd_to_full(t); }
        for (i = 1; i <= m2; ++i){
              init_2(t);
              if (bad(t)){ ++cnt; continue; }
              if (t.a[0] == Basic::id("属性伤害") && !Basic::Rand.check(1.0/7)){ ++cnt; continue; }
              upd_to_full(t);
        }
        m4 = m2 = 0;
        while (cnt >= 10){
            m = cnt / 10; cnt %= 10;
            while (m--){
                t.c = Choose(); assert(0 <= t.c && t.c < 6);
                ++data3[t.c];
                if (t.c < 4) init_4(t,t.c); else init_2(t,t.c);
                if (bad(t)){ ++cnt; continue; }
                if (t.a[0] == Basic::id("属性伤害") && !Basic::Rand.check(1.0/7)){ ++cnt; continue; }
                upd_to_full(t);
            }
        }
        data4[Id_test] = cnt;
    }


    db data1[MAXT]; // 总分
    db data2[C+1][L]; // 每个部位、每种副词条期望词条数
    db data5[C][MAXT]; // 每个部位总分
    db calcvar(db a[],int n){
        db tot = 0,avg = 0; int i;
        for (i = 1; i <= n; ++i) tot += a[i];
        avg = tot / n,tot = 0;
        for (i = 1; i <= n; ++i) tot += a[i] * a[i];
        tot /= n; return tot - avg * avg;
    }
    std::string Relics_obtain_work(){
        Output.clear(),Basic::Rand.init(0),Basic::Rate::init();
        memset(data1,0,sizeof(data1));
        memset(data2,0,sizeof(data2));
        memset(data3,0,sizeof(data3));
        memset(data4,0,sizeof(data4));
        for (int i = 0; i < C; ++i) Choose_calc_init(i); //

        for (int i = 1; i <= T; ++i){
            Simulate(i);
            data1[i] = 0;
            for (int j = 0; j < C; ++j) data5[j][i] = std::max(0.0,fnow[j]),data1[i] += std::max(0.0,fnow[j]);
            for (int j = 0; j < C; ++j) for (int k = 0; k < L; ++k) data2[j][k] += ask(now[j],k);
        }

        for (int j = 0; j < C; ++j) for (int k = 0; k < L; ++k) data2[j][k] /= T,data2[C][k] += data2[j][k];
        db tot = 0;
        for (int i = 1; i <= T; ++i) tot += data1[i];
        tot /= T;



        w("测试 "),w(T),w(" 组刷取 "),w(n4),w(" 个四件套金色遗器,"),w(n2),w(" 个两件套金色遗器:\n");
        w("(相当于刷取 "),w(nn4),w(" 天四件套,"),w(nn2),w(" 天两件套)\n");

        w("期望评分 "),w(tot),w("\n");
        w("评分的方差 "),w(calcvar(data1,T)),w("\n");
        w("\n");
        w("每种副词条期望出现次数:\n");
        for (int i = 0; i < L; ++i) if (data2[C][i] > 1e-7 && k[i] > 1e-7)
            w(data2[C][i]),w(" 词条 "),w(Basic::name(i)),w("\n");

        w("\n");
        w("各部位每种副词条期望出现次数:\n");
        for (int j = 0; j< C; ++j){
            w(Basic::Rate::s[j]),w(":\n");
            tot = 0;
            for (int i = 1; i <= T; ++i) tot += data5[j][i];
            tot /= T;
            w("期望评分 : "),w(tot),w("\n");
            for (int i = 0; i < L; ++i) if (data2[j][i] > 1e-7 && k[i] > 1e-7)
                w(data2[j][i]),w(" 词条 "),w(Basic::name(i)),w("\n");
        }
        for (int i = 0; i <= 5; ++i)
            w("十合一"),w(Basic::Rate::s[i]),w("数量："),w((db)(data3[i] / T)),w("  \n");
        db tot4 = 0;
        for (int i = 1; i <= T; ++i) tot4 += data4[i];
        tot4 /= T;
        w("剩余无用胚子数(用于校验,应该<10) : "),w(tot4),w("\n");
        return Output;
    }


    void input(int t,int N4,int N2,int level,std::string S[12],db K[12],int Choose_tp[6],db Choose_v[6]){
        T = t,n4 = N4,n2 = N2; nn4 = N4,nn2 = N2;
        static double c[6+1] = {0,0,0,1,1.5,2,2.1};
        //n4 = n4 * c[level],n2 = n2 * c[level];
        nn4 = n4 /c[level]/6,nn2 = n2/c[level]/6;
        memset(k,0,sizeof(k));
        for (int i = 0; i < 12; ++i)
                k[Basic::id(S[i])] = K[i],
                preRead::s[i] = S[i],preRead::k[i] = K[i];
        for (int i = 0; i < 6; ++i) choose_tp[i] = Choose_tp[i];
        for (int i = 0; i < 6; ++i) choose_v[i] = Choose_v[i];
    }
}



void MainWindow::on_start_clicked()
{
    // 获取 T,n2,n4,均衡等级 level 系数k,有效主词条数据
    // n2,n4:遗器数量
    static QString output = "";
    static bool valid; valid = 1;
    static int T,n4,n2,Level;
    T = MainWindow::ui->lineEdit_10->text().toInt();
    n4 = MainWindow::ui->lineEdit_11->text().toInt();
    n2 = MainWindow::ui->lineEdit_12->text().toInt();
    Level = MainWindow::ui->comboBox_11->currentText().toInt();

    if (T < 0 || T > 100000) valid = 0,output = "invalid input : 样本数不在区间 [0,100000] 里\n";
    if (n4 < 0 || n4 > 2000) valid = 0,output = "invalid input : 四件套金遗器个数不在区间 [0,2000] 里\n";
    if (n2 < 0 || n2 > 2000) valid = 0,output = "invalid input : 两件套金遗器个数不在区间 [0,2000] 里\n";

    static std::string s[12]; static double k[12];
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
    k[0] = MainWindow::ui->lineEdit->text().toDouble();
    k[1] = MainWindow::ui->crit_rate->text().toDouble();
    k[2] = MainWindow::ui->speed->text().toDouble();
    k[3] = MainWindow::ui->lineEdit_4->text().toDouble();
    k[4] = MainWindow::ui->lineEdit_5->text().toDouble();
    k[5] = MainWindow::ui->lineEdit_6->text().toDouble();
    k[6] = MainWindow::ui->lineEdit_7->text().toDouble();
    k[7] = MainWindow::ui->lineEdit_8->text().toDouble();
    k[8] = MainWindow::ui->lineEdit_9->text().toDouble();
    k[9] = MainWindow::ui->lineEdit_45->text().toDouble();
    k[10] = MainWindow::ui->lineEdit_46->text().toDouble();
    k[11] = MainWindow::ui->lineEdit_47->text().toDouble();

    // 副词条权重

    for (int i = 0; i < 12; ++i) if (k[i] < 0 || k[i] > 100){
        valid = 0,output = "invalid input : 存在副词条权重不在区间 [0,100] 里\n";
    }
    static int choose_tp[6];
    choose_tp[0] = Basic :: id("生命");
    choose_tp[1] = Basic :: id("攻击");
    choose_tp[2] = Basic :: id(ui->comboBox->currentText().toStdString());
    choose_tp[3] = Basic :: id(ui->comboBox_2->currentText().toStdString());
    choose_tp[4] = Basic :: id(ui->comboBox_3->currentText().toStdString());
    choose_tp[5] = Basic :: id(ui->comboBox_4->currentText().toStdString());

    static double choose_v[6];
    choose_v[0] = MainWindow::ui->lineEdit_21->text().toDouble();
    choose_v[1] = MainWindow::ui->lineEdit_22->text().toDouble();
    choose_v[2] = MainWindow::ui->lineEdit_23->text().toDouble();
    choose_v[3] = MainWindow::ui->lineEdit_24->text().toDouble();
    choose_v[5] = MainWindow::ui->lineEdit_25->text().toDouble();
    choose_v[4] = MainWindow::ui->lineEdit_26->text().toDouble();

    for (int i = 0; i < 6; ++i) if (choose_v[i] < 0 || choose_v[i] > 1000){
        if (fabs(choose_v[i]+1) > 1e-7) valid = 0,output = "invalid input : 目前遗器评分不是 -1, 也不在区间 [0,1000] 里\n";
    }

    if (valid){
        Relics_obtain::input(T,n4,n2,Level,s,k,choose_tp,choose_v);
       // std::cerr << "qwq\n";
        output = QString::fromStdString(Relics_obtain :: Relics_obtain_work()); // 从模拟程序中获取输出
    }
    ui->output->setText(output);
}
