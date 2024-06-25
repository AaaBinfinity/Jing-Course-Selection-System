#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <codecvt>
#include <locale>

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

// 将用户信息写入文件
void writeUsersToFile(const vector<User>& users, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.username << " " << user.password << endl;
        }
        file.close();
    }
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

// 用户注册
void registerUser(vector<User>& users, const string& filename) {
    User user;
    cout << "请输入用户名: ";
    cin >> user.username;
    cout << "请输入密码: ";
    cin >> user.password;
    users.push_back(user);
    writeUsersToFile(users, filename);
    cout << "注册成功！" << endl;
}

// 添加用户
void addUser(vector<User>& users, const string& filename) {
    registerUser(users, filename);
}

// 删除用户
void deleteUser(vector<User>& users, const string& filename, const string& username) {
    auto it = remove_if(users.begin(), users.end(), [&](const User& user) {
        return user.username == username;
    });
    users.erase(it, users.end());
    writeUsersToFile(users, filename);
    cout << "删除成功！" << endl;
}

// 显示所有课程信息  
void displayCourses(const vector<Course>& courses) {  
    for (const auto& course : courses) {  
        cout << "课程编号: " << course.courseId << endl;  
        cout << "课程名称: " << course.courseName << endl;  
        cout << "课程学分: " << course.courseCredits << endl;  
        cout << "已选课学生数: " << course.enrolledStudents << endl;  
        cout << "课程人数上限: " << course.maxStudents << endl;  
        cout << "选课学生名单: ";  
        for (const auto& student : course.enrolledStudentNames) {  
            cout << student << " ";  
        }  
        cout << endl << endl;  
    }  
}  
void searchCoursesByName(const vector<Course>& courses, const string& name) {  
    cout << "课程名称为 " << name << " 的课程列表：" << endl;  
    for (const auto& course : courses) {  
        if (course.courseName == name) {  
            cout << "课程编号: " << course.courseId << ", 学分: " << course.courseCredits << endl;  
        }  
    }  
}
void searchCoursesByCredits(const vector<Course>& courses, int credits) {  
    cout << "学分为 " << credits << " 的课程列表：" << endl;  
    for (const auto& course : courses) {  
        if (course.courseCredits == credits) {  
            cout << "课程编号: " << course.courseId << ", 课程名称: " << course.courseName << endl;  
        }  
    }  
}
void deleteCourse(vector<Course>& courses, const string& courseId) {  
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {  
        return c.courseId == courseId;  
    });  
    if (it != courses.end()) {  
        courses.erase(it);  
        cout << "课程删除成功！" << endl;  
    } else {  
        cout << "课程编号不存在，删除失败！" << endl;  
    }  
}

void selectCourse(vector<Course>& courses, const string& studentName, const string& courseId) {  
    // 查找课程  
    auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) {  
        return c.courseId == courseId;  
    });  
  
    if (courseIt != courses.end()) { // 如果找到了课程  
        // 检查课程是否已满  
        if (courseIt->enrolledStudents >= courseIt->maxStudents) {  
            cout << "课程已满，无法选课！" << endl;  
        } else {  
            // 将学生添加到课程的学生列表中  
            courseIt->enrolledStudentNames.push_back(studentName);  
            courseIt->enrolledStudents++;  
            cout << "选课成功！" << endl;  
        }  
    } else { // 如果没有找到课程  
        cout << "课程编号不存在，无法选课！" << endl;  
    }  
}
// 输入课程信息并添加到课程列表中  
void inputCourseInfo(vector<Course>& courses) {  
    Course course;  
    cout << "请输入课程编号: ";  
    cin >> course.courseId;  
    cout << "请输入课程名称: ";  
    cin >> course.courseName;  
    cout << "请输入课程学分: ";  
    cin >> course.courseCredits;  
    cout << "请输入已选课学生数: ";  
    cin >> course.enrolledStudents;  
    cout << "请输入课程人数上限: ";  
    cin >> course.maxStudents;  
      
    // 直接输入选课学生名单，用空格分隔  
    string studentNames;  
    cout << "请输入选课学生名单（用空格分隔）: ";  
    cin.ignore(); // 清除输入缓冲区中的换行符  
    getline(cin, studentNames);  
    istringstream iss(studentNames);  
    string studentName;  
    while (iss >> studentName) {  
        course.enrolledStudentNames.push_back(studentName);  
    }  
      
    courses.push_back(course);  
}  
void addCourse(vector<Course>& courses) {
    inputCourseInfo(courses);
} 
// 其他函数如addCourse、deleteCourse等需要类似地实现  
// ...

// 修改密码
void changePassword(vector<User>& users, const string& filename, const string& username) {
    for (auto& user : users) {
        if (user.username == username) {
            cout << "请输入新密码: ";
            cin >> user.password;
            writeUsersToFile(users, filename);
            cout << "密码修改成功！" << endl;
            return;
        }
    }
    cout << "用户不存在！" << endl;
}

// 学生退课
void dropCourse(vector<Course>& courses, const string& studentName, const string& courseId) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& course) {
        return course.courseId == courseId;
    });
    if (it != courses.end()) {
        auto studentIt = find(it->enrolledStudentNames.begin(), it->enrolledStudentNames.end(), studentName);
        if (studentIt != it->enrolledStudentNames.end()) {
            it->enrolledStudentNames.erase(studentIt);
            it->enrolledStudents--;
            cout << "退课成功！" << endl;
        } else {
            cout << "未找到学生，退课失败！" << endl;
        }
    } else {
        cout << "课程编号不存在，退课失败！" << endl;
    }
}

// 修改课程信息
void modifyCourse(vector<Course>& courses, const string& courseId) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& course) {
        return course.courseId == courseId;
    });
    if (it != courses.end()) {
        cout << "请输入新的课程名称: ";
        cin >> it->courseName;
        cout << "请输入新的课程学分: ";
        cin >> it->courseCredits;
        cout << "请输入新的课程人数上限: ";
        cin >> it->maxStudents;
        cout << "课程信息修改成功！" << endl;
    } else {
        cout << "课程编号不存在，修改失败！" << endl;
    }
}
