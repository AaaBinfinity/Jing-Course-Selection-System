# Jing-Course-Selection-System

**主要内容：**使用c++开发一个简易的学生选课系统。

------

### 【数据结构】

课程信息数据：课程编号、课程名称、课程学分、课程已选人数、课程人数上限；

------

### 【系统实现功能】

**系统以菜单方式工作：**

（1）课程信息录入功能；

（2）课程信息浏览功能；

（3）课程信息的添加功能；

（4）课程信息的删除功能；

（5）学生的登录、浏览、选课功能等；

**查询功能：**

（1）按学分查询；

（2）按课程性质查询；

（3）学生选修课程等；

**功能扩展：**

按照自己对该系统的需求理解进行扩展。

例如

（1）权限处理；

（2）模糊查询；

（3）综合查询；

（4）统计功能等，并可以对文件中的信息进行读取与显示等。

------

任务要求 一、提交材料应包括：（1）系统源代码 （2）课程报告



------



# ABOUT CODE

## 概述

### 主函数 (main)

- `main`函数是程序的入口。它首先设置输出流为UTF-8编码，然后从文件中读取课程和用户信息。
- 主循环询问用户的登录类型：教师或学生。
  - 教师登录后，可以执行添加、删除和修改课程信息，添加和删除学生及教师，修改密码等操作。
  - 学生登录后，可以浏览课程、选课、退课和修改密码等操作。

### 菜单显示函数

- `displayTeacherMenu`：显示教师操作菜单。
- `displayStudentMenu`：显示学生操作菜单。

### 文件操作函数

- `readCoursesFromFile`：从文件读取课程信息。
- `writeCoursesToFile`：将课程信息写入文件。
- `readUsersFromFile`：从文件读取用户信息。
- `writeUsersToFile`：将用户信息写入文件。

### 用户管理函数

- `login`：用户登录验证。
- `registerUser`：用户注册。
- `addUser`：添加用户。
- `deleteUser`：删除用户。
- `changePassword`：修改用户密码。
- `teacherLogin`：教师登录验证。
- `studentLogin`：学生登录验证。

### 课程管理函数

- `displayCourses`：显示所有课程信息。
- `searchCoursesByName`：按课程名称搜索课程。
- `searchCoursesByCredits`：按学分搜索课程。
- `deleteCourse`：删除课程。
- `inputCourseInfo`：输入课程信息并添加到课程列表中。
- `addCourse`：添加课程。
- `selectCourse`：学生选课。
- `dropCourse`：学生退课。
- `modifyCourse`：修改课程信息。

## 课程管理系统介绍

这是一个用C++编写的课程管理系统，旨在帮助教师和学生管理和参与课程。系统提供了教师和学生两种用户类型，各自具有不同的操作权限和功能。以下是系统的详细介绍，包括主要功能、代码结构和使用示例。

### 主要功能

#### 教师功能

1. **课程信息录入**
   - 添加新的课程信息，包括课程编号、课程名称、课程学分、已选课学生数、课程人数上限及选课学生名单。

2. **课程信息浏览**
   - 查看所有课程的详细信息，包括课程编号、课程名称、课程学分、已选课学生数、课程人数上限及选课学生名单。

3. **课程信息删除**
   - 删除指定课程。

4. **修改密码**
   - 修改教师账户密码。

5. **添加学生**
   - 注册新的学生账户。

6. **删除学生**
   - 删除指定学生账户。

7. **添加教师**
   - 注册新的教师账户。

8. **删除教师**
   - 删除指定教师账户。

#### 学生功能

1. **课程信息浏览**
   - 查看所有课程的详细信息。

2. **选课**
   - 选择加入某个课程。

3. **退课**
   - 从已选的课程中退课。

4. **修改密码**
   - 修改学生账户密码。

## 代码结构

这段代码实现了一个简易的学生选课系统的主函数。它通过菜单方式工作，用户可以选择教师或学生身份登录，并执行相应的操作。以下是代码的详细解释：

## Main()主函数

### 1. 设置输出流为UTF-8编码
```cpp
cout.imbue(locale(locale(), new codecvt_utf8_utf16<wchar_t>));
```
这行代码设置了控制台输出流的编码格式为UTF-8，以支持在控制台上正确显示UTF-8编码的字符。

### 2. 从文件中读取数据
```cpp
vector<Course> courses = readCoursesFromFile("classes.txt");
vector<User> students = readUsersFromFile("students.txt");
vector<User> teachers = readUsersFromFile("teachers.txt");
```
这些代码行从文件中读取课程信息、学生信息和教师信息，存储在相应的向量中。

