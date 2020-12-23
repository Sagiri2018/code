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
    printf("��ѡ���˲�ѯ��ϵ��\n");
    int choice1;
    printf("��ѡ����Ҫ��ѯ������\n");
    printf("1.ͨ��������ѯ\n");
    printf("2.ͨ���ֻ��Ų�ѯ\n");
    printf("3.�����ϲ�\n");
    printf("������ѡ�");
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
            printf("���������ѯ��������");
            scanf("%s", name);
            sprintf(p, "select* from persons where name = \'%s\';", name);
            sqlite3_get_table(db, p, &table, &r, &c, &errmsg);
            if (errmsg == NULL) {
                if (r != 0) {
                    printf("��ѯ�ɹ���\n");
                    printf("������%s\n", table[3]);
                    printf("�绰���룺%s\n", table[4]);
                    printf("��ַ��%s\n", table[5]);
                    menu();
                } else {
                    printf("���޴��ˣ�\n");
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
            printf("���������ѯ�ĵ绰��");
            scanf("%s",number);
            sprintf(p, "select* from persons where tel = \'%s\';", number);
            sqlite3_get_table(db, p, &table, &r, &c, &errmsg);
            if (errmsg == NULL) {
                if (r != 0) {
                    printf("��ѯ�ɹ���\n");
                    printf("������%s\n", table[3]);
                    printf("�绰���룺%s\n", table[4]);
                    printf("��ַ��%s\n", table[5]);
                    menu();
                } else {
                    printf("���޴��ˣ�\n");
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
            printf("�����������������!\n");
            inquire();
            break;
        }
    }


}

void add() {
    printf("��ѡ�����½���ϵ��\n");
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
    printf("����������:");
    scanf("%s", name);
    printf("������绰����:");
    scanf("%s", number);
    printf("�������ַ:");
    scanf("%s", address);
    sprintf(p1, "select *from persons where tel = \'%s\';", number);
    char **table = NULL;
    int r = 0, c = 0;
    errmsg = NULL;
    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (errmsg == NULL) {
        if (r != 0) {
            printf("�绰�����ظ�����¼�����ϵ��Ϊ��%s��������¼�룡\n", table[4]);
            add();
        } else {
            sprintf(p2, "insert into persons values (\'%s\',\'%s\',\'%s\');", name, number, address);
            sqlite3_exec(db, p2, NULL, NULL, &errmsg);
            sqlite3_close(db);
        }
    }
    printf("�Ƿ�������(1.�� 2.��)?");
    scanf("%d", &choice);
    if (choice == 1) {
        add();
    } else {
        main();
    }
}

void del() {
    printf("��ѡ����ɾ����ϵ��");
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
    printf("������Ҫɾ������ϵ�ˣ�");
    scanf("%s",name);
    sprintf(sql1, "select* from persons where name = \'%s\';", name);
    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (r != 0) {
        printf("��ѯ����ϵ�ˣ�\n");
        printf("������%s\n", table[3]);
        printf("�绰���룺%s\n", table[4]);
        printf("��ַ��%s\n", table[5]);
        printf("ȷ��ɾ��(1.ȷ�� 2.ȡ��)?");
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
                    printf("ɾ���ɹ���\n");
                }
            }
        } else {
            printf("δɾ����\n");
        }
    } else {
        printf("���޴��ˣ�\n");
    }
    sqlite3_close(db);
    menu();
}

void edit() {
    printf("��ѡ�����޸���ϵ��\n");
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
    printf("������Ҫ�޸ĵ���ϵ�ˣ�");
    scanf("%s",name);
    sprintf(p1, "select* from persons where name = \'%s\';", name);

    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (r != 0) {
        printf("��ѯ����ϵ�ˣ�\n");
        printf("������\n", table[3]);
        printf("�绰���룺\n", table[4]);
        printf("��ַ��\n", table[5]);
        printf("ȷ���޸�(1.ȷ�� 2.ȡ��)?");
        scanf("%d", &choice1);
        if (choice1 == 1) {
            printf("�����޸ĵ���Ŀ��\n");
            printf("1.����\n");
            printf("2.�绰����\n");
            printf("3.סַ\n");
            printf("��ѡ����Ҫ�޸ĵ���Ŀ��");
            scanf("%d", &choice2);
            switch (choice2) {
                case 1: {
                    char new_name[100];
                    printf("��������������");
                    scanf("%s", new_name);
                    sprintf(p2, "update persons set name = \'%s\' where name = \'%s\'", new_name, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    printf("�޸ĳɹ���\n");
                    sqlite3_close(db);
                    menu();
                    break;
                }
                case 2: {
                    char new_number[100];
                    printf("�������µ绰��");
                    scanf("%s", new_number);
                    sprintf(p2, "update persons set tel = \'%s\' where name = \'%s\'", new_number, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    printf("�޸ĳɹ���\n");
                    sqlite3_close(db);
                    menu();
                    break;
                }
                case 3: {
                    char new_address[100];
                    printf("�������µ�ַ��");
                    scanf("%s", new_address);
                    sprintf(p2, "update persons set tel = \'%s\' where name = \'%s\'", new_address, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    printf("�޸ĳɹ���\n");
                    sqlite3_close(db);
                    menu();
                    break;
                }
                default: {
                    printf("�������\n");
                    sqlite3_close(db);
                    del();
                    break;
                }
            }
        } else {
            printf("δ�޸ģ�\n");
            menu();
        }
    } else {
        printf("���޴��ˣ�\n");
        sqlite3_close(db);
        menu();
    }
}

void menu() {
    int choice;
    printf("��ϵ�˹���ϵͳ\n");
    printf("���˵�\n");
    printf("1.��ѯ��ϵ��\n");
    printf("2.�½���ϵ��\n");
    printf("3.ɾ����ϵ��\n");
    printf("4.�޸���ϵ��\n");
    printf("0.�˳�\n");
    printf("��ѡ���ܣ�");
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
            printf("�˳�ϵͳ��\n");
            exit(0);
            break;
        default:
            printf("�����������������!\n");
            main();
            break;
    }
}