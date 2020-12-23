#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

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
    printf("你选择了查询联系人\n");
    int choice1;
    printf("请选择你要查询的依据\n");
    printf("1.通过姓名查询\n");
    printf("2.通过手机号查询\n");
    printf("3.返回上层\n");
    printf("请输入选项：");
    scanf("%d", &choice1);
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
            printf("请输入需查询的姓名：");
            scanf("%s", name);
            sprintf(p, "select* from persons where name = \'%s\';", name);
            sqlite3_get_table(db, p, &table, &r, &c, &errmsg);
            if (errmsg == NULL) {
                if (r != 0) {
                    printf("查询成功！\n");
                    printf("姓名：%s\n", table[3]);
                    printf("电话号码：%s\n", table[4]);
                    printf("地址：%s\n", table[5]);
                    menu();
                } else {
                    printf("查无此人！\n");
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
            printf("请输入需查询的电话：");
            scanf("%s",number);
            sprintf(p, "select* from persons where tel = \'%s\';", number);
            sqlite3_get_table(db, p, &table, &r, &c, &errmsg);
            if (errmsg == NULL) {
                if (r != 0) {
                    printf("查询成功！\n");
                    printf("姓名：%s\n", table[3]);
                    printf("电话号码：%s\n", table[4]);
                    printf("地址：%s\n", table[5]);
                    menu();
                } else {
                    printf("查无此人！\n");
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
            printf("输入错误，请重新输入!\n");
            inquire();
            break;
        }
    }


}

void add() {
    printf("你选择了新建联系人\n");
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
    printf("请输入姓名:");
    scanf("%s", name);
    printf("请输入电话号码:");
    scanf("%s", number);
    printf("请输入地址:");
    scanf("%s", address);
    sprintf(p1, "select *from persons where tel = \'%s\';", number);
    char **table = NULL;
    int r = 0, c = 0;
    errmsg = NULL;
    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (errmsg == NULL) {
        if (r != 0) {
            printf("电话号码重复，已录入的联系人为：%s，请重新录入！\n", table[4]);
            add();
        } else {
            sprintf(p2, "insert into persons values (\'%s\',\'%s\',\'%s\');", name, number, address);
            sqlite3_exec(db, p2, NULL, NULL, &errmsg);
            sqlite3_close(db);
        }
    }
    printf("是否继续添加(1.是 2.否)?");
    scanf("%d", &choice);
    if (choice == 1) {
        add();
    } else {
        main();
    }
}

void del() {
    printf("你选择了删除联系人");
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
    printf("输入需要删除的联系人：");
    scanf("%s",name);
    sprintf(sql1, "select* from persons where name = \'%s\';", name);
    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (r != 0) {
        printf("查询到联系人：\n");
        printf("姓名：%s\n", table[3]);
        printf("电话号码：%s\n", table[4]);
        printf("地址：%s\n", table[5]);
        printf("确认删除(1.确认 2.取消)?");
        scanf("%d",&choice);
        if (choice == 1) {
            errmsg = NULL;
            if (r != 0) {
                char sql2[100];
                char *p2 = sql2;
                sprintf(p2, "delete from persons where name = \'%s\';", name);
                sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                sqlite3_get_table(db, p2, &table, &r, &c, &errmsg);
                if (r == 0) {
                    printf("删除成功！\n");
                }
            }
        } else {
            printf("未删除！\n");
        }
    } else {
        printf("查无此人！\n");
    }
    sqlite3_close(db);
    menu();
}

void edit() {
    printf("你选择了修改联系人\n");
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
    printf("输入需要修改的联系人：");
    scanf("%s",name);
    sprintf(p1, "select* from persons where name = \'%s\';", name);

    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (r != 0) {
        printf("查询到联系人：\n");
        printf("姓名：\n", table[3]);
        printf("电话号码：\n", table[4]);
        printf("地址：\n", table[5]);
        printf("确认修改(1.确认 2.取消)?");
        scanf("%d", &choice1);
        if (choice1 == 1) {
            printf("可以修改的项目：\n");
            printf("1.姓名\n");
            printf("2.电话号码\n");
            printf("3.住址\n");
            printf("请选择需要修改的项目：");
            scanf("%d", &choice2);
            switch (choice2) {
                case 1: {
                    char new_name[100];
                    printf("请输入新姓名：");
                    scanf("%s", new_name);
                    sprintf(p2, "update persons set name = \'%s\' where name = \'%s\'", new_name, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    printf("修改成功！\n");
                    sqlite3_close(db);
                    menu();
                    break;
                }
                case 2: {
                    char new_number[100];
                    printf("请输入新电话：");
                    scanf("%s", new_number);
                    sprintf(p2, "update persons set tel = \'%s\' where name = \'%s\'", new_number, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    printf("修改成功！\n");
                    sqlite3_close(db);
                    menu();
                    break;
                }
                case 3: {
                    char new_address[100];
                    printf("请输入新地址：");
                    scanf("%s", new_address);
                    sprintf(p2, "update persons set tel = \'%s\' where name = \'%s\'", new_address, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    printf("修改成功！\n");
                    sqlite3_close(db);
                    menu();
                    break;
                }
                default: {
                    printf("输入错误！\n");
                    sqlite3_close(db);
                    del();
                    break;
                }
            }
        } else {
            printf("未修改！\n");
            menu();
        }
    } else {
        printf("查无此人！\n");
        sqlite3_close(db);
        menu();
    }
}

void menu() {
    int choice;
    printf("联系人管理系统\n");
    printf("主菜单\n");
    printf("1.查询联系人\n");
    printf("2.新建联系人\n");
    printf("3.删除联系人\n");
    printf("4.修改联系人\n");
    printf("0.退出\n");
    printf("请选择功能：");
    scanf("%d",&choice);
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
            printf("退出系统！\n");
            exit(0);
            break;
        default:
            printf("输入错误，请重新输入!\n");
            main();
            break;
    }
}