### 3. 主循环：用户选择登录类型
```cpp
while (true) {
    cout << "请选择登录类型：" << endl;
    cout << "1. 教师" << endl;
    cout << "2. 学生" << endl;
    cout << "3. 退出" << endl;
    int userType;
    cin >> userType;
```
主循环不断提示用户选择登录类型，直到用户选择退出（选项3）。

### 4. 教师登录及操作
```cpp
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
```
- 用户选择教师登录后，系统调用`teacherLogin`函数验证教师身份。
- 如果登录成功，系统显示教师菜单，教师可以选择以下操作：
  - 录入课程信息并保存到文件
  - 浏览课程信息
  - 删除课程信息并保存到文件
  - 修改密码
  - 添加学生信息并保存到文件
  - 删除学生信息并保存到文件
  - 添加教师信息并保存到文件
  - 删除教师信息并保存到文件
  - 退出教师菜单

### 5. 学生登录及操作
```cpp
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
                    cout << "请输入要选的课程编号: ";
                    cin >> courseId;
                    selectCourse(courses, username, courseId);
                    writeCoursesToFile(courses, "classes.txt");
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
```
- 用户选择学生登录后，系统调用`studentLogin`函数验证学生身份。
- 如果登录成功，系统显示学生菜单，学生可以选择以下操作：
  - 浏览课程信息
  - 选课并保存到文件
  - 退课并保存到文件
  - 修改密码
  - 退出学生菜单

### 6. 退出系统
```cpp
case 3:  // 退出系统
    cout << "退出系统" << endl;
    return 0;
default:
    cout << "无效的选择，请重新输入" << endl;
```
用户选择退出系统，程序终止运行。

### 总结
该主函数通过一个循环实现了教师和学生的登录及其相应的操作功能。系统通过从文件中读取数据并将修改后的数据写入文件，确保数据的持久性。教师和学生可以通过菜单进行相应的操作，实现课程管理和选课功能。

### 文件操作函数

1. ### **读取课程信息**

   ```
   cpp复制代码vector<Course> readCoursesFromFile(const string& filename) {
       vector<Course> courses;
       ifstream file(filename);
       if (file.is_open()) {
           Course course;
           string line;
           while (getline(file, line)) {
               istringstream iss(line);
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
   ```

   这段代码定义了一个从文件中读取课程信息的函数 `readCoursesFromFile`。它的工作过程如下：

   1. **初始化：** 定义一个 `vector` 容器 `courses` 用于存储课程信息。打开指定的文件 `filename`。
   2. **读取文件内容：**
      - 如果文件成功打开，逐行读取文件内容。
      - 每行内容存储在字符串 `line` 中，然后使用 `istringstream` 处理。
   3. **解析课程信息：**
      - 解析每行中的课程信息，包括课程ID、课程名称、课程学分、已注册学生人数和最大学生人数。
      - 清空 `enrolledStudentNames` 向量，然后逐个读取并存储注册学生的名字。
   4. **存储课程信息：** 将解析后的课程信息存入 `courses` 向量中。
   5. **关闭文件：** 读取完毕后关闭文件，返回 `courses` 向量。

   ### 2. **读取用户信息**

   ```
   cpp复制代码vector<User> readUsersFromFile(const string& filename) {
       vector<User> users;
       ifstream file(filename);
       if (file.is_open()) {
           User user;
           string line;
           while (getline(file, line)) {
               istringstream iss(line);
               iss >> user.username >> user.password;
               users.push_back(user);
           }
           file.close();
       }
       return users;
   }
   ```

   这段代码定义了一个从文件中读取用户信息的函数 `readUsersFromFile`。它的工作过程如下：

   1. **初始化：** 定义一个 `vector` 容器 `users` 用于存储用户信息。打开指定的文件 `filename`。
   2. **读取文件内容：**
      - 如果文件成功打开，逐行读取文件内容。
      - 每行内容存储在字符串 `line` 中，然后使用 `istringstream` 处理。
   3. **解析用户信息：**
      - 解析每行中的用户信息，包括用户名和密码。
   4. **存储用户信息：** 将解析后的用户信息存入 `users` 向量中。
   5. **关闭文件：** 读取完毕后关闭文件，返回 `users` 向量

   ### 3. **写入课程信息**
   
   ```
   cpp复制代码void writeCoursesToFile(const vector<Course>& courses, const string& filename) {
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
   ```
   
   这段代码定义了一个将课程信息写入文件的函数 `writeCoursesToFile`。它的工作过程如下：
   
   1. **初始化：** 创建一个输出文件流，并打开指定的文件 `filename`。
   2. **写入课程信息：**
      - 遍历传入的课程信息 `courses` 向量。
      - 将每个课程的课程ID、课程名称、课程学分、已注册学生人数和最大学生人数写入文件。
      - 如果课程有已注册学生，也将学生名字写入文件。
   3. **关闭文件：** 写入完毕后关闭文件。
   
   ### 4. **读取用户信息**
   
   ```
   cpp复制代码vector<User> readUsersFromFile(const string& filename) {
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
   ```
   
   这段代码定义了一个从文件中读取用户信息的函数 `readUsersFromFile`。它的工作过程如下：
   
   1. **初始化：** 创建一个输入文件流，并打开指定的文件 `filename`。
   2. 读取用户信息：
      - 通过文件流按行读取用户名和密码，并将其存储到 `users` 向量中。
      - 每行包含一个用户名和一个密码，读取完毕后将 `User` 对象添加到向量中。
   3. **关闭文件：** 读取完毕后关闭文件。
   
   ### 5. **写入用户信息**
   
   ```
   cpp复制代码void writeUsersToFile(const vector<User>& users, const string& filename) {
       ofstream file(filename);
       if (file.is_open()) {
           for (const auto& user : users) {
               file << user.username << " " << user.password << endl;
           }
           file.close();
       }
   }
   ```
   
   这段代码定义了一个将用户信息写入文件的函数 `writeUsersToFile`。它的工作过程如下：
   
   1. **初始化：** 创建一个输出文件流，并打开指定的文件 `filename`。
   2. 写入用户信息：
      - 遍历传入的用户信息 `users` 向量。
      - 将每个用户的用户名和密码写入文件，并在每行末尾添加换行符。
   3. **关闭文件：** 写入完毕后关闭文件。
   
   ### 用户管理函数
