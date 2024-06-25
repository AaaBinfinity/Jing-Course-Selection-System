#include <iostream>
#include <vector>
#include <locale>
#include <codecvt>
#include "course_selection_system.h"  // 请替换为你的课程函数头文件和相关函数的实现

using namespace std;

void displayTeacherMenu() {
    cout << "1. 课程信息录入" << endl;
    cout << "2. 课程信息浏览" << endl;
    cout << "3. 课程信息删除" << endl;
    cout << "4. 修改密码" << endl;
    cout << "5. 添加学生" << endl;
    cout << "6. 删除学生" << endl;
    cout << "7. 添加老师" << endl;
    cout << "8. 删除老师" << endl;
    cout << "9. 退出" << endl;
}

void displayStudentMenu() {
    cout << "1. 课程信息浏览" << endl;
    cout << "2. 选课" << endl;
    cout << "3. 退课" << endl;
    cout << "4. 修改密码" << endl;
    cout << "5. 退出" << endl;
}

int main() {
    // 设置输出流为UTF-8编码
    cout.imbue(locale(locale(), new codecvt_utf8_utf16<wchar_t>));

    vector<Course> courses = readCoursesFromFile("classes.txt");
    vector<User> students = readUsersFromFile("students.txt");
    vector<User> teachers = readUsersFromFile("teachers.txt");

    string username; // 将变量声明移到switch之前
    string courseId; // 将变量声明移到switch之前
    string studentUsername; // 将变量声明移到switch之前
    string teacherUsername; // 将变量声明移到switch之前

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
                        displayTeacherMenu();  // 显示教师菜单
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
                            case 4:  // 修改密码
                                cout << "请输入用户名: ";
                                cin >> username;
                                changePassword(teachers, "teachers.txt", username);
                                break;
                            case 5:  // 添加学生
                                addUser(students, "students.txt");
                                break;
                            case 6:  // 删除学生
                                cout << "请输入要删除的学生用户名: ";
                                cin >> studentUsername;
                                deleteUser(students, "students.txt", studentUsername);
                                break;
                            case 7:  // 添加老师
                                addUser(teachers, "teachers.txt");
                                break;
                            case 8:  // 删除老师
                                cout << "请输入要删除的教师用户名: ";
                                cin >> teacherUsername;
                                deleteUser(teachers, "teachers.txt", teacherUsername);
                                break;
                            case 9:  // 退出
                                cout << "退出教师菜单" << endl;
                                return 0;
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
                        displayStudentMenu();  // 显示学生菜单
                        int choice;
                        cin >> choice;
                        switch (choice) {
                            case 1:  // 课程信息浏览
                                displayCourses(courses);
                                break;
                            case 2:  // 选课
                                cout << "实现选课功能" << endl; // 实现选课功能
                                break;
                            case 3:  // 退课
                                cout << "请输入要退的课程编号: ";
                                cin >> courseId;
                                dropCourse(courses, username, courseId);
                                writeCoursesToFile(courses, "classes.txt");
                                break;
                            case 4:  // 修改密码
                                cout << "请输入用户名: ";
                                cin >> username;
                                changePassword(students, "students.txt", username);
                                break;
                            case 5:  // 退出
                                cout << "退出学生菜单" << endl;
                                return 0;
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