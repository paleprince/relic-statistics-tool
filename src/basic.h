namespace Basic{
    class Random_generator{ // 用于作随机判定 , s_r_f 的随机数板子 qwq
        private:
        typedef double db; std::mt19937 rnd;
        public:
        void init(unsigned seed){ // seed = 0 : time() ; seed ≠0 : 指定的 seed
            if (seed == 0) rnd.seed(time(0)); else rnd.seed(seed);
        }
        const db N = 1ll<<32;
        bool check(db rate){ if (rate >= 1) return 1; if (rate <= 0) return 0; return (rnd()) < (rate * rnd.max()); }
        int generate(int n,db r[]){
            static db tot,x; tot = 0;
            for (int i = 0; i < n; ++i) tot += r[i]; assert(fabs(tot - 1) < 1e-7); // 概率总和必须是1
            x = (rnd()) * 1.0 / N;
            for (int i = 0; i < n; ++i) if (x <= r[i]) return i; else x -= r[i];
            return n - 1;
        }
        int generate2(int n,db r[]){
            static db tot,x; tot = 0;
            for (int i = 0; i < n; ++i) tot += r[i];
            for (int i = 0; i < n; ++i) r[i] /= tot; x = (rnd()) * 1.0 / N;
            for (int i = 0; i < n; ++i) if (r[i] > 0){ if (x <= r[i]) return i; else x -= r[i]; }
            return n - 1;
        }
    }Rand;

    const int L = 15; // 词条种类数
    namespace Entry{
        const std::string s[L] = {
            "攻击%","攻击","防御%","防御","生命%","生命",
            "暴击率","暴击伤害","速度",
            "效果命中","效果抵抗","击破特攻",
            "治疗加成","充能效率","属性伤害"
        };
        int id(std::string entry){ for (int i = 0; i < L; ++i) if (entry == s[i]) return i; assert(0); return -1; }
        std::string name(int id){ return s[id]; }
    }
    using Entry::id;
    using Entry::name;
    const int C = 6; // 部位数
    namespace Rate{
        typedef double db;
        const std::string s[C] = {"头部","手部","躯干","鞋子","连结绳","位面球"};
        int id2(std::string entry){ for (int i = 0; i < C; ++i) if (entry == s[i]) return i; assert(0); return -1; }

        db a[C][L]; // 每种词条在各部位主词条的权重
        const db b[L] = {5,5,5,5,5,5,3,3,2,4,4,4,0,0,0}; // 副词条的权重
        const db v[L][3] = {
        {3.46,3.89,4.32},{16.9,19,21}, // 攻
        {4.32,4.86,5.4},{16.9,19,21}, // 防
        {3.46,3.89,4.32},{33.8,38,42},  // 生
        {2.59,2.92,3.24},{5.18,5.83,6.48}, // 双爆
        {2,2.3,2.6}, // 速度
        {3.46,3.89,4.32},{3.46,3.89,4.32}, // 效果命中/抵抗
        {5.18,5.83,6.48}, // 击破
        {-1,-1,-1},{-1,-1,-1},{-1,-1,-1} // 治疗量加成/充能效率/属性伤害:invalid
        };
        // 副词条单次强化数值，三个档位
        void init(){ // 初始化 a
            memset(a,0,sizeof(a)); // 清空
            for (int i = 0; i < L; ++i) assert(i == Entry::id(Entry::s[i]));

            a[0][id("生命")] = 1,a[1][id("攻击")] = 1;

            a[2][id("生命%")] = a[2][id("攻击%")] = a[2][id("防御%")] = 2;
            a[2][id("暴击率")] = a[2][id("暴击伤害")] = a[2][id("治疗加成")] = a[2][id("效果命中")] = 1;

            a[3][id("生命%")] = a[3][id("攻击%")] = a[3][id("防御%")] = 3;
            a[3][id("速度")] = 1;

            a[4][id("击破特攻")] = 15;
            a[4][id("充能效率")] = 5;
            a[4][id("生命%")] = a[4][id("攻击%")] = a[4][id("防御%")] = 26 + ((db)2.0/3);
            ///连结绳：15:5:26.67
            a[5][id("生命%")] = a[5][id("攻击%")] = a[5][id("防御%")] = 12 + ((db)1.0/3);
            a[5][id("属性伤害")] = 63.00;
        }
    }
}