### **1，登录验证**

```
cpp复制代码bool login(const vector<User>& users, const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}
```

这段代码定义了一个用于验证用户登录的函数 `login`。它的工作过程如下：

1. **参数说明：** 接受一个用户信息的向量 `users`，以及要验证的用户名 `username` 和密码 `password`。
2. **遍历用户：** 遍历用户信息向量，逐个检查用户名和密码是否匹配传入的参数。
3. **匹配检查：** 如果找到匹配的用户名和密码，返回 `true`，表示登录成功；否则返回 `false`，表示登录失败。

### 2. **注册用户**

```
cpp复制代码void registerUser(vector<User>& users, const string& filename) {
    User user;
    cout << "请输入用户名: ";
    cin >> user.username;
    cout << "请输入密码: ";
    cin >> user.password;
    users.push_back(user);
    writeUsersToFile(users, filename);
    cout << "注册成功！" << endl;
}
```

这段代码定义了一个用户注册函数 `registerUser`。它的工作过程如下：

1. **输入信息：** 提示用户输入用户名和密码，并将其存储到一个新的 `User` 对象中。
2. **用户存储：** 将新创建的用户对象添加到用户信息向量 `users` 中。
3. **写入文件：** 调用 `writeUsersToFile` 函数将更新后的用户信息写入到文件中。
4. **反馈信息：** 输出注册成功的提示信息。

### **3.添加用户**

```
cpp复制代码void addUser(vector<User>& users, const string& filename) {
    registerUser(users, filename);
}
```

这段代码定义了一个添加用户的函数 `addUser`，它实际上是调用了之前定义的注册用户函数 `registerUser`，将新用户添加到用户信息向量中，并将更新后的用户信息写入文件。

### 4. **删除用户**

```
cpp复制代码void deleteUser(vector<User>& users, const string& filename, const string& username) {
    auto it = remove_if(users.begin(), users.end(), [&](const User& user) {
        return user.username == username;
    });
    users.erase(it, users.end());
    writeUsersToFile(users, filename);
    cout << "删除成功！" << endl;
}
```

这段代码定义了一个删除用户的函数 `deleteUser`，它根据输入的用户名 `username` 在用户信息向量中查找并删除对应的用户信息，并将更新后的用户信息写入文件。

### 5. **修改密码**

```
cpp复制代码void changePassword(vector<User>& users, const string& filename, const string& username) {
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
```

这段代码定义了一个修改用户密码的函数 `changePassword`，它首先根据输入的用户名 `username` 在用户信息向量中查找对应的用户，然后提示用户输入新密码，并将更新后的用户信息写入文件。

### 课程管理函数

