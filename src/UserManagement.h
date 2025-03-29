#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H
#include <Arduino.h>
#include <vector>
void initUserManagement();
bool validateUser(const String& username, const String& password);
String getUserRole(const String& username);
bool isAdmin(const String& username);
bool changeUserRole(const String& admin, const String& targetUser, const String& newRole);
bool changePassword(const String& admin, const String& targetUser, const String& newPassword);
struct User {
    String username;
    String password;
    String role;
};
std::vector<User> getAllUsers();
#endif
