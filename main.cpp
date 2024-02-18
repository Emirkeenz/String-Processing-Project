#include <iostream>
#include <regex>
using namespace std;

void encryptCaesar() {
  // encryption
  string msg;
  cout << "Message can only be alphabetic" << endl;
  cout << "Enter message: ";
  getline(cin, msg);
  cin.ignore();

  int key;
  cout << "Enter key (0-25): ";
  cin >> key;
  cin.ignore();

  string encryptedText = msg;

  for (int i = 0; i < msg.size(); i ++){
    if(msg[i]==32){
      continue; //32 is ASCII of space character, we will ignore it
    } else {
      if((msg[i]+key) > 122) {
        //after lowercase z move back to a, z's ASCII is 122
        int temp = (msg[i] + key) - 122;
        encryptedText[i] = 96 + temp;
      } else if (msg[i] + key > 90 && msg[i] <= 96){
        //after uppercase Z move back to A, 90 is Z's ASCII
        int temp = (msg[i] + key) - 90;
        encryptedText[i] = 64 + temp;
      } else {
        //in case of characters being in between A-Z & a-z
        encryptedText[i] += key;
      }
    }
  }

  cout << "Encrypted Message: " << encryptedText;
}

void decryptCaesar() {
  //decryption
  string encpMsg;
  cout << "Message can only be alphabetic" << endl;
  cout << "Enter encrypted text: ";
  getline(cin, encpMsg);
  cin.ignore();

  int dcyptKey;
  cout << "Enter key (0-25): ";
  cin >> dcyptKey;
  cin.ignore();

  string decryptedText = encpMsg;

  for (int i = 0; i < encpMsg.size(); i++){
    if(encpMsg[i]==32){
      continue; //ignoring space
    } else {
        if((encpMsg[i] - dcyptKey) < 97 && (encpMsg[i] - dcyptKey) > 90){
          int temp = (encpMsg[i] - dcyptKey) + 26;
          decryptedText[i] = temp;
        } else if((encpMsg[i] - dcyptKey) < 65){
          int temp = (encpMsg[i] - dcyptKey) + 26;
          decryptedText[i] = temp;
        } else {
          decryptedText[i] = encpMsg[i] - dcyptKey;
        }
    }
  }
  cout << "Decrypted Message: " << decryptedText << endl;
}

void railFenceEncryption(){
  string message;
  cout << "Enter message: ";
  getline(cin , message);
  cin.ignore();

  // removing white space from message
  message = regex_replace(message, regex("\\s+"), "");

  cout << "Enter key(number of rails): ";
  int rails;
  cin >> rails;

  // creating empty matrix
  char railMatrix[rails][message.length()];
  for (int i = 0; i < rails; i++){
    for (int j = 0; j < message.length(); j++){
      railMatrix[i][j] = '.';
    }
  }

  // testing newly created matrix
  // for (int i = 0; i < rails; i++){
  //   for (int j = 0; j < message.length(); j++){
  //     cout << railMatrix[i][j];
  //   }
  //   cout << endl;
  // }

  // putting message letters one by one in rail matrix in zig-zag
  int row = 0;
  int check = 0;
  for (int i = 0; i < message.length(); i++){
    if (check == 0){
      railMatrix[row][i] = message[i];
      row++;
      if(row == rails){
        check = 1;
        row--;
      }
    } else if (check == 1){
      row--;
      railMatrix[row][i] = message[i];
      if (row == 0){
        check = 0;
        row = 1;
      }
    }
  }

  // creating encrypted text
  string encrypText = "";
  for (int i = 0; i < rails; i++){
    for (int j = 0; j < message.length(); j++){
      //cout << railMatrix[i][j];
      encrypText += railMatrix[i][j];
    }
    //cout << endl;
  }

  // removing '.' from encrypted Text
  encrypText = regex_replace(encrypText, regex("\\."), "");
  cout << "Encrypted Text: " << encrypText;
}

