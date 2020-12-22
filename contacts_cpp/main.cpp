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
    cout << "��ѡ���˲�ѯ��ϵ��" << endl;
    int choice1;
    cout << "��ѡ����Ҫ��ѯ������" << endl;
    cout << "1.ͨ��������ѯ" << endl;
    cout << "2.ͨ���ֻ��Ų�ѯ" << endl;
    cout << "3.�����ϲ�" << endl;
    cout << "������ѡ�";
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
            cout << "���������ѯ��������";
            cin >> name;
            sprintf(p, "select* from persons where name = \'%s\';", name);
            sqlite3_get_table(db, p, &table, &r, &c, &errmsg);
            if (errmsg == NULL) {
                if (r != 0) {
                    cout << "��ѯ�ɹ���" << endl;
                    cout << "������" << table[3] << endl;
                    cout << "�绰���룺" << table[4] << endl;
                    cout << "��ַ��" << table[5] << endl;
                    menu();
                } else {
                    cout << "���޴��ˣ�" << endl;
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
            cout << "���������ѯ�ĵ绰��";
            cin >> number;
            sprintf(p, "select* from persons where tel = \'%s\';", number);
            sqlite3_get_table(db, p, &table, &r, &c, &errmsg);
            if (errmsg == NULL) {
                if (r != 0) {
                    cout << "��ѯ�ɹ���" << endl;
                    cout << "������" << table[3] << endl;
                    cout << "�绰���룺" << table[4] << endl;
                    cout << "��ַ��" << table[5] << endl;
                    menu();
                } else {
                    cout << "���޴��ˣ�" << endl;
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
            cout << "�����������������!" << endl;
            inquire();
            break;
        }
    }


}

void add() {
    cout << "��ѡ�����½���ϵ��" << endl;
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
    cout << "����������:";
    cin >> name;
    cout << "������绰����:";
    cin >> number;
    cout << "�������ַ:";
    cin >> address;
    sprintf(p1, "select *from persons where tel = \'%s\';", number);
    char **table = NULL;
    int r = 0, c = 0;
    errmsg = NULL;
    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (errmsg == NULL) {
        if (r != 0) {
            cout << "�绰�����ظ�����¼�����ϵ��Ϊ��" << table[3] << "��������¼�룡" << endl;
            add();
        } else {
            sprintf(p2, "insert into persons values (\'%s\',\'%s\',\'%s\');", name, number, address);
            sqlite3_exec(db, p2, NULL, NULL, &errmsg);
            sqlite3_close(db);
        }
    }
    cout << "�Ƿ��������(1.�� 2.��)?";
    cin >> choice;
    if (choice == 1) {
        add();
    } else {
        main();
    }
}

void del() {
    cout << "��ѡ����ɾ����ϵ��" << endl;
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
    cout << "������Ҫɾ������ϵ�ˣ�";
    cin >> name;
    sprintf(sql1, "select* from persons where name = \'%s\';", name);
    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (r != 0) {
        cout << "��ѯ����ϵ�ˣ�" << endl;
        cout << "������" << table[3] << endl;
        cout << "�绰���룺" << table[4] << endl;
        cout << "��ַ��" << table[5] << endl;
        cout << "ȷ��ɾ��(1.ȷ�� 2.ȡ��)?";
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
                    cout << "ɾ���ɹ���";
                }
            }
        } else {
            cout << "δɾ����" << endl;
        }
    } else{
        cout<<"���޴��ˣ�"<<endl;
    }
    sqlite3_close(db);
    menu();
}

void edit() {
    cout << "��ѡ�����޸���ϵ��" << endl;
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
    cout << "������Ҫ�޸ĵ���ϵ�ˣ�";
    cin >> name;
    sprintf(p1, "select* from persons where name = \'%s\';", name);

    sqlite3_get_table(db, p1, &table, &r, &c, &errmsg);
    if (r != 0) {
        cout << "��ѯ����ϵ�ˣ�" << endl;
        cout << "������" << table[3] << endl;
        cout << "�绰���룺" << table[4] << endl;
        cout << "��ַ��" << table[5] << endl;
        cout << "ȷ���޸�(1.ȷ�� 2.ȡ��)?";
        cin >> choice1;
        if (choice1 == 1) {
            cout << "�����޸ĵ���Ŀ��" << endl;
            cout << "1.����" << endl;
            cout << "2.�绰����" << endl;
            cout << "3.סַ" << endl;
            cout << "��ѡ����Ҫ�޸ĵ���Ŀ��";
            cin >> choice2;
            switch (choice2) {
                case 1: {
                    char new_name[100];
                    cout << "��������������";
                    cin >> new_name;
                    sprintf(p2, "update persons set name = \'%s\' where name = \'%s\'", new_name, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    cout << "�޸ĳɹ���" << endl;
                    sqlite3_close(db);
                    menu();
                    break;
                }
                case 2: {
                    char new_number[100];
                    cout << "�������µ绰��";
                    cin >> new_number;
                    sprintf(p2, "update persons set tel = \'%s\' where name = \'%s\'", new_number, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    cout << "�޸ĳɹ���" << endl;
                    sqlite3_close(db);
                    menu();
                    break;
                }
                case 3: {
                    char new_address[100];
                    cout << "�������µ�ַ��";
                    cin >> new_address;
                    sprintf(p2, "update persons set tel = \'%s\' where name = \'%s\'", new_address, name);
                    sqlite3_exec(db, p2, NULL, NULL, &errmsg);
                    cout << "�޸ĳɹ���" << endl;
                    sqlite3_close(db);
                    menu();
                    break;
                }
                default: {
                    cout << "�������" << endl;
                    sqlite3_close(db);
                    del();
                    break;
                }
            }
        } else {
            cout << "δ�޸ģ�" << endl;
            menu();
        }
    } else {
        cout << "���޴��ˣ�" << endl;
        sqlite3_close(db);
        menu();
    }
}

void menu() {
    int choice;
    cout << "��ϵ�˹���ϵͳ" << endl;
    cout << "���˵�" << endl;
    cout << "1.��ѯ��ϵ��" << endl;
    cout << "2.�½���ϵ��" << endl;
    cout << "3.ɾ����ϵ��" << endl;
    cout << "4.�޸���ϵ��" << endl;
    cout << "0.�˳�" << endl;
    cout << "��ѡ���ܣ�";
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
            cout << "�˳�ϵͳ��" << endl;
            exit(0);
            break;
        default:
            cout << "�����������������!" << endl;
            main();
            break;
    }
}