#ifndef MAIN_H
#define MAIN_H

#include <QString>
#include <QJsonObject>

// struct athl{
//     QString name;
//     QString team;
//     QString range;
//     QString category;
//     QString age;
//     QString weight;
// };

struct athlete
{
    athlete(int i = -1,
            QString n = "",
            QString t = "",
            QString r = "",
            QString rt = "",
            QString ar = "",
            QString p = "")
            {
            id = i,
            name = n,
            team = t,
            range = r,
            rate = rt,
            add_rate = ar,
            place = p;
            }
    int id;
    QString name;
    QString team;
    QString range;

    ///////////////////////////////////////////
    /// Только для первого (общего) круга   ///
    ///////////////////////////////////////////
    QString rate = "";
    QString add_rate = "";
    QString place = "";
};

struct rates
{
    rates(int _id, QString r, QString ar) {id = _id; rate = r; add_rate = ar;}
    int id;
    QString rate;
    QString add_rate;
};

///////////////////////////////////////////////////////////////////
/// структура данных финальной части с полуфиналом, финалом и   ///
/// одним третьим местом при количестве участников не менее 4   ///
///////////////////////////////////////////////////////////////////
struct final_0
{
    final_0(
        int w1 = 0,
        int w2 = 0,
        int w3 = 0,
        int w4 = 0,
        QString r1 = "",
        QString r2 = "",
        QString r3 = "",
        QString r4 = "",
        QString ar1 = "",
        QString ar2 = "",
        QString ar3 = "",
        QString ar4 = "",
        QString rf1 = "",
        QString rf2 = "",
        QString rt1 = "",
        QString rt2 = "",
        QString arf1 = "",
        QString arf2 = "",
        QString art1 = "",
        QString art2 = "",
        bool fc = false,
        bool fh = false,
        bool ff = false
        )
    {
        win_1 = w1;
        win_2 = w2;
        win_final = w3;
        win_third = w4;
        rate1 = r1;
        rate2 = r2;
        rate3 = r3;
        rate4 = r4;
        add_rate1 = ar1;
        add_rate2 = ar2;
        add_rate3 = ar3;
        add_rate4 = ar4;
        rate_fin1 = rf1;
        rate_fin2 = rf2;
        rate_third1 = rt1;
        rate_third2 = rt2;
        add_rate_fin1 = arf1;
        add_rate_fin2 = arf2;
        add_rate_third1 = art1;
        add_rate_third2 = art2;
        flag_on_mat_common = fc;
        flag_on_mat_half = fh;
        flag_on_mat_final = ff;
    }
    int win_1;
    int win_2;
    int win_final;
    int win_third;
    QString rate1;
    QString rate2;
    QString rate3;
    QString rate4;
    QString add_rate1;
    QString add_rate2;
    QString add_rate3;
    QString add_rate4;
    QString rate_fin1;
    QString rate_fin2;
    QString rate_third1;
    QString rate_third2;
    QString add_rate_fin1;
    QString add_rate_fin2;
    QString add_rate_third1;
    QString add_rate_third2;
    bool flag_on_mat_common;
    bool flag_on_mat_half;
    bool flag_on_mat_final;
};



// QJsonObject jSystem_0_obj(){
//     QJsonObject jObj = QJsonObject{
//         {"win_1", 0},
//         {"win_2", 0},
//         {"win_final", 0},
//         {"win_third", 0},
//         {"rate1", 0.0},
//         {"rate2", 0.0},
//         {"rate3", 0.0},
//         {"rate4", 0.0},
//         {"add_rate1", ""},
//         {"add_rate2", ""},
//         {"add_rate3", ""},
//         {"add_rate4", ""},
//         {"rate_fin1", 0.0},
//         {"rate_fin2", 0.0},
//         {"rate_third1", 0.0},
//         {"rate_third2", 0.0},
//         {"add_rate_fin1", ""},
//         {"add_rate_fin2", ""},
//         {"add_rate_third1", ""},
//         {"add_rate_third2", ""},
//         {"flag_on_mat_half", false},
//         {"flag_on_mat_final", false},
//     };
//     return jObj;
// }

Q_DECLARE_METATYPE(final_0)

#endif // MAIN_H
