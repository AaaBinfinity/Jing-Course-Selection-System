#include <iostream>
#include <vector>
#include <locale>
#include <codecvt>
#include "course_selection_system.h"  

using namespace std;

void displayMenu() {
    cout << "1. 课程信息录入" << endl;
    cout << "2. 课程信息浏览" << endl;
    cout << "3. 课程信息删除" << endl;
    cout << "4. 学生登录" << endl;
    cout << "5. 按学分查询课程" << endl;
    cout << "6. 按课程名称查询课程" << endl;
    cout << "7. 添加学生" << endl;
    cout << "8. 删除学生" << endl;
    cout << "9. 添加老师" << endl;
    cout << "10. 删除老师" << endl;
    cout << "11. 修改密码" << endl;
    cout << "12. 退出" << endl;
}

bool teacherLogin(vector<User>& teachers) {
    cout << "请输入教师用户名: ";
    string username;
    cin >> username;
    cout << "请输入密码: ";
    string password;
    cin >> password;
    return login(teachers, username, password);
}

bool studentLogin(vector<User>& students) {
    cout << "请输入学生用户名: ";
    string username;
    cin >> username;
    cout << "请输入密码: ";
    string password;
    cin >> password;
    return login(students, username, password);
}

int main() {
    // 设置输出流为UTF-8编码
    cout.imbue(locale(locale(), new codecvt_utf8_utf16<wchar_t>));

    vector<Course> courses = readCoursesFromFile("classes.txt");
    vector<User> students = readUsersFromFile("students.txt");
    vector<User> teachers = readUsersFromFile("teachers.txt");

    string courseId;  // 移动变量定义到这里

    while (true) {
        cout << "请选择登录类型：" << endl;
        cout << "1. 教师" << endl;
        cout << "2. 学生" << endl;
        cout << "3. 退出" << endl;
        int userType;
        cin >> userType;

        switch (userType) {
            case 1: {  // 教师登录
                if (teacherLogin(teachers)) {
                    while (true) {
                        displayMenu();  // 显示菜单
                        int choice;
                        cin >> choice;
                        switch (choice) {
                            case 1:  // 课程信息录入
                                inputCourseInfo(courses);
                                writeCoursesToFile(courses, "classes.txt");
                                break;
                            case 2:  // 课程信息浏览
                                displayCourses(courses);
                                break;
                            case 3:  // 课程信息删除
                                cout << "请输入要删除的课程编号: ";
                                cin >> courseId;
                                deleteCourse(courses, courseId);
                                writeCoursesToFile(courses, "classes.txt");
                                break;
                            // 其他 case 分支...
                            default:
                                cout << "无效的选择，请重新输入" << endl;
                        }
                    }
                } else {
                    cout << "登录失败" << endl;
                }
                break;
            }
            case 2: {  // 学生登录
                if (studentLogin(students)) {
                    while (true) {
                        displayMenu();  // 显示菜单
                        int choice;
                        cin >> choice;
                        switch (choice) {
                            case 2:  // 课程信息浏览
                                displayCourses(courses);
                                break;
                            // 其他 case 分支...
                            default:
                                cout << "无效的选择，请重新输入" << endl;
                        }
                    }
                } else {
                    cout << "登录失败" << endl;
                }
                break;
            }
            case 3:  // 退出系统
                cout << "退出系统" << endl;
                return 0;
            default:
                cout << "无效的选择，请重新输入" << endl;
        }
    }

    return 0;
}
