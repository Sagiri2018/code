#include <stdio.h>
#include <stdlib.h>

#include "sqlite3.h"

void inquire();

void add();

void delete();

void edit();

void menu();

int main() {
    setbuf(stdout, NULL);
    menu();
    return 0;
}

void menu() {
    int choice;
    printf("主菜单\n1.查询联系人\n2.新建联系人\n3.删除联系人\n4.修改联系人\n0.退出\n请选择功能：");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            inquire();
            break;
        case 2:
            add();
            break;
        case 3:
            delete();
        case 4:
            edit();
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("输入错误，请重新输入！\n");
            main();
            break;
    }
}


void inquire() {
    printf("你选择了查询联系人\n");

}

void add() {
    printf("你选择了新建联系人\n");
    int choice;
    sqlite3 *db;
    int ret = sqlite3_open("contacts.db", &db);
    if (ret != SQLITE_OK) {
        perror("sqlite3_open");
    }
    char *sql1;
    char name[100];
    char number[20];
    char address[100];
    char *errmsg = NULL;
    printf("请输入姓名：");
    scanf("%s", name);
//    sprintf(sql1,"select name from persons where name = \'%s\';",name);
//    int ret1=sqlite3_exec(db,sql1,NULL,NULL,&errmsg);
//    if (ret1==1){
//        printf("数据库中已有此数据, 请重新添加！");
//        add();
//    }
    printf("请输入电话号码：");
    scanf("%s", number);
    printf("请输入地址：");
    scanf("%s", address);
    sprintf(sql1, "insert into persons values (\'%s\',\'%s\',\'%s\');", name, number, address);
    sqlite3_exec(db, sql1, NULL, NULL, &errmsg);
    sqlite3_close(db);
    printf("是否继续添加(1.是,2.否):");
    scanf("%d", &choice);
    if (choice == 1) {
        add();
    } else if (choice == 2) {
        main();
    } else {
        printf("输入错误，回到主菜单\n");
    }
}

void delete() {

}

void edit() {

}