1. **显示所有课程信息**
```cpp
void displayCourses(const vector<Course>& courses) {
    for (const auto& course : courses) {
        cout << "课程编号: " << course.courseId << " "
             << "课程名称: " << course.courseName << " "
             << "学分: " << course.courseCredits << " "
             << "已选课学生数: " << course.enrolledStudents << " "
             << "课程人数上限: " << course.maxStudents << " "
             << "选课学生名单: ";
        for (const auto& student : course.enrolledStudentNames) {
            cout << student << " ";
        }
        cout << endl;
    }
}
```

2. **按课程名称搜索课程**
```cpp
void searchCoursesByName(const vector<Course>& courses, const string& name) {
    for (const auto& course : courses) {
        if (course.courseName.find(name) != string::npos) {
            cout << "课程编号: " << course.courseId << " "
                 << "课程名称: " << course.courseName << " "
                 << "学分: " << course.courseCredits << " "
                 << "已选课学生数: " << course.enrolledStudents << " "
                 << "课程人数上限: " << course.maxStudents << " "
                 << "选课学生名单: ";
            for (const auto& student : course.enrolledStudentNames) {
                cout << student << " ";
            }
            cout << endl;
        }
    }
}
```

3. **按学分搜索课程**
```cpp
void searchCoursesByCredits(const vector<Course>& courses, int credits) {
    for (const auto& course : courses) {
        if (course.courseCredits == credits) {
            cout << "课程编号: " << course.courseId << " "
                 << "课程名称: " << course.courseName << " "
                 << "学分: " << course.courseCredits << " "
                 << "已选课学生数: " << course.enrolledStudents << " "
                 << "课程人数上限: " << course.maxStudents << " "
                 << "选课学生名单: ";
            for (const auto& student : course.enrolledStudentNames) {
                cout << student << " ";
            }
            cout << endl;
        }
    }
}
```

4. **删除课程**
```cpp
void deleteCourse(vector<Course>& courses, const string& courseId) {
    auto it = remove_if(courses.begin(), courses.end(), [&](const Course& course) {
        return course.courseId == courseId;
    });
    courses.erase(it, courses.end());
    cout << "课程删除成功！" << endl;
}
```

5. **输入课程信息并添加到课程列表中**
```cpp
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
    courses.push_back(course);
}
```

6. **选课**
```cpp
void selectCourse(vector<Course>& courses, const string& username, const string& courseId) {
    for (auto& course : courses) {
        if (course.courseId == courseId) {
            if (course.enrolledStudents < course.maxStudents) {
                course.enrolledStudentNames.push_back(username);
                course.enrolledStudents++;
                cout << "选课成功！" << endl;
            } else {
                cout << "课程人数已满，选课失败！" << endl;
            }
            return;
        }
    }
    cout << "课程不存在，选课失败！" << endl;
}
```

7. **退课**
```cpp
void dropCourse(vector<Course>& courses, const string& username, const string& courseId) {
    for (auto& course : courses) {
        if (course.courseId == courseId) {
            auto it = find(course.enrolledStudentNames.begin(), course.enrolledStudentNames.end(), username);
            if (it != course.enrolledStudentNames.end()) {
                course.enrolledStudentNames.erase(it);
                course.enrolledStudents--;
                cout << "退课成功！" << endl;
            } else {
                cout << "未选此课程，退课失败！" << endl;
            }
            return;
        }
    }
    cout << "课程不存在，退课失败！" << endl;
}
```

8. **修改课程信息**
```cpp
void modifyCourse(vector<Course>& courses, const string& courseId) {
    for (auto& course : courses) {
        if (course.courseId == courseId) {
            cout << "请输入新的课程名称: ";
            cin >> course.courseName;
            cout << "请输入新的课程学分: ";
            cin >> course.courseCredits;
            cout << "请输入新的课程人数上限: ";
            cin >> course.maxStudents;
            cout << "课程修改成功！" << endl;
            return;
        }
    }
    cout << "课程不存在，修改失败！" << endl;
}
```

## 使用示例

1. 启动程序后，系统将提示选择登录类型：

```plaintext
请选择登录类型：
1. 教师
2. 学生
3. 退出
```

2. 选择1进入教师登录：

```plaintext
请输入用户名: Bin
请输入密码: 123123
```

登录成功后显示教师菜单：

```plaintext
1. 课程信息录入
2. 课程信息浏览
3. 课程信息删除
4. 修改密码
5. 添加学生
6. 删除学生
7. 添加老师
8. 删除老师
9. 退出
```

3. 选择2进入学生登录：

```plaintext
请输入用户名: student1
请输入密码: 123456
```

登录成功后显示学生菜单：

```plaintext
1. 课程信息浏览
2. 选课
3. 退课
4. 修改密码
5. 退出
```

4. 选择3退出系统。



- [x] 祝你答辩顺利！
