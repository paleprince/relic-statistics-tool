
namespace Single_distribution{
    typedef double db;
    const int L = Basic :: L;
    db k[L]; std::string Output;
    db a[L];
    //12 种副词条
    void w(std::string s){ Output += s; }
    void w(char s){ Output += s; }
    void w(int s){ if (s < 0) w("-"),s=-s; if (s > 9) w(s/10); Output += (char)('0' + s%10); }
    void w(db x){
        if (fabs(x) < 1e-7){ w(0); return;} if (x < 0) w("-"),x=-x;
        w((int)x),w("."),x -= (int)x;
        for (int i = 0; i < 7; ++i) x *= 10,w((char)('0' + (int)x)),x -= (int)x;
    }
    void w2(int x){ w(x/10),w("."),w(x%10); } // 一位小数
    int T,t[5 + 5]; // 4个副词条
    //////////////////
    db qwq; int qwq2;
    //////////////////
    db data[100000 + 50];
    db E;
    int id(db p){ return p * qwq2; }//根据输出间隔决定统计间隔
    void dfs2(int dep,db p,db v){
        if (dep == -1){ v -= k[t[4]],dep = 0; }
        if (dep == 0){ data[id(v)] += p; E += v * p; return; }
        for (int i = 1; i <= 4; ++i) dfs2(dep - 1,p * 0.25,v + k[t[i]]);
    }
    db nowa[L],tota; bool Type; //Type = 0/1 表示否/是 提前确定胚子
    void dfs1(int dep,db p,db v){
        db x;
        if (dep == 5 && !Type){ dfs2(T - 1,p * 0.8,v),dfs2(T,p * 0.2,v); return; }
        if (dep == 5 && Type){ dfs2(T,p,v); return; }
        for (int i = 0; i < L; ++i) if (nowa[i] > 1e-7){
            x = nowa[i],nowa[i] = 0,tota -= x; t[dep] = i;
            dfs1(dep + 1,p * (x) / (x + tota),v + k[i]);
            nowa[i] = x,tota += x;
        }
    }
    int at[5+5];

    std::string Query_single_Relic(int c,int tt){
        memset(data,0,sizeof(data));
        T = tt;
        /////////////////////////////// 非法数据检测
        if (T < 0) return "invalid input : 强化次数 < 0 或输入的不是数字\n";
        if (T > 5) return "invalid input : 强化次数 > 5 或输入的不是数字 \n";
        qwq2 = -1; E = 0;
        if (fabs(qwq - 0.1) < 1e-7) qwq = 0.1,qwq2 = 10;
        if (fabs(qwq - 0.5) < 1e-7) qwq = 0.5,qwq2 = 2;
        if (fabs(qwq - 1) < 1e-7) qwq = 1,qwq2 = 1;
        if (qwq2 == -1) return "invalid input : 不支持的评分间隔\n";
        for (int i = 0; i < L; ++i) if ((fabs(k[i]) > 1e-7 && k[i] < 0) || (k[i] != k[i]))
               return "invalid input : 存在 < 0 的权重或者非法权重\n";
        for (int i = 0; i < L; ++i) if ((fabs(k[i]) > 1e-7 && k[i] > 100) || (k[i] != k[i]))
               return "invalid input : 存在 > 100 的权重或者非法权重\n";
        if (Type == 1){
            for (int i = 1; i <= 4; ++i) for (int j = i+1; j <= 4; ++j) if (i != j && at[i] == at[j]) return "invalid input : 存在相同的副词条预设\n";
            for (int i = 1; i <= 4; ++i) if (c == at[i]) return "invalid input : 副词条预设不能和主词条相同\n";
        }
        ///////////////////////////////
        Output.clear();
        if (Type == 1){
            db st = 0;
            for (int i = 0; i < L; ++i) a[i] = Basic::Rate::b[i];
            a[c] = 0,tota = 0;
            if (at[4] == -1){
                --T;
                for (int i = 1; i <= 3; ++i) t[i] = at[i],a[t[i]] = 0.0,st += k[t[i]];
                for (int i = 0; i < L; ++i) tota += a[i],nowa[i] = a[i];
                dfs1(4,1,st);
            }
            else{
                for (int i = 1; i <= 4; ++i) t[i] = at[i],a[t[i]] = 0.0,st += k[t[i]];
                for (int i = 0; i < L; ++i) tota += a[i],nowa[i] = a[i];
                dfs1(5,1,st);
            }
        }
        else{
            for (int i = 0; i < L; ++i) a[i] = Basic::Rate::b[i];
            a[c] = 0,tota = 0;
            for (int i = 0; i < L; ++i) tota += a[i],nowa[i] = a[i];
            dfs1(1,1,0);
        }
        db tott = 0;
        for (int i = 0; i < 100000; ++i) if (data[i] > 1e-7){
            w("评分区间 ["),w2(i*(10/qwq2)),w(","),w2((i+1)*(10/qwq2)),w(") : "),w(data[i]*100.0),w("%\n");
            tott += data[i]; //E += i * 1.0 / qwq2 * data[i];
        }
        w("评分期望 : "),w(E),w("\n");
        w("总概率校验(这里应该输出 100%-eps): "),w(tott * 100.0),w("\n");
        return Output;
    }
    void output_load(int &n,db *l,db *r,db *v){ // 调用者传地址，我们把上一次计算的结果传过去(必须是0.1精度)
        n = 0;
        assert(Type == 0); assert(fabs(qwq - 0.1) < 1e-7); // 只支持导出 0.1 精度的结果，且无法提前定胚子。
        for (int i = 0; i < 100000; ++i) if (1){ // 10w个点直接传过去
            ++n; l[n] = i * qwq,r[n] = i * qwq + qwq,v[n] = data[i];
        }
    }

    void input(std::string s[],db v[],int n,db p){ // p 是间隔
        Type = 0;
        memset(k,0,sizeof(k));
        for (int i = 0; i < n; ++i) k[Basic :: id(s[i])] = v[i];
        qwq = p;
    }
    void input_confirm(int At[5]){ Type = 1; for (int i = 0; i <= 4; ++i) at[i] = At[i]; }
    void input_not_confirm(){ Type = 0; }
}