void railFenceDecryption(){
  string message;
  cout << "Enter message: ";
  getline(cin , message);
  cin.ignore();
  
  // removing white space from message
  message = regex_replace(message, regex("\\s+"), "");

  cout << "Enter key(number of rails): ";
  int rails;
  cin >> rails;

  // creating empty matrix
  char railMatrix[rails][message.length()];
  for (int i = 0; i < rails; i++){
    for (int j = 0; j < message.length(); j++){
      railMatrix[i][j] = '.';
    }
  }

  // testing newly created matrix
  // for (int i = 0; i < rails; i++){
  //   for (int j = 0; j < message.length(); j++){
  //     cout << railMatrix[i][j];
  //   }
  //   cout << endl;
  // }

  // putting message letters one by one in rail matrix in zig-zag
  int row = 0;
  int check = 0;
  for (int i = 0; i < message.length(); i++){
    if (check == 0){
      railMatrix[row][i] = message[i];
      row++;
      if(row == rails){
        check = 1;
        row--;
      }
    } else if (check == 1){
        row--;
        railMatrix[row][i] = message[i];
        if (row == 0){
          check = 0;
          row = 1;
        }
    }
  }

  // reordering rails
  int ordr = 0;
  for (int i = 0; i < rails; i++){
    for (int j = 0; j < message.length(); j++){
      string temp = "";
      temp += railMatrix[i][j];
      if(regex_match(temp, regex("\\."))){
        // skipping '.'
        continue;
      } else {
        // adding cipher letters one by one diagonally
        railMatrix[i][j] = message[ordr];
        ordr++;
      }
    }
  }

  // testing reordering
  // for (int i = 0; i < rails; i++){
  //   for (int j = 0; j < message.length(); j++){
  //     cout << railMatrix[i][j];
  //   }
  //   cout << endl;
  // }

  // converting rows back into a message of single line
  string decrypText = "";
  check = 0;
  row = 0;
  for (int i = 0; i < message.length(); i++){
    if (check == 0){
      decrypText += railMatrix[row][i];
      row++;
      if (row == rails){
        check = 1;
        row--;
      }
    } else if (check == 1){
      row--;
      decrypText += railMatrix[row][i];
      if (row == 0){
        check = 0;
        row = 1;
      }
    }
  }

  // removing '.' from decrypted text
  decrypText = regex_replace(decrypText, regex("\\.+"), "");
  cout << "Decrypted Text: " << decrypText;
}

int main()
{
  bool continueProgram = true;
  while (continueProgram) {
    int choice;
    cout << "1. Encryption" << endl << "2. Decryption" << endl << "Enter choice(1,2): ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
      int choiceMethod;
      cout << endl << "Choose encryption method" << endl << "1. Caesar " << "2. rail-fence" << endl << "Enter choice(1,2): ";
      cin >> choiceMethod;
      cin.ignore();
      if (choiceMethod == 1) {
        encryptCaesar();
      } else if (choiceMethod == 2) {
        railFenceEncryption();
      } else {
        cerr << "Error: you have chosen wrong method";
      }
    } else if (choice == 2) {
      int choiceMethod;
      cout << endl << "Choose decryption method" << endl << "1. Caesar " << "2. rail-fence" << endl << "Enter choice(1,2): ";
      cin >> choiceMethod;
      cin.ignore();

      if (choiceMethod == 1) {
        decryptCaesar();
      } else if (choiceMethod == 2) {
        railFenceDecryption();
      } else {
        cerr << "Error: you have chosen wrong method";
      }
    } else {
      cout << "Invalid choice";
    }

    // Asking if the user wants to continue
    char continueChoice;
    cout << endl << "Do you want to continue? (Y/N): ";
    cin >> continueChoice;
    if (continueChoice != 'Y' && continueChoice != 'y') {
      continueProgram = false; // Set to false to exit the loop
    }
  }
  return 0;
}