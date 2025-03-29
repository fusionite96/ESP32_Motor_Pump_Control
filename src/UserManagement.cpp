#include "UserManagement.h"
#include "Variables.h"
#include <map>
std::map<String, User> users;
void initUserManagement() {
    if (users.empty()) {
        users[DEFAULT_ADMIN_USERNAME] = {DEFAULT_ADMIN_USERNAME, DEFAULT_ADMIN_PASSWORD, "admin"};
    }
}
bool validateUser(const String& username, const String& password) {
    return users.count(username) && users[username].password == password;
}
String getUserRole(const String& username) {
    return users.count(username) ? users[username].role : "none";
}
bool isAdmin(const String& username) {
    return getUserRole(username) == "admin";
}
bool changeUserRole(const String& admin, const String& targetUser, const String& newRole) {
    if (!isAdmin(admin)) return false;
    if (users.count(targetUser)) {
        users[targetUser].role = newRole;
        return true;
    }
    return false;
}
bool changePassword(const String& admin, const String& targetUser, const String& newPassword) {
    if (!isAdmin(admin)) return false;
    if (users.count(targetUser)) {
        users[targetUser].password = newPassword;
        return true;
    }
    return false;
}
std::vector<User> getAllUsers() {
    std::vector<User> list;
    for (const auto& pair : users) {
        list.push_back(pair.second);
    }
    return list;
}
