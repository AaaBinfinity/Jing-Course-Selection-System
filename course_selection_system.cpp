#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream> // 添加这个头文件

using namespace std;

// 定义课程信息结构体
struct Course {
    string courseId;
    string courseName;
    int courseCredits;
    int enrolledStudents;
    int maxStudents;
    vector<string> enrolledStudentNames;  // 选课学生用户名列表
};

// 定义用户信息结构体
struct User {
    string username;
    string password;
};

// 从文件读取课程信息
vector<Course> readCoursesFromFile(const string& filename) {
    vector<Course> courses;
    ifstream file(filename);
    if (file.is_open()) {
        Course course;
        string line;
        while (getline(file, line)) {
            istringstream iss(line); // 使用istringstream解析每一行
            iss >> course.courseId >> course.courseName >> course.courseCredits
                >> course.enrolledStudents >> course.maxStudents;
            string studentName;
            course.enrolledStudentNames.clear();
            while (iss >> studentName) {
                course.enrolledStudentNames.push_back(studentName);
            }
            courses.push_back(course);
        }
        file.close();
    }
    return courses;
}

// 将课程信息写入文件
void writeCoursesToFile(const vector<Course>& courses, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& course : courses) {
            file << course.courseId << " " << course.courseName << " "
                 << course.courseCredits << " " << course.enrolledStudents << " "
                 << course.maxStudents;
            for (const auto& student : course.enrolledStudentNames) {
                file << " " << student;
            }
            file << endl;
        }
        file.close();
    }
}

// 从文件读取用户信息
vector<User> readUsersFromFile(const string& filename) {
    vector<User> users;
    ifstream file(filename);
    if (file.is_open()) {
        User user;
        while (file >> user.username >> user.password) {
            users.push_back(user);
        }
        file.close();
    }
    return users;
}

// 用户登录验证
bool login(const vector<User>& users, const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

// 显示菜单
void displayMenu() {
    cout << "====== 学生选课系统 ======" << endl;
    cout << "1. 课程信息录入" << endl;
    cout << "2. 课程信息浏览" << endl;
    cout << "3. 课程信息添加" << endl;
    cout << "4. 课程信息删除" << endl;
    cout << "5. 学生登录" << endl;
    cout << "6. 退出" << endl;
}

// 课程信息录入
void inputCourseInfo(vector<Course>& courses) {
    cout << "====== 课程信息录入 ======" << endl;
    Course course;
    cout << "请输入课程编号: ";
    cin >> course.courseId;
    cout << "请输入课程名称: ";
    cin >> course.courseName;
    cout << "请输入课程学分: ";
    cin >> course.courseCredits;
    cout << "请输入课程已选人数: ";
    cin >> course.enrolledStudents;
    cout << "请输入课程人数上限: ";
    cin >> course.maxStudents;
    courses.push_back(course);
}

// 课程信息浏览
void displayCourses(const vector<Course>& courses) {
    for (const auto& course : courses) {
        cout << "====== 课程信息浏览 ======" << endl;
        cout << "课程编号: " << course.courseId
             << ", 课程名称: " << course.courseName
             << ", 课程学分: " << course.courseCredits
             << ", 已选人数: " << course.enrolledStudents
             << ", 人数上限: " << course.maxStudents
             << ", 选课学生: ";
        for (const auto& student : course.enrolledStudentNames) {
            cout << student << " ";
        }
        cout << endl;
    }
}

// 课程信息添加
void addCourse(vector<Course>& courses) {
    inputCourseInfo(courses);
}

// 课程信息删除
void deleteCourse(vector<Course>& courses, const string& courseId) {
    auto it = remove_if(courses.begin(), courses.end(), [&](const Course& course) {
        return course.courseId == courseId;
    });
    courses.erase(it, courses.end());
}

// 学生选课
void selectCourse(vector<Course>& courses, const string& studentName) {
    cout << "可选课程列表：" << endl;
    displayCourses(courses);

    cout << "请输入课程编号以选择课程: ";
    string courseId;
    cin >> courseId;
    
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& course) {
        return course.courseId == courseId;
    });

    if (it != courses.end()) {
        if (it->enrolledStudents < it->maxStudents) {
            it->enrolledStudentNames.push_back(studentName);
            it->enrolledStudents++;
            cout << "选课成功！" << endl;
        } else {
            cout << "课程人数已满，选课失败！" << endl;
        }
    } else {
        cout << "课程编号不存在，选课失败！" << endl;
    }
}

int main() {
    vector<Course> courses = readCoursesFromFile("classes.txt");
    vector<User> students = readUsersFromFile("students.txt");
    vector<User> teachers = readUsersFromFile("teachers.txt");

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "请输入教师用户名: ";
                string username;
                cin >> username;
                cout << "请输入密码: ";
                string password;
                cin >> password;
                if (login(teachers, username, password)) {
                    inputCourseInfo(courses);
                    writeCoursesToFile(courses, "classes.txt");
                } else {
                    cout << "登录失败" << endl;
                }
                break;
            }
            case 2:
                displayCourses(courses);
                break;
            case 3: {
                cout << "请输入教师用户名: ";
                string username;
                cin >> username;
                cout << "请输入密码: ";
                string password;
                cin >> password;
                if (login(teachers, username, password)) {
                    addCourse(courses);
                    writeCoursesToFile(courses, "classes.txt");
                } else {
                    cout << "登录失败" << endl;
                }
                break;
            }
            case 4: {
                cout << "请输入教师用户名: ";
                string username;
                cin >> username;
                cout << "请输入密码: ";
                string password;
                cin >> password;
                if (login(teachers, username, password)) {
                    cout << "请输入要删除的课程编号: ";
                    string courseId;
                    cin >> courseId;
                    deleteCourse(courses, courseId);
                    writeCoursesToFile(courses, "classes.txt");
                } else {
                    cout << "登录失败" << endl;
                }
                break;
            }
            case 5: {
                cout << "请输入学生用户名: ";
                string username;
                cin >> username;
                cout << "请输入密码: ";
                string password;
                cin >> password;
                if (login(students, username, password)) {
                    cout << "学生登录成功，可以选择课程" << endl;
                    selectCourse(courses, username);
                    writeCoursesToFile(courses, "classes.txt");
                } else {
                    cout << "登录失败" << endl;
                }
                break;
            }
            case 6:
                return 0;
            default:
                cout << "无效的选择，请重新输入" << endl;
                break;
        }
    }
    return 0;
}
