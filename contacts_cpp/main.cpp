#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void menu();

void inquire();

void add();

void del();

void edit();

int main() {
    menu();
    return 0;
}

void inquire() {
    cout << "你选择了查询联系人" << endl;
    int choice1;
    cout << "请选择你要查询的依据" << endl;
    cout << "1.通过姓名查询" << endl;
    cout << "2.通过手机号查询" << endl;
    cout << "3.返回上层" << endl;
    cout << "请输入选项：";
    cin >> choice1;
    switch (choice1) {
        case 1: {
            sqlite3 *db;
            int ret = sqlite3_open("contacts.db", &db);
            if (ret != SQLITE_OK) {
                perror("sqlite3_open");
            }
            char name[20];
            char sql1[100];
            char *p = sql1;
            char *errmsg = NULL;
            char **table = NULL;
            int r = 0, c = 0;
            cout << "请输入需查询的姓名：";
            cin >> name;
            sprintf(p, "select* from persons where name = \'%s\';", name);
            sqlite3_get_table(db, p, &table, &r, &c, &errmsg);
            if (errmsg == NULL) {
                if (r != 0) {
                    cout << "查询成功！" << endl;
                    cout << "姓名：" << table[3] << endl;
                    cout << "电话号码：" << table[4] << endl;
                    cout << "地址：" << table[5] << endl;
                    menu();
                } else {
                    cout << "查无此人！" << endl;
                    menu();
                }
            }
            sqlite3_close(db);
            break;
        }
        case 2: {
            sqlite3 *db;
            int ret = sqlite3_open("contacts.db", &db);
            if (ret != SQLITE_OK) {
                perror("sqlite3_open");
            }
            char number[20];
            char sql1[100];
            char *p = sql1;
            char *errmsg = NULL;
            char **table = NULL;
            int r = 0, c = 0;
            cout << "请输入需查询的电话：";
            cin >> number;
            sprintf(p, "select* from persons where tel = \'%s\';", number);
            sqlite3_get_table(db, p, &table, &r, &c, &errmsg);
            if (errmsg == NULL) {
                if (r != 0) {
                    cout << "查询成功！" << endl;
                    cout << "姓名：" << table[3] << endl;
                    cout << "电话号码：" << table[4] << endl;
                    cout << "地址：" << table[5] << endl;
                    menu();
                } else {
                    cout << "查无此人！" << endl;
                    menu();
                }
            }
            sqlite3_close(db);
            break;
        }
        case 3: {
            menu();
            break;
        }
        default: {
            cout << "输入错误，请重新输入!" << endl;
            inquire();
            break;
        }
    }


}

void add() {
    cout << "你选择了新建联系人" << endl;
    sqlite3 *db;
    int ret = sqlite3_open("contacts.db", &db);
    if (ret != SQLITE_OK) {
        perror("sqlite3_open");
    }
    char sql1[100];
    char sql2[100];
    char *p1 = sql1;
    char *p2 = sql2;
    int choice;
    char name[100];
    char number[20];
    char address[100];
    char *errmsg = NULL;
    cout << "请输入姓名:";
    cin >> name;
    cout << "请输入电话号码:";
    cin >> number;
    cout << "请输入地址:";
    cin >> address;
    sprintf(p1, "select *from persons where tel = \'%s\';", number);
    char **table = NULL;
    int r = 0, c = 0;
    errmsg = NULL;
    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (errmsg == NULL) {
        if (r != 0) {
            cout << "电话号码重复，已录入的联系人为：" << table[3] << "，请重新录入！" << endl;
            add();
        } else {
            sprintf(p2, "insert into persons values (\'%s\',\'%s\',\'%s\');", name, number, address);
            sqlite3_exec(db, p2, NULL, NULL, &errmsg);
            sqlite3_close(db);
        }
    }
    cout << "是否继续添加(1.是 2.否)?";
    cin >> choice;
    if (choice == 1) {
        add();
    } else {
        main();
    }
}

