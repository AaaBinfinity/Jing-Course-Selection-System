#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

// 课程信息数据结构
struct Course {
    string courseID;       // 课程编号
    string courseName;     // 课程名称
    int credits;           // 课程学分
    int enrolledStudents;  // 课程已选人数
    int maxStudents;       // 课程人数上限

    Course(string id, string name, int credit, int max) 
        : courseID(id), courseName(name), credits(credit), enrolledStudents(0), maxStudents(max) {}
};

// 存储课程信息的向量
vector<Course> courses;

void displayMenu() {
    cout << "====== 学生选课系统 ======" << endl;
    cout << "1. 课程信息录入" << endl;
    cout << "2. 课程信息浏览" << endl;
    cout << "3. 课程信息添加" << endl;
    cout << "4. 课程信息删除" << endl;
    cout << "5. 学生登录" << endl;
    cout << "6. 学生浏览课程" << endl;
    cout << "7. 学生选课" << endl;
    cout << "8. 按学分查询课程" << endl;
    cout << "9. 按课程名称查询课程" << endl;
    cout << "0. 退出系统" << endl;
    cout << "请选择操作：";
}

void addCourse() {
    string id, name;
    int credit, max;
    cout << "输入课程编号: ";
    cin >> id;
    cout << "输入课程名称: ";
    cin >> name;
    cout << "输入课程学分: ";
    cin >> credit;
    cout << "输入课程人数上限: ";
    cin >> max;
    courses.push_back(Course(id, name, credit, max));
    cout << "课程信息录入成功！" << endl;
}

void viewCourses() {
    cout << "当前课程信息如下：" << endl;
    for (const auto& course : courses) {
        cout << "课程编号: " << course.courseID 
             << ", 课程名称: " << course.courseName 
             << ", 学分: " << course.credits 
             << ", 已选人数: " << course.enrolledStudents 
             << ", 人数上限: " << course.maxStudents << endl;
    }
}

void deleteCourse() {
    string id;
    cout << "输入要删除的课程编号: ";
    cin >> id;
    auto it = remove_if(courses.begin(), courses.end(), [id](Course& c) { return c.courseID == id; });
    if (it != courses.end()) {
        courses.erase(it, courses.end());
        cout << "课程删除成功！" << endl;
    } else {
        cout << "未找到该课程。" << endl;
    }
}

void searchCourseByCredits() {
    int credit;
    cout << "输入要查询的课程学分: ";
    cin >> credit;
    for (const auto& course : courses) {
        if (course.credits == credit) {
            cout << "课程编号: " << course.courseID 
                 << ", 课程名称: " << course.courseName 
                 << ", 学分: " << course.credits 
                 << ", 已选人数: " << course.enrolledStudents 
                 << ", 人数上限: " << course.maxStudents << endl;
        }
    }
}

void searchCourseByName() {
    string name;
    cout << "输入要查询的课程名称: ";
    cin >> name;
    for (const auto& course : courses) {
        if (course.courseName == name) {
            cout << "课程编号: " << course.courseID 
                 << ", 课程名称: " << course.courseName 
                 << ", 学分: " << course.credits 
                 << ", 已选人数: " << course.enrolledStudents 
                 << ", 人数上限: " << course.maxStudents << endl;
        }
    }
}

// 以下函数模拟学生的相关操作，例如登录和选课
void studentLogin() {
    cout << "学生登录成功。" << endl;
}

void studentViewCourses() {
    viewCourses();
}

void studentSelectCourse() {
    string id;
    cout << "输入要选修的课程编号: ";
    cin >> id;
    for (auto& course : courses) {
        if (course.courseID == id) {
            if (course.enrolledStudents < course.maxStudents) {
                course.enrolledStudents++;
                cout << "选课成功！" << endl;
            } else {
                cout << "该课程人数已满。" << endl;
            }
            return;
        }
    }
    cout << "未找到该课程。" << endl;
}

int main() {
    // 设置控制台输出为 UTF-8 编码
    SetConsoleOutputCP(CP_UTF8);
    
    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                addCourse();
                break;
            case 2:
                viewCourses();
                break;
            case 3:
                addCourse();
                break;
            case 4:
                deleteCourse();
                break;
            case 5:
                studentLogin();
                break;
            case 6:
                studentViewCourses();
                break;
            case 7:
                studentSelectCourse();
                break;
            case 8:
                searchCourseByCredits();
                break;
            case 9:
                searchCourseByName();
                break;
            case 0:
                cout << "退出系统。" << endl;
                return 0;
            default:
                cout << "无效选择，请重新输入。" << endl;
        }
    }
    return 0;
}
