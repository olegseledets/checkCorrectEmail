#include <iostream>
#include <vector>
#include <algorithm>

bool checkSymbol (char symbol, bool &right) {  
  if (!right) {
    return (symbol == '!' || (symbol >= '"' && symbol <= '\'') ||       
              symbol == '*' || (symbol >= '+' && symbol <= '9') ||
              symbol == '=' || (symbol >= '?' && symbol <= 'Z') || 
             (symbol >= '^' && symbol <= '~'));
  } else {
    return (symbol == '-' || symbol == '.' ||
        (symbol >= '0' && symbol <= '9') ||
        (symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z'));
  }
}

bool checkEmail (std::string &email) {
  bool correctEmail = true;
  bool right = false;  
  if (email[0] == '.' || email[email.size()-1] == '.')
    return false;
  int atCount = count(email.begin(), email.end(), '@'); // количество @
  if (atCount > 1 || atCount < 1)
    return false;
  int firstSideCounter = (email.substr(0, email.find("@"))).size(); //количество символов первой части
  int secondSideCounter = (email.substr(email.find("@") + 1)).size(); //количество символов второй части
  for (int i = 0; i < email.length(); ++i) {   
    if (checkSymbol(email[i], right)) {
      if(email[i] == '@')
        right = 1;
      if ((email[i] == '.' && email[i+1] == '.') || (email[i] == '.' && email[i+1] == '@') || (email[i] == '@' && email[i+1] == '.'))
        return false;     
      if (firstSideCounter > 64 || secondSideCounter > 63 || (firstSideCounter == 0) || (secondSideCounter == 0 ))
        return false;      
    } else
      return false;
  }
  return true;
}

void testEmail(std::vector <std::string> vecEmail){
  for (int i = 0; i < vecEmail.size(); ++i) {
    std::cout << (checkEmail(vecEmail[i]) ? "Yes" : "No") << std::endl;
  }
}

void test(){
  std::vector<std::string> testCorrectEmail = { "simple@example.com",
                                                "very.common@example.com",
                                                "disposable.style.email.with+symbol@example.com",
                                                "other.email-with-hyphen@example.com",
                                                "fully-qualified-domain@example.com",
                                                "user.name+tag+sorting@example.com",
                                                "x@example.com",
                                                "example-indeed@strange-example.com",
                                                "admin@mailserver1",
                                                "example@s.example",
                                                "mailhost!username@example.org",
                                                "user%example.com@example.org"
                                              };
  std::vector<std::string> testIncorrectEmail = { "John..Doe@example.com", 
                                                  "Abc.example.com",
                                                  "A@b@c@example.com",
                                                  "a\"b(c)d,e:f;g<h>i[j\\k]l@example.com",
                                                  "1234567890123456789012345678901234567890123456789012345678901234+x@example.com",
                                                  "i_like_underscore@but_its_not_allow_in _this_part.example.com"
                                                };
  std::cout << "Test correct email\n";
  testEmail(testCorrectEmail);
  std::cout << "\nTest incorrect email\n";
  testEmail(testIncorrectEmail);
}

int main() {
  //test();
  std::string email;
  getline(std::cin, email);
  std::cout << (checkEmail(email) ? "Yes" : "No") << std::endl;
}

/*
Напишите программу, которая проверяет корректность email-адреса, введённого пользователем.
Согласно международным требованиям, корректный email-адрес должен состоять из двух частей, разделённых знаком @. 
Первая часть должна иметь длину не менее одного и не более 64 символов, вторая часть — не менее одного и не более 63 символов. 
Из символов допускаются только английские буквы, цифры и знак «-» (дефис), а также точка. 
Точка не может быть первым или последним символом, а кроме того, две точки не могут идти подряд. 
В первой части (которая предшествует символу @), кроме вышеперечисленных, разрешены ещё следующие символы: ! # $ % & ' * + - / = ? ^ _ ` { | } ~
Пользователь вводит строку, задающую email-адрес. Программа должна вывести слово Yes, если адрес корректен, а в противном случае — слово No.
*/