void del() {
    cout << "你选择了删除联系人" << endl;
    sqlite3 *db;
    int ret = sqlite3_open("contacts.db", &db);
    if (ret != SQLITE_OK) {
        perror("sqlite3_open");
    }
    char name[20] = "";
    char sql1[100] = "";
    char *p1 = sql1;
    char *errmsg = NULL;
    char **table = NULL;
    int r = 0, c = 0;
    int choice;
    cout << "输入需要删除的联系人：";
    cin >> name;
    sprintf(sql1, "select* from persons where name = \'%s\';", name);
    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (r != 0) {
        cout << "查询到联系人：" << endl;
        cout << "姓名：" << table[3] << endl;
        cout << "电话号码：" << table[4] << endl;
        cout << "地址：" << table[5] << endl;
        cout << "确认删除(1.确认 2.取消)?";
        cin >> choice;
        if (choice == 1) {
            errmsg = NULL;
            if (r != 0) {
                char sql2[100];
                char *p2 = sql2;
                sprintf(p2, "delete from persons where name = \'%s\';", name);
                sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                sqlite3_get_table(db, p2, &table, &r, &c, &errmsg);
                if (r == 0) {
                    cout << "删除成功！";
                }
            }
        } else {
            cout << "未删除！" << endl;
        }
    } else{
        cout<<"查无此人！"<<endl;
    }
    sqlite3_close(db);
    menu();
}

void edit() {
    cout << "你选择了修改联系人" << endl;
    sqlite3 *db;
    char name[100];
    char sql1[100];
    char sql2[100];
    char *p1 = sql1;
    char *p2 = sql2;
    char *errmsg = NULL;
    char **table = NULL;
    int r = 0, c = 0;
    int choice1;
    int choice2;
    int ret = sqlite3_open("contacts.db", &db);
    if (ret != SQLITE_OK) {
        perror("sqlite3_open");
    }
    cout << "输入需要修改的联系人：";
    cin >> name;
    sprintf(p1, "select* from persons where name = \'%s\';", name);

    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (r != 0) {
        cout << "查询到联系人：" << endl;
        cout << "姓名：" << table[3] << endl;
        cout << "电话号码：" << table[4] << endl;
        cout << "地址：" << table[5] << endl;
        cout << "确认修改(1.确认 2.取消)?";
        cin >> choice1;
        if (choice1 == 1) {
            cout << "可以修改的项目：" << endl;
            cout << "1.姓名" << endl;
            cout << "2.电话号码" << endl;
            cout << "3.住址" << endl;
            cout << "请选择需要修改的项目：";
            cin >> choice2;
            switch (choice2) {
                case 1: {
                    char new_name[100];
                    cout << "请输入新姓名：";
                    cin >> new_name;
                    sprintf(p2, "update persons set name = \'%s\' where name = \'%s\'", new_name, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    cout << "修改成功！" << endl;
                    sqlite3_close(db);
                    menu();
                    break;
                }
                case 2: {
                    char new_number[100];
                    cout << "请输入新电话：";
                    cin >> new_number;
                    sprintf(p2, "update persons set tel = \'%s\' where name = \'%s\'", new_number, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    cout << "修改成功！" << endl;
                    sqlite3_close(db);
                    menu();
                    break;
                }
                case 3: {
                    char new_address[100];
                    cout << "请输入新地址：";
                    cin >> new_address;
                    sprintf(p2, "update persons set tel = \'%s\' where name = \'%s\'", new_address, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    cout << "修改成功！" << endl;
                    sqlite3_close(db);
                    menu();
                    break;
                }
                default: {
                    cout << "输入错误！" << endl;
                    sqlite3_close(db);
                    del();
                    break;
                }
            }
        } else {
            cout << "未修改！" << endl;
            menu();
        }
    } else {
        cout << "查无此人！" << endl;
        sqlite3_close(db);
        menu();
    }
}

void menu() {
    int choice;
    cout << "联系人管理系统" << endl;
    cout << "主菜单" << endl;
    cout << "1.查询联系人" << endl;
    cout << "2.新建联系人" << endl;
    cout << "3.删除联系人" << endl;
    cout << "4.修改联系人" << endl;
    cout << "0.退出" << endl;
    cout << "请选择功能：";
    cin >> choice;
    switch (choice) {
        case 1:
            inquire();
            break;
        case 2:
            add();
            break;
        case 3:
            del();
            break;
        case 4:
            edit();
            break;
        case 0:
            cout << "退出系统！" << endl;
            exit(0);
            break;
        default:
            cout << "输入错误，请重新输入!" << endl;
            main();
            break;
    }
